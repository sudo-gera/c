from __future__ import annotations
from collections.abc import Callable as caCallable
from dataclasses import *
from typing import *
from itertools import *
from functools import *
from operator import *
from abc import ABC, abstractmethod
import numpy as np

return_same_t = TypeVar('return_same_t')

def return_same(x: return_same_t) -> return_same_t:
    return x

autograd_jacobian = return_same if TYPE_CHECKING and abs(hash('-')) > -1 else None

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
    def value_ivalue(self) -> IValue:
        ...

    @property
    @abstractmethod
    def value_ndarray(self) -> ndarray:
        ...

    # @property
    # @abstractmethod
    # def jacobian_ivalue(self) -> IValue:
    #     ...

    # @property
    # @abstractmethod
    # def jacobian_ndarray(self) -> ndarray:
    #     ...

    def __mul__(self, other: object) -> IValue:
        if not isinstance(other, IValue):
            other = JustValue(np.array(other))
        assert isinstance(other, IValue)
        ivalue_mul(self, other)

    # @staticmethod
    # def make_equal_level(v1: IValue, v2: IValue) -> tuple[IValue, IValue]:
    #     if v1._value_level == v2._value_level:
    #         return v1, v2

    #     vmin = v1 if v1._value_level < v2._value_level else v2
    #     vmax = v1 if v1._value_level > v2._value_level else v2

    #     assert isinstance(vmin, Tracer)

    #     if vmax._value_level != JustValue._value_level:
    #         assert vmin._value_level + 1 == vmax._value_level
        
    #     vmax = vmin.upgrade(vmax)

    #     return vmin, vmax if vmin is v1 else vmax, vmin



    #     return type(higher_level).mul(self, other)

    @property
    @abstractmethod
    def _value_level(self) -> int | float:
        ...

    # @staticmethod
    # @abstractmethod
    # def mul(v1: IValue, v2: IValue) -> IValue:
    #     ...


    @property
    @abstractmethod
    def shape(self) -> tuple[int, ...]:
        ...

    @property
    @abstractmethod
    def size(self) -> int:
        ...

    @abstractmethod
    def __neg__(self) -> IValue:
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

###########################################################################################################

@dataclass(frozen=True)
class JustValue(IValue):
    value_: ndarray

    def __post_init__(self) -> None:
        if isinstance(self.value_, np.ndarray):
            self.value_.flags.writeable=False

    @property
    def shape(self) -> tuple[int, ...]:
        return cast(
            tuple[int, ...],
            self.value_.shape
        )

    @property
    def size(self) -> int:
        return self.value_.size

    def reshape(self, shape: tuple[int, ...]) -> JustValue:
        return JustValue(
            self.value_.reshape(shape)
        )

    def broadcast_to(self, shape: tuple[int, ...]) -> JustValue:
        return JustValue(
            np.broadcast_to(
                self.value_,
                shape,
            )
        )

    def __len__(self) -> int:
        return len(self.value_)

    def __bool__(self) -> bool:
        return bool(self.value_)

    def __neg__(self) -> JustValue:
        return JustValue(
            cast(
                ndarray,
                -self.value_
            )
        )

    @property
    def value_ndarray(self) -> ndarray:
        return self.value_

    @property
    def value_ivalue(self) -> IValue:
        return to_value(self.value_)

    _value_level = float('inf')

def to_value(x: ndarray | IValue) -> IValue:
    if isinstance(x, IValue):
        return x
    return JustValue(x)

###########################################################################################################

