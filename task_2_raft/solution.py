from __future__ import annotations
import pathlib
import shutil
import os
import random
import ipaddress
import common
import asyncio
import sys
import time
import io
import functools
import psutil
import traceback
import logging
import typing
import weakref
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

tasks : set[asyncio.Task[None]] = set()

class alert:
    def __del__(self) -> None:
        print('\x03\x03\x03')
        print('FAIL !FAIL!', file=error_stream)

alerter = alert()

# def fire(coro: typing.Generator[typing.Any, None, None] | typing.Coroutine[typing.Any, typing.Any, None]) -> None:
def fire(coro: typing.Awaitable[typing.Any]) -> None:
    async def wrapper() -> None:
        try:
            await coro
        except BaseException:
            alert()
            print(traceback.format_exc(), file=error_stream)
            raise
    task : asyncio.Task[None] = asyncio.create_task(wrapper())
    tasks.add(task)
    task.add_done_callback(tasks.discard)

client_at_start : list[typing.Awaitable[typing.Any]] = []
server_at_start : list[typing.Awaitable[typing.Any]] = []

##############################################################################################################################################

class awaitable_event:
    def __init__(self) -> None:
        self.future : asyncio.Future[None] | None = None

    def __call__(self) -> None:
        if self.future is not None:
            self.future.set_result(None)
        self.future = None

    async def wait(self) -> None:
        if self.future is None:
            self.future = asyncio.Future()
        assert isinstance(self.future, asyncio.Future)
        await self.future

    def __await__(self) -> typing.Generator[None, None, None]:
        return self.wait().__await__()

##############################################################################################################################################

host_ips = sys.argv[1:]
host_ips.sort()
my_ip = common.select_my_ip(host_ips)

@dataclasses.dataclass(frozen=True)
class host_info:
    ip: str
    id: int

hosts = [
    host_info(
        id = host_id,
        ip = host_ip,
    )
    for host_id, host_ip in enumerate(host_ips)
]

mes = [host for host in hosts if host.ip == my_ip]
other_hosts = {*hosts} - {*mes}
assert len(mes) <= 1
if mes:
    me = mes[0]

consensus_size = min([
    q
    for q in range(len(hosts)+4)
    if q*2 > len(hosts)
])

##############################################################################################################################################

async def connect_stdin_stdout() -> tuple[asyncio.StreamReader, asyncio.StreamWriter]:
    loop = asyncio.get_event_loop()
    reader = asyncio.StreamReader()
    protocol = asyncio.StreamReaderProtocol(reader)
    # await loop.connect_read_pipe(lambda: protocol, sys.stdin)
    w_transport, w_protocol = await loop.connect_write_pipe(asyncio.streams.FlowControlMixin, sys.stdout)
    writer = asyncio.StreamWriter(w_transport, w_protocol, reader, loop)
    return reader, writer

out_queue : asyncio.Queue[str] = asyncio.Queue()

async def out_printer() -> None:
    stdin, stdout = await connect_stdin_stdout()
    while 1:
        data = await out_queue.get()
        while not out_queue.empty():
            data += out_queue.get_nowait()
        stdout.write(data.encode())
        await stdout.drain()

client_at_start.append(out_printer())
server_at_start.append(out_printer())

class queue_stream:
    def __init__(self, q: asyncio.Queue[str]) -> None:
        self.q = q
    
    def write(self, data: str) -> None:
        self.q.put_nowait(data)

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='[ %(asctime)s ]: %(message)s', stream=queue_stream(out_queue))

class log_stream:
    def __init__(self, logger_func: typing.Callable[[str], None]):
        self.logger_func = logger_func
        self.buffer = ''
    def write(self, data: str) -> None:
        self.buffer += data
        while '\n' in self.buffer:
            data, self.buffer = self.buffer.split('\n', 1)
            data = data + ' \x00 ' + f'{time.time_ns():024d}_{my_ip}'
            assert not set(data) & set('\r\n')
            out_queue.put_nowait('\x05' + data + '\n')
            self.logger_func(data)
            # sys.stdout.flush()
            # sys.stderr.flush()

debug_stream = log_stream(logging.debug)
info_stream = log_stream(logging.info)
error_stream = log_stream(logging.error)

##############################################################################################################################################

@dataclasses.dataclass
class log_payload:
    value: int

@dataclasses.dataclass
class log_message:
    msg_id: int
    payload: log_payload

@dataclasses.dataclass
class log_entry:
    term: int
    message: log_message | None

