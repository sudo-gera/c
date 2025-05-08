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
        print('\x03')

alerter = alert()

# def fire(coro: typing.Generator[typing.Any, None, None] | typing.Coroutine[typing.Any, typing.Any, None]) -> None:
def fire(coro: typing.Awaitable[typing.Any]) -> None:
    async def wrapper() -> None:
        try:
            await coro
        except BaseException:
            alert()
            raise
    task : asyncio.Task[None] = asyncio.create_task(wrapper())
    tasks.add(task)
    task.add_done_callback(tasks.discard)

at_start : list[typing.Awaitable[typing.Any]] = []

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

me = [host for host in hosts if host.ip == my_ip][0]
other_hosts = {*hosts} - {me}

consensus_size = min([
    q
    for q in range(len(hosts)+4)
    if q*2 > len(hosts)
])

##############################################################################################################################################

# colors = [
#     '\x1b[90m',
#     '\x1b[91m',
#     '\x1b[92m',
#     '\x1b[93m',
#     '\x1b[94m',
#     '\x1b[95m',
#     '\x1b[96m',
#     '\x1b[97m',
# ]
# my_color = colors[hosts.index(my_ip)]
# clear_color = '\x1b[0m'

##############################################################################################################################################

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='[ %(asctime)s ]: %(message)s')

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

class log_payload:
    def __init__(
        self,
        # name: str,
        # key: str,
        # value: str|None
    ) -> None:
        ...
        # self.name = name
        # self.key = key
        # self.value = value

class log_entry:
    def __init__(
        self,
        term: int,
        payload: log_payload,
    ):
        self.term = term
        self.payload = payload

class append_entries_req:
    def __init__(
        self,
        term: int,
        log_len: int,
        last_log_term: int,
        commit_len: int,
        entries: list[log_entry],
        msg_id: int,
    ):
        self.term = term
        self.log_len = log_len
        self.last_log_term = last_log_term
        self.entries = entries
        self.commit_len = commit_len
        self.msg_id = msg_id

class append_entries_res:
    def __init__(
        self,
        term: int,
        success: bool,
    ):
        self.term = term
        self.success = success

class request_vote_req:
    def __init__(
        self,
        candidate_id: int,
        term: int,
        log_len: int,
        last_log_term: int,
    ):
        self.candidate_id = candidate_id
        self.term = term
        self.log_len = log_len
        self.last_log_term = last_log_term

class request_vote_res:
    def __init__(
        self,
        term: int,
        vote_granted: bool,
    ):
        self.term = term
        self.vote_granted = vote_granted

##############################################################################################################################################

class WrongTypeError(Exception):
    pass

T = typing.TypeVar('T')

def dumps(msg: T) -> bytes:
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

    # def __getattr__(self, name: str) -> int:
    #     return int.from_bytes(self[name], 'big')

    # def __setattr__(self, name: str, value: int) -> None:
    #     self[name] = value.to_bytes(8, 'big')

    # def __getitem__(self, name: int|str) -> bytes:
    #     if isinstance(name, int):
    #         name = f'{name:020d}'
    #     assert isinstance(name, str)
    #     return self.cached_get(name)

    # def __setitem__(self, name: int|str, value: bytes) -> None:
    #     if isinstance(name, int):
    #         name = f'{name:020d}'
    #     assert isinstance(name, str)
    #     self.cached_set(name, value)

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
        self.set_waiters : list[typing.Callable[[], None]] = []
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
        while self.set_waiters:
            self.set_waiters.pop()()
        self.storage.cached_set(
            self.name,
            value.to_bytes(8, 'big')
        )
    
    async def wait_changed(self) -> None:
        f : asyncio.Future[None] = asyncio.Future()
        self.set_waiters.append(lambda: f.set_result(None))
        await f

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
        assert isinstance(self.size_storage, int_storage)

    def append(self, value: list_storage_item) -> None:
        self.resize(len(self)+1, value)
    
    def pop(self) -> list_storage_item:
        value = self[len(self)-1]
        self.resize(len(self)-1)
        return value

# class has_storage:
#     storage: cached_persistent_storage


# class int_storage:
#     def __init__(self, name: str, default: int):
#         self.name = name
#         self.default = default
#         self.set_waiters : list[typing.Callable[[], None]] = []

