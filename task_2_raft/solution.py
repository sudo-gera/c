from __future__ import annotations
import pickle
import base64
import json
import hashlib
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
import copy
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

key_type = str
val_type = bytes

class kv_storage_state:
    def __init__(self) -> None:
        self.data : dict[key_type, val_type] = {}

# kv_storage_states : list[kv_storage_state] = [kv_storage_state()]
kv_storage_states : dict[int, kv_storage_state] = {0: kv_storage_state()}

def clear_old_states() -> None:
    keys = [*kv_storage_states]
    while len(keys) > 8 * storage.commit_len.bit_length():
        keys.remove(random.choice(keys))
    keys.append(0)
    keys.append(max(kv_storage_states))
    to_del = {*kv_storage_states} - {*keys}
    for val in to_del:
        del kv_storage_states[val]

    # inv_keep_f : list[float] = [1]
    # while inv_keep_f[-1] < len(kv_storage_states):
    #     inv_keep_f.append(inv_keep_f[-1] * 2**0.5)
    # storage_len = len(kv_storage_states)
    # keep_i = [storage_len - 1 - round(val) % storage_len for val in inv_keep_f]
    # keep_i.append(0)
    # to_del = {*kv_storage_states.keys()} - {*keep_i}
    # for val in to_del:
    #     del kv_storage_states[val]

def apply_command_to_kv_state(old_state: kv_storage_state, committed_element: log_entry|log_payload) -> tuple[kv_storage_state, val_type|None]:
    new_state = copy.deepcopy(old_state)
    if isinstance(committed_element, log_entry):
        message = committed_element.message
        if message is None:
            return (new_state, None)
        assert message is not None
        command = message.payload.command
    else:
        command = committed_element.command
    if isinstance(command, get_command):
        value = new_state.data.get(command.key, None)
        print(f'applying {command} with result {value!r}')
        return (new_state, value)
    if isinstance(command, set_command):
        old_value = new_state.data.get(command.key, None)
        new_state.data[command.key] = command.value
        print(f'applying {command} replacing {old_value!r} with {command.value!r}')
        return (new_state, None)
    if isinstance(command, del_command):
        old_value = new_state.data.get(command.key, None)
        new_state.data.pop(command.key, None)
        print(f'applying {command} removing {old_value!r}')
        return (new_state, None)
    if isinstance(command, cas_command):
        old_value = new_state.data.get(command.key, None)
        if old_value and hashlib.sha256(old_value).digest() == command.old_value_sha256:
            print(f'applying {command} replacing {old_value!r} with {command.new_value!r}')
            new_state.data[command.key] = command.new_value
        else:
            print(f'applying {command} not replacing {old_value!r}')
        return (new_state, old_value)
    assert False

def get_result_for_command_by_index(command_index: int) -> tuple[command_result, kv_storage_state]:
    assert command_index < storage.commit_len
    assert storage.commit_len <= len(storage.logs)
    key_command_index = command_index
    while key_command_index not in kv_storage_states:
        key_command_index -= 1
        assert key_command_index >= 0
    for i in range(key_command_index+1, command_index + 1):
        assert i not in kv_storage_states
        assert i-1 in kv_storage_states
        kv_storage_states[i] = apply_command_to_kv_state(
            kv_storage_states[i-1],
            storage.logs[i-1],
        )[0]
    assert command_index in kv_storage_states
    state_before_command = kv_storage_states[command_index]
    state_after_command, result = apply_command_to_kv_state(
        state_before_command,
        storage.logs[command_index]
    )
    kv_storage_states[command_index+1] = state_after_command
    clear_old_states()
    return (
        command_result(
            value=result
        ),
        state_after_command
    )


##############################################################################################################################################

class WrongTypeError(Exception):
    pass

class serializable:
    def dump(self) -> bytes:
        assert False
        # import pickle
        # data = pickle.dumps(self)
        # data = wrap(data)
        # return data
    
    @classmethod
    def load(cls: typing.Type[serializable_t], data: bytes) -> serializable_t:
        assert False
        # data = unwrap(data)
        # import pickle
        # msg = pickle.loads(data)
        # if not isinstance(msg, cls):
        #     raise WrongTypeError
        # return msg

serializable_t = typing.TypeVar('serializable_t', bound=serializable)