@dataclasses.dataclass
class append_entries_req:
    term: int
    log_len: int
    last_log_term: int
    commit_len: int
    entries: list[log_entry]
    msg_id: int
    leader_id: int

@dataclasses.dataclass
class append_entries_res:
    term: int
    status: typing.Literal['good', 'wrong_last_log', 'wrong_term', 'wrong_msg_id']

@dataclasses.dataclass
class request_vote_req:
    candidate_id: int
    term: int
    log_len: int
    last_log_term: int

@dataclasses.dataclass
class request_vote_res:
    term: int
    vote_granted: bool

@dataclasses.dataclass
class new_entry_req:
    message: log_message

@dataclasses.dataclass
class new_entry_res:
    success: bool
    logs: list[log_message]

##############################################################################################################################################

class WrongTypeError(Exception):
    pass

T = typing.TypeVar('T')

def dumps(msg: T) -> bytes:
    assert msg is not None
    import pickle
    data = pickle.dumps(msg)
    data = wrap(data)
    return data

def loads(data: bytes, msg_type: typing.Type[T]) -> T:
    data = unwrap(data)
    import pickle
    msg = pickle.loads(data)
    if not isinstance(msg, msg_type):
        raise WrongTypeError
    return msg

##############################################################################################################################################

def static_hash(value: int | float | str | bytes | bytearray, size: int) -> bytes:
    return random.Random(value).randbytes(size)

hash_len = 8

class HashError(Exception):
    pass

def wrap(data: bytes) -> bytes:
    return static_hash(data, hash_len) + data

def unwrap(data: bytes) -> bytes:
    h, d = data[:hash_len], data[hash_len:]
    if h != static_hash(d, hash_len):
        raise HashError
    return d

##############################################################################################################################################

storage_changed = awaitable_event()

class cached_persistent_storage:
    def __init__(self, storage_path: pathlib.Path):
        self.storage_path = storage_path

        storage_prefixes = [storage_path]

        while 1:
            to_add = storage_prefixes[-1].parent
            if to_add in storage_prefixes:
                break
            storage_prefixes.append(to_add)

        storage_prefixes.reverse()

        for storage_prefix in storage_prefixes:
            if not storage_prefix.is_dir():
                storage_prefix.mkdir()

        for file in storage_path.iterdir():
            if file.suffix == '.tmp':
                file.unlink()

        self.cache : dict[str, bytes] = {}

    def cached_get(self, name: str) -> bytes|Exception:
        if name not in self.cache:
            data = self.uncached_get(name)
            if isinstance(data, Exception):
                return data
            assert isinstance(data, bytes)
            self.cache[name] = data
        return self.cache[name]

    def cached_set(self, name: str, value: bytes) -> None:
        if name in self.cache and self.cache[name] == value:
            return
        self.cache[name] = value
        self.uncached_set(name, value)

    def uncached_get(self, name: str) -> bytes|Exception:
        assert not set(name) & set('./')
        path = self.storage_path / name
        try:
            file = path.open('rb')
        except FileNotFoundError as e:
            return e
        with file:
            data = file.read()
        return unwrap(data)

    def uncached_set(self, name: str, data: bytes) -> None:
        assert not set(name) & set('./')
        path = self.storage_path / name
        tmp_file = (
            self.storage_path / random.randbytes(8).hex()
        ).with_suffix('.tmp')
        with tmp_file.open('wb') as file:
            file.write(wrap(data))
        tmp_file.rename(path)
        storage_changed()


##############################################################################################################################################

object_descriptor_get = typing.TypeVar('object_descriptor_get')
object_descriptor_set = typing.TypeVar('object_descriptor_set')

class object_descriptor(typing.Generic[object_descriptor_get, object_descriptor_set]):
    def __init__(self) -> None:
        self.object_to_object_descriptor : weakref.WeakValueDictionary[int, base_object_descriptor[object_descriptor_get, object_descriptor_set]] = weakref.WeakValueDictionary()

    @typing.overload
    def __get__(self, instance: None, instance_class: typing.Type[object]) -> object_descriptor[object_descriptor_get, object_descriptor_set]:
        ...

    @typing.overload
    def __get__(self, instance: object, instance_class: typing.Type[object]) -> object_descriptor_get:
        ...

    def __get__(self, instance: object|None, instance_class: typing.Type[object]) -> object_descriptor_get|object_descriptor[object_descriptor_get, object_descriptor_set]:
        if instance is None:
            return self
        else:
            return self.object_to_object_descriptor[id(instance)].object_get()

    def __set__(self, instance: object, value: object_descriptor_set) -> None:
        return self.object_to_object_descriptor[id(instance)].object_set(value)

