from __future__ import annotations
from dataclasses import *
from typing import *
from itertools import *
from functools import *
from operator import *
import abc
import numpy as np

class MultiExpr(abc.ABC):

    @abc.abstractmethod
    def get_variables_count(self) -> int:
        ...

    @abc.abstractmethod
    def grad(self) -> np.ndarray[Any, Any]:
        ...

    @abc.abstractmethod
    def eval(self) -> np.ndarray[Any, Any]:
        ...

    def __add__(self, other: object) -> MultiExpr:
        if not isinstance(other, MultiExpr):
            other = Constant(self.get_variables_count(), np.array(other))
        return AddOperator(self.get_variables_count(), self, other)

    def __mul__(self, other: object) -> MultiExpr:
        if not isinstance(other, MultiExpr):
            other = Constant(self.get_variables_count(), np.array(other))
        return MulOperator(self.get_variables_count(), self, other)

    def __getitem__(self, index: Any) -> MultiExpr:
        return GetItemOperator(self.get_variables_count(), self, index)

    # def __sub__(self, other: object):
    #     if not isinstance(other, MultiExpr):
    #         other = Constant(other)
    #     return SubOperator(self, other)

    # def __truediv__(self, other: object):
    #     if not isinstance(other, MultiExpr):
    #         other = Constant(other)
    #     return TrueDivOperator(self, other)

    # def __neg__(self):
    #     return NegOperator(self)

@dataclass(frozen=True)
class Variable(MultiExpr):
    variables_count: int
    value: np.ndarray[Any, Any]

    def get_variables_count(self) -> int:
        return self.variables_count

    def grad(self) -> np.ndarray[Any, Any]:
        result = np.eye(self.value.size)
        result.resize(self.value.shape + (self.value.size, ))
        return result
        
    def eval(self) -> np.ndarray[Any, Any]:
        return self.value

@dataclass(frozen=True)
class Constant(MultiExpr):
    variables_count: int
    value: np.ndarray[Any, Any]

    def get_variables_count(self) -> int:
        return self.variables_count

    def grad(self) -> np.ndarray[Any, Any]:
        return np.array(0)
        
    def eval(self) -> np.ndarray[Any, Any]:
        return self.value

@dataclass(frozen=True)
class AddOperator(MultiExpr):
    variables_count: int
    v1: MultiExpr
    v2: MultiExpr

    def get_variables_count(self) -> int:
        return self.variables_count

    def grad(self) -> np.ndarray[Any, Any]:
        return cast(np.ndarray[Any, Any],
            self.v1.grad() + self.v2.grad()
        )

    def eval(self) -> np.ndarray[Any, Any]:
        return cast(np.ndarray[Any, Any],
            self.v1.eval() + self.v2.eval()
        )

@dataclass(frozen=True)
class MulOperator(MultiExpr):
    variables_count: int
    v1: MultiExpr
    v2: MultiExpr

    def get_variables_count(self) -> int:
        return self.variables_count

    def grad(self) -> np.ndarray[Any, Any]:
        return cast(
            np.ndarray[Any, Any],
            self.v1.grad() * self.v2.eval() + self.v1.eval() * self.v2.grad()
        )

    def eval(self) -> np.ndarray[Any, Any]:
        return cast(
            np.ndarray[Any, Any],
            self.v1.eval() * self.v2.eval()
        )

@dataclass(frozen=True)
class GetItemOperator(MultiExpr):
    variables_count: int
    value: MultiExpr
    index: Any

    def get_variables_count(self) -> int:
        return self.variables_count

    # def grad(self) -> np.ndarray[Any, Any]:
    #     assert False


#     def grad(self) -> MultiExpr:
#         value = self.value.eval()
#         grad = self.value.grad()
#         data = np.array(range(value.size))
#         data.resize(value.shape)
#         indexed_data = data[self.index]
#         np.zeros(indexed_data.shape + ())



#         np.array(range(self.value.__sizeof__))
# #        return self.v1.grad() * self.v2 + self.v1 * self.v2.grad()

    def eval(self) -> Any:
        return cast(
            np.ndarray[Any, Any],
           self.value.eval()[self.index]
        )





def grad_impl(func: Callable[[np.ndarray[Any, Any] | MultiExpr], np.ndarray[Any, Any] | MultiExpr], x: np.ndarray[Any, Any]) -> np.ndarray[Any, Any]:
    if x is None:
        return partial(grad, func)

    result = func(Variable(x.size, x))

    if isinstance(result, MultiExpr):
        return result.grad()
    else:
        return np.zeros(x.shape)

def grad(func: Callable[[np.ndarray[Any, Any] | MultiExpr], np.ndarray[Any, Any] | MultiExpr]) -> Callable[[np.ndarray[Any, Any] | MultiExpr], np.ndarray[Any, Any]]:
    return partial(grad_impl, func)

if __name__ == '__main__':
    
    def test1() -> None:
        def f(x: np.ndarray[Any, Any] | MultiExpr) -> np.ndarray[Any, Any] | MultiExpr:
            return np.array(5)

        assert f       (np.array(4)) == 5
        assert grad(f) (np.array(4)) == 0
    test1()

    def test2() -> None:
        def f(x: np.ndarray[Any, Any] | MultiExpr) -> np.ndarray[Any, Any] | MultiExpr:
            return x
        assert f       (np.array(4)) == 4
        assert grad(f) (np.array(4)) == 1
    test2()

    def test3() -> None:
        def f(x: np.ndarray[Any, Any] | MultiExpr) -> np.ndarray[Any, Any] | MultiExpr:
            return cast(
                np.ndarray[Any, Any],
                x+3
            )
        f = lambda x:x+3
        assert f       (np.array(4)) == 7
        assert grad(f) (np.array(4)) == 1
    test3()

    def test4() -> None:
        def f(x: np.ndarray[Any, Any] | MultiExpr) -> np.ndarray[Any, Any] | MultiExpr:
            return cast(
                np.ndarray[Any, Any],
                x*3
            )
        assert f       (np.array(4)) == 12
        assert grad(f) (np.array(4)) == 3
    test4()

    def test5() -> None:
        def f(x: np.ndarray[Any, Any] | MultiExpr) -> np.ndarray[Any, Any] | MultiExpr:
            return cast(
                np.ndarray[Any, Any],
                x[0]+x[1]
            )
        assert f       (np.array((4, 5))) == 9
        assert grad(f) (np.array((4, 5))) == (1, 1)
    test5()

    def test6() -> None:
        def f(x: np.ndarray[Any, Any] | MultiExpr) -> np.ndarray[Any, Any] | MultiExpr:
            return cast(
                np.ndarray[Any, Any],
                x[0]*x[1]
            )
        assert f       (np.array((4, 5))) == 20
        assert grad(f) (np.array((4, 5))) == (5, 4)
    test5()