def dumps(msg: serializable) -> bytes:
    # custom_data = msg.dump()
    # usual_data = wrap(pickle.dumps(msg))
    # real_data = len(custom_data).to_bytes(8, 'big') + custom_data + usual_data
    # return wrap(real_data)

    return msg.dump()

    # assert msg is not None
    # data = pickle.dumps(msg)
    # data = wrap(data)
    # return data

T = typing.TypeVar('T', bound=serializable)

def loads(data: bytes, msg_type: typing.Type[T]) -> T:
    # data = unwrap(data)
    # custom_data_len = int.from_bytes(data[:8], 'big')
    # custom_data = data[8:][:custom_data_len]
    # usual_data = data[8+custom_data_len:]
    # msg = msg_type.load(custom_data)
    # print(msg, file=debug_stream)
    # print(pickle.loads(unwrap(usual_data)), file=debug_stream)
    # assert wrap(pickle.dumps(msg)) == usual_data
    # return msg

    return msg_type.load(data)

    # data = unwrap(data)
    # import pickle
    # msg = pickle.loads(data)
    # if not isinstance(msg, msg_type):
    #     raise WrongTypeError
    # return msg

##############################################################################################################################################

class json_serializable(serializable):
    def json_dump_public(self) -> typing.Any:
        obj = self.json_dump_private()
        return {
            'type': type(self).__name__,
            'data': obj,
        }
    
    def json_dump_private(self) -> typing.Any:
        assert False
    
    @classmethod
    def json_load_private(cls: typing.Type[json_serializable_t], obj: typing.Any) -> json_serializable_t:
        assert False

    @classmethod
    def json_load_public(cls: typing.Type[json_serializable_t], obj: typing.Any) -> json_serializable_t:
        assert isinstance(obj, dict)
        assert {*obj.keys()} == {'type', 'data'}
        if obj['type'] != cls.__name__:
            raise WrongTypeError
        return cls.json_load_private(obj['data'])

    def dump(self) -> bytes:
        return wrap(json.dumps(self.json_dump_public()).encode())

    @classmethod 
    def load(cls: typing.Type[json_serializable_t], data: bytes) -> json_serializable_t:
        data = unwrap(data)
        try:
            obj = json.loads(data.decode())
        except Exception:
            raise WrongTypeError
        return cls.json_load_public(obj)

json_serializable_t = typing.TypeVar('json_serializable_t', bound=json_serializable)

json_load_t = typing.TypeVar('json_load_t', bound=json_serializable)

def json_load(cls: typing.Type[json_load_t], data: typing.Any) -> json_load_t:
    return cls.json_load_public(data)

class trivially_json_serializable(json_serializable):
    def json_dump_private(self) -> typing.Any:
        obj = copy.deepcopy(self.__dict__)
        for k in obj:
            if isinstance(obj[k], bytes):
                obj[k] = {
                    'type': 'bytes',
                    'data': base64.b64encode(obj[k]).decode(),
                }
            else:
                obj[k] = {
                    'type': 'default',
                    'data': obj[k],
                }
        return obj

    @classmethod
    def json_load_private(cls: typing.Type[trivially_json_serializable_t], obj: typing.Any) -> trivially_json_serializable_t:
        obj = copy.deepcopy(obj)
        for k in obj:
            assert isinstance(obj[k], dict)
            assert {*obj[k].keys()} == {'type', 'data'}
            if obj[k]['type'] == 'bytes':
                obj[k] = base64.b64decode(obj[k]['data'])
            elif obj[k]['type'] == 'default':
                obj[k] = obj[k]['data']
            else:
                assert False
        return cls(**obj)

trivially_json_serializable_t = typing.TypeVar('trivially_json_serializable_t', bound=json_serializable)

##############################################################################################################################################

@dataclasses.dataclass
class get_command(trivially_json_serializable):
    key: key_type

@dataclasses.dataclass
class set_command(trivially_json_serializable):
    key: key_type
    value: val_type

@dataclasses.dataclass
class del_command(trivially_json_serializable):
    key: key_type

@dataclasses.dataclass
class cas_command(trivially_json_serializable):
    key: key_type
    old_value_sha256: bytes
    new_value: val_type

@dataclasses.dataclass
class command_result(trivially_json_serializable):
    value: val_type|None