class base_object_descriptor(typing.Generic[object_descriptor_get, object_descriptor_set]):
    def object_get(self) -> object_descriptor_get:
        assert False

    def object_set(self, value: object_descriptor_set) -> None:
        assert False

    def init(self, instance: object, desc: object_descriptor[object_descriptor_get, object_descriptor_set]) -> None:
        desc.object_to_object_descriptor[id(instance)] = self

##############################################################################################################################################

class int_storage(base_object_descriptor[int, int]):
    def __init__(self, name: str, default: int, storage: cached_persistent_storage):
        self.name = name
        self.default = default
        self.storage = storage

    def object_get(self) -> int:
        data = self.storage.cached_get(self.name)
        if isinstance(data, Exception):
            self.object_set(self.default)
            return self.default
        assert isinstance(data, bytes)
        value = int.from_bytes(data, 'big')
        return value

    def object_set(self, value: int) -> None:
        self.storage.cached_set(
            self.name,
            value.to_bytes(8, 'big')
        )

list_storage_item = typing.TypeVar('list_storage_item')

class list_storage(typing.Generic[list_storage_item]):
    size_storage : object_descriptor[int, int] = object_descriptor()

    def __init__(self, storage: cached_persistent_storage, name: str, element_type: typing.Type[list_storage_item]):
        self.size_storage_object = int_storage(f'{name}_size', 0, storage)
        self.size_storage_object.init(self, type(self).size_storage)
        self.storage = storage
        self.name = name
        self.element_type = element_type

    @typing.overload
    def __getitem__(self, key: int) -> list_storage_item:
        ...

    @typing.overload
    def __getitem__(self, key: slice) -> list[list_storage_item]:
        ...

    def __getitem__(self, key: int|slice) -> list_storage_item | list[list_storage_item]:
        if isinstance(key, slice):
            return [self[key] for key in [*range(len(self))][key]]
        if isinstance(key, int):
            key %= len(self)
            data = self.storage.cached_get(f'{self.name}_{key:020d}')
            if isinstance(data, Exception):
                raise data
            return loads(data, self.element_type)

    def __setitem__(self, key: int, value: list_storage_item) -> None:
        data = dumps(value)
        self.storage.cached_set(f'{self.name}_{key:020d}', data)

    def __len__(self) -> int:
        return self.size_storage

    def resize(self, new_len: int, value: list_storage_item|None = None) -> None:
        for i in range(len(self), new_len):
            assert value is not None
            self[i] = value
        self.size_storage = new_len

    def append(self, value: list_storage_item) -> None:
        self.resize(len(self)+1, value)

    def pop(self) -> list_storage_item:
        value = self[len(self)-1]
        self.resize(len(self)-1)
        return value

##############################################################################################################################################

nan = 2**62

class raft_storage:
    voted_for : object_descriptor[int, int] = object_descriptor()
    term : object_descriptor[int, int] = object_descriptor()
    commit_len : object_descriptor[int, int] = object_descriptor()
    last_msg_id : object_descriptor[int, int] = object_descriptor()

    def __init__(self) -> None:
        self.storage = cached_persistent_storage(
            pathlib.Path('/raft').resolve()
        )

        self.voted_for_object = int_storage('voted_for', nan, self.storage)
        self.term_object = int_storage('term', 1, self.storage)
        self.commit_len_object = int_storage('commit_len', 0, self.storage)
        self.last_msg_id_object = int_storage('last_msg_id', 0, self.storage)

        self.voted_for_object.init(self, type(self).voted_for)
        self.term_object.init(self, type(self).term)
        self.commit_len_object.init(self, type(self).commit_len)
        self.last_msg_id_object.init(self, type(self).last_msg_id)

        self.logs = list_storage(self.storage, 'logs', log_entry)


storage = raft_storage()

##############################################################################################################################################

role_type = typing.Literal['leader', 'follower', 'candidate']

@dataclasses.dataclass(frozen=True)
class role_info:
    name : role_type
    id: int

role = role_info(
    name='follower',
    id=0,
)

def set_role(name: role_type) -> None:
    global role
    role = role_info(
        name = name,
        id = role.id + 1,
    )

##############################################################################################################################################

class base_ipc_server():

    async def try_process(self, data: bytes, writer: asyncio.StreamWriter) -> typing.Any:
        assert False

