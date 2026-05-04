from __future__ import annotations
from collections.abc import Callable as caCallable
from dataclasses import *
from typing import *
from itertools import *
from functools import *
from operator import *
import abc

if TYPE_CHECKING:
    import numpy as np
    j_t = TypeVar('j_t')
    def original_j_f(x: j_t) -> j_t:
        return x
    original_j = original_j_f if int is int else None
else:
    try:
        import autograd.numpy as np
        from autograd import jacobian as original_j
    except ImportError:
        import numpy as np
        j_t = TypeVar('j_t')
        original_j = None
        def original_j(x: j_t) -> j_t:
            return x

ndarray = np.ndarray[Any, Any]

@dataclass(frozen=True)
class Tracer:
    jacobian: ndarray
    value: ndarray

    @property
    def _variables_count(self) -> int:
        return reduce(mul, self._input_shape, 1)

    @property
    def _input_shape(self) -> tuple[int, ...]:
        return cast(
            tuple[int, ...],
            self.jacobian.shape[len(self.value.shape):]
        )

    @property
    def shape(self) -> tuple[int, ...]:
        return cast(
            tuple[int, ...],
            self.value.shape
        )

    def reshape(self, shape: tuple[int, ...]) -> Tracer:
        return Tracer(
            self.jacobian.reshape(shape + self._input_shape),
            self.value.reshape(shape),
        )

    def _broadcast_to(self, shape: tuple[int, ...]) -> Tracer:
        return Tracer(
            np.broadcast_to(
                self.jacobian,
                shape + self._input_shape,
            ),
            np.broadcast_to(
                self.value,
                shape,
            ),
        )

    def _broadcast_value_to_jacobian(self, value: ndarray) -> ndarray:
        return np.broadcast_to(
            value.reshape(value.shape + (1, ) * len(self._input_shape)),
            self.jacobian.shape,
        )

    def constant(self, value: ndarray) -> Tracer:
        return Tracer(
            np.zeros(value.shape + self._input_shape),
            value,
        )

    @staticmethod
    def variable(value: ndarray) -> Tracer:
        return Tracer(
            np.eye(value.size).reshape(value.shape * 2),
            value,
        )

    def __post_init__(self) -> None:
        if isinstance(self.value, np.ndarray):
            self.value.flags.writeable=False
        if isinstance(self.jacobian, np.ndarray):
            self.jacobian.flags.writeable=False

    def __bool__(self) -> bool:
        return bool(self.value)

    def __len__(self) -> int:
        return len(self.value)

    @staticmethod
    def __add(v1: Tracer, v2: Tracer) -> Tracer:
        return Tracer(
            cast(ndarray, v1.jacobian + v2.jacobian),
            cast(ndarray, v1.value + v2.value),
        )

    def __add__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self.constant(np.array(other))
        return Tracer.__add(self, other)

    def __radd__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self.constant(np.array(other))
        return Tracer.__add(other, self)

    @staticmethod
    def __sub(v1: Tracer, v2: Tracer) -> Tracer:
        return Tracer(
            cast(ndarray, v1.jacobian - v2.jacobian),
            cast(ndarray, v1.value - v2.value),
        )

    def __sub__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self.constant(np.array(other))
        return Tracer.__sub(self, other)

    def __rsub__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self.constant(np.array(other))
        return Tracer.__sub(other, self)

    def __neg__(self) -> Tracer:
        return Tracer(
            cast(ndarray, -self.jacobian),
            cast(ndarray, -self.value),
        )

    @staticmethod
    def __mul(v1: Tracer, v2: Tracer) -> Tracer:
        value_shape = np.broadcast_shapes(v1.shape, v2.shape)
        v1 = v1._broadcast_to(value_shape)
        v2 = v2._broadcast_to(value_shape)
        assert v1.shape == v2.shape == value_shape
        assert v1.jacobian.shape == v2.jacobian.shape
        return Tracer(
            cast(
                ndarray,
                v1.jacobian * v1._broadcast_value_to_jacobian(v2.value)
                +
                v2.jacobian * v2._broadcast_value_to_jacobian(v1.value)
            ),
            cast(
                ndarray,
                v1.value * v2.value
            ),
        )

    def __mul__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self.constant(np.array(other))
        return self.__mul(self, other)

    def __rmul__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = self.constant(np.array(self))
        return self.__mul(other, self)

    def __getitem__(self, index: Any) -> Tracer:
        variables_count = self._variables_count
        old_value = self.value
        old_jacobian = self.jacobian
        old_indexes = np.arange(old_value.size, dtype=np.int64).reshape(old_value.shape)
        new_indexes = old_indexes[index]
        new_jacobian = np.empty((new_indexes.size, variables_count))
        old_jacobian = old_jacobian.reshape((old_indexes.size, variables_count))
        for new_i, old_i in enumerate(new_indexes.flat):
            new_jacobian[new_i, :] = old_jacobian[old_i, :]
        new_jacobian = new_jacobian.reshape(new_indexes.shape + self._input_shape)
        return Tracer(
            new_jacobian,
            cast(
                ndarray,
                self.value[index]
            ),
        )

    # def __sub__(self, other: object):
    #     if not isinstance(other, MultiExprResult):
    #         other = Constant(other)
    #     return SubOperator(self, other)

    # def __truediv__(self, other: object):
    #     if not isinstance(other, MultiExprResult):
    #         other = Constant(other)
    #     return TrueDivOperator(self, other)

    # def __neg__(self):
    #     return NegOperator(self)

