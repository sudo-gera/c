from __future__ import annotations
import asyncio
import typing
import ssl
import functools

import sign
signer = sign.Signer(8)

first_arg_type =  asyncio.StreamReader | tuple[asyncio.StreamReader, asyncio.StreamWriter]
second_arg_type = asyncio.StreamWriter|None

class StreamPlugin:
    def __init__(self, stream: Stream):
        self.stream = stream

    async def __aenter__(self) -> Stream:
        return self.stream

    async def __aexit__(self, *a: typing.Any) -> None:
        return await self.safe_close()

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
        self.stream.write(data)
        await self.stream.drain()


class Stream(asyncio.StreamReader, asyncio.StreamWriter, StreamPlugin):
    def __init__(self, reader: first_arg_type, writer: second_arg_type = None):
        if writer is None:
            assert isinstance(reader, tuple)
            reader, writer = reader
        assert isinstance(reader, asyncio.StreamReader)
        assert isinstance(writer, asyncio.StreamWriter)
        self.__reader = reader
        self.__writer = writer
        self.__plugin = StreamPlugin(self)

    def __dir__(self) -> list[str]:
        return dir(self.__reader) + dir(self.__writer) + dir(self.__plugin)

    @functools.cache
    def __getattribute__(self, name:str) -> typing.Any:
        if name.startswith(f'_Stream_') or name in 'safe_write safe_close send_msg recv_msg __aenter__ __aexit__'.split():
            return super().__getattribute__(name)
        a = [w for w in [self.__reader, self.__writer, self.__plugin] if name in dir(w)]
        assert len(a) == 1, name
        return getattr(a[0], name)

    def __repr__(self) -> str:
        return repr((self.__reader, self.__writer))

    def __del__(self) -> None:
        pass

T = typing.TypeVar('T')

def streamify(func: typing.Callable[[Stream], typing.Awaitable[T]]) -> typing.Callable[[first_arg_type, second_arg_type], typing.Awaitable[T]]:
    @functools.wraps(func)
    async def wrapper(reader: first_arg_type, writer: second_arg_type = None) -> T:
        async with Stream(reader, writer) as sock:
            return await func(sock)
    return wrapper

