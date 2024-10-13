import functools
import typing

@functools.lru_cache(2**16)
def has_never_seen_impl(data: typing.Any) -> list[bool]:
    return [True]

def has_never_seen(data: typing.Any) -> bool:
    z=has_never_seen_impl(data)
    d=z[0]
    z[0]=False
    return d