@dataclasses.dataclass
class log_payload(json_serializable):
    # value: int
    command: cas_command | set_command | get_command | del_command

    def json_dump_private(self) -> typing.Any:
        command = self.command
        obj = command.json_dump_public()
        if isinstance(command, cas_command):
            return {
                'type': 'cas_command_',
                'data': obj,
            }
        if isinstance(command, set_command):
            return {
                'type': 'set_command_',
                'data': obj,
            }
        if isinstance(command, get_command):
            return {
                'type': 'get_command_',
                'data': obj,
            }
        if isinstance(command, del_command):
            return {
                'type': 'del_command_',
                'data': obj,
            }

    @classmethod
    def json_load_private(cls, obj: typing.Any) -> log_payload:
        return log_payload(
            json_load(
                dict(
                    get_command_=get_command,
                    set_command_=set_command,
                    del_command_=del_command,
                    cas_command_=cas_command,
                )[obj['type']],
                obj['data']
            )
        )

@dataclasses.dataclass
class log_message(json_serializable):
    msg_id: int
    payload: log_payload

    def json_dump_private(self) -> typing.Any:
        obj = copy.deepcopy(self.__dict__)
        obj['payload'] = self.payload.json_dump_public()
        return obj

    @classmethod
    def json_load_private(cls, obj: typing.Any) -> log_message:
        obj = copy.deepcopy(obj)
        obj['payload']=log_payload.json_load_public(obj['payload'])
        return log_message(**obj)

@dataclasses.dataclass
class log_entry(json_serializable):
    term: int
    message: log_message | None

    def json_dump_private(self) -> typing.Any:
        obj = copy.deepcopy(self.__dict__)
        message = self.message
        if message is not None:
            obj['message'] = message.json_dump_public()
        return obj

    @classmethod
    def json_load_private(cls, obj: typing.Any) -> log_entry:
        obj = copy.deepcopy(obj)
        if obj['message'] is not None:
            obj['message']=log_message.json_load_public(obj['message'])
        return log_entry(**obj)

@dataclasses.dataclass
class append_entries_req(json_serializable):
    term: int
    log_len: int
    last_log_term: int
    commit_len: int
    entries: list[log_entry]
    msg_id: int
    leader_id: int

    def json_dump_private(self) -> typing.Any:
        obj = copy.deepcopy(self.__dict__)
        obj['entries'] = []
        for entry in self.entries:
            obj['entries'].append(entry.json_dump_public())
        return obj

    @classmethod
    def json_load_private(cls, obj: typing.Any) -> append_entries_req:
        obj = copy.deepcopy(obj)
        entries: list[log_entry] = []
        for entry in obj['entries']:
            entries.append(log_entry.json_load_public(entry))
        obj['entries'] = entries
        return append_entries_req(**obj)

@dataclasses.dataclass
class append_entries_res(trivially_json_serializable):
    term: int
    status: typing.Literal['good', 'wrong_last_log', 'wrong_term', 'wrong_msg_id']

@dataclasses.dataclass
class request_vote_req(trivially_json_serializable):
    candidate_id: int
    term: int
    log_len: int
    last_log_term: int

@dataclasses.dataclass
class request_vote_res(trivially_json_serializable):
    term: int
    vote_granted: bool

@dataclasses.dataclass
class read_req(trivially_json_serializable):
    key: key_type
    redirected_to_id: int | None

@dataclasses.dataclass
class new_entry_req(json_serializable):
    message: log_message

    def json_dump_private(self) -> typing.Any:
        obj = copy.deepcopy(self.__dict__)
        obj['message'] = self.message.json_dump_public()
        return obj

    @classmethod
    def json_load_private(cls, obj: typing.Any) -> new_entry_req:
        obj = copy.deepcopy(obj)
        obj['message']=log_message.json_load_public(obj['message'])
        return new_entry_req(**obj)

@dataclasses.dataclass
class raft_facade_req(json_serializable):
    command: new_entry_req | read_req

    def json_dump_private(self) -> typing.Any:
        command = self.command
        obj = command.json_dump_public()
        if isinstance(command, new_entry_req):
            return {
                'type': 'new_entry_req_',
                'data': obj,
            }
        if isinstance(command, read_req):
            return {
                'type': 'read_req_',
                'data': obj,
            }

    @classmethod
    def json_load_private(cls, obj: typing.Any) -> raft_facade_req:
        return raft_facade_req(
            json_load(
                dict(
                    new_entry_req_=new_entry_req,
                    read_req_=read_req,
                )[obj['type']],
                obj['data']
            )
        )