#     def __get__(self, instance: has_storage | None, instance_class: typing.Type[has_storage] | None = None) -> int:
#         assert instance is not None
#         data = instance.storage.cached_get(self.name)
#         if isinstance(data, Exception):
#             self.__set__(instance, self.default)
#             return self.default
#         assert isinstance(data, bytes)
#         value = int.from_bytes(data, 'big')
#         return value
    
#     def __set__(self, instance: has_storage, value: int) -> None:
#         while self.set_waiters:
#             self.set_waiters.pop()()
#         instance.storage.cached_set(
#             self.name,
#             value.to_bytes(8, 'big')
#         )
    
#     async def wait_changed(self) -> None:
#         f : asyncio.Future[None] = asyncio.Future()
#         self.set_waiters.append(lambda: f.set_result(None))
#         await f

# list_storage_item = typing.TypeVar('list_storage_item')

# class list_storage(has_storage, typing.Generic[list_storage_item]):

#     def __init__(self, storage: cached_persistent_storage, name: str, element_type: typing.Type[list_storage_item], size_storage: int_storage):
#         self.storage = storage
#         self.name = name
#         self.size_storage = size_storage
#         self.element_type = element_type

#     @typing.overload
#     def __getitem__(self, key: int) -> list_storage_item:
#         ...

#     @typing.overload
#     def __getitem__(self, key: slice) -> list[list_storage_item]:
#         ...

#     def __getitem__(self, key: int|slice) -> list_storage_item | list[list_storage_item]:
#         if isinstance(key, slice):
#             return [self[key] for key in [*range(len(self))][key]]
#         if isinstance(key, int):
#             key %= len(self)
#             data = self.storage.cached_get(f'{self.name}_{key:020d}')
#             if isinstance(data, Exception):
#                 raise data
#             return loads(data, self.element_type)

#     def __setitem__(self, key: int, value: list_storage_item) -> None:
#         data = dumps(value)
#         self.storage.cached_set(f'{self.name}_{key:020d}', data)
    
#     def __len__(self) -> int:
#         return self.size_storage

#     def resize(self, new_len: int, value: list_storage_item|None = None) -> None:
#         for i in range(len(self), new_len):
#             assert value is not None
#             self[i] = value
#         self.size_storage = new_len
#         assert isinstance(self.size_storage, int_storage)

#     def append(self, value: list_storage_item) -> None:
#         self.resize(len(self)+1, value)
    
#     def pop(self) -> list_storage_item:
#         value = self[len(self)-1]
#         self.resize(len(self)-1)
#         return value

##############################################################################################################################################

nan = 2**62

class raft_storage:
    voted_for : object_descriptor[int, int] = object_descriptor()
    log_len : object_descriptor[int, int] = object_descriptor()
    term : object_descriptor[int, int] = object_descriptor()
    commit_len : object_descriptor[int, int] = object_descriptor()
    # voted_for = int_storage('voted_for', nan)
    # log_len = int_storage('log_len', 0)
    # term = int_storage('term', 1)
    # commit_len = int_storage('commit_len', 0)
    # logs_len = int_storage('logs_len', 0)

    def __init__(self) -> None:
        self.storage = cached_persistent_storage(
            pathlib.Path('/raft').resolve()
        )

        self.voted_for_object = int_storage('voted_for', nan, self.storage)
        self.log_len_object = int_storage('log_len', 0, self.storage)
        self.term_object = int_storage('term', 1, self.storage)
        self.commit_len_object = int_storage('commit_len', 0, self.storage)

        self.voted_for_object.init(self, type(self).voted_for)
        self.log_len_object.init(self, type(self).log_len)
        self.term_object.init(self, type(self).term)
        self.commit_len_object.init(self, type(self).commit_len)

        self.logs = list_storage(self.storage, 'logs', log_entry)

    # @property
    # def voted_for(self) -> int:
    #     return self.voted_for_storage.get_int(nan)

    # @voted_for.setter
    # def voted_for(self, value) -> None:
    #     return self.voted_for_storage.set_int(value)

    # @property
    # def log_len(self) -> int:
    #     return self.log_len_storage.get_int(0)

    # @log_len.setter
    # def log_len(self, value) -> None:
    #     return self.log_len_storage.set_int(value)

    # @property
    # def term(self) -> int:
    #     return self.term_storage.get_int(1)

    # @term.setter
    # def term(self, value) -> None:
    #     return self.term_storage.set_int(value)
    
    # @property
    # def commit_len(self) -> int:
    #     return self.commit_len_storage.get_int(0)

    # @commit_len.setter
    # def commit_len(self, value) -> None:
    #     return self.commit_len_storage.set_int(value)


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

