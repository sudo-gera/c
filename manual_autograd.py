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
    def _to_ndarray(self) -> ndarray:
        ...

    def __add__(self, other: object) -> IValue:
        return IValue.__bin_op(self, other, JustValue._add, Tracer._add)

    def __radd__(self, other: object) -> IValue:
        return IValue.__bin_op(other, self, JustValue._add, Tracer._add)

    def __sub__(self, other: object) -> IValue:
        return IValue.__bin_op(self, other, JustValue._sub, Tracer._sub)

    def __rsub__(self, other: object) -> IValue:
        return IValue.__bin_op(other, self, JustValue._sub, Tracer._sub)

    def __mul__(self, other: object) -> IValue:
        return IValue.__bin_op(self, other, JustValue._mul, Tracer._mul)

    def __rmul__(self, other: object) -> IValue:
        return IValue.__bin_op(other, self, JustValue._mul, Tracer._mul)

    @staticmethod
    def __bin_op(v1_object: object, v2_object: object, just_value_op: Callable[[JustValue, JustValue], IValue], tracer_op: Callable[[Tracer, Tracer], IValue]) -> IValue:
        v1 = v1_object if isinstance(v1_object, IValue) else JustValue(np.array(v1_object))
        v2 = v2_object if isinstance(v2_object, IValue) else JustValue(np.array(v2_object))
        if isinstance(v1, JustValue) and isinstance(v2, JustValue):
            return just_value_op(v1, v2)
        if isinstance(v1, Tracer)    and isinstance(v2, Tracer):
            return tracer_op(v1, v2)
        if isinstance(v1, Tracer)    and isinstance(v2, JustValue):
            return tracer_op(v1, v1._from_constant(v2))
        if isinstance(v1, JustValue) and isinstance(v2, Tracer):
            return tracer_op(v2._from_constant(v1), v2)
        assert False

    @property
    @abstractmethod
    def _value_level(self) -> int | float:
        ...

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

    @abstractmethod
    def __getitem__(self, index: Any) -> IValue:
        ...

###########################################################################################################

@dataclass(frozen=True)
class JustValue(IValue):
    __value: ndarray

    def __post_init__(self) -> None:
        if isinstance(self.__value, np.ndarray):
            self.__value.flags.writeable=False

    @property
    def shape(self) -> tuple[int, ...]:
        return cast(
            tuple[int, ...],
            self.__value.shape
        )

    @property
    def size(self) -> int:
        return self.__value.size

    def reshape(self, shape: tuple[int, ...]) -> JustValue:
        return JustValue(
            self.__value.reshape(shape)
        )

    def broadcast_to(self, shape: tuple[int, ...]) -> JustValue:
        return JustValue(
            np.broadcast_to(
                self.__value,
                shape,
            )
        )

    def __len__(self) -> int:
        return len(self.__value)

    def __bool__(self) -> bool:
        return bool(self.__value)

    def __neg__(self) -> JustValue:
        return JustValue(
            -self.__value
        )

    def __getitem__(self, index: Any) -> JustValue:
        return JustValue(
            cast(
                ndarray,
                self.__value[index]
            )
        )

    @property
    def _to_ndarray(self) -> ndarray:
        return self.__value

    _value_level = float('inf')

    @staticmethod
    def _add(v1: JustValue, v2: JustValue) -> JustValue:
        return JustValue(
            v1.__value + v2.__value
        )

    @staticmethod
    def _sub(v1: JustValue, v2: JustValue) -> JustValue:
        return JustValue(
            v1.__value - v2.__value
        )

    @staticmethod
    def _mul(v1: JustValue, v2: JustValue) -> JustValue:
        return JustValue(
            v1.__value * v2.__value
        )

###########################################################################################################

@dataclass(frozen=True)
class Tracer(IValue):
    jacobian: IValue
    value: IValue
    __value_level: int

    @property
    def _value_level(self) -> int | float:
        return self.__value_level

    def __post_init__(self) -> None:
        assert self.jacobian.shape[:len(self.value.shape)] == self.value.shape
        if isinstance(self.value, Tracer):
            assert self.value.__value_level == self.__value_level + 1
        if isinstance(self.jacobian, Tracer):
            assert self.jacobian.__value_level == self.__value_level + 1

    @staticmethod
    def _from_variable_and_level(value: IValue, level: int) -> IValue:
        return Tracer(
            JustValue(
                np.eye(value.size).reshape(value.shape * 2)
            ),
            value,
            level,
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
    def size(self) -> int:
        return self.value.size

    def reshape(self, shape: tuple[int, ...]) -> Tracer:
        return Tracer(
            self.jacobian.reshape(shape + self.__input_shape),
            self.value.reshape(shape),
            self.__value_level,
        )

    def broadcast_to(self, shape: tuple[int, ...]) -> Tracer:
        return Tracer(
            self.jacobian.broadcast_to(
                shape + self.__input_shape,
            ),
            self.value.broadcast_to(
                shape,
            ),
            self.__value_level,
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
            self.__value_level,
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

    @staticmethod
    def _add(v1: Tracer, v2: Tracer) -> Tracer:
        assert v1.__value_level == v2.__value_level
        v1, v2 = Tracer.__broadcast_to_each_other(v1, v2)
        return Tracer(
            v1.jacobian + v2.jacobian,
            v1.value + v2.value,
            v1.__value_level,
        )

    @staticmethod
    def _sub(v1: Tracer, v2: Tracer) -> Tracer:
        assert v1.__value_level == v2.__value_level
        v1, v2 = Tracer.__broadcast_to_each_other(v1, v2)
        return Tracer(
            v1.jacobian - v2.jacobian,
            v1.value - v2.value,
            v1.__value_level,
        )

    def __neg__(self) -> Tracer:
        return Tracer(
            -self.jacobian,
            -self.value,
            self.__value_level,
        )

    @staticmethod
    def _mul(v1: Tracer, v2: Tracer) -> Tracer:
        assert v1.__value_level == v2.__value_level
        v1, v2 = Tracer.__broadcast_to_each_other(v1, v2)
        return Tracer(
            v1.jacobian * v1.__broadcast_value_to_jacobian(v2.value)
            +
            v2.jacobian * v2.__broadcast_value_to_jacobian(v1.value),
            v1.value * v2.value,
            v1.__value_level,
        )

    def __getitem__(self, index: Any) -> Tracer:
        return Tracer(
            self.jacobian[index],
            self.value[index],
            self.__value_level,
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

    def same(_a: Any, _s: Any) -> bool:
        a = np.array(_a)
        s = np.array(_s)
        if a.shape == s.shape and np.allclose(a, s):
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
                assert same(f(x), result), "original autograd disagrees"
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

    def test19() -> None:
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
    test19()

    def test20() -> None:
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
    test20()

