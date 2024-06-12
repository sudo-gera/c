from __future__ import annotations
from testable_thread import TestableThread
from queue import Queue, Empty
import base64
import json
import socket


class UDPBasedProtocol:
    def __init__(self, *, local_addr, remote_addr):
        self.udp_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
        self.remote_addr = remote_addr
        self.udp_socket.bind(local_addr)

    def sendto(self, data):
        return self.udp_socket.sendto(data, self.remote_addr)

    def recvfrom(self, n):
        msg, addr = self.udp_socket.recvfrom(n)
        return msg

    def close(self):
        self.udp_socket.close()

class DataChunk:
    def __init__(self: DataChunk, index: int, data: bytes):
        self.index = index
        self.data = data
        self.sending_iteration = 0
    @property
    def data(self: DataChunk) -> bytes|None:
        if hasattr(self, '_data'):
            return base64.b64decode(self._data.encode())
        else:
            return None
    @data.setter
    def data(self: DataChunk, value: bytes) -> None:
        self._data = base64.b64encode(value).decode()

class Status:
    def __init__(self: Status, received_bitmask: int, taken_from_buffer_count: int):
        self.received_bitmask = received_bitmask
        self.taken_from_buffer_count = taken_from_buffer_count
    def __or__(self: Status, oth: DataChunk|None) -> bytes:
        return json.dumps(self.__dict__ | ({} if oth is None else oth.__dict__)).encode()

class Packet(DataChunk, Status):
    def __init__(self, data: bytes):
        self.__dict__ = json.loads(data)

class Sender:
    def __init__(self: Sender):
        self.queue : Queue[bytes] = Queue()
        self.first_index_never_been_in_buffer = 0
        self.buffer : dict[int, DataChunk] = {}

    def move_chunks_from_queue_to_buffer(self: Sender) -> None:
        chunk_size = 2**13
        chunks = []
        while 1:
            try:
                chunks.append(self.queue.get_nowait())
            except Empty:
                break
        data = b''.join(chunks)
        pos = 0
        while pos < len(data):
            self.buffer[self.first_index_never_been_in_buffer] = DataChunk(
                index = self.first_index_never_been_in_buffer,
                data = data[pos:pos+chunk_size],
            )
            self.first_index_never_been_in_buffer += 1
            pos += chunk_size

    def remove_chunks_that_were_received(self: Sender, status: Status) -> None:
        taken_from_buffer_count = status.taken_from_buffer_count
        received_bitmask = status.received_bitmask
        for chunk_index in [*self.buffer]:
            if chunk_index < taken_from_buffer_count or (1 << chunk_index - taken_from_buffer_count) & received_bitmask:
                del self.buffer[chunk_index]

class Recver:
    def __init__(self: Recver):
        self.queue : Queue[bytes] = Queue()
        self.taken_from_buffer_count = 0
        self.buffer : dict[int, DataChunk] = {}
        self.tmp_data = [b'']

    def move_from_buffer_to_queue(self: Recver) -> None:
        while 1:
            try:
                self.tmp_data.append(self.buffer.pop(self.taken_from_buffer_count).data or b'')
            except KeyError:
                break
            self.taken_from_buffer_count += 1
        data = b''.join(self.tmp_data)
        pos = 0
        while 1:
            if pos + 8 > len(data):
                break
            chunk_length = int.from_bytes(data[pos : pos+8], 'little')
            if pos + 8 + chunk_length > len(data):
                break
            pos += 8
            chunk = data[pos : pos+chunk_length]
            pos += chunk_length
            self.queue.put(chunk)
        assert pos <= len(data)
        data = data[pos:]
        self.tmp_data = [data]

    def add_chunk_to_buffer_if_never_received(self, chunk: DataChunk) -> int:
        message_index = chunk.index
        if message_index < self.taken_from_buffer_count:
            return 0
        if message_index not in self.buffer:
            self.buffer[message_index] = chunk
            self.move_from_buffer_to_queue()
            return 1
        self.move_from_buffer_to_queue()
        return 0

    def get_status(self: Recver) -> Status:
        res = Status(
            taken_from_buffer_count = self.taken_from_buffer_count,
            received_bitmask = 0,
        )
        for chunk_index in self.buffer:
            res.received_bitmask |= 1 << chunk_index - self.taken_from_buffer_count
        return res

class MyTCPProtocol(UDPBasedProtocol):
    def __init__(self: MyTCPProtocol, local_addr: tuple[str, int], remote_addr: tuple[str, int]):
        super().__init__(local_addr=local_addr, remote_addr=remote_addr)
        self.udp_socket.settimeout(1)
        self.sender = Sender()
        self.recver = Recver()
        self.events = Queue()
        self.recvfrom_thread = TestableThread(target=self.recvfrom_loop)
        self.recvfrom_thread.start()
        self.main_thread = TestableThread(target=self.main_loop)
        self.main_thread.start()

    def recvfrom_loop(self: MyTCPProtocol) -> None:
        while 1:
            try:
                recv_chunk = Packet(self.recvfrom(2**16))
                self.events.put(recv_chunk)
            except TimeoutError:
                continue
            except OSError:
                self.events.put(...)
                break

    def main_loop(self: MyTCPProtocol) -> None:
        try:
            has_to_send_status = 0
            while 1:
                self.sender.move_chunks_from_queue_to_buffer()
                recv_status = self.recver.get_status()
                for chunk in self.sender.buffer.values():
                    if chunk.sending_iteration % 2 == 0:
                        self.sendto(recv_status | chunk)
                        has_to_send_status = 0
                    chunk.sending_iteration += 1
                if has_to_send_status > 1:
                    self.sendto(recv_status | None)
                    has_to_send_status = 0
                try:
                    recv_chunk = self.events.get(timeout=1)
                    if recv_chunk is None:
                        raise Empty
                    if recv_chunk is ...:
                        return
                except Empty:
                    has_to_send_status <<= 1
                    continue
                self.sender.remove_chunks_that_were_received(recv_chunk)
                if recv_chunk.data is not None:
                    has_to_send_status |= self.recver.add_chunk_to_buffer_if_never_received(recv_chunk)
        except OSError:
            pass

    def send(self: MyTCPProtocol, data: bytes) -> int:
        data_len = len(data)
        data = len(data).to_bytes(8, 'little') + data
        self.sender.queue.put(data)
        self.events.put(None)
        return data_len

    def recv(self: MyTCPProtocol, n: int) -> bytes:
        data = self.recver.queue.get()
        return data

    def close(self: MyTCPProtocol) -> None:
        super().close()
        self.main_thread.join()
        self.recvfrom_thread.join()

