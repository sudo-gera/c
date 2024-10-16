from __future__ import annotations
import asyncio
import typing
import ssl
import functools
import await_if_necessary

import sign
signer = sign.Signer(8)

first_arg_type =  asyncio.StreamReader | tuple[asyncio.StreamReader, asyncio.StreamWriter] | typing.Awaitable[asyncio.StreamReader] | typing.Awaitable[tuple[asyncio.StreamReader, asyncio.StreamWriter]]
second_arg_type = asyncio.StreamWriter | None | typing.Awaitable[asyncio.StreamWriter]

drainers : dict[int, asyncio.Task[None]] = {}

class StreamImpl:
    def __init__(self, stream: Stream, reader: first_arg_type, writer: second_arg_type):
        self.stream = stream
        self.write_exc : Exception | None = None
        self._reader = reader
        self._writer = writer
        self.entered=False

    async def __aenter__(self) -> Stream:
        self._reader = await await_if_necessary.await_if_necessary(self._reader)
        self._writer = await await_if_necessary.await_if_necessary(self._writer)
        if self._writer is None:
            assert isinstance(self._reader, tuple)
            self._reader, self._writer = self._reader
        self._reader = await await_if_necessary.await_if_necessary(self._reader)
        self._writer = await await_if_necessary.await_if_necessary(self._writer)
        assert isinstance(self._reader, asyncio.StreamReader)
        assert isinstance(self._writer, asyncio.StreamWriter)
        self.reader = self._reader
        self.writer = self._writer
        self.entered=True
        return self.stream

    async def __aexit__(self, *a: typing.Any) -> None:
        assert self.entered
        await self.safe_close()
        if id(self) in drainers:
            await drainers.pop(id(self))
        del self.reader
        del self.writer
        self.entered = False

    def __del__(self) -> None:
        drainers.pop(id(self), None)

    async def safe_close(self) -> None:
        try:
            await self.stream.drain()
            if self.stream.can_write_eof():
                self.stream.write_eof()
                await self.stream.drain()
            self.stream.close()
            try:
                await self.stream.wait_closed()
            except ssl.SSLError as e:
                if e.reason != 'APPLICATION_DATA_AFTER_CLOSE_NOTIFY':
                    raise
        except (OSError, ConnectionResetError):
            pass
    
    async def send_msg(self, data: bytes) -> None:
        data = signer.sign(data)
        data = len(data).to_bytes(8, 'big') + data
        await self.safe_write(data)

    async def recv_msg(self) -> bytes:
        l = int.from_bytes(await self.stream.readexactly(8), 'big')
        data = await self.stream.readexactly(l)
        data = signer.unsign(data)
        return data

    async def safe_write(self, data: bytes) -> None:
        await self.safe_drain(lambda: self.stream.write(data))

    async def safe_write_eof(self) -> None:
        await self.safe_drain(lambda: self.stream.write_eof())

    async def safe_drain(self, writer: typing.Callable[[], None] | None = None) -> None:
        if self.write_exc is not None:
            raise self.write_exc
        if writer is not None:
            writer()
        if id(self) not in drainers:
            drainers[id(self)] = asyncio.create_task(self._safe_drain())
        await asyncio.shield(drainers[id(self)])
        if self.write_exc is not None:
            raise self.write_exc

    async def _safe_drain(self) -> None:
        while self.writer.transport.get_write_buffer_size():
            try:
                await self.stream.drain()
            except Exception as e:
                self.write_exc = e
                break


class Stream(asyncio.StreamReader, asyncio.StreamWriter, StreamImpl):
    def __init__(self, reader: first_arg_type, writer: second_arg_type = None):
        self.__impl = StreamImpl(self, reader, writer)

    def __dir__(self) -> list[str]:
        return dir(self.__impl.reader) + dir(self.__impl.writer) + dir(self.__impl)

    @functools.cache
    def __getattribute__(self, name:str) -> typing.Any:
        if name.startswith(f'_Stream_') or name in 'safe_write safe_close send_msg recv_msg __aenter__ __aexit__'.split():
            return super().__getattribute__(name)
        a = [w for w in [self.__impl.reader, self.__impl.writer, self.__impl] if name in dir(w)]
        assert len(a) == 1, name
        return getattr(a[0], name)

    def __repr__(self) -> str:
        return repr((self.__impl.reader, self.__impl.writer))

    def __del__(self) -> None:
        pass

    async def __aenter__(self) -> Stream:
        return await self.__impl.__aenter__()

    async def __aexit__(self, *a: typing.Any) -> None:
        return await self.__impl.__aexit__(*a)

T = typing.TypeVar('T')

def streamify(func: typing.Callable[[Stream], typing.Awaitable[T]]) -> typing.Callable[[first_arg_type, second_arg_type], typing.Awaitable[T]]:
    @functools.wraps(func)
    async def wrapper(reader: first_arg_type, writer: second_arg_type = None) -> T:
        async with Stream(reader, writer) as sock:
            return await func(sock)
    return wrapper

