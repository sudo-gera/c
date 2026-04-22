from __future__ import annotations
from dataclasses import *
from typing import *
from itertools import *
from functools import *
from operator import *
import abc

class ComputeGraphNode(abc.ABC):
    ...

class FunctionCallComputeGraphNode(ComputeGraphNode):
    ...

class FunctionCallComputeGraphNode(ComputeGraphNode):
    ...











sensor_ignores_getting_this_names : Final = ('__class__', )

@dataclass
class ComputeGraphNode:

    # def __new__(self, )

    def __getattr__(self, name: str) -> Any:
        if name.startswith(f'_{self.__class__.__name__}__'):
            return getattr(super(), name)
        if name in sensor_ignores_getting_this_names:
            return getattr(super(), name)


    def __delattr__(self, name: str) -> Any:
        if name.startswith(f'_{self.__class__.__name__}__'):
            return delattr(super(), name)
        assert False

    def __setattr__(self, name: str, value: Any):
        if name.startswith(f'_{self.__class__.__name__}__'):
            return setattr(super(), name, value)
        assert False

def get_private_attr(obj: Any, name: str) -> Any:
    getattr(obj, f'_{obj.__class__.__name__}')



differentiable_t = TypeVar('differentiable_t')

def differentiable(wrapped_func: differentiable_t) -> differentiable_t:
    
    @wraps(wrapped_func)
    def wrapper(*args):
        sensor_results = {isinstance(arg, ComputeGraphNode) for arg in args}
        assert len(sensor_results) < 2
        if True in sensor_results:
            return ComputeGraphNode()





def actual_grad(f: Callable[[Any], Any], *args, **kwargs):
    

grad = lambda f: partial(actual_grad, f)

##################################################################################

def square(x: float):
    return x*x

assert grad(square)(444) == 888