@dataclasses.dataclass
class raft_facade_res(json_serializable):
    redirected_to_id: int | None
    result: command_result | None

    def json_dump_private(self) -> typing.Any:
        obj = copy.deepcopy(self.__dict__)
        result = self.result
        if result is not None:
            obj['result'] = result.json_dump_public()
        return obj

    @classmethod
    def json_load_private(cls, obj: typing.Any) -> raft_facade_res:
        obj = copy.deepcopy(obj)
        if obj['result'] is not None:
            obj['result']=command_result.json_load_public(obj['result'])
        return raft_facade_res(**obj)


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

list_storage_item = typing.TypeVar('list_storage_item', bound=serializable)

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

    async def try_process(self, data: bytes, writer: asyncio.StreamWriter) -> serializable | None:
        assert False

ipc_client_req = typing.TypeVar('ipc_client_req', bound=serializable)
ipc_client_res = typing.TypeVar('ipc_client_res', bound=serializable)

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

ipc_servers : list[typing.Type[base_ipc_server]] = []

##############################################################################################################################################

ipc_server_req = typing.TypeVar('ipc_server_req', bound=serializable)
ipc_server_res = typing.TypeVar('ipc_server_res', bound=serializable)

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

ipc_servers.append(append_entries_server)

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

ipc_servers.append(request_vote_server)

##############################################################################################################################################

raft_facade_lock = asyncio.Lock()

