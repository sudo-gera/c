from __future__ import annotations
from collections.abc import Callable as caCallable
import functools
from typing import *
import sys

############################################################################################################################

if sys.version_info < (3, 10):
    def call(obj: Any, /, *args: Any, **kwargs: Any) -> Any:
        return obj(*args, **kwargs)

elif sys.version_info < (3, 11):
    call_R = TypeVar("call_R")
    call_P = ParamSpec("call_P")
    def call(obj: caCallable[call_P, call_R], /, *args: call_P.args, **kwargs: call_P.kwargs) -> call_R:
        return obj(*args, **kwargs)

else:
    from operator import call

############################################################################################################################

if sys.version_info < (3, 10):
    cache_T = TypeVar("cache_T", bound=Callable[..., Any])
    def cache(func: cache_T) -> cache_T:
        return cast(cache_T, functools.cache(func))
else:
    cache_R = TypeVar("cache_R")
    cache_P = ParamSpec("cache_P")
    def cache(func: caCallable[cache_P, cache_R]) -> caCallable[cache_P, cache_R]:
        return cast(caCallable[cache_P, cache_R], functools.cache(func))

############################################################################################################################

checking_cast_t = TypeVar('checking_cast_t')

def checking_cast(t: type[checking_cast_t], val: Any) -> checking_cast_t:
    if not isinstance(val, t):
        raise TypeError(f"Value {val!r} is not instance of type {t!r}")
    return val