ipc_client_req = typing.TypeVar('ipc_client_req')
ipc_client_res = typing.TypeVar('ipc_client_res')

class ipc_server(base_ipc_server, typing.Generic[ipc_client_req, ipc_client_res]):
    req_type : typing.Type[ipc_client_req]
    res_type : typing.Type[ipc_client_res]

    async def async_handle_msg(self, msg: ipc_client_req) -> ipc_client_res:
        return self.handle_msg(msg)

    def handle_msg(self, msg: ipc_client_req) -> ipc_client_res:
        assert False

    async def try_process(self, data: bytes, writer: asyncio.StreamWriter) -> ipc_client_res | None:
        try:
            req = loads(data, self.req_type)
        except (WrongTypeError, HashError):
            # print(f'>>>>>>>>> {self}', file=debug_stream)
            return None
        print(f'recv {req = } at {writer.transport.get_extra_info("peername")[0]}', file=debug_stream)
        res = await self.async_handle_msg(req)
        print(f'send {res = } at {writer.transport.get_extra_info("peername")[0]}', file=debug_stream)
        return res

ipc_clients : list[typing.Type[base_ipc_server]] = []

##############################################################################################################################################

ipc_server_req = typing.TypeVar('ipc_server_req')
ipc_server_res = typing.TypeVar('ipc_server_res')

class ipc_client(typing.Generic[ipc_server_req, ipc_server_res]):
    req_type : typing.Type[ipc_server_req]
    res_type : typing.Type[ipc_server_res]
    role_when_started : role_info

    def send_all(self) -> None:
        print(f'{other_hosts = }', file=debug_stream)
        for host in other_hosts:
            # print(f'firing {host} for {self}', file=debug_stream)
            fire(self.send_one(host))

    def get_req(self, host: host_info) -> ipc_server_req:
        assert False

    def handle_res(self, host: host_info, res: ipc_server_res, req: ipc_server_req) -> None:
        assert False

    async def send_one(self, host: host_info) -> None:
        req = self.get_req(host)
        # print(f'fired {host} for {self} and {req}', file=debug_stream)
        try:
            reader, writer = await asyncio.open_connection(host.ip, 4444)
        except Exception as e:
            print(f'failed to connect to {host.ip} with {type(e)} {e}', file=debug_stream)
            return
        try:
            print(f'connected to {host.ip}', file=debug_stream)
            # if role is not self.role_when_started:
            #     print(f'role changed, drop connection at {host.ip}', file=debug_stream)
            #     return
            print(f'send {req = } at {host.ip}', file=debug_stream)
            await asyncio.sleep(random.random()**6) # FOR TESTING
            writer.write(dumps(req))
            writer.write_eof()
            await writer.drain()
            data = await reader.read()
            await asyncio.sleep(random.random()**6) # FOR TESTING
            try:
                res = loads(data, self.res_type)
            except (WrongTypeError):
                # import pickle
                # print('failed to load data:', pickle.loads(unwrap(data)), self.res_type, file=debug_stream)
                raise
            except (HashError):
                return
            print(f'recv {res = } at {host.ip}', file=debug_stream)
            if role is not self.role_when_started:
                print(f'role changed, drop {res = } at {host.ip}', file=debug_stream)
                return
            print(f'handle {res = } at {host.ip}', file=debug_stream)
            self.handle_res(host, res, req)
        except OSError as e:
            print(f'Got OSError: {type(e)}, {e}', file=debug_stream)
        finally:
            await common.safe_socket_close(writer)

##############################################################################################################################################

