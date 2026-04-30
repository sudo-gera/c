from __future__ import annotations
from dataclasses import *
from typing import *
from itertools import *
from functools import *
from operator import *
import abc

class TracingNode(abc.ABC):
    
    @abc.abstractmethod

    def __add__(self, other: object):
        if not isinstance(other, TracingNode):
            other = Constant(other)
        return AddOperator(self, other)

    def __mul__(self, other: object):
        if not isinstance(other, TracingNode):
            other = Constant(other)
        return MulOperator(self, other)

    def __sub__(self, other: object):
        if not isinstance(other, TracingNode):
            other = Constant(other)
        return SubOperator(self, other)

    def __truediv__(self, other: object):
        if not isinstance(other, TracingNode):
            other = Constant(other)
        return TrueDivOperator(self, other)

    def __neg__(self):
        return NegOperator(self)

@dataclass
class MultiVariable(TracingNode):
    value: Any

@cache
@dataclass
class Constant(TracingNode):
    value: Any

@cache
@dataclass(frozen=True)
class AddOperator(TracingNode):
    v1: TracingNode
    v2: TracingNode

@cache
@dataclass(frozen=True)
class AddOperator(TracingNode):
    v1: TracingNode
    v2: TracingNode





def grad(func, x = None):
    if x is None:
        return partial(grad, func)

    result = func(MultiVariable(x))

    if isinstance(result, TracingNode):
        return result.grad().result()
    else:
        assert False        

if __name__ == '__main__':
    
    def test():
        
        # f = lambda x:5
        # assert f       (4) == 5
        # assert grad(f) (4) == 0

        f = lambda x:x
        assert f       (4) == 4
        assert grad(f) (4) == 1

        f = lambda x:x+3
        assert f       (4) == 7
        assert grad(f) (4) == 1

        f = lambda x:x*3
        assert f       (4) == 12
        assert grad(f) (4) == 3

        f = lambda x:x[0]+x[1]
        assert f       ((4, 5)) == 9
        assert grad(f) ((4, 5)) == (1, 1)

        f = lambda x:x[0]*x[1]
        assert f       ((4, 5)) == 20
        assert grad(f) ((4, 5)) == (5, 4)

    
    test()






# sensor_ignores_getting_this_names : Final = ('__class__', )

# @dataclass
# class ComputeGraphNode:

#     # def __new__(self, )

#     def __getattr__(self, name: str) -> Any:
#         if name.startswith(f'_{self.__class__.__name__}__'):
#             return getattr(super(), name)
#         if name in sensor_ignores_getting_this_names:
#             return getattr(super(), name)


#     def __delattr__(self, name: str) -> Any:
#         if name.startswith(f'_{self.__class__.__name__}__'):
#             return delattr(super(), name)
#         assert False

#     def __setattr__(self, name: str, value: Any):
#         if name.startswith(f'_{self.__class__.__name__}__'):
#             return setattr(super(), name, value)
#         assert False

# def get_private_attr(obj: Any, name: str) -> Any:
#     getattr(obj, f'_{obj.__class__.__name__}')



# differentiable_t = TypeVar('differentiable_t')

# def differentiable(wrapped_func: differentiable_t) -> differentiable_t:
    
#     @wraps(wrapped_func)
#     def wrapper(*args):
#         sensor_results = {isinstance(arg, ComputeGraphNode) for arg in args}
#         assert len(sensor_results) < 2
#         if True in sensor_results:
#             return ComputeGraphNode()





# def actual_grad(f: Callable[[Any], Any], *args, **kwargs):
    

# grad = lambda f: partial(actual_grad, f)

# ##################################################################################

# def square(x: float):
#     return x*x

# assert grad(square)(444) == 888

