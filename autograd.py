from __future__ import annotations
from dataclasses import dataclass
from types import *
import abc
from functools import *
from enum import Enum
import ast
import sys

class ICanGetGrad(abc.ABC):

    @abc.abstractmethod
    def grad(self, var: Variable) -> ICanGetGrad:
        ...

    def __add__(self, other: ICanGetGrad) -> ICanGetGrad:
        return Sum(self, other)
    
    def __sum__(self, other: ICanGetGrad) -> ICanGetGrad:
        return Difference(self, other)
    
    def __mul__(self, other: ICanGetGrad) -> ICanGetGrad:
        return Product(self, other)

    def __truediv__(self, other: ICanGetGrad) -> ICanGetGrad:
        return Quotient(self, other)

    @abc.abstractmethod
    def ast(self) -> ast.AST:
        ...

    @abc.abstractmethod
    def variables(self) -> frozenset[str]:
        ...

@cache
@dataclass(frozen=True)
class Value(ICanGetGrad):
    value: float

    def grad(self, var: Variable) -> ICanGetGrad:
        return Value(0)

    def ast(self) -> ast.AST:
        return ast.Constant(value=self.value)

    def variables(self) -> frozenset[str]:
        return frozenset()

@cache
@dataclass(frozen=True)
class Variable(ICanGetGrad):
    id: str

    def grad(self, var: Variable) -> ICanGetGrad:
        if self is var:
            return Value(1)
        return Value(0)

    def ast(self) -> ast.AST:
        return ast.Name(id=self.id)

    def variables(self) -> frozenset[str]:
        return frozenset((self.id, ))

@dataclass(frozen=True)
class IBinOp(ICanGetGrad):
    f1: ICanGetGrad
    f2: ICanGetGrad

    @staticmethod
    @abc.abstractmethod
    def op() -> ast.AST:
        ...

    def ast(self) -> ast.AST:
        return ast.BinOp(
            left=self.f1.ast(),
            op=self.op(),
            right=self.f2.ast(),
        )

    def variables(self) -> frozenset[str]:
        return self.f1.variables() | self.f2.variables()

@dataclass(frozen=True)
class Sum(IBinOp):

    @staticmethod
    def op() -> ast.AST:
        return ast.Add()

    def grad(self, var: Variable) -> ICanGetGrad:
        return Sum(
            self.f1.grad(var),
            self.f2.grad(var)
        )

@dataclass(frozen=True)
class Difference(IBinOp):

    @staticmethod
    def op() -> ast.AST:
        return ast.Sub()

    def grad(self, var: Variable) -> ICanGetGrad:
        return Difference(
            self.f1.grad(var),
            self.f2.grad(var)
        )

@dataclass(frozen=True)
class Product(IBinOp):

    @staticmethod
    def op() -> ast.AST:
        return ast.Mult()

    def grad(self, var: Variable) -> ICanGetGrad:
        return Sum(
            Product(
                self.f1.grad(var),
                self.f2,
            ),
            Product(
                self.f1,
                self.f2.grad(var),
            ),
        )

@dataclass(frozen=True)
class Quotient(IBinOp):

    @staticmethod
    def op() -> ast.AST:
        return ast.Div()

    def grad(self, var: Variable) -> ICanGetGrad:
        return Quotient(
            Difference(
                Product(
                    self.f1.grad(var),
                    self.f2,
                ),
                Product(
                    self.f1,
                    self.f2.grad(var),
                ),
            ),
            Product(
                self.f2,
                self.f2,
            )
        )

def ast_traversal(root: ast.AST) -> ICanGetGrad:
    if isinstance(root, ast.Expression):
        return ast_traversal(root.body)
    if isinstance(root, ast.BinOp):
        if isinstance(root.op, ast.Add):
            return ast_traversal(root.left) + ast_traversal(root.right)
        if isinstance(root.op, ast.Sub):
            return ast_traversal(root.left) - ast_traversal(root.right)
        if isinstance(root.op, ast.Mult):
            return ast_traversal(root.left) * ast_traversal(root.right)
        if isinstance(root.op, ast.Div):
            return ast_traversal(root.left) / ast_traversal(root.right)
    if isinstance(root, ast.Constant):
        return Value(float(root.value))
    if isinstance(root, ast.Name):
        return Variable(root.id)

    print(ast.dump(root, indent=4), file=sys.stderr)
    assert False

def symbolic_grad(expr: str) -> dict[str, str]:
    tree = ast.parse(expr, mode='eval')
    can_get_grad = ast_traversal(tree)
    return {
        variable: ast.unparse(
            can_get_grad.grad(
                Variable(
                    variable
                )
            ).ast()
        )
        for variable in can_get_grad.variables()
    }

for variable, part_der in symbolic_grad(input()).items():
    print(f'{variable!r}: {part_der}')

