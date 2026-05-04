from __future__ import annotations
from collections.abc import Callable as caCallable
from dataclasses import *
from typing import *
from itertools import *
from functools import *
from operator import *
import abc
import numpy as np

@dataclass(frozen=True)
class Tracer:
    jacobian: np.ndarray[Any, Any]
    value: np.ndarray[Any, Any]
    variables_count: int

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
    jacobian = np.eye(value.size)
    jacobian.resize(value.shape + (value.size, ))
    return Tracer(
        jacobian,
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
    return Tracer(
        cast(
            np.ndarray[Any, Any],
            v1.jacobian * v2.value + v1.value * v2.jacobian
        ),
        cast(
            np.ndarray[Any, Any],
            v1.value * v2.value
        ),
        variables_count,
    )

def GetItemOperator(variables_count: int, value: Tracer,    index: Any) -> Tracer:
    old_value = value.value
    old_jacobian = value.jacobian
    var_count = variables_count
    assert old_jacobian.shape == old_value.shape + (var_count, )
    old_indexes = np.arange(old_value.size, dtype=np.int64)
    old_indexes.reshape(old_value.shape)
    new_indexes = old_indexes[index]
    new_jacobian = np.empty((new_indexes.size, var_count))
    old_jacobian = old_jacobian.reshape((old_indexes.size, var_count))
    for new_i, old_i in enumerate(new_indexes.flat):
        new_jacobian[new_i, :] = old_jacobian[old_i, :]
    new_jacobian.reshape(new_indexes.shape + (var_count, ))
    return Tracer(
        new_jacobian,
        cast(
            np.ndarray[Any, Any],
            value.value[index]
        ),
        variables_count,
    )



def jacobian_and_value(func: Callable[[np.ndarray[Any, Any] | Tracer], np.ndarray[Any, Any] | Tracer], x: np.ndarray[Any, Any]) -> tuple[np.ndarray[Any, Any], np.ndarray[Any, Any]]:
    result = func(Variable(x.size, x))

    if isinstance(result, Tracer):
        return result.value, result.jacobian
    else:
        return result, np.zeros(x.shape)

if __name__ == '__main__':
    
    def test1() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return np.array(5)

        jacobian1, value1 = jacobian_and_value(f, np.array(4))
        jacobian2, value2 = 5, 0
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test1()

    def test2() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return x
        jacobian1, value1 = jacobian_and_value(f, np.array(4))
        jacobian2, value2 = 4, 1
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test2()

    def test3() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return cast(
                np.ndarray[Any, Any],
                x+3
            )
        f = lambda x:x+3
        jacobian1, value1 = jacobian_and_value(f, np.array(4))
        jacobian2, value2 = 7, 1
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test3()

    def test4() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return cast(
                np.ndarray[Any, Any],
                x*3
            )
        jacobian1, value1 = jacobian_and_value(f, np.array(4))
        jacobian2, value2 = 12, 3
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test4()

    def test5() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return cast(
                np.ndarray[Any, Any],
                x
            )
        jacobian1, value1 = jacobian_and_value(f, np.array((4, 5)))
        jacobian2, value2 = (4, 5), ((1, 0), (0, 1))
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test5()

    def test6() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return cast(
                np.ndarray[Any, Any],
                x*x
            )
        jacobian1, value1 = jacobian_and_value(f, np.array((4, 5)))
        jacobian2, value2 = (16, 25), ((8, 0), (0, 10))
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test6()

    def test7() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return cast(
                np.ndarray[Any, Any],
                x*x[::-1]
            )
        jacobian1, value1 = jacobian_and_value(f, np.array((4, 5)))
        jacobian2, value2 = (20, 20), ((5, 5), (4, 4))
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test7()

    def test8() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return cast(
                np.ndarray[Any, Any],
                x[0]
            )
        jacobian1, value1 = jacobian_and_value(f, np.array((4, 5)))
        jacobian2, value2 = 4, (1, 0)
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test8()

    def test9() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return cast(
                np.ndarray[Any, Any],
                x[1]
            )
        jacobian1, value1 = jacobian_and_value(f, np.array((4, 5)))
        jacobian2, value2 = 5, (0, 1)
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test9()

    def test10() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return cast(
                np.ndarray[Any, Any],
                x[0]+x[1]
            )
        jacobian1, value1 = jacobian_and_value(f, np.array((4, 5)))
        jacobian2, value2 = 9, (1, 1)
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test10()

    def test11() -> None:
        def f(x: np.ndarray[Any, Any] | Tracer) -> np.ndarray[Any, Any] | Tracer:
            return cast(
                np.ndarray[Any, Any],
                x[0]*x[1]
            )
        jacobian1, value1 = jacobian_and_value(f, np.array((4, 5)))
        jacobian2, value2 = 20, (5, 4)
        assert np.allclose(jacobian1, jacobian2)
        assert np.allclose(value1, value2)

    test11()