@dataclass(frozen=True)
class Tracer(IValue):
    jacobian_: IValue
    value_: IValue

    @property
    def _value_level(self) -> int | float:
        return 0

    @staticmethod
    def from_x_and_level(x: IValue, level: int) -> IValue:
        assert level == 0
        return x

    @staticmethod
    def from_just_value_or_ndarray(a: IValue | ndarray, s: IValue | ndarray) -> Tracer:
        return Tracer(to_value(a), to_value(s))

    @property
    def jacobian_ndarray(self) -> ndarray:
        return to_value(self.jacobian_).value_ndarray

    @property
    def value_ndarray(self) -> ndarray:
        return to_value(self.value_).value_ndarray

    @property
    def jacobian_ivalue(self) -> IValue:
        return to_value(self.jacobian_)

    @property
    def value_ivalue(self) -> IValue:
        return to_value(self.value_)

    @property
    def __variables_count(self) -> int:
        return reduce(mul, self.__input_shape, 1)

    @property
    def __input_shape(self) -> tuple[int, ...]:
        return self.jacobian_ivalue.shape[len(self.value_ivalue.shape):]

    @property
    def shape(self) -> tuple[int, ...]:
        return self.value_ivalue.shape

    @property
    def size(self) -> int:
        return self.value_ivalue.size

    def reshape(self, shape: tuple[int, ...]) -> Tracer:
        return Tracer.from_just_value_or_ndarray(
            self.jacobian_ivalue.reshape(shape + self.__input_shape),
            self.value_ivalue.reshape(shape),
        )

    def broadcast_to(self, shape: tuple[int, ...]) -> Tracer:
        return Tracer.from_just_value_or_ndarray(
            self.jacobian_ivalue.broadcast_to(
                shape + self.__input_shape,
            ),
            self.value_ivalue.broadcast_to(
                shape,
            ),
        )

    def __broadcast_value_to_jacobian(self, value: IValue) -> IValue:
        return value.reshape(
            value.shape + (1, ) * len(self.__input_shape)
        ).broadcast_to(
            self.jacobian_ivalue.shape,
        )

    def _from_constant(self, value: JustValue) -> Tracer:
        return Tracer.from_just_value_or_ndarray(
            JustValue(
                np.zeros(value.shape + self.__input_shape)
            ),
            value,
        )

    @staticmethod
    def _from_variable(value: JustValue) -> Tracer:
        return Tracer.from_just_value_or_ndarray(
            JustValue(
                np.eye(value.size).reshape(value.shape * 2)
            ),
            value,
        )

    def __post_init__(self) -> None:
        if isinstance(self.value_ndarray, np.ndarray):
            self.value_ndarray.flags.writeable=False
        if isinstance(self.jacobian_ndarray, np.ndarray):
            self.jacobian_ndarray.flags.writeable=False

    def __bool__(self) -> bool:
        return bool(self.value_ivalue)

    def __len__(self) -> int:
        return len(self.value_ivalue)

    @staticmethod
    def __broadcast_to_each_other(*ts: Tracer) -> tuple[Tracer, ...]:
        value_shape = np.broadcast_shapes(*[t.shape for t in ts])
        ts = tuple([t.broadcast_to(value_shape) for t in ts])
        assert len({t.shape for t in ts}) == 1
        assert len({t.jacobian_ivalue.shape for t in ts}) == 1
        return ts

    @staticmethod
    def __add(v1: Tracer, v2: Tracer) -> Tracer:
        v1, v2 = Tracer.__broadcast_to_each_other(v1, v2)
        return Tracer.from_just_value_or_ndarray(
            cast(ndarray, v1.jacobian_ndarray + v2.jacobian_ndarray),
            cast(ndarray, v1.value_ndarray + v2.value_ndarray),
        )

    def __add__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self._from_constant(JustValue(np.array(other)))
        return Tracer.__add(self, other)

    def __radd__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self._from_constant(JustValue(np.array(other)))
        return Tracer.__add(other, self)

    @staticmethod
    def __sub(v1: Tracer, v2: Tracer) -> Tracer:
        v1, v2 = Tracer.__broadcast_to_each_other(v1, v2)
        return Tracer.from_just_value_or_ndarray(
            cast(ndarray, v1.jacobian_ndarray - v2.jacobian_ndarray),
            cast(ndarray, v1.value_ndarray - v2.value_ndarray),
        )

    def __sub__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self._from_constant(JustValue(np.array(other)))
        return Tracer.__sub(self, other)

    def __rsub__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self._from_constant(JustValue(np.array(other)))
        return Tracer.__sub(other, self)

    def __neg__(self) -> Tracer:
        return Tracer.from_just_value_or_ndarray(
            -self.jacobian_ivalue,
            -self.value_ivalue,
        )

    @staticmethod
    def __mul(v1: Tracer, v2: Tracer) -> Tracer:
        v1, v2 = Tracer.__broadcast_to_each_other(v1, v2)
        return Tracer.from_just_value_or_ndarray(
            cast(
                ndarray,
                v1.jacobian_ndarray * v1.__broadcast_value_to_jacobian(v2.value_ivalue).value_ndarray
                +
                v2.jacobian_ndarray * v2.__broadcast_value_to_jacobian(v1.value_ivalue).value_ndarray
            ),
            cast(
                ndarray,
                v1.value_ndarray * v2.value_ndarray
            ),
        )

    def __mul__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self._from_constant(JustValue(np.array(other)))
        return self.__mul(self, other)

    def __rmul__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self._from_constant(JustValue(np.array(other)))
        return self.__mul(other, self)

    def __getitem__(self, index: Any) -> Tracer:
        old_indexes = np.arange(self.value_ivalue.size, dtype=np.int64).reshape(self.value_ivalue.shape)
        new_indexes = old_indexes[index]
        new_jacobian = np.empty((new_indexes.size, self.__variables_count))
        old_jacobian = self.jacobian_ndarray.reshape((old_indexes.size, self.__variables_count))
        for new_i, old_i in enumerate(new_indexes.flat):
            new_jacobian[new_i, :] = old_jacobian[old_i, :]
        new_jacobian = new_jacobian.reshape(new_indexes.shape + self.__input_shape)
        return Tracer.from_just_value_or_ndarray(
            new_jacobian,
            cast(
                ndarray,
                self.value_ndarray[index]
            ),
        )