class append_entries_server(ipc_server[append_entries_req, append_entries_res]):
    req_type = append_entries_req
    res_type = append_entries_res

    def handle_msg(self, req: append_entries_req) -> append_entries_res:

        if req.term < storage.term:
            print(f'append_entries from {hosts[req.leader_id].ip} failed because it has old term', file=info_stream)
            print(f'{req = } is older than current term {storage.term}', file=debug_stream)
            return append_entries_res(
                term = storage.term,
                status='wrong_term',
            )

        assert storage.term <= req.term
        if storage.term < req.term:
            print(f'{req = } is newer than current term {storage.term}, updating...', file=debug_stream)
            storage.last_msg_id = 0
            storage.voted_for = nan
            storage.term = req.term

        if role.name != 'follower':
            print(f'changing role from {role.name} to follower', file=debug_stream)
            set_role('follower')

        global last_incoming_message_time
        last_incoming_message_time = time.time()

        if req.msg_id < storage.last_msg_id:
            print(f'append_entries from {hosts[req.leader_id].ip} failed because it has old msg_id', file=info_stream)
            print(f'{req = } has older msg_id than my {storage.last_msg_id}', file=debug_stream)
            return append_entries_res(
                term = storage.term,
                status='wrong_msg_id',
            )
        
        assert req.msg_id > storage.last_msg_id
        storage.last_msg_id = req.msg_id

        if req.log_len > len(storage.logs):
            print(f'append_entries from {hosts[req.leader_id].ip} failed because it has longer logs', file=info_stream)
            print(f'{req = } server has longer logs than my {len(storage.logs) = }', file=debug_stream)
            return append_entries_res(
                term = storage.term,
                status='wrong_last_log',
            )

        if storage.commit_len > req.log_len:
            print(f'append_entries from {hosts[req.leader_id].ip} failed because its log_len shorter than my commit_len', file=info_stream)
            print(f'{req = } log len is shorter than {storage.commit_len = }', file=debug_stream)
            return append_entries_res(
                term = storage.term,
                status='wrong_last_log',
            )

        assert len(storage.logs) >= req.log_len
        print(f'{req = } resizing my log from {len(storage.logs)} to {req.log_len}', file=debug_stream)
        print(f'{req = } while having committed {storage.commit_len} logs', file=debug_stream)
        print(f'resizing my log from {len(storage.logs)} to {req.log_len}', file=info_stream)
        print(f'while having committed {storage.commit_len} logs', file=info_stream)
        storage.logs.resize(req.log_len)
        assert storage.commit_len <= len(storage.logs)

        last_log_term = storage.logs[-1].term if len(storage.logs) else 0
        if req.last_log_term != last_log_term:
            print(f'append_entries from {hosts[req.leader_id].ip} failed because last log is different', file=info_stream)
            print(f'{req = } i have another {last_log_term = }', file=debug_stream)
            return append_entries_res(
                term = storage.term,
                status='wrong_last_log',
            )

        print(f'{req = } i have to add {req.entries = } to log', file=debug_stream)
        print(f'i have to add {req.entries = } to log', file=info_stream)
        for entry in req.entries:
            storage.logs.append(entry)

        if req.commit_len >= storage.commit_len:
            print(f'{req = } updating commit_len from {storage.commit_len} to {req.commit_len}', file=debug_stream)
            storage.commit_len = req.commit_len
        else:
            print(f'{req = } not updating commit_len from {storage.commit_len} to {req.commit_len}', file=debug_stream)

        print(f'append_entries succeeded', file=info_stream)
        print(f'{req = } append_entries succeeded', file=debug_stream)
        return append_entries_res(
            term = storage.term,
            status='good',
        )

ipc_clients.append(append_entries_server)

##############################################################################################################################################

class request_vote_server(ipc_server[request_vote_req, request_vote_res]):
    req_type = request_vote_req
    res_type = request_vote_res

    def handle_msg(self, req: request_vote_req) -> request_vote_res:

        if req.term < storage.term:
            print(f'not voting for {hosts[req.candidate_id].ip} because it has old term', file=info_stream)
            print(f'{req = } is older than current term {storage.term}', file=debug_stream)
            return request_vote_res(
                term=storage.term,
                vote_granted=False,
            )

        assert storage.term <= req.term

        if storage.term < req.term:
            print(f'{req = } is newer than current term {storage.term}, updating...', file=debug_stream)
            storage.last_msg_id = 0
            storage.voted_for = nan
            storage.term = req.term

        if role.name == 'leader':
            print(f'changing role from {role.name} to follower', file=debug_stream)
            set_role('follower')

        assert storage.term == req.term
        assert storage.voted_for != req.candidate_id

        global last_incoming_message_time
        last_incoming_message_time = time.time()

        if storage.voted_for != nan:
            print(f'not voting for {hosts[req.candidate_id].ip} because i have already voted', file=info_stream)
            print(f'{req = } is failed because i have already voted', file=debug_stream)
            return request_vote_res(
                term=storage.term,
                vote_granted=False,
            )

        last_log_term = storage.logs[-1].term if len(storage.logs) else 0

        print(f'{req = } my log is {(last_log_term, len(storage.logs))}', file=debug_stream)
        if (req.last_log_term, req.log_len) >= (last_log_term, len(storage.logs)):
            print(f'voting for {hosts[req.candidate_id].ip}', file=info_stream)
            print(f'{req = } is succseeded', file=debug_stream)
            storage.voted_for = req.candidate_id
            return request_vote_res(
                term=storage.term,
                vote_granted=True,
            )

        print(f'not voting for {hosts[req.candidate_id].ip} because log is too short', file=info_stream)
        print(f'{req = } is failed because its log is too short', file=debug_stream)
        return request_vote_res(
            term=storage.term,
            vote_granted=False,
        )