class base_ipc_client():

    async def try_process(self, data: bytes, writer: asyncio.StreamWriter) -> typing.Any:
        assert False

ipc_client_req = typing.TypeVar('ipc_client_req')
ipc_client_res = typing.TypeVar('ipc_client_res')

class ipc_client(base_ipc_client, typing.Generic[ipc_client_req, ipc_client_res]):
    req_type : typing.Type[ipc_client_req]
    res_type : typing.Type[ipc_client_res]

    def handle_msg(self, msg: ipc_client_req) -> ipc_client_res:
        assert False

    async def try_process(self, data: bytes, writer: asyncio.StreamWriter) -> ipc_client_res | None:
        try:
            msg = loads(data, self.req_type)
        except (WrongTypeError, HashError):
            return None
        return self.handle_msg(msg)
        
ipc_clients : list[typing.Type[base_ipc_client]] = []

##############################################################################################################################################

ipc_server_req = typing.TypeVar('ipc_server_req')
ipc_server_res = typing.TypeVar('ipc_server_res')

class ipc_server(typing.Generic[ipc_server_req, ipc_server_res]):
    req_type : typing.Type[ipc_server_req]
    res_type : typing.Type[ipc_server_res]
    role_when_started : role_info

    def send_all(self) -> None:
        for host in other_hosts:
            fire(self.send_one(host))
    
    def get_req(self, host: host_info) -> ipc_server_req:
        assert False

    def handle_res(self, host: host_info, res: ipc_server_res, req: ipc_server_req) -> None:
        assert False

    async def send_one(self, host: host_info) -> None:
        try:
            reader, writer = await asyncio.open_connection(host.ip, 4444)
        except Exception as e:
            print(f'failed to connect to {host.ip} with {type(e)} {e}')
            return
        try:
            print(f'connected to {host.ip}', file=debug_stream)
            req = self.get_req(host)
            writer.write(dumps(req))
            writer.write_eof()
            await writer.drain()
            print(f'send req {req} at {host.ip}', file=debug_stream)
            try:
                res = loads(await reader.read(), self.res_type)
            except (HashError):
                return
            print(f'recv res {res} at {host.ip}', file=debug_stream)
            if role is not self.role_when_started:
                print(f'role changed, drop res {res} at {host.ip}', file=debug_stream)
                return
            print(f'handle res {res} at {host.ip}', file=debug_stream)
            self.handle_res(host, res, req)
        finally:
            await common.safe_socket_close(writer)

##############################################################################################################################################

class append_entries_client(ipc_client[append_entries_req, append_entries_res]):
    req_type = append_entries_req
    res_type = append_entries_res

    def handle_msg(self, msg: append_entries_req) -> append_entries_res:

        if msg.term < storage.term:
            return append_entries_res(
                term = storage.term,
                success = False,
            )

        assert storage.term <= msg.term
        if storage.term < msg.term:
            storage.voted_for = nan
            storage.term = msg.term

        if role.name == 'candidate':
            set_role('follower')
        assert role.name == 'follower'

        global last_incoming_message_time
        last_incoming_message_time = time.time()

        if msg.log_len > len(storage.logs):
            return append_entries_res(
                term = storage.term,
                success = False,
            )

        assert len(storage.logs) >= msg.log_len
        storage.logs.resize(msg.log_len)
        assert storage.commit_len >= len(storage.logs)

        if msg.last_log_term != storage.logs[-1].term:
            return append_entries_res(
                term = storage.term,
                success = False,
            )

        for entry in msg.entries:
            storage.logs.append(entry)

        assert storage.commit_len <= msg.commit_len
        assert msg.commit_len <= len(storage.logs)
        storage.commit_len = msg.commit_len

        return append_entries_res(
            term = storage.term,
            success = True,
        )

ipc_clients.append(append_entries_client)

