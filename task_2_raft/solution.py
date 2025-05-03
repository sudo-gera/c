import ipaddress
import common
import asyncio
import sys
import time
import psutil
import traceback
import logging
import typing
import dataclasses

''' # converted from https://ongardie.net/static/raft/userstudy/raft.pdf by ChatGPT
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                         Raft Protocol Summary                                                                                  |
+------------------------------------------------------------------------------------------------+---------------------------------------------------------------+
| Followers                                                                                      | RequestVote RPC                                               |
|------------------------------------------------------------------------------------------------|---------------------------------------------------------------|
| • Respond to RPCs from candidates and leaders.                                                 | Invoked by candidates to gather votes.                        |
| • Convert to candidate if election timeout elapses without either:                             |                                                               |
|   – Receiving valid AppendEntries RPC, or                                                      | Arguments:                                                    |
|   – Granting vote to candidate                                                                 |   candidateId      candidate requesting vote                  |
|------------------------------------------------------------------------------------------------|   term             candidate's term                           |
| Candidates                                                                                     |   lastLogIndex     index of candidate's last log entry        |
|------------------------------------------------------------------------------------------------|   lastLogTerm      term of candidate's last log entry         |
| • Increment currentTerm, vote for self                                                         |                                                               |
| • Reset election timeout                                                                       | Results:                                                      |
| • Send RequestVote RPCs to all other servers, wait for either:                                 |   term             currentTerm, for candidate to update itself|
|   – Votes received from majority of servers: become leader                                     |   voteGranted      true means candidate received vote         |
|   – AppendEntries RPC received from new leader: step down                                      |                                                               |
|   – Election timeout elapses without resolution: increment term, start new election            | Implementation:                                               |
|   – Discover higher term: step down                                                            | 1. If term > currentTerm, currentTerm ← term (step down if    |
|------------------------------------------------------------------------------------------------|    leader or candidate)                                       |
| Leaders                                                                                        | 2. If term == currentTerm, votedFor is null or candidateId,   |
|------------------------------------------------------------------------------------------------|    and candidate's log is at least as complete as local log,  |
| • Initialize nextIndex for each to last log index + 1                                          |    grant vote and reset election timeout                      |
| • Send initial empty AppendEntries RPCs (heartbeat) to each follower;                          |                                                               |
|   repeat during idle periods to prevent election timeouts                                      |                                                               |
| • Accept commands from clients, append new entries to local log                                |                                                               |
| • Whenever last log index ≥ nextIndex for a follower, send AppendEntries RPC with log entries  |                                                               |
|   starting at nextIndex, update nextIndex if successful                                        |                                                               |
| • If AppendEntries fails because of log inconsistency, decrement nextIndex and retry           |                                                               |
| • Mark log entries committed if stored on a majority of servers and at least one entry from    |                                                               |
|   current term is stored on a majority of servers                                              |                                                               |
| • Step down if currentTerm changes                                                             |                                                               |
|------------------------------------------------------------------------------------------------|---------------------------------------------------------------|
| Persistent State                                                                               | AppendEntries RPC                                             |
|------------------------------------------------------------------------------------------------|---------------------------------------------------------------|
| Each server persists the following to stable storage synchronously before responding to RPCs:  | Invoked by leader to replicate log entries and discover       |
|   currentTerm   latest term server has seen (initialized to 0 on first boot)                   | inconsistencies; also used as heartbeat.                      |
|   votedFor      candidateId that received vote in current term (or null if none)               |                                                               |
|   log[]         log entries                                                                    | Arguments:                                                    |
|------------------------------------------------------------------------------------------------|   term             leader's term                              |
| Log Entry                                                                                      |   leaderId         so follower can redirect clients           |
|------------------------------------------------------------------------------------------------|   prevLogIndex     index of log entry immediately preceding   |
|   term    term when entry was received by leader                                               |   prevLogTerm      term of prevLogIndex entry                 |
|   index   position of entry in the log                                                         |   entries[]        log entries to store (empty for heartbeat) |
|   command command for state machine                                                            |   commitIndex      last entry known to be committed           |
|                                                                                                |                                                               |
|                                                                                                | Results:                                                      |
|                                                                                                |   term      currentTerm, for leader to update itself          |
|                                                                                                |   success   true if follower contained entry matching         |
|                                                                                                |             prevLogIndex and prevLogTerm                      |
|                                                                                                |                                                               |
|                                                                                                | Implementation:                                               |
|                                                                                                | 1. Return if term < currentTerm                               |
|                                                                                                | 2. If term > currentTerm, currentTerm ← term                  |
|                                                                                                | 3. If candidate or leader, step down                          |
|                                                                                                | 4. Reset election timeout                                     |
|                                                                                                | 5. Return failure if log doesn't contain an entry at          |
|                                                                                                |    prevLogIndex whose term matches prevLogTerm                |
|                                                                                                | 6. If existing entries conflict with new entries, delete all  |
|                                                                                                |    existing entries starting with first conflicting entry     |
|                                                                                                | 7. Append any new entries not already in the log              |
|                                                                                                | 8. Advance state machine with newly committed entries         |
+------------------------------------------------------------------------------------------------+---------------------------------------------------------------+
'''