ipc_clients.append(request_vote_server)

##############################################################################################################################################

class new_entry_server(ipc_server[new_entry_req, new_entry_res]):
    req_type = new_entry_req
    res_type = new_entry_res

    def get_logs(self) -> list[log_message]:
        return [log.message for log in storage.logs[:storage.commit_len] if log.message is not None][-4:]

    async def async_handle_msg(self, req: new_entry_req | None) -> new_entry_res:
        role_when_started = role

        if role_when_started.name != 'leader':
            print(f'{req = } attempt to add new entry to {role.name}', file=debug_stream)
            return new_entry_res(
                success=False,
                logs=self.get_logs(),
            )

        expected_commit_len : int | None = None
        if req is not None:
            for i in range(len(storage.logs))[::-1]:
                message = storage.logs[i].message
                if message is not None:
                    if message.msg_id == req.message.msg_id:
                        expected_commit_len = i + 1
                        print(f'{req = } new entry was found at {expected_commit_len - 1}: {storage.logs[i]}', file=debug_stream)
                        break
        if expected_commit_len is None:
            print(f'{req = } adding new entry to log', file=debug_stream)
            storage.logs.append(
                log_entry(
                    term=storage.term,
                    message=req.message if req else None,
                )
            )
            expected_commit_len = len(storage.logs)

        assert expected_commit_len is not None

        append_entries_heartbeat()

        print(f'{req = } waiting {storage.commit_len = } to be {expected_commit_len}', file=debug_stream)
        while storage.commit_len < expected_commit_len:
            assert expected_commit_len
            if storage.logs[expected_commit_len-1].term != storage.term:
                await new_entry_server().async_handle_msg(None)
            else:
                await storage_changed

            if role_when_started != role:
                print(f'{req = } role changed, not adding new log entry', file=debug_stream)

                return new_entry_res(
                    logs=self.get_logs(),
                    success=False,
                )

        assert storage.commit_len >= expected_commit_len

        print(f'{req = } adding new log entry succeeded', file=debug_stream)

        return new_entry_res(
            logs=self.get_logs(),
            success=True,
        )

ipc_clients.append(new_entry_server)

##############################################################################################################################################

@dataclasses.dataclass
class context_about_follower:
    log_len_lower_estimate : int = 0
    log_len_upper_estimate : int = 0
    commit_len : int = 0
    last_sent_msg_id : int = 0
    last_recv_msg_id : int = 0

append_entries_heartbeat = awaitable_event()

async def generate_heartbeats() -> None:
    while 1:
        print(f'append_entries_heartbeat', file=debug_stream)
        append_entries_heartbeat()
        await asyncio.sleep(0.101)

server_at_start.append(generate_heartbeats())