class raft_facade_server(ipc_server[raft_facade_req, raft_facade_res]):
    req_type = raft_facade_req
    res_type = raft_facade_res

    # def get_logs(self, len_after_adding: int) -> list[log_message]:
    #     return [log.message for log in storage.logs[:len_after_adding] if log.message is not None][-4:]

    def get_result(self, len_after_adding: int) -> command_result:
        assert len_after_adding
        return get_result_for_command_by_index(len_after_adding - 1)[0]

    async def async_handle_msg(self, req: raft_facade_req | None) -> raft_facade_res:
        if req is None:
            return await self.async_handle_msg_unlocked(req)
        else:
            command = req.command
            if isinstance(command, read_req):
                res = self.try_handle_read(req, command)
                if res is not None:
                    return res
            async with raft_facade_lock:
                return await self.async_handle_msg_unlocked(req)
    
    def try_handle_read(self, req: raft_facade_req | None, command: read_req) -> raft_facade_res | None:
        role_when_started = role

        expected_commit_len : int | None = None

        if command.redirected_to_id is not None:
            if command.redirected_to_id != me.id:
                print(f'{req = } attempt to add new entry to {role.name}', file=debug_stream)
                return raft_facade_res(
                    redirected_to_id=None,
                    # success=False,
                    # logs=[],
                    result=None,
                )
        else:
            if role_when_started.name != 'leader':
                print(f'{req = } attempt to add new entry to {role.name}', file=debug_stream)
                return raft_facade_res(
                    redirected_to_id=None,
                    # success=False,
                    # logs=[],
                    result=None,
                )

        if role.name == 'leader':
            expected_commit_len = len(storage.logs)
            while 1:
                if expected_commit_len == 0:
                    break
                log = storage.logs[expected_commit_len-1]
                message = log.message
                if message is None:
                    expected_commit_len -= 1
                    continue
                if message.payload.command.key != command.key:
                    expected_commit_len -= 1
                    continue
                else:
                    break
        else:
            expected_commit_len = 0

        assert expected_commit_len is not None

        append_entries_heartbeat()

        print(f'{req = } waiting {storage.commit_len = } to be {expected_commit_len}', file=debug_stream)

        if storage.commit_len < expected_commit_len:
            return None

        assert storage.commit_len >= expected_commit_len

        print(f'{req = } waited {storage.commit_len = } to be {expected_commit_len}', file=debug_stream)

        if command.redirected_to_id is None:
            shuffled_followers = followers[:]
            random.shuffle(shuffled_followers)
            for follower in shuffled_followers:
                if follower.commit_len >= expected_commit_len:
                    return raft_facade_res(
                        redirected_to_id=follower.id,
                        result=None,
                    )
        current_state = get_result_for_command_by_index(storage.commit_len-1)[1]
        value = apply_command_to_kv_state(
            current_state,
            log_payload(
                get_command(
                    key=command.key,
                )
            )
        )[1]
        return raft_facade_res(
            redirected_to_id=None,
            result=command_result(value=value),
        )

    async def async_handle_msg_unlocked(self, req: raft_facade_req | None) -> raft_facade_res:
        role_when_started = role

        command = req.command if req else None

        expected_commit_len : int | None = None

        if not isinstance(command, read_req):

            if role_when_started.name != 'leader':
                print(f'{req = } attempt to add new entry to {role.name}', file=debug_stream)
                return raft_facade_res(
                    redirected_to_id=None,
                    # success=False,
                    # logs=[],
                    result=None,
                )

            if command is not None:
                for i in range(len(storage.logs))[::-1]:
                    message = storage.logs[i].message
                    if message is not None:
                        if message.msg_id == command.message.msg_id:
                            expected_commit_len = i + 1
                            print(f'{req = } new entry was found at {expected_commit_len - 1}: {storage.logs[i]}', file=debug_stream)
                            break
            if expected_commit_len is None:
                print(f'{req = } adding new entry to log', file=debug_stream)
                storage.logs.append(
                    log_entry(
                        term=storage.term,
                        message=command.message if command else None,
                    )
                )
                expected_commit_len = len(storage.logs)

        else:

            if command.redirected_to_id is not None:
                if command.redirected_to_id != me.id:
                    print(f'{req = } attempt to add new entry to {role.name}', file=debug_stream)
                    return raft_facade_res(
                        redirected_to_id=None,
                        # success=False,
                        # logs=[],
                        result=None,
                    )
            else:
                if role_when_started.name != 'leader':
                    print(f'{req = } attempt to add new entry to {role.name}', file=debug_stream)
                    return raft_facade_res(
                        redirected_to_id=None,
                        # success=False,
                        # logs=[],
                        result=None,
                    )

            if role.name == 'leader':
                expected_commit_len = len(storage.logs)
                while 1:
                    if expected_commit_len == 0:
                        break
                    log = storage.logs[expected_commit_len-1]
                    message = log.message
                    if message is None:
                        expected_commit_len -= 1
                        continue
                    if message.payload.command.key != command.key:
                        expected_commit_len -= 1
                        continue
                    else:
                        break
            else:
                expected_commit_len = 0

        assert expected_commit_len is not None

        append_entries_heartbeat()

        print(f'{req = } waiting {storage.commit_len = } to be {expected_commit_len}', file=debug_stream)
        while storage.commit_len < expected_commit_len:
            assert expected_commit_len
            if storage.logs[expected_commit_len-1].term != storage.term:
                await raft_facade_server().async_handle_msg(None)
            else:
                await storage_changed

            if role_when_started != role:
                print(f'{req = } role changed, not adding new log entry', file=debug_stream)

                return raft_facade_res(
                    redirected_to_id=None,
                    # logs=[],
                    # success=False,
                    result=None,
                )

        assert storage.commit_len >= expected_commit_len

        print(f'{req = } waited {storage.commit_len = } to be {expected_commit_len}', file=debug_stream)

        if not isinstance(command, read_req):

            print(f'{req = } adding new log entry succeeded', file=debug_stream)

            return raft_facade_res(
                redirected_to_id=None,
                # logs=self.get_logs(expected_commit_len),
                result=self.get_result(expected_commit_len),
                # success=True,
            )

        else:
            if command.redirected_to_id is None:
                shuffled_followers = followers[:]
                random.shuffle(shuffled_followers)
                for follower in shuffled_followers:
                    if follower.commit_len >= expected_commit_len:
                        return raft_facade_res(
                            redirected_to_id=follower.id,
                            result=None,
                        )
            current_state = get_result_for_command_by_index(storage.commit_len-1)[1]
            value = apply_command_to_kv_state(
                current_state,
                log_payload(
                    get_command(
                        key=command.key,
                    )
                )
            )[1]
            return raft_facade_res(
                redirected_to_id=None,
                result=command_result(value=value),
            )


ipc_servers.append(raft_facade_server)

