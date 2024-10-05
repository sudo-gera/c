from __future__ import annotations
import asyncio
import typing
import ssl
import functools

first_arg_type =  asyncio.StreamReader | tuple[asyncio.StreamReader, asyncio.StreamWriter]
second_arg_type = asyncio.StreamWriter|None

class Stream(asyncio.StreamReader, asyncio.StreamWriter):
    def __init__(self, reader: first_arg_type, writer: second_arg_type = None):
        if writer is None:
            assert isinstance(reader, tuple)
            reader, writer = reader
        assert isinstance(reader, asyncio.StreamReader)
        assert isinstance(writer, asyncio.StreamWriter)
        self.__reader = reader
        self.__writer = writer

    def __dir__(self) -> list[str]:
        return dir(self.__reader) + dir(self.__writer)

    @functools.cache
    def __getattribute__(self, name:str) -> typing.Any:
        if name.startswith(f'_Stream_'):
            return super().__getattribute__(name)
        a = [w for w in [self.__reader, self.__writer] if name in dir(w)]
        assert len(a) == 1, name
        return getattr(a[0], name)

    def __repr__(self) -> str:
        return repr((self.__reader, self.__writer))

    async def __aenter__(self) -> Stream:
        return self

    async def __aexit__(self, *a: typing.Any) -> None:
        try:
            await self.drain()
            if self.can_write_eof():
                self.write_eof()
                await self.drain()
            self.close()
            try:
                await self.wait_closed()
            except ssl.SSLError as e:
                if e.reason != 'APPLICATION_DATA_AFTER_CLOSE_NOTIFY':
                    raise
        except (OSError, ConnectionResetError):
            pass

    def __del__(self) -> None:
        pass

T = typing.TypeVar('T')

def streamify(func: typing.Callable[[Stream], typing.Awaitable[T]]) -> typing.Callable[[first_arg_type, second_arg_type], typing.Awaitable[T]]:
    @functools.wraps(func)
    async def wrapper(reader: first_arg_type, writer: second_arg_type = None) -> T:
        async with Stream(reader, writer) as sock:
            return await func(sock)
    return wrapper