def same(_a: Any, _s: Any) -> bool:
    a = np.array(_a)
    s = np.array(_s)
    if a.shape == s.shape and np.allclose(a, s):
        return True
    print(a)
    print(s)
    return False

def value_and_jacobian(func: Callable[[ndarray | Tracer], ndarray | Tracer], x: ndarray) -> tuple[ndarray, ndarray]:

    result = func(Tracer.variable(x))

    if isinstance(result, Tracer):
        v, ja = result.value, result.jacobian
    else:
        v, ja = result, np.zeros(result.shape + x.shape)

    if original_j is not None:
        assert same( original_j(func)(x), ja)

    return v, ja

def jacobian(func: Callable[[ndarray | Tracer], ndarray | Tracer]) -> Callable[[ndarray], ndarray]:

    def wrapper(x: ndarray) -> ndarray:
        result = value_and_jacobian(func, x)[1]
        return result

    return wrapper

if __name__ == '__main__':

    def test1() -> None:
        def f(x: ndarray | Tracer) -> ndarray:
            return np.array([5])

        value1, jacobian1 = value_and_jacobian(f, np.array([4]))
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
        value1, jacobian1 = value_and_jacobian(f, np.array(4))
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
        value1, jacobian1 = value_and_jacobian(f, np.array(4.))
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
        value1, jacobian1 = value_and_jacobian(f, np.array(4.))
        value2, jacobian2 = 12., 3.
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)
    test4()

    def test5() -> None:
        def f(x: ndarray | Tracer) -> ndarray:
            return cast(
                ndarray,
                x
            )
        value1, jacobian1 = value_and_jacobian(f, np.array((4., 5.)))
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
        value1, jacobian1 = value_and_jacobian(f, np.array((4., 5.)))
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
        value1, jacobian1 = value_and_jacobian(f, np.array((4., 5.)))
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
        value1, jacobian1 = value_and_jacobian(f, np.array((4., 5.)))
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
        value1, jacobian1 = value_and_jacobian(f, np.array((4., 5.)))
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
        value1, jacobian1 = value_and_jacobian(f, value)
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
        value1, jacobian1 = value_and_jacobian(f, value)
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
        assert same(result.shape + value.shape, jacobian(f)(value).shape)
        assert same(                                          jacobian(f) (value),  jac )
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
        assert same(                                          jacobian(f) (value),  jac )
        assert result.shape + value.shape == jac.shape
        assert result.shape + value.shape == jacobian(f)(value).shape
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
        assert same(                                          jacobian(f) (value),  jac )
        assert result.shape + value.shape == jac.shape
        assert result.shape + value.shape == jacobian(f)(value).shape
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
        assert same(                                          jacobian(f) (value),  jac )
        assert result.shape + value.shape == jac.shape
        assert result.shape + value.shape == jacobian(f)(value).shape
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
        assert same(                                          jacobian(f) (value),  jac )
        assert result.shape + value.shape == jacobian(f)(value).shape
        assert result.shape + value.shape == jac.shape
    test16()