##############################################################################################################################################

@dataclasses.dataclass
class context_about_follower:
    log_len_upper_estimate : int
    id: int
    log_len_lower_estimate : int = 0
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

followers: list[context_about_follower] = []

class append_entries_client(ipc_client[append_entries_req, append_entries_res]):
    req_type = append_entries_req
    res_type = append_entries_res

    def __init__(self) -> None:
        set_role('leader')
        self.role_when_started = role
        self.term = storage.term
        self.followers = [
            context_about_follower(
                log_len_upper_estimate=len(storage.logs),
                id=host.id,
            )
            for host in hosts
        ]
        global followers
        followers = self.followers
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
                # min(
                #     max_log_len+1,
                    len(storage.logs)
                # )
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

successful_request_count = 0

async def logs_size_printer() -> None:
    while 1:
        old_len = successful_request_count
        await asyncio.sleep(5)
        new_len = successful_request_count
        print(f'Last five seconds gave {new_len - old_len} new ops!', file=info_stream)

client_at_start.append(logs_size_printer())

# local_log : list[log_payload] = []

# async def raft_client() -> None:
#     while 1:
#         payload = log_payload(random.randint(0, 255))
#         remote_log = await raft_facade_client(payload)
#         assert not local_log or len(remote_log) >= 2
#         local_log.append(payload)
#         assert local_log[-len(remote_log):] == remote_log
#         if len(remote_log) != len(local_log):
#             break
#     while 1:
#         remote_logs = await asyncio.gather(
#             *[
#                 raft_facade_client(payload)
#                 for payload in [
#                     log_payload(random.randint(0, 255))
#                     for q in range(random.randint(1, 20))
#                 ]
#             ]
#         )
#         remote_log_len = len(remote_logs[0])
#         assert remote_log_len >= 2
#         assert all([len(remote_log) == remote_log_len for remote_log in remote_logs])
#         sorted_remote_logs = [local_log[-remote_log_len:]]
#         while len(sorted_remote_logs) != len(remote_logs) + 1:
#             for remote_log in remote_logs:
#                 if remote_log[:-1] == sorted_remote_logs[-1][1:]:
#                     sorted_remote_logs.append(remote_log)
#                     break
#             else:
#                 assert False
#         for remote_log in sorted_remote_logs[1:]:
#             assert remote_log[:-1] == local_log[-remote_log_len+1:]
#             local_log.append(remote_log[-1])

action_type = typing.Literal['invent_new_key',    'get',    'set',    'del',    'good_cas',       'bad_cas']

async def raft_client() -> None:
    keys : list[key_type] = []
    local_storage : dict[key_type, val_type] = {}
    while 1:
        actions : list[action_type] = []
        action: action_type
        for q in range(1):
            action = 'invent_new_key'
            actions.append(action)
        for q in range(20):
            action = 'get'
            actions.append(action)
        for q in range(1):
            action = 'set'
            actions.append(action)
        for q in range(1):
            action = 'del'
            actions.append(action)
        for q in range(20):
            action = 'good_cas'
            actions.append(action)
        for q in range(20):
            action = 'bad_cas'
            actions.append(action)

        action = random.choice(actions)

        if not keys:
            action = 'invent_new_key'
        if keys and not local_storage:
            action = 'set'

        if action == 'invent_new_key':
            keys.append(random.randbytes(4).hex())
        elif action == 'get':
            key = random.choice(keys)
            res = await raft_facade_client(
                payload=log_payload(
                    command=get_command(
                        key=key,
                    ),
                ),
            )
            assert res.value == local_storage.get(key, None)
        elif action == 'set':
            key = random.choice(keys)
            value = random.randbytes(4)
            res = await raft_facade_client(
                payload=log_payload(
                    command=set_command(
                        key=key,
                        value=value,
                    ),
                ),
            )
            assert res.value is None
            local_storage[key] = value
        elif action == 'del':
            key = random.choice(keys)
            res = await raft_facade_client(
                payload=log_payload(
                    command=del_command(
                        key=key,
                    ),
                ),
            )
            assert res.value is None
            local_storage.pop(key, None)
        elif action == 'good_cas':
            key = random.choice([*local_storage.keys()])
            old_value = local_storage[key]
            new_value = random.randbytes(4)
            res = await raft_facade_client(
                payload=log_payload(
                    command=cas_command(
                        key=key,
                        old_value_sha256=hashlib.sha256(old_value).digest(),
                        new_value=new_value,
                    ),
                ),
            )
            assert res.value == old_value
            local_storage[key] = new_value
        elif action == 'bad_cas':
            key = random.choice(keys)
            while 1:
                old_value = random.randbytes(4)
                if old_value != local_storage.get(key, None):
                    break
            new_value = random.randbytes(4)
            res = await raft_facade_client(
                payload=log_payload(
                    command=cas_command(
                        key=key,
                        old_value_sha256=hashlib.sha256(old_value).digest(),
                        new_value=new_value,
                    ),
                ),
            )
            assert res.value == local_storage.get(key, None)
        else:
            assert False
        