##############################################################################################

def _jacobian_impl(level: int, func: Callable[[ndarray | Tracer], ndarray | Tracer], x_ndarray: ndarray) -> ndarray:

    x : IValue = JustValue(x_ndarray)

    for i in range(level):
        x = Tracer.from_x_and_level(x, i)
    
    assert isinstance(x, JustValue)

    result_any = func(Tracer._from_variable(x))

    result: IValue = result_any if isinstance(result_any, IValue) else JustValue(result_any)

    for i in range(level):

        if isinstance(result, Tracer):
            result = result.jacobian_ivalue
        else:
            result = JustValue(np.zeros(result.shape + x.shape))

    return result.value_ndarray

##############################################################################################

@dataclass(frozen=True)
class manual_jacobian:
    func: Callable[[ndarray | Tracer], ndarray | Tracer] | manual_jacobian

    def __call__(self, x: ndarray) -> ndarray:
        return _jacobian_impl(self._level(), self._func(), x)
    
    def _func(self) -> Callable[[ndarray | Tracer], ndarray | Tracer]:
        if isinstance(self.func, manual_jacobian):
            return self.func._func()
        return self.func

    def _level(self) -> int:
        if isinstance(self.func, manual_jacobian):
            return self.func._level() + 1
        return 1

##############################################################################################