class append_entries_client(ipc_client[append_entries_req, append_entries_res]):
    req_type = append_entries_req
    res_type = append_entries_res

    def __init__(self) -> None:
        set_role('leader')
        self.role_when_started = role
        self.term = storage.term
        self.followers = [context_about_follower() for host in hosts]
        for follower in self.followers:
            follower.log_len_upper_estimate = len(storage.logs)
        fire(self.main())

    async def main(self) -> None:
        while self.role_when_started == role:
            self.send_all()
            self.check_commit_len()
            await append_entries_heartbeat

    def get_req(self, host: host_info) -> append_entries_req:
        max_log_len = self.followers[host.id].log_len_upper_estimate
        self.followers[host.id].last_sent_msg_id += 1
        return append_entries_req(
            leader_id=me.id,
            msg_id=self.followers[host.id].last_sent_msg_id,
            term=self.term,
            log_len=max_log_len,
            last_log_term=storage.logs[max_log_len-1].term if max_log_len else 0,
            commit_len=min(storage.commit_len, max_log_len),
            entries=storage.logs[
                max_log_len
                    :
                min(
                    max_log_len+1,
                    len(storage.logs)
                )
            ]
        )

    def handle_res(self, host: host_info, res: append_entries_res, req: append_entries_req) -> None:

        assert res.term >= storage.term

        global last_incoming_message_time
        last_incoming_message_time = time.time()

        if res.term > storage.term:
            print(f'{req = } {res = } has higher term than my {storage.term = }', file=debug_stream)
            storage.voted_for = nan
            storage.term = res.term
            set_role('follower')
            return

        assert res.status != 'wrong_term'

        assert self.followers[host.id].last_recv_msg_id != req.msg_id

        if self.followers[host.id].last_recv_msg_id > req.msg_id:
            print(f'{req = } {res = } has older msg_id than current {self.followers[host.id].last_recv_msg_id}', file=debug_stream)
            return

        assert self.followers[host.id].last_recv_msg_id < req.msg_id
        self.followers[host.id].last_recv_msg_id = req.msg_id

        if res.status == 'good':
            print(f'{req = } {res = } request succeeded, updating follower values', file=debug_stream)
            assert self.followers[host.id].commit_len <= req.commit_len <= storage.commit_len
            print(f'{req = } {res = } changing commit_len from {self.followers[host.id].commit_len} to {req.commit_len}', file=debug_stream)
            self.followers[host.id].commit_len = req.commit_len
            print(f'{req = } {res = } changing log_len_lower_estimate from {self.followers[host.id].log_len_lower_estimate} to {req.log_len + len(req.entries)}', file=debug_stream)
            self.followers[host.id].log_len_lower_estimate = req.log_len + len(req.entries)
            print(f'{req = } {res = } changing log_len_upper_estimate from {self.followers[host.id].log_len_upper_estimate} to {req.log_len + len(req.entries)}', file=debug_stream)
            self.followers[host.id].log_len_upper_estimate = req.log_len + len(req.entries)
            self.check_commit_len()
        elif res.status == 'wrong_last_log':
            print(f'{req = } {res = } request failed with {res.status = }, updating follower values', file=debug_stream)
            log_len_upper_estimate = min(
                self.followers[host.id].log_len_upper_estimate,
                req.log_len - 1,
            )
            print(f'{req = } {res = } changing log_len_upper_estimate from {self.followers[host.id].log_len_upper_estimate} to {log_len_upper_estimate}', file=debug_stream)
            self.followers[host.id].log_len_upper_estimate = log_len_upper_estimate
        else:
            assert res.status == 'wrong_msg_id'
            print(f'{req = } {res = } request failed with {res.status = }', file=debug_stream)


    def check_commit_len(self) -> None:
        self.followers[me.id].log_len_lower_estimate = len(storage.logs)
        max_stored_on_consensus_log_len = min(
            sorted(
                [
                    self.followers[host.id].log_len_lower_estimate
                    for host in hosts
                ],
                reverse=True
            )[:consensus_size]
        )
        print(f'{max_stored_on_consensus_log_len = }', file=debug_stream)
        assert max_stored_on_consensus_log_len <= len(storage.logs)
        if max_stored_on_consensus_log_len:
            if storage.logs[max_stored_on_consensus_log_len-1].term == storage.term:
                storage.commit_len = max(
                    storage.commit_len,
                    max_stored_on_consensus_log_len
                )

##############################################################################################################################################

class request_vote_client(ipc_client[request_vote_req, request_vote_res]):
    req_type = request_vote_req
    res_type = request_vote_res

    def __init__(self) -> None:
        set_role('candidate')
        self.role_when_started = role
        self.voters : set[host_info] = set()
        storage.last_msg_id = 0
        storage.voted_for = nan
        storage.term += 1
        print(f'incrementing {storage.term = }', file=debug_stream)
        storage.voted_for = me.id
        self.voters.add(me)
        self.send_all()
        self.check_leader()

    def get_req(self, host: host_info) -> request_vote_req:
        return request_vote_req(
            candidate_id=me.id,
            term=storage.term,
            log_len=len(storage.logs),
            last_log_term=storage.logs[-1].term if len(storage.logs) else 0,
        )

    def handle_res(self, host: host_info, res: request_vote_res, req: request_vote_req) -> None:
        if res.term < storage.term:
            return

        global last_incoming_message_time
        last_incoming_message_time = time.time()

        if res.term > storage.term:
            storage.last_msg_id = 0
            storage.voted_for = nan
            storage.term = res.term
            set_role('follower')
            return

        assert res.term == storage.term

        if res.vote_granted:
            assert host not in self.voters
            self.voters.add(host)
    
        self.check_leader()

    def check_leader(self) -> None:
        if len(self.voters) >= consensus_size:
            print(f'{self.voters = }, i am leader', file=debug_stream)
            print(f'i am leader', file=info_stream)
            append_entries_client()
        else:
            print(f'{self.voters = }, waiting for more', file=debug_stream)