client_at_start.append(raft_client())

@dataclasses.dataclass
class append_context:
    message: log_message
    has_success: asyncio.Future[command_result]
    redirected_to_id: int | None

class raft_facade_client(ipc_client[raft_facade_req, raft_facade_res]):
    req_type = raft_facade_req
    res_type = raft_facade_res

    def __init__(self, payload: log_payload) -> None:
        self.payload = payload
        self.role_when_started = role
        self.append_context = append_context(
            message=log_message(
                msg_id=random.randint(0, 2**60-1),
                payload=payload,
            ),
            has_success=asyncio.Future(),
            redirected_to_id=None,
        )

    def __await__(self) -> typing.Generator[typing.Any, None, command_result]:
        return self.main().__await__()

    async def main(self) -> command_result:
        res = await self.append(self.payload)
        global successful_request_count
        successful_request_count += 1
        return res
        # global local_log
        
        # while 1:
        #     value = random.randint(0, 2**20-1)
        #     payload = log_payload(
        #         value=value,
        #     )
        #     remote_log = await self.append(payload)
        #     assert len(remote_log) >= 2 or not local_log
        #     local_log.append(remote_log[-1])
        #     assert local_log[-len(remote_log):] == remote_log


    async def message_sender(self, context: append_context) -> None:
        while not context.has_success.done():
            print(f'send_all while appending {context.message.payload}', file=debug_stream)
            self.send_all()
            await asyncio.sleep(0.11)

    async def append(self, payload: log_payload) -> command_result:
        print(f'starting to append {payload}', file=info_stream)
        fire(self.message_sender(self.append_context))
        result = await self.append_context.has_success
        print(f'succeeded to append {payload}', file=info_stream)
        # return [log.payload for log in logs]
        return result

    def get_req(self, host: host_info) -> raft_facade_req:
        context = self.append_context
        assert isinstance(context, append_context)
        if isinstance(context.message.payload.command, get_command):
            return raft_facade_req(
                command=read_req(
                    redirected_to_id=context.redirected_to_id,
                    key=context.message.payload.command.key,
                )
            )
        else:
            return raft_facade_req(
                command=new_entry_req(
                    message=context.message,
                )
            )

    def handle_res(self, host: host_info, res: raft_facade_res, req: raft_facade_req) -> None:
        context = self.append_context

        if not isinstance(context, append_context):
            print(f'{res = } context is None', file=debug_stream)
            return
        assert isinstance(context, append_context)

        command = req.command
        if isinstance(command, new_entry_req):
            if command.message  is not context.message:
                print(f'{res = } message is too old', file=debug_stream)
                return
        
        if isinstance(command, read_req):
            if res.redirected_to_id is not None:
                print(f'{res = } was redirected to {res.redirected_to_id}', file=debug_stream)
                context.redirected_to_id = res.redirected_to_id
                fire(self.send_one(hosts[res.redirected_to_id]))

        if res.result is None:
            print(f'{res = } request has failure message', file=debug_stream)
            return

        print(f'{res = } request succeeded', file=debug_stream)
        if not context.has_success.done():
            context.has_success.set_result(res.result)

##############################################################################################################################################

async def on_connection_unhandled(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    fire(on_connection(reader, writer))

async def on_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    global last_incoming_message_time
    try:
        data = await reader.read()
        for ipc_server in ipc_servers:
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
        await asyncio.sleep(timeout * (1 + 2 * random.Random().random()))
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
    else:
        for coro in server_at_start:
            fire(coro)
    await asyncio.Future()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