##############################################################################################################################################

hosts = sys.argv[1:]
hosts.sort()
my_ip = common.select_my_ip(hosts)
other_hosts = {*hosts} - {my_ip}
consensus_size = min([
    q
    for q in range(len(hosts)+4)
    if q*2 > len(hosts)
])

##############################################################################################################################################

colors = [
    '\x1b[90m',
    '\x1b[91m',
    '\x1b[92m',
    '\x1b[93m',
    '\x1b[94m',
    '\x1b[95m',
    '\x1b[96m',
    '\x1b[97m',
]
my_color = colors[hosts.index(my_ip)]
clear_color = '\x1b[0m'

##############################################################################################################################################

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='[ %(asctime)s ]: %(message)s' + clear_color)

class log_stream:
    def __init__(self, logger_func: typing.Callable[[str], None]):
        self.logger_func = logger_func
        self.buffer = ''
    def write(self, data: str) -> None:
        self.buffer += data
        while '\n' in self.buffer:
            data, self.buffer = self.buffer.split('\n', 1)
            self.logger_func(data)
            sys.stdout.flush()
            sys.stderr.flush()

debug_stream = log_stream(logging.debug)
info_stream = log_stream(logging.info)
error_stream = log_stream(logging.error)

##############################################################################################################################################

class log_command:
    def __init__(self, name: str, key: str, value: str|None):
        self.name = name
        self.key = key
        self.value = value

class log_entry:
    def __init__(self, term: int, index: int, commnad: log_command):
        ...

##############################################################################################################################################

async def on_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    try:
        host = writer.get_extra_info('peername')[0]
        print('got connection from', colors[hosts.index(host)]+host+clear_color, file=debug_stream)
    finally:
        await common.safe_socket_close(writer)

async def listening_server() -> None:
    try:
        async with await asyncio.start_server(on_connection, '0.0.0.0', 4444) as server:
            try:
                await server.serve_forever()
            except asyncio.CancelledError:
                pass
    except:
        print(traceback.format_exc(), file=error_stream)

async def ping_one_host(host:str) -> None:
    try:
        reader, writer = await common.run_with_timeout(asyncio.open_connection(host, 4444), 1)
        try:
            print('connected to', colors[hosts.index(host)]+host+clear_color, file=debug_stream)
        finally:
            await common.safe_socket_close(writer)
    except Exception:
        pass

async def pinger() -> None:
    while 1:
        await asyncio.sleep(1)
        await asyncio.gather(*map(ping_one_host, other_hosts))

async def main() -> None:
    await asyncio.gather(
        pinger(),
        listening_server(),
    )

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass


