from __future__ import annotations
from collections.abc import Callable as caCallable
from dataclasses import *
from typing import *
from itertools import *
from functools import *
from operator import *
from abc import ABC, abstractmethod
import numpy as np
import numbers

return_as_is_t = TypeVar('return_as_is_t')

def return_as_is(x: return_as_is_t) -> return_as_is_t:
    return x

autograd_jacobian = return_as_is if TYPE_CHECKING and abs(hash('-')) > -1 else None

if not TYPE_CHECKING:
    try:
        import autograd.numpy as np
        from autograd import jacobian as autograd_jacobian
    except ImportError:
        pass

ndarray = np.ndarray[Any, Any]

###########################################################################################################

class IValue(ABC):
    ...

    @property
    @abstractmethod
    def _to_ndarray(self) -> ndarray:
        ...

    def __add__(self, other: object) -> IValue:
        v1, v2 = prepare_one_level(self, other)
        return v1._add(v2)

    def __radd__(self, other: object) -> IValue:
        v1, v2 = prepare_one_level(other, self)
        return v1._add(v2)

    def __sub__(self, other: object) -> IValue:
        v1, v2 = prepare_one_level(self, other)
        return v1._sub(v2)

    def __rsub__(self, other: object) -> IValue:
        v1, v2 = prepare_one_level(other, self)
        return v1._sub(v2)

    def __mul__(self, other: object) -> IValue:
        v1, v2 = prepare_one_level(self, other)
        return v1._mul(v2)

    def __rmul__(self, other: object) -> IValue:
        v1, v2 = prepare_one_level(other, self)
        return v1._mul(v2)

    def __truediv__(self, other: object) -> IValue:
        v1, v2 = prepare_one_level(self, other)
        return v1._truediv(v2)

    def __rtruediv__(self, other: object) -> IValue:
        v1, v2 = prepare_one_level(other, self)
        return v1._truediv(v2)

    @abstractmethod
    def _mul(self, other: IValue) -> IValue:
        ...

    @abstractmethod
    def _add(self, other: IValue) -> IValue:
        ...

    @abstractmethod
    def _sub(self, other: IValue) -> IValue:
        ...

    @abstractmethod
    def _truediv(self, other: IValue) -> IValue:
        ...

    @abstractmethod
    def _tensordot(self, other: IValue, axes: tuple[list[int], list[int]]) -> IValue:
        ...

    @staticmethod
    def _bin_op(v1_object: object, v2_object: object, just_value_op: Callable[[JustValue, JustValue], IValue], tracer_op: Callable[[Tracer, Tracer], IValue]) -> IValue:
        v1, v2 = prepare_one_level(v1_object, v2_object)
        if isinstance(v1, JustValue) and isinstance(v2, JustValue):
            return just_value_op(v1, v2)
        if isinstance(v1, Tracer) and isinstance(v2, Tracer):
            return tracer_op(v1, v2)
        assert False

    @property
    @abstractmethod
    def shape(self) -> tuple[int, ...]:
        ...

    @property
    @abstractmethod
    def ndim(self) -> int:
        ...

    @property
    @abstractmethod
    def size(self) -> int:
        ...

    @abstractmethod
    def __neg__(self) -> IValue:
        ...

    @abstractmethod
    def __pos__(self) -> IValue:
        ...

    @abstractmethod
    def reshape(self, shape: tuple[int, ...]) -> IValue:
        ...

    @abstractmethod
    def broadcast_to(self, shape: tuple[int, ...]) -> IValue:
        ...

    @abstractmethod
    def __len__(self) -> int:
        ...

    @abstractmethod
    def __bool__(self) -> bool:
        ...

    @abstractmethod
    def __getitem__(self, index: Any) -> IValue:
        ...

    def __matmul__(self, other: object) -> IValue:
        return np_tensordot(self, other, ([-1], [-2]))

    def __rmatmul__(self, other: object) -> IValue:
        return np_tensordot(other, self, ([-1], [-2]))

    @abstractmethod
    def transpose(self, *axes: SupportsIndex | Iterable[SupportsIndex]) -> IValue:
        ...

    def sum(self, axes: Any = None) -> IValue:
        if axes is None:
            axes = tuple(range(self.ndim))
        assert axes is not None
        try:
            iter(axes)
        except TypeError:
            axes = (axes, )
        axes = tuple([int(axe) for axe in axes])
        assert isinstance(axes, tuple)
        return self._sum(axes)

    @abstractmethod
    def _sum(self, axes: tuple[int]) -> IValue:
        ...

    @abstractmethod
    def _sign(self) -> ndarray:
        ...

    def _abs(self) -> IValue:
        return self * self._sign()

    @abstractmethod
    def __pow__(self, other: float) -> IValue:
        ...

    @abstractmethod
    def _exp(self) -> IValue:
        ...

    @abstractmethod
    def _log(self) -> IValue:
        ...

###########################################################################################################

def np_sign(value: ndarray | IValue) -> ndarray:
    if isinstance(value, IValue):
        return value._sign()
    return cast(
        ndarray,
        np.sign(
            value
        )
    )

###########################################################################################################

log_t = TypeVar('log_t', bound=ndarray | IValue)

def np_log(value: log_t) -> log_t:
    if isinstance(value, IValue):
        return cast(
            log_t,
            value._log()
        )
    return cast(
        log_t,
        np.log(
            cast(
                ndarray,
                value
            ),
        )
    )

###########################################################################################################

exp_t = TypeVar('exp_t', bound=ndarray | IValue)

def np_exp(value: exp_t) -> exp_t:
    if isinstance(value, IValue):
        return cast(
            exp_t,
            value._exp()
        )
    return cast(
        exp_t,
        np.exp(
            cast(
                ndarray,
                value
            ),
        )
    )

###########################################################################################################

abs_t = TypeVar('abs_t', bound=ndarray | IValue)

def np_abs(value: abs_t) -> abs_t:
    if isinstance(value, IValue):
        return cast(
            abs_t,
            value._abs()
        )
    return cast(
        abs_t,
        np.abs(
            cast(
                ndarray,
                value
            ),
        )
    )

###########################################################################################################

def np_clip(x: IValue | ndarray, lo: float, hi: float) -> IValue | ndarray:
    return (
        (x + lo + np_abs(x - lo)) / 2
        - (x + hi + np_abs(x - hi)) / 2
        + hi
    )

###########################################################################################################

sum_t = TypeVar('sum_t', bound=ndarray | IValue)

def np_sum(value: sum_t, axes: Iterable[SupportsIndex] | SupportsIndex | None = None) -> sum_t:
    if isinstance(value, IValue):
        return cast(
            sum_t,
            value.sum(axes)
        )
    return cast(
        sum_t,
        np.sum(
            cast(
                ndarray,
                value
            ),
            cast(
                None,
                axes
            )
        )
    )

###########################################################################################################

def prepare_one_level(*arg_objects: object) -> tuple[IValue, ...]:
    args = [arg if isinstance(arg, IValue) else JustValue(np.array(arg)) for arg in arg_objects]
    tracers = [arg for arg in args if isinstance(arg, Tracer)]
    if not tracers:
        return tuple(args)
    args = [tracers[0]._from_constant(arg) if isinstance(arg, JustValue) else arg for arg in args]
    return tuple(args)

###########################################################################################################

transpose_t = TypeVar('transpose_t')

def np_transpose(value: transpose_t, axes: Iterable[SupportsIndex] = ()) -> transpose_t:
    if isinstance(value, IValue):
        return cast(
            transpose_t,
            value.transpose(*axes)
        )
    return cast(
        transpose_t,
        np.transpose(
            cast(
                ndarray,
                value
            ),
            list(axes)
        )
    )

###########################################################################################################

def np_shape(value: object) -> tuple[int, ...]:
    if isinstance(value, IValue):
        return value.shape
    return np.shape(
        cast(
            ndarray,
            value
        )
    )

###########################################################################################################

def tensordot_parse_axes(v1_shape: tuple[int, ...], v2_shape: tuple[int, ...], axes: Any) -> tuple[list[int], list[int]]:
    v1_axes: Any
    v2_axes: Any
    try:
        iter(axes)
    except Exception:
        v1_axes = list(range(-axes, 0))
        v2_axes = list(range(0, axes))
    else:
        v1_axes, v2_axes = axes
    try:
        v1_axes = list(v1_axes)
    except TypeError:
        v1_axes = [v1_axes]
    try:
        v2_axes = list(v2_axes)
    except TypeError:
        v2_axes = [v2_axes]

    assert len(v1_axes) == len(v2_axes)

    for v1_axe, v2_axe in zip(v1_axes, v2_axes):
        assert v1_shape[v1_axe] == v2_shape[v2_axe]

    v1_axes = [v1_axe % len(v1_shape) for v1_axe in v1_axes]
    v2_axes = [v2_axe % len(v2_shape) for v2_axe in v2_axes]

    return v1_axes, v2_axes

@overload
def np_tensordot(v1: IValue, v2: object | IValue, axes: Any = 2) -> IValue:
    ...

@overload
def np_tensordot(v1: object | IValue, v2: IValue, axes: Any = 2) -> IValue:
    ...

@overload
def np_tensordot(v1: object, v2: object, axes: Any = 2) -> object:
    ...

def np_tensordot(v1: object | IValue, v2: object | IValue, axes: Any = 2) -> ndarray | IValue:
    parsed_axes = tensordot_parse_axes(np_shape(v1), np_shape(v2), axes)
    if isinstance(v1, IValue) or isinstance(v2, IValue):
        v1, v2 = prepare_one_level(v1, v2)
        return v1._tensordot(v2, parsed_axes)
    return cast(
        ndarray,
        np.tensordot(
            cast(
                ndarray,
                v1,
            ),
            cast(
                ndarray,
                v2,
            ),
            parsed_axes
        )
    )

###########################################################################################################

@dataclass(frozen=True)
class JustValue(IValue):
    value: ndarray

    def __post_init__(self) -> None:
        if isinstance(self.value, np.ndarray):
            self.value.flags.writeable=False
        assert self.value.dtype != object

    @property
    def shape(self) -> tuple[int, ...]:
        return cast(
            tuple[int, ...],
            self.value.shape
        )

    @property
    def ndim(self) -> int:
        return self.value.ndim

    @property
    def size(self) -> int:
        return self.value.size

    def reshape(self, shape: tuple[int, ...]) -> JustValue:
        return JustValue(
            self.value.reshape(shape)
        )

    def broadcast_to(self, shape: tuple[int, ...]) -> JustValue:
        return JustValue(
            np.broadcast_to(
                self.value,
                shape,
            )
        )

    def __len__(self) -> int:
        return len(self.value)

    def __bool__(self) -> bool:
        return bool(self.value)

    def __neg__(self) -> JustValue:
        return JustValue(
            -self.value
        )

    def __pos__(self) -> JustValue:
        return self

    def __getitem__(self, index: Any) -> JustValue:
        return JustValue(
            cast(
                ndarray,
                self.value[index]
            )
        )

    @property
    def _to_ndarray(self) -> ndarray:
        return self.value

    def _add(v1: JustValue, v2: IValue) -> JustValue:
        assert isinstance(v2, JustValue)
        return JustValue(
            v1.value + v2.value
        )

    def _sub(v1: JustValue, v2: IValue) -> JustValue:
        assert isinstance(v2, JustValue)
        return JustValue(
            v1.value - v2.value
        )

    def _mul(v1: JustValue, v2: IValue) -> JustValue:
        assert isinstance(v2, JustValue)
        return JustValue(
            v1.value * v2.value
        )

    def _truediv(v1: JustValue, v2: IValue) -> JustValue:
        assert isinstance(v2, JustValue)
        return JustValue(
            v1.value / v2.value
        )

    def _tensordot(v1: JustValue, v2: IValue, axes: tuple[list[int], list[int]]) -> JustValue:
        assert isinstance(v2, JustValue)
        return JustValue(
            cast(
                ndarray,
                np.tensordot(
                    v1.value,
                    v2.value,
                    axes,
                )
            )
        )

    def transpose(self, *axes: SupportsIndex | Iterable[SupportsIndex]) -> IValue:
        parsed_axes = list(np.array(axes).flat)
        parsed_axes = [axe % self.ndim for axe in parsed_axes]
        # print(self.value.ndim, parsed_axes)
        return JustValue(
            self.value.transpose(*parsed_axes)
        )

    def _sum(self, axes: tuple[int]) -> IValue:
        return JustValue(
            cast(
                ndarray,
                self.value.sum(axes)
            )
        )

    def _sign(self) -> ndarray:
        return cast(
            ndarray,
            np.sign(self.value)
        )

    def __pow__(self, other: float) -> IValue:
        return JustValue(
            cast(
                ndarray,
                self.value ** other
            )
        )

    def _exp(self) -> IValue:
        return JustValue(
            cast(
                ndarray,
                np.exp(self.value)
            )
        )

    def _log(self) -> IValue:
        return JustValue(
            cast(
                ndarray,
                np.log(self.value)
            )
        )

###########################################################################################################

@dataclass(frozen=True)
class Tracer(IValue):
    jacobian: IValue
    value: IValue

    def __post_init__(self) -> None:
        assert self.jacobian.shape[:len(self.value.shape)] == self.value.shape

    @staticmethod
    def _from_variable_and_level(value: IValue, level: int) -> IValue:
        return Tracer(
            JustValue(
                np.eye(value.size).reshape(value.shape * 2)
            ),
            value,
        )

    @property
    def _to_ndarray(self) -> ndarray:
        return self.value._to_ndarray

    @property
    def __input_shape(self) -> tuple[int, ...]:
        return self.jacobian.shape[len(self.value.shape):]

    @property
    def shape(self) -> tuple[int, ...]:
        return self.value.shape

    @property
    def ndim(self) -> int:
        return self.value.ndim

    @property
    def size(self) -> int:
        return self.value.size

    def reshape(self, shape: tuple[int, ...]) -> Tracer:
        return Tracer(
            self.jacobian.reshape(shape + self.__input_shape),
            self.value.reshape(shape),
        )

    def broadcast_to(self, shape: tuple[int, ...]) -> Tracer:
        return Tracer(
            self.jacobian.broadcast_to(
                shape + self.__input_shape,
            ),
            self.value.broadcast_to(
                shape,
            ),
        )

    def __broadcast_value_to_jacobian(self, value: IValue) -> IValue:
        return value.reshape(
            value.shape + (1, ) * len(self.__input_shape)
        ).broadcast_to(
            self.jacobian.shape,
        )

    def _from_constant(self, value: JustValue) -> Tracer:
        return Tracer(
            JustValue(
                np.zeros(value.shape + self.__input_shape)
            ),
            value,
        )

    def __bool__(self) -> bool:
        return bool(self.value)

    def __len__(self) -> int:
        return len(self.value)

    @staticmethod
    def __broadcast_to_each_other(*ts: Tracer) -> tuple[Tracer, ...]:
        value_shape = np.broadcast_shapes(*[t.shape for t in ts])
        ts = tuple([t.broadcast_to(value_shape) for t in ts])
        assert len({t.shape for t in ts}) == 1
        assert len({t.jacobian.shape for t in ts}) == 1
        return ts

    def _add(v1: Tracer, v2: IValue) -> Tracer:
        assert isinstance(v2, Tracer)
        v1, v2 = Tracer.__broadcast_to_each_other(v1, v2)
        return Tracer(
            v1.jacobian + v2.jacobian,
            v1.value + v2.value,
        )

    def _sub(v1: Tracer, v2: IValue) -> Tracer:
        assert isinstance(v2, Tracer)
        v1, v2 = Tracer.__broadcast_to_each_other(v1, v2)
        return Tracer(
            v1.jacobian - v2.jacobian,
            v1.value - v2.value,
        )

    def __neg__(self) -> Tracer:
        return Tracer(
            -self.jacobian,
            -self.value,
        )

    def __pos__(self) -> Tracer:
        return self

    def _mul(v1: Tracer, v2: IValue) -> Tracer:
        assert isinstance(v2, Tracer)
        v1, v2 = Tracer.__broadcast_to_each_other(v1, v2)
        return Tracer(
            v1.jacobian * v1.__broadcast_value_to_jacobian(v2.value)
            +
            v2.jacobian * v2.__broadcast_value_to_jacobian(v1.value),
            v1.value * v2.value,
        )

    def _truediv(v1: Tracer, v2: IValue) -> Tracer:
        assert isinstance(v2, Tracer)
        v1, v2 = Tracer.__broadcast_to_each_other(v1, v2)
        tmp1 = Tracer(
            v1.jacobian * v1.__broadcast_value_to_jacobian(v2.value)
            -
            v2.jacobian * v2.__broadcast_value_to_jacobian(v1.value),
            v1.value / v2.value,
        )
        tmp2 = tmp1.__broadcast_value_to_jacobian(v2.value)
        return Tracer(
            tmp1.jacobian / tmp2 / tmp2,
            tmp1.value,
        )

    def _tensordot(v1: Tracer, v2: IValue, axes: tuple[list[int], list[int]]) -> Tracer:
        assert isinstance(v2, Tracer)
        tj1 = np_tensordot(
            v1.jacobian,
            v2.value,
            axes
        )
        v1_ndim = v1.ndim - len(axes[0])
        in_ndim = len(v1.__input_shape)
        v2_ndim = v2.ndim - len(axes[1])
        assert tj1.ndim == v1_ndim + in_ndim + v2_ndim
        tj1_old_axes = [*range(tj1.ndim)]
        tj1_new_axes = (
            tj1_old_axes[:v1_ndim]
                +
            tj1_old_axes[v1_ndim+in_ndim:]
                +
            tj1_old_axes[v1_ndim:v1_ndim+in_ndim]

        )
        assert set(tj1_new_axes) == set(tj1_old_axes)
        assert len(set(tj1_new_axes)) == len(tj1_new_axes)
        # print(tj1.ndim, tj1_new_axes)
        tj1 = tj1.transpose(tj1_new_axes)
        return Tracer(
            tj1 + np_tensordot(
                v1.value,
                v2.jacobian,
                axes
            ),
            np_tensordot(v1.value, v2.value, axes),
        )

    def __getitem__(self, index: Any) -> Tracer:
        return Tracer(
            self.jacobian[index],
            self.value[index],
        )

    def transpose(self, *axes: SupportsIndex | Iterable[SupportsIndex]) -> IValue:
        parsed_axes = [int(axe) % self.ndim for axe in list(np.array(axes).flat)]
        return Tracer(
            self.jacobian.transpose(parsed_axes + list(range(self.value.ndim, self.jacobian.ndim))),
            self.value.transpose(parsed_axes),
        )

    def _sum(self, axes: tuple[int]) -> IValue:
        return Tracer(
            self.jacobian._sum(axes),
            self.value._sum(axes),
        )

    def _sign(self) -> ndarray:
        return self.value._sign()

    def __pow__(self, other: float) -> IValue:
        return Tracer(
            self.__broadcast_value_to_jacobian(
                other * self.value ** (other-1)
            ) * self.jacobian,
            self.value ** other,
        )

    def _exp(self) -> IValue:
        return Tracer(
            self.__broadcast_value_to_jacobian(
                self.value._exp()
            ) * self.jacobian,
            self.value._exp(),
        )

    def _log(self) -> IValue:
        return Tracer(
            self.__broadcast_value_to_jacobian(
                1 / self.value
            ) * self.jacobian,
            self.value._log(),
        )

##############################################################################################

def _jacobian_impl(level: int, func: Callable[[ndarray | IValue], ndarray | IValue], x_ndarray: ndarray) -> ndarray:

    x : IValue = JustValue(x_ndarray)

    for i in range(level)[::-1]:
        x = Tracer._from_variable_and_level(x, i)

    result_any = func(x)

    result: IValue = result_any if isinstance(result_any, IValue) else JustValue(result_any)

    for i in range(level):

        if isinstance(result, Tracer):
            result = result.jacobian
        else:
            result = JustValue(np.zeros(result.shape + x.shape))

    return result._to_ndarray

##############################################################################################

@dataclass(frozen=True)
class manual_jacobian:
    func: Callable[[ndarray | IValue], ndarray | IValue] | manual_jacobian

    def __call__(self, x: ndarray) -> ndarray:
        return _jacobian_impl(self._level(), self._func(), x)

    def _func(self) -> Callable[[ndarray | IValue], ndarray | IValue]:
        if isinstance(self.func, manual_jacobian):
            return self.func._func()
        return self.func

    def _level(self) -> int:
        if isinstance(self.func, manual_jacobian):
            return self.func._level() + 1
        return 1

##############################################################################################

if __name__ == '__main__':

    def same(_a: Any, _s: Any, rtol: float = 1e-05, atol: float = 1e-08, equal_nan: bool = False) -> bool:
        a = np.array(_a)
        s = np.array(_s)
        if a.shape == s.shape and np.allclose(a, s, rtol, atol, equal_nan):
            return True
        print()
        print()
        print()
        print()
        print()
        print()
        print(repr(a))
        print()
        print()
        print()
        print()
        print()
        print()
        print(repr(s))
        print()
        print()
        print()
        print()
        print()
        print()
        return False

    class jacobian_test_wrapper(manual_jacobian):

        def __call__(self, x: ndarray) -> ndarray:
            result = super().__call__(x)
            if autograd_jacobian is not None:
                f = self._func()
                for i in range(self._level()):
                    f = autograd_jacobian(f)
                assert same(f(x), result), "!!!! original autograd disagrees !!!!"
            return result

##############################################################################################

    def test1() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return np.array([5])

        value = np.array([4])
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = [5], [[0]]
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test1()

    def test2() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x
            )
        value = np.array(4)
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = 4, 1
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test2()

    def test3() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x+3
            )
        value = np.array(4.)
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = 7., 1.
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test3()

    def test4() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x*3
            )
        value = np.array(4.)
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = 12, 3
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test4()

    def test5() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x
            )
        value = np.array((4., 5.))
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = (4, 5), ((1, 0), (0, 1))
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test5()

    def test6() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x*x
            )
        value = np.array((4., 5.))
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = (16, 25), ((8, 0), (0, 10))
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test6()

    def test7() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x*x[::-1]
            )
        value = np.array((4., 5.))
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = (20, 20), ((5, 4), (5, 4))
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test7()

    def test8() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x[0]
            )
        value = np.array((4., 5.))
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = 4, (1, 0)
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test8()

    def test9() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x[1]
            )
        value = np.array((4., 5.))
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = 5, (0, 1)
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test9()

    def test10() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x[0]+x[1]
            )
        value = np.array((4., 5.))
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = np.array(9.), np.array((1., 1.))
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
        assert value1.shape + value.shape == jacobian1.shape
        assert value2.shape + value.shape == jacobian2.shape
    test10()

    def test11() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x[0]*x[1]
            )
        value = np.array((4., 5.))
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = np.array(20), np.array((5, 4))
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
        assert value1.shape + value.shape == jacobian1.shape
        assert value2.shape + value.shape == jacobian2.shape
    test11()

    def test12() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                (
                    x.reshape((4,1)) * x.reshape((1,4))
                ).reshape((8, 2))[3:5, :]
            )
        value = np.array( [ [3, 5], [7, 11] ] )
        result = np.array( [ [ 35, 55 ], [ 21, 35 ] ] )
        jac = np.array(
            [
                [
                    [ [ 0, 7 ], [ 5, 0 ] ], [ [ 0, 11 ],[ 0, 5 ] ],
                ],
                [
                    [ [ 7, 0 ], [ 3, 0 ] ], [ [ 0, 7 ], [ 5, 0 ] ],
                ]
            ]
        )
        assert same(                                                                f  (value), result )
        assert same(result.shape + value.shape, jac.shape)
        assert same(result.shape + value.shape, jacobian_test_wrapper(f)(value).shape)
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
    test12()

    def test13() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x,
            )
        value = np.array( [ [3, 5], [7, 11], [13, 17] ] )
        result = np.array( [ [3, 5], [7, 11], [13, 17] ] )
        jac = np.array(
            [
                [ [ [ 1, 0 ], [ 0, 0 ], [ 0, 0, ] ], [ [ 0, 1 ], [ 0, 0 ], [ 0, 0 ] ] ],
                [ [ [ 0, 0 ], [ 1, 0 ], [ 0, 0, ] ], [ [ 0, 0 ], [ 0, 1 ], [ 0, 0 ] ] ],
                [ [ [ 0, 0 ], [ 0, 0 ], [ 1, 0, ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 1 ] ] ],
            ]
        )
        assert same(                                                                f  (value), result )
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
        assert result.shape + value.shape == jac.shape
        assert result.shape + value.shape == jacobian_test_wrapper(f)(value).shape
    test13()

    def test14() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                (
                    x.reshape((1,2)) * x.reshape((2, 1))
                )[0][1],
            )
        value = np.array( [3., 5.] )
        result = np.array( 15 )
        jac = np.array( [ 5, 3 ] )
        assert same(                                                                f  (value), result )
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
        assert result.shape + value.shape == jac.shape
        assert result.shape + value.shape == jacobian_test_wrapper(f)(value).shape
    test14()

    def test15() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x[0] * x[1],
            )
        value = np.array( [3., 5.] )
        result = np.array( 15 )
        jac = np.array( [ 5, 3 ] )
        assert same(                                                                f  (value), result )
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
        assert result.shape + value.shape == jac.shape
        assert result.shape + value.shape == jacobian_test_wrapper(f)(value).shape
    test15()

    def test16() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x.reshape((2,1))
            )
        value = np.array( [ [3, 5] ] )
        result = np.array( [ [ 3 ], [ 5 ] ] )
        jac = np.array(
            [
                [ [ [ 1, 0 ] ] ],
                [ [ [ 0, 1 ] ] ]
            ]
        )
        assert same(                                                                f  (value), result )
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
        assert result.shape + value.shape == jacobian_test_wrapper(f)(value).shape
        assert result.shape + value.shape == jac.shape
    test16()

    def test17() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x.reshape((2,1))
            )
        value = np.array( [ [3, 5] ] )
        result = np.array( [ [ 3 ], [ 5 ] ] )
        jac = np.array(
            [
                [ [ [ 1, 0 ] ] ],
                [ [ [ 0, 1 ] ] ]
            ]
        )
        assert same(                                                                f  (value), result )
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
        assert result.shape + value.shape == jacobian_test_wrapper(f)(value).shape
        assert result.shape + value.shape == jac.shape
    test17()

    def test18() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return np.array([5])

        value = np.array( [4] )
        result0 = np.array( [5] )
        result1 = np.array( [[0]] )
        result2 = np.array( [[[0]]] )
        assert same(                                                    f (value), result0 )
        assert same(value.shape + result0.shape, result1.shape)
        assert same(                             jacobian_test_wrapper(f) (value), result1 )
        assert same(value.shape + result1.shape, result2.shape)
        assert same(      jacobian_test_wrapper(jacobian_test_wrapper(f)) (value), result2  )
    test18()

    def test19() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return np.array([5])

        value = np.array( [4, 7] )
        result0 = np.array( [5] )
        result1 = np.array( [[0, 0]] )
        result2 = np.array( [[[0,0],[0,0]]] )
        result3 = np.array( [[[[0,0],[0,0]],[[0,0],[0,0]]]] )
        assert same(                                                                     f   (value), result0  )
        assert same(result0.shape + value.shape, result1.shape)
        assert same(                                              jacobian_test_wrapper(f)   (value), result1  )
        assert same(result1.shape + value.shape, result2.shape)
        assert same(                        jacobian_test_wrapper(jacobian_test_wrapper(f))  (value), result2  )
        assert same(result2.shape + value.shape, result3.shape)
        assert same(  jacobian_test_wrapper(jacobian_test_wrapper(jacobian_test_wrapper(f))) (value), result3  )
    test19()

    def test20() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x
            )

        value = np.array( [4, 7] )
        result0 = np.array( [4, 7] )
        result1 = np.array( [[1, 0], [0, 1]] )
        result2 = np.array( [[[0, 0], [0, 0]], [[0, 0], [0, 0]]] )
        result3 = np.array( [[[[0, 0], [0, 0]], [[0, 0], [0, 0]]], [[[0, 0], [0, 0]], [[0, 0], [0, 0]]]] )
        assert same(                                                                     f   (value), result0  )
        assert same(result0.shape + value.shape, result1.shape)
        assert same(                                              jacobian_test_wrapper(f)   (value), result1  )
        assert same(result1.shape + value.shape, result2.shape)
        assert same(                        jacobian_test_wrapper(jacobian_test_wrapper(f))  (value), result2  )
        assert same(result2.shape + value.shape, result3.shape)
        assert same(  jacobian_test_wrapper(jacobian_test_wrapper(jacobian_test_wrapper(f))) (value), result3  )
    test20()

    def test21() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                (
                    x.reshape((4,1)) * x.reshape((1,4))
                ).reshape((8, 2))[3:5, :] - x
            )

        value = np.array( [ [3, 5], [7, 11] ] )
        result0 = np.array( [[32, 50], [14, 24]] )
        result1 = np.array( [[[[-1, 7], [5, 0]], [[0, 10], [0, 5]]], [[[7, 0], [2, 0]], [[0, 7], [5, -1]]]] )
        result2 = np.array(
            [
                [
                    [
                        [[[0., 0.], [0., 0.]], [[0., 0.], [1., 0.]]],
                        [[[0., 1.], [0., 0.]], [[0., 0.], [0., 0.]]]
                    ],
                    [
                        [[[0., 0.], [0., 0.]], [[0., 0.], [0., 1.]]],
                        [[[0., 0.], [0., 0.]], [[0., 1.], [0., 0.]]]
                    ]
                ],[
                    [
                        [[[0., 0.], [1., 0.]], [[0., 0.], [0., 0.]]],
                        [[[1., 0.], [0., 0.]], [[0., 0.], [0., 0.]]]
                    ], [
                        [[[0., 0.], [0., 0.]], [[0., 0.], [1., 0.]]],
                        [[[0., 1.], [0., 0.]], [[0., 0.], [0., 0.]]]
                    ]
                ]
            ]
        )

        result3 = np.zeros((2,2,2,2,2,2,2,2))
        assert same(                                                                     f   (value), result0  )
        assert same(result0.shape + value.shape, result1.shape)
        assert same(                                              jacobian_test_wrapper(f)   (value), result1  )
        assert same(result1.shape + value.shape, result2.shape)
        assert same(                        jacobian_test_wrapper(jacobian_test_wrapper(f))  (value), result2  )
        assert same(result2.shape + value.shape, result3.shape)
        assert same(  jacobian_test_wrapper(jacobian_test_wrapper(jacobian_test_wrapper(f))) (value), result3  )
    test21()

    def test22() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                (
                    x[0:5, 0:3] @ x[5:8, 0:2]
                )
            )

        value = np.array(
            [
                [ 2,  3,  5],
                [ 7, 11, 13],
                [17, 19, 23],
                [29, 31, 37],
                [41, 43, 47],

                [53, 59, 61],
                [67, 71, 73],
                [79, 83, 89]
            ]
        )
        result0 = np.array(
            [
                [ 702,  746],
                [2135, 2273],
                [3991, 4261],
                [6537, 6983],
                [8767, 9373]
            ]
        )
        result1 = np.array(
            [
                [
                    [
                        [53., 67., 79.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 2.,  0.,  0.],
                        [ 3.,  0.,  0.],
                        [ 5.,  0.,  0.]
                    ], [
                        [59., 71., 83.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  2.,  0.],
                        [ 0.,  3.,  0.],
                        [ 0.,  5.,  0.]
                    ]
                ], [
                    [
                        [ 0.,  0.,  0.],
                        [53., 67., 79.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 7.,  0.,  0.],
                        [11.,  0.,  0.],
                        [13.,  0.,  0.]
                    ], [
                        [ 0.,  0.,  0.],
                        [59., 71., 83.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  7.,  0.],
                        [ 0., 11.,  0.],
                        [ 0., 13.,  0.]
                    ]
                ], [
                    [
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [53., 67., 79.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [17.,  0.,  0.],
                        [19.,  0.,  0.],
                        [23.,  0.,  0.]
                    ], [
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [59., 71., 83.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0., 17.,  0.],
                        [ 0., 19.,  0.],
                        [ 0., 23.,  0.]
                    ]
                ], [
                    [
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [53., 67., 79.],
                        [ 0.,  0.,  0.],
                        [29.,  0.,  0.],
                        [31.,  0.,  0.],
                        [37.,  0.,  0.]
                    ], [
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [59., 71., 83.],
                        [ 0.,  0.,  0.],
                        [ 0., 29.,  0.],
                        [ 0., 31.,  0.],
                        [ 0., 37.,  0.]
                    ]
                ], [
                    [
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [53., 67., 79.],
                        [41.,  0.,  0.],
                        [43.,  0.,  0.],
                        [47.,  0.,  0.]
                    ], [
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [ 0.,  0.,  0.],
                        [59., 71., 83.],
                        [ 0., 41.,  0.],
                        [ 0., 43.,  0.],
                        [ 0., 47.,  0.]
                    ]
                ]
            ]
        )
        assert same(                                                                     f   (value), result0  )
        assert same(result0.shape + value.shape, result1.shape)
        assert same(                                              jacobian_test_wrapper(f)   (value), result1  )
        jacobian_test_wrapper(jacobian_test_wrapper(f))  (value)
        jacobian_test_wrapper(jacobian_test_wrapper(jacobian_test_wrapper(f))) (value)

    test22()

    def test23() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                x[0] / x[1]
            )

        value = np.array( [7., 5.] )
        result0 = np.array( 1.4 )
        result1 = np.array( [0.2, -0.28] )
        result2 = np.array(
            [
                [ 0.   , -0.04 ],
                [-0.04 ,  0.112]
            ]
        )
        result3 = np.array(
            [
                [
                    [ 0.    ,  0.    ],
                    [ 0.    ,  0.016 ]
                ],
                [
                    [ 0.    ,  0.016 ],
                    [ 0.016 , -0.0672]
                ]
            ]
        )
        assert same(                                                                     f   (value), result0  )
        assert same(result0.shape + value.shape, result1.shape)
        assert same(                                              jacobian_test_wrapper(f)   (value), result1  )
        assert same(result1.shape + value.shape, result2.shape)
        assert same(                        jacobian_test_wrapper(jacobian_test_wrapper(f))  (value), result2  )
        assert same(result2.shape + value.shape, result3.shape)
        assert same(  jacobian_test_wrapper(jacobian_test_wrapper(jacobian_test_wrapper(f))) (value), result3  )
    test23()

    def test24() -> None:
        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                np_log(x)
            )

        value = np.array( 25. )
        result0 = np.array( 3.21887582 )
        result1 = np.array( 0.04 )
        result2 = np.array( -0.0016 )
        result3 = np.array( 0.000128 )
        assert same(                                                                     f   (value), result0  )
        assert same(result0.shape + value.shape, result1.shape)
        assert same(                                              jacobian_test_wrapper(f)   (value), result1  )
        assert same(result1.shape + value.shape, result2.shape)
        assert same(                        jacobian_test_wrapper(jacobian_test_wrapper(f))  (value), result2  )
        assert same(result2.shape + value.shape, result3.shape)
        assert same(  jacobian_test_wrapper(jacobian_test_wrapper(jacobian_test_wrapper(f))) (value), result3  )
    test24()

    def test25() -> None:

        def leaky_relu(x: ndarray | IValue) -> ndarray | IValue:
            return np_abs(x) * 0.495 + x * 0.505

        def pow_act(x: ndarray | IValue) -> ndarray | IValue:
            return np_abs(x) ** 0.2 * np_sign(x)

        def sigmoid(x: ndarray | IValue) -> ndarray | IValue:
            return 1 / (1 + np_exp(-x))

        def as_is_act(x: ndarray | IValue) -> ndarray | IValue:
            return x

        def tanh(x: ndarray | IValue) -> ndarray | IValue:
            return (np_exp(x) - np_exp(-x)) / (np_exp(x) + np_exp(-x))

        wslices = [
            (0, slice(0, 2), slice(0, 3)),
            (2, slice(0, 3), slice(0, 3)),
            (4, slice(0, 3), slice(0, 1)),
        ]

        bslices = [
            (1, 0, slice(0, 3)),
            (3, 0, slice(0, 3)),
            (5, 0, slice(0, 1)),
        ]

        activators = [
            leaky_relu,
            leaky_relu,
            sigmoid,
        ]

        assert len(wslices) == len(bslices) == len(activators)

        def neural_net(x: ndarray | IValue, ws: ndarray | IValue) -> ndarray | IValue:
            x = x.reshape((1, x.size))
            for s, b, act in zip(wslices, bslices, activators):
                x = ws[s].__rmatmul__(x)
                x = x + ws[b]
                x = act(x)
            x = x.reshape(())
            return x

        def error(x: ndarray | IValue, ws: ndarray | IValue, ans: ndarray) -> ndarray | IValue:
            y = neural_net(x, ws)
            y = np_clip(y, 0.001, 0.999)
            return -(np_log(y) * ans + np_log(1 - y) * (1 - ans))

        training = [
            ([0, 0], 0),
            ([0, 1], 1),
            ([1, 0], 1),
            ([1, 1], 0),
        ]

        def avg_error(ws: ndarray | IValue) -> ndarray | float | IValue:
            errs = [
                error(np.array(x), ws, np.array(ans))
                for x, ans in training
            ]
            return sum(errs) / len(errs)

        def f(x: ndarray | IValue) -> ndarray:
            return cast(
                ndarray,
                avg_error(x)
            )

        ws : ndarray = np.ones((6, 3, 3))
        ws = np.arange(ws.size).reshape(ws.shape) - ws.size/2
        ws = ws / ws.sum()
        v = np.zeros_like(ws)
        for q in range(999):
            d = jacobian_test_wrapper(f)(ws)
            # print(f"err = {f(ws):5.3f} d(err) = {np_abs(d).sum():5.3f}")
            v = 0.9 * v - 1.0 * d
            ws = ws + v

        for x, ans in training:
            # print(f"{x = }, {neural_net(np.array(x), ws) = :5.3f}, {ans = }")
            assert same(neural_net(np.array(x), ws), ans, atol=0.001)

    test25()

