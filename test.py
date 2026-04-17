from __future__ import annotations
from dataclasses import dataclass
from types import *
import abc
from functools import *
from enum import Enum
import ast
import sys

class CanGetGrad(abc.ABC):

    @abc.abstractmethod
    def grad(self) -> CanGetGrad:
        ...

    def __add__(self, other: CanGetGrad) -> CanGetGrad:
        return Sum(self, other)
    
    def __mul__(self, other: CanGetGrad) -> CanGetGrad:
        return Product(self, other)

    @abc.abstractmethod
    def ast(self) -> ast.AST:
        ...

@cache
@dataclass(frozen=True)
class Value(CanGetGrad):
    value: float

    def grad(self) -> CanGetGrad:
        return Value(0)

    def ast(self) -> ast.AST:
        return ast.Constant(value=self.value)

@cache
@dataclass(frozen=True)
class Variable(CanGetGrad):
    id: str

    def grad(self) -> CanGetGrad:
        return Value(1)

    def ast(self) -> ast.AST:
        return ast.Name(id=self.id)

@dataclass(frozen=True)
class Sum(CanGetGrad):
    f1: CanGetGrad
    f2: CanGetGrad

    def grad(self) -> CanGetGrad:
        return Sum(
            self.f1.grad(),
            self.f2.grad()
        )

    def ast(self) -> ast.AST:
        return ast.BinOp(
            left=self.f1.ast(),
            op=ast.Add(),
            right=self.f2.ast(),
        )

@dataclass(frozen=True)
class Product(CanGetGrad):
    f1: CanGetGrad
    f2: CanGetGrad

    def grad(self) -> CanGetGrad:
        return Sum(
            Product(
                self.f1.grad(),
                self.f2,
            ),
            Product(
                self.f1,
                self.f2.grad(),
            ),
        )

    def ast(self) -> ast.AST:
        return ast.BinOp(
            left=self.f1.ast(),
            op=ast.Mult(),
            right=self.f2.ast(),
        )

def ast_traversal(root: ast.AST):
    if isinstance(root, ast.Expression):
        return ast_traversal(root.body)
    if isinstance(root, ast.BinOp):
        if isinstance(root.op, ast.Add):
            return ast_traversal(root.left) + ast_traversal(root.right)
        if isinstance(root.op, ast.Mult):
            return ast_traversal(root.left) * ast_traversal(root.right)
    if isinstance(root, ast.Constant):
        return Value(float(root.value))
    if isinstance(root, ast.Name):
        return Variable(root.id)

    print(ast.dump(root, indent=4), file=sys.stderr)
    assert False

def symbolic_grad(expr: str):
    tree = ast.parse(expr, mode='eval')
    can_get_grad = ast_traversal(tree)
    can_get_grad = can_get_grad.grad()
    return ast.unparse(can_get_grad.ast())

print(symbolic_grad('0+0*a'))
# print(symbolic_grad(input()))