##############################################################################################################################################

async def logs_size_printer() -> None:
    while 1:
        old_len = len(local_logs)
        await asyncio.sleep(60)
        new_len = len(local_logs)
        print(f'Last minute gave {new_len - old_len} new logs!', file=info_stream)

client_at_start.append(logs_size_printer())

local_logs : list[log_payload] = []

@dataclasses.dataclass
class append_context:
    message: log_message
    has_success: asyncio.Future[list[log_message]]

class new_entry_client(ipc_client[new_entry_req, new_entry_res]):
    req_type = new_entry_req
    res_type = new_entry_res

    def __init__(self) -> None:
        self.role_when_started = role
        self.append_context : append_context | None = None
        fire(self.main())

    async def main(self) -> None:
        global local_logs
        
        while 1:
            # value = random.randint(-2**60, 2**60)
            value = random.randint(0, 2**8-1)
            payload = log_payload(
                value=value,
            )
            remote_logs = await self.append(payload)
            local_logs.append(payload)
            print(f'{remote_logs      = }', file=debug_stream)
            print(f'{ local_logs[-4:] = }', file=debug_stream)
            assert remote_logs == local_logs[-4:]


    async def message_sender(self, context: append_context) -> None:
        while not context.has_success.done():
            print(f'send_all while appending {context.message.payload}', file=debug_stream)
            self.send_all()
            await asyncio.sleep(0.11)

    async def append(self, payload: log_payload) -> list[log_payload]:
        print(f'starting to append {payload}', file=info_stream)
        self.append_context = append_context(
            message=log_message(
                msg_id=random.randint(0, 2**60-1),
                payload=payload,
            ),
            has_success=asyncio.Future(),
        )
        fire(self.message_sender(self.append_context))
        logs = await self.append_context.has_success
        print(f'succeeded to append {payload}', file=info_stream)
        return [log.payload for log in logs]

    def get_req(self, host: host_info) -> new_entry_req:
        context = self.append_context
        assert isinstance(context, append_context)
        return new_entry_req(
            message=context.message,
        )

    def handle_res(self, host: host_info, res: new_entry_res, req: new_entry_req) -> None:
        context = self.append_context

        if not isinstance(context, append_context):
            print(f'{res = } context is None', file=debug_stream)
            return
        assert isinstance(context, append_context)

        if req.message  is not context.message:
            print(f'{res = } message is too old', file=debug_stream)
            return

        if not res.success:
            print(f'{res = } request has failure message', file=debug_stream)
            return

        print(f'{res = } request succeeded', file=debug_stream)
        if not context.has_success.done():
            context.has_success.set_result(res.logs)

##############################################################################################################################################

async def on_connection_unhandled(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    fire(on_connection(reader, writer))

async def on_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    global last_incoming_message_time
    try:
        data = await reader.read()
        for ipc_server in ipc_clients:
            res = await ipc_server().try_process(data, writer)
            if res is not None:
                break
        else:
            # import pickle
            # print('failed to parse data:', pickle.loads(unwrap(data)), file=debug_stream)
            return
        writer.write(dumps(res))
        writer.write_eof()
        await writer.drain()
    except OSError as e:
        print(f'Got OSError: {type(e)}, {e}', file=debug_stream)
    finally:
        await common.safe_socket_close(writer)

##############################################################################################################################################

last_incoming_message_time = time.time()
timeout = 0.4321

async def timeout_checker() -> None:
    while 1:
        await asyncio.sleep(timeout * (1 + random.Random().random()))
        if last_incoming_message_time + timeout < time.time():
            print(f'last message was {time.time() - last_incoming_message_time} seconds ago, sending request vote', file=info_stream)
            request_vote_client()
        else:
            print(f'last message was {time.time() - last_incoming_message_time} seconds ago, not a problem', file=debug_stream)


server_at_start.append(timeout_checker())

##############################################################################################################################################

async def listening_client() -> None:
    try:
        async with await asyncio.start_server(on_connection_unhandled, '0.0.0.0', 4444) as server:
            try:
                await server.serve_forever()
            except asyncio.CancelledError:
                pass
    except:
        print(traceback.format_exc(), file=error_stream)

server_at_start.append(listening_client())


##############################################################################################################################################

async def main() -> None:
    if my_ip is None:
        for coro in client_at_start:
            fire(coro)
        new_entry_client()
    else:
        for coro in server_at_start:
            fire(coro)
    await asyncio.Future()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

