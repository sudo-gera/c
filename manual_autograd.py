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
    def j(x: j_t) -> j_t:
        return x
else:
    import autograd.numpy as np
    from autograd import jacobian as j

@dataclass(frozen=True)
class Tracer:
    jacobian: np.ndarray[Any, Any]
    value: np.ndarray[Any, Any]
    variables_count: int

    @property
    def input_shape(self) -> tuple[int, ...]:
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

    def __post_init__(self) -> None:
        if isinstance(self.value, np.ndarray):
            self.value.flags.writeable=False
        if isinstance(self.jacobian, np.ndarray):
            self.jacobian.flags.writeable=False

    def __add__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = Constant(self.variables_count, np.array(other))
        return AddOperator(self.variables_count, self, other)

    def __mul__(self, other: object) -> Tracer:
        if not isinstance(other, Tracer):
            other = Constant(self.variables_count, np.array(other))
        return MulOperator(self.variables_count, self, other)

    def __getitem__(self, index: Any) -> Tracer:
        return GetItemOperator(self.variables_count, self, index)

    def reshape(self, shape: tuple[int, ...]) -> Tracer:
        return Tracer(
            self.jacobian.reshape(shape + (self.variables_count, )),
            self.value.reshape(shape),
            self.variables_count,
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

def Variable(variables_count: int, value: np.ndarray[Any, Any]) -> Tracer:
    return Tracer(
        np.eye(value.size).reshape(value.shape * 2),
        value,
        variables_count,
    )

def Constant(variables_count: int, value: np.ndarray[Any, Any]) -> Tracer:
    return Tracer(
        np.array(0),
        value,
        variables_count,
    )

def AddOperator(variables_count: int, v1: Tracer, v2: Tracer) -> Tracer:
    return Tracer(
        cast(np.ndarray[Any, Any],
            v1.jacobian + v2.jacobian
        ),
        cast(np.ndarray[Any, Any],
            v1.value + v2.value
        ),
        variables_count,
    )

def MulOperator(variables_count: int, v1: Tracer, v2: Tracer) -> Tracer:
    v1_value, v2_value = np.broadcast_arrays(v1.value, v2.value)
    v1_jacobian = np.broadcast_to(v1.jacobian, v1_value.shape + v1.input_shape)
    v2_jacobian = np.broadcast_to(v2.jacobian, v2_value.shape + v2.input_shape)
    return Tracer(
        cast(
            np.ndarray[Any, Any],
            v1_jacobian * v2_value + v1_value * v2_jacobian
        ),
        cast(
            np.ndarray[Any, Any],
            v1_value * v2_value
        ),
        variables_count,
    )

def GetItemOperator(variables_count: int, value: Tracer,    index: Any) -> Tracer:
    old_value = value.value
    old_jacobian = value.jacobian
    var_count = variables_count
    # assert old_jacobian.shape == old_value.shape + (var_count, )
    old_indexes = np.arange(old_value.size, dtype=np.int64).reshape(old_value.shape)
    new_indexes = old_indexes[index]
    new_jacobian = np.empty((new_indexes.size, var_count))
    old_jacobian = old_jacobian.reshape((old_indexes.size, var_count))
    for new_i, old_i in enumerate(new_indexes.flat):
        new_jacobian[new_i, :] = old_jacobian[old_i, :]
    new_jacobian = new_jacobian.reshape(new_indexes.shape + value.input_shape)
    return Tracer(
        new_jacobian,
        cast(
            np.ndarray[Any, Any],
            value.value[index]
        ),
        variables_count,
    )



def value_and_jacobian(func: Callable[[np.ndarray[Any, Any] | Tracer], np.ndarray[Any, Any] | Tracer], x: np.ndarray[Any, Any]) -> tuple[np.ndarray[Any, Any], np.ndarray[Any, Any]]:
    result = func(Variable(x.size, x))

    if isinstance(result, Tracer):
        return result.value, result.jacobian
    else:
        return result, np.zeros(x.shape)

def jacobian(func: Callable[[np.ndarray[Any, Any] | Tracer], np.ndarray[Any, Any] | Tracer]) -> Callable[[np.ndarray[Any, Any]], np.ndarray[Any, Any]]:

    def wrapper(x: np.ndarray[Any, Any]) -> np.ndarray[Any, Any]:
        return value_and_jacobian(func, x)[1]

    return wrapper

if __name__ == '__main__':

    def same(_a: Any, _s: Any) -> bool:
        a = np.array(_a)
        s = np.array(_s)
        return a.shape == s.shape and np.allclose(a, s)

    def test1() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return np.array(5)

        value1, jacobian1 = value_and_jacobian(f, np.array(4))
        value2, jacobian2 = 5, 0
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test1()

    def test2() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x
            )
        value1, jacobian1 = value_and_jacobian(f, np.array(4))
        value2, jacobian2 = 4, 1
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test2()

    def test3() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x+3
            )
        value1, jacobian1 = value_and_jacobian(f, np.array(4))
        value2, jacobian2 = 7, 1
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test3()

    def test4() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x*3
            )
        value1, jacobian1 = value_and_jacobian(f, np.array(4))
        value2, jacobian2 = 12, 3
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test4()

    def test5() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x
            )
        value1, jacobian1 = value_and_jacobian(f, np.array((4, 5)))
        value2, jacobian2 = (4, 5), ((1, 0), (0, 1))
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test5()

    def test6() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x*x
            )
        value1, jacobian1 = value_and_jacobian(f, np.array((4, 5)))
        value2, jacobian2 = (16, 25), ((8, 0), (0, 10))
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test6()

    def test7() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x*x[::-1]
            )
        value1, jacobian1 = value_and_jacobian(f, np.array((4, 5)))
        value2, jacobian2 = (20, 20), ((5, 5), (4, 4))
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test7()

    def test8() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x[0]
            )
        value1, jacobian1 = value_and_jacobian(f, np.array((4, 5)))
        value2, jacobian2 = 4, (1, 0)
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test8()

    def test9() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x[1]
            )
        value1, jacobian1 = value_and_jacobian(f, np.array((4, 5)))
        value2, jacobian2 = 5, (0, 1)
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test9()

    def test10() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x[0]+x[1]
            )
        value1, jacobian1 = value_and_jacobian(f, np.array((4, 5)))
        value2, jacobian2 = 9, (1, 1)
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test10()

    def test11() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x[0]*x[1]
            )
        value1, jacobian1 = value_and_jacobian(f, np.array((4, 5)))
        value2, jacobian2 = 20, (5, 4)
        assert same(value1, value2)
        assert same(jacobian1, jacobian2)

    test11()

    def test12() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                (
                    x.reshape((4,1)) * x.reshape((1,4))
                ).reshape((8, 2))[3:5, :]
            )
        value = np.array( [ [3, 5], [7, 11] ] )
        result = np.array( [ [ 35, 55 ], [ 21, 35 ] ] )
        jac = np.array(
            [
                [ [ 0,  5,  7,  0,], [ 0,  5,  0, 11,], ],
                [ [ 3,  0,  7,  0,], [ 0,  5,  7,  0,], ],
            ]
        )
        assert value.shape + result.shape == jac.shape
        assert same(                                                    f (value), result )
        assert same(                                          jacobian(f) (value),  jac )

    test12()

    def test13() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
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

    test13()

    def test14() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                (
                    x.reshape((1,2)) * x.reshape((2, 1))
                )[0][1],
            )
        value = np.array( [3., 5.] )
        result = np.array( 15 )
        jac = np.array( [ 3, 5 ] )
        assert same(                                                    f (value), result )
        assert same(                                          jacobian(f) (value),  jac )

    test14()

    def test15() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any]:
            return cast(
                np.ndarray[Any, Any],
                x[0] * x[1],
            )
        value = np.array( [3., 5.] )
        result = np.array( 15 )
        jac = np.array( [ 5, 3 ] )
        assert same(                                                    f (value), result )
        assert same(                                          jacobian(f) (value),  jac )

    test15()