##############################################################################################################################################

class request_vote_client(ipc_client[request_vote_req, request_vote_res]):
    req_type = request_vote_req
    res_type = request_vote_res

    def handle_msg(self, msg: request_vote_req) -> request_vote_res:
        assert role.name == 'candidate'

        if msg.term < storage.term:
            return request_vote_res(
                term=storage.term,
                vote_granted=False,
            )

        assert storage.term <= msg.term

        if storage.term < msg.term:
            storage.voted_for = nan
            storage.term = msg.term

        assert storage.term == msg.term
        assert storage.voted_for != msg.candidate_id
        assert storage.voted_for != me.id

        global last_incoming_message_time
        last_incoming_message_time = time.time()

        if storage.voted_for != nan:
            return request_vote_res(
                term=storage.term,
                vote_granted=False,
            )

        last_log_term = storage.logs[-1] if len(storage.logs) else 0

        if (msg.last_log_term, msg.log_len) >= (last_log_term, len(storage.logs)):
            storage.voted_for = msg.candidate_id
            return request_vote_res(
                term=storage.term,
                vote_granted=True,
            )
            
        return request_vote_res(
            term=storage.term,
            vote_granted=False,
        )

ipc_clients.append(request_vote_client)

##############################################################################################################################################

@dataclasses.dataclass
class context_about_follower:
    log_len_lower_estimate : int = 0
    log_len_upper_estimate : int = 0
    commit_len : int = 0
    last_sent_msg_id : int = 0
    last_recv_msg_id : int = 0