if __name__ == '__main__':

    def same(_a: Any, _s: Any) -> bool:
        a = np.array(_a)
        s = np.array(_s)
        if a.shape == s.shape and np.allclose(a, s):
            return True
        print(a)
        print(s)
        return False

    @dataclass(frozen=True)
    class jacobian_test_base:
        test_jacobian: manual_jacobian
        original_jacobian: Callable[[Any], Any] | None

        def __call__(self, x: ndarray) -> ndarray:
            result = self.test_jacobian(x)
            if self.original_jacobian is not None:
                assert same(result, self.original_jacobian(x))
            return result

    class jacobian_test_wrapper(jacobian_test_base):
        
        def __init__(self, func: Callable[[ndarray | Tracer], ndarray | Tracer]) -> None:
            test_jacobian = manual_jacobian(func)
            original_jacobian = None if autograd_jacobian is None else autograd_jacobian(func)
            super().__init__(test_jacobian, original_jacobian)
        
    def value_and_jacobian(func: Callable[[ndarray | Tracer], ndarray | Tracer], x: ndarray) -> tuple[ndarray, ndarray]:
        return cast(ndarray, func(x)), jacobian_test_wrapper(func)(x)

##############################################################################################

    def test1() -> None:
        def f(x: ndarray | Tracer) -> ndarray:
            return np.array([5])

        value = np.array([4])
        value1, jacobian1 = f(value), jacobian_test_wrapper(f)(value)
        value2, jacobian2 = [5], [[0]]
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test1()

    def test2() -> None:
        def f(x: ndarray | Tracer) -> ndarray:
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
        def f(x: ndarray | Tracer) -> ndarray:
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
        def f(x: ndarray | Tracer) -> ndarray:
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
        def f(x: ndarray | Tracer) -> ndarray:
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
        def f(x: ndarray | Tracer) -> ndarray:
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
        def f(x: ndarray | Tracer) -> ndarray:
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
        def f(x: ndarray | Tracer) -> ndarray:
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
        def f(x: ndarray | Tracer) -> ndarray:
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
        def f(x: ndarray | Tracer) -> ndarray:
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
        def f(x: ndarray | Tracer) -> ndarray:
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
        def f(x: ndarray | Tracer) -> ndarray:
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
        assert same(                                                    f (value), result )
        assert same(result.shape + value.shape, jac.shape)
        assert same(result.shape + value.shape, jacobian_test_wrapper(f)(value).shape)
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
    test12()

    def test13() -> None:
        def f(x: ndarray | Tracer) -> ndarray:
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
        assert same(                                                    f (value), result )
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
        assert result.shape + value.shape == jac.shape
        assert result.shape + value.shape == jacobian_test_wrapper(f)(value).shape
    test13()

    def test14() -> None:
        def f(x: ndarray | Tracer) -> ndarray:
            return cast(
                ndarray,
                (
                    x.reshape((1,2)) * x.reshape((2, 1))
                )[0][1],
            )
        value = np.array( [3., 5.] )
        result = np.array( 15 )
        jac = np.array( [ 5, 3 ] )
        assert same(                                                    f (value), result )
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
        assert result.shape + value.shape == jac.shape
        assert result.shape + value.shape == jacobian_test_wrapper(f)(value).shape
    test14()

    def test15() -> None:
        def f(x: ndarray | Tracer) -> ndarray:
            return cast(
                ndarray,
                x[0] * x[1],
            )
        value = np.array( [3., 5.] )
        result = np.array( 15 )
        jac = np.array( [ 5, 3 ] )
        assert same(                                                    f (value), result )
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
        assert result.shape + value.shape == jac.shape
        assert result.shape + value.shape == jacobian_test_wrapper(f)(value).shape
    test15()

    def test16() -> None:
        def f(x: ndarray | Tracer) -> ndarray:
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
        assert same(                                                    f (value), result )
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
        assert result.shape + value.shape == jacobian_test_wrapper(f)(value).shape
        assert result.shape + value.shape == jac.shape
    test16()

    def test17() -> None:
        def f(x: ndarray | Tracer) -> ndarray:
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
        assert same(                                                    f (value), result )
        assert same(                                          jacobian_test_wrapper(f) (value),  jac )
        assert result.shape + value.shape == jacobian_test_wrapper(f)(value).shape
        assert result.shape + value.shape == jac.shape
    test17()