class append_entries_server(ipc_server[append_entries_req, append_entries_res]):
    req_type = append_entries_req
    res_type = append_entries_res

    def __init__(self) -> None:
        set_role('leader')
        self.role_when_started = role
        self.followers = [context_about_follower() for host in hosts]
        for follower in self.followers:
            follower.log_len_upper_estimate = len(storage.logs)
        fire(self.main())

    async def main(self) -> None:
        while self.role_when_started == role:
            self.send_all()
            await asyncio.sleep(1)

    def get_req(self, host: host_info) -> append_entries_req:
        max_log_len = self.followers[host.id].log_len_upper_estimate
        self.followers[host.id].last_sent_msg_id += 1
        return append_entries_req(
            msg_id=self.followers[host.id].last_sent_msg_id,
            term=storage.term,
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
            storage.voted_for = nan
            storage.term = res.term
            set_role('follower')
            return

        assert self.followers[host.id].last_recv_msg_id != req.msg_id

        if self.followers[host.id].last_recv_msg_id > req.msg_id:
            return

        assert self.followers[host.id].last_recv_msg_id < req.msg_id
        self.followers[host.id].last_recv_msg_id = req.msg_id

        if res.success:
            assert self.followers[host.id].commit_len <= req.commit_len <= storage.commit_len
            self.followers[host.id].commit_len = req.commit_len
            self.followers[host.id].log_len_lower_estimate = req.log_len + len(req.entries)
            self.followers[host.id].log_len_upper_estimate = req.log_len + len(req.entries)
            max_stored_on_consensus_log_len = min(
                sorted(
                    [
                        self.followers[host.id].log_len_lower_estimate
                        for host in hosts
                    ],
                    reverse=True
                )[:consensus_size]
            )
            assert max_stored_on_consensus_log_len <= len(storage.logs)
            if max_stored_on_consensus_log_len:
                if storage.logs[max_stored_on_consensus_log_len].term == storage.term:
                    storage.commit_len = max(
                        storage.commit_len,
                        max_stored_on_consensus_log_len
                    )
        else:
            assert self.followers[host.id].log_len_upper_estimate
            self.followers[host.id].log_len_upper_estimate -= 1

##############################################################################################################################################

class request_vote_server(ipc_server[request_vote_req, request_vote_res]):
    req_type = request_vote_req
    res_type = request_vote_res

    def __init__(self) -> None:
        set_role('candidate')
        self.role_when_started = role
        self.voters : set[host_info] = set()
        storage.voted_for = nan
        storage.term += 1
        storage.voted_for = me.id
        self.send_all()
    
    def get_req(self, host: host_info) -> request_vote_req:
        return request_vote_req(
            candidate_id=me.id,
            term=storage.term,
            log_len=storage.log_len,
            last_log_term=storage.logs[-1].term if storage.log_len else 0,
        )

    def handle_res(self, host: host_info, res: request_vote_res, req: request_vote_req) -> None:
        if res.term < storage.term:
            return

        global last_incoming_message_time
        last_incoming_message_time = time.time()

        if res.term > storage.term:
            storage.voted_for = nan
            storage.term = res.term
            set_role('follower')
            return

        assert res.term == storage.term

        if res.vote_granted:
            assert host not in self.voters
            self.voters.add(host)
        
        if len(self.voters) >= consensus_size:
            append_entries_server()
        

##############################################################################################################################################

async def on_connection_unhandled(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    fire(on_connection(reader, writer))

async def on_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    global last_incoming_message_time
    try:
        data = await reader.read()
        for ipc_client in ipc_clients:
            res = await ipc_client().try_process(data, writer)
            if res is not None:
                break
        writer.write(dumps(res))
        writer.write_eof()
        await writer.drain()
    finally:
        await common.safe_socket_close(writer)

##############################################################################################################################################

# ##############################################################################################################################################

# async def on_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
#     global last_incoming_message_time
#     try:
#         data = await reader.read()
#         for ipc_client in ipc_clients:
#             res = ipc_client().try_process(data, writer)
#             if res is not None:
#                 break
#             await awrite_msg(writer, res)
#         # try:
#         #     msg = await aread_msg(reader, append_entries_req)
#         # except Exception:
#         #     pass
#         # else:
#         #     last_incoming_message_time = time.time()
#         #     await awrite_msg(writer, on_append_entries(msg))

#         # try:
#         #     msg = await aread_msg(reader, request_vote_req)
#         # except Exception:
#         #     pass
#         # else:
#         #     last_incoming_message_time = time.time()
#         #     await awrite_msg(writer, on_request_vote(msg))

#     finally:
#         await common.safe_socket_close(writer)

# def on_request_vote(req: request_vote_req) -> request_vote_res:
#     if req.term < storage.term:
#         return request_vote_res(
#             term = storage.current_term,
#             vote_granted = False,
#         )
#     if req.term > storage.term:
#         storage.term = req.term
#         storage.voted_for = -1
#         if storage.logs:
#             last_log = storage.logs[-1]
#             if req.last_log_term < last_log.term:
#                 return request_vote_res(
#                     term = storage.current_term,
#                     vote_granted = False,
#                 )
#             if req.last_log_index < last_log.index:
#                 return request_vote_res(
#                     term = storage.current_term,
#                     vote_granted = False,
#                 )
#         storage.voted_for = req.candidate_id
#         return request_vote_res(
#             term = storage.current_term,
#             vote_granted = True,
#         )
#     if req.term == storage.term:
#         if storage.voted_for != req.candidate_id:
#             return request_vote_res(
#                 term = storage.current_term,
#                 vote_granted = False,
#             )
#         elif storage.voted_for == -1:
#             storage.voted_for = req.candidate_id
#             return request_vote_res(
#                 term = storage.current_term,
#                 vote_granted = True,
#             )
#     assert False

# def on_append_entries(req: append_entries_req) -> append_entries_res:
#     ...

##############################################################################################################################################

last_incoming_message_time = time.time()
timeout = 4

async def timeout_checker() -> None:
    while 1:
        await asyncio.sleep(timeout * (1 + random.Random().random()))
        if last_incoming_message_time + timeout < time.time():
            print(f'last message was {time.time() - last_incoming_message_time} seconds ago, sending request vote', file=debug_stream)
            request_vote_server()
        else:
            print(f'last message was {time.time() - last_incoming_message_time} seconds ago, not a problem', file=debug_stream)
            

at_start.append(timeout_checker())

# ##############################################################################################################################################

# class request_vote_context:
#     def __init__(self, role_when_started: role):
#         self.voters : set[str] = set()
#         self.role_when_started = role_when_started

# async def send_request_vote(host: str, context: request_vote_context):
#     if storage.logs:
#         last_log_index = storage.logs[-1].index
#         last_log_term = storage.logs[-1].term
#     else:
#         last_log_index = 0
#         last_log_term = 0
#     try:
#         reader, writer = await asyncio.open_connection(host, 4444)
#     except Exception:
#         return
#     try:
#         await awrite_msg(
#             writer,
#             request_vote_req(
#                 candidate_id = me.id,
#                 term = storage.current_term,
#                 last_log_index = last_log_index,
#                 last_log_term = last_log_term,
#             )
#         )
#         res = await aread_msg(
#             reader,
#             request_vote_res,
#         )
#         if res.term < storage.current_term:
#             return
#         if current_role is not context.role_when_started:
#             return
#         if res.vote_granted:
#             assert res.term == storage.current_term
#             context.voters.add(host)
#             if len(context.voters) >= consensus_size:
#                 global current_role
#                 current_role = role(
#                     role_name='leader',
#                     role_id=current_role.role_id + 1,
#                 )
#                 fire(leader(current_role))
#     finally:
#         await common.safe_socket_close(writer)

# async def candidate():
#     storage.current_term += 1
#     storage.voted_for = me.id
#     voters : set[str] = set()
#     global current_role
#     current_role = role(
#         role_name='candidate',
#         role_id=current_role.role_id + 1
#     )
#     for host in other_hosts:
#         fire(send_request_vote(host, current_role, voters))

# class leader():
#     def __init__(self, role_when_started: role):
#         fire(main(role_when_started))
    
#     async def main(self, role_when_started: role):
#         self.commit_len = [0 for host in hosts]
#         self.log_len = [storage.log_size for host in hosts]
#         next_index = [last_log_index + 1 for host in hosts]
#         context = append_entries_context(
#             next_index=next_index
#         )
#         while role_when_started is current_role:
#             for host in hosts:
#                 fire(send_request_vote(host, context))
#             await asyncio.sleep(0.05)


#     def __init__(self, next_index: list[int]):
#         self.next_index = next_index

# async def send_append_entries(host: str, context: append_entries_context):
#     try:
#         reader, writer = await asyncio.open_connection(host, 4444)
#     except Exception:
#         return
#     try:
#         await awrite_msg(
#             writer,
#             append_entries_req(
#                 term = storage.current_term,
#                 leader_id = my_id,
#                 prev_log_index = context.next_index[hosts.index(host)]-1,
#                 prev_log_term = storage[context.next_index[hosts.index(host)]-1],
#                 entries=
#             )
#         )
#         res = await aread_msg(
#             reader,
#             append_entries_res,
#         )
#         if res.term < storage.current_term:
#             return
#         if current_role is not context.role_when_started:
#             return
#     finally:
#         common.safe_socket_close(writer)

# async def leader(role_when_started: role):
#     last_log = get_last_log()
#     last_log_index = last_log.index if last_log is not None else 0
#     next_index = [last_log_index + 1 for host in hosts]
#     context = append_entries_context(
#         next_index=next_index
#     )
#     while role_when_started is current_role:
#         for host in hosts:
#             fire(send_request_vote(host, context))
#         await asyncio.sleep(0.05)


# ##############################################################################################################################################

# async def on_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
#     try:
#         host = writer.get_extra_info('peername')[0]
#         print('got connection from', colors[hosts.index(host)]+host+clear_color, file=debug_stream)
#     finally:
#         await common.safe_socket_close(writer)

async def listening_server() -> None:
    try:
        async with await asyncio.start_server(on_connection_unhandled, '0.0.0.0', 4444) as server:
            try:
                await server.serve_forever()
            except asyncio.CancelledError:
                pass
    except:
        print(traceback.format_exc(), file=error_stream)

at_start.append(listening_server())

# async def ping_one_host(host:str) -> None:
#     try:
#         reader, writer = await common.run_with_timeout(asyncio.open_connection(host, 4444), 1)
#         try:
#             print('connected to', colors[hosts.index(host)]+host+clear_color, file=debug_stream)
#         finally:
#             await common.safe_socket_close(writer)
#     except Exception:
#         pass

# async def pinger() -> None:
#     while 1:
#         await asyncio.sleep(1)
#         await asyncio.gather(*map(ping_one_host, other_hosts))

# async def main() -> None:
#     await asyncio.gather(
#         pinger(),
#         listening_server(),
#     )

async def main() -> None:
    for coro in at_start:
        fire(coro)
    await asyncio.Future()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass




