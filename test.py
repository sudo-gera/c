import typing as tp

T1 = tp.TypeVar('T1')
T2 = tp.TypeVar('T2')
T3 = tp.TypeVar('T3')
T4 = tp.TypeVar('T4', int, float, bool)

def f(g: tp.Callable[[T1, T2, T3], T4], x: T1, y: T2, z: T3) -> T4:
    return g(x,y,z)

def A(x: float, y: float, z:complex) -> int:
    return 1
f(A, 1, 4.5, 1j)

def B(x: complex, y: complex, z:complex) -> bool:
    return True
f(A, 1, 4, True)

def C(x: bool, y: float, z:complex) -> int:
    return 1
f(C, 1, 4.5, 1j)

def D(x: int, y: int, z:complex) -> int:
    return 1
f(D, 1, 4.5, 1j)

def E(x: int, y: float, z:float) -> int:
    return 1
f(E, 1, 4.5, 1j)


def F(x: float, y: float, z:complex) -> float:
    return 1.0
f(E, True, True, True)

def G(x: float, y: float, z:complex) -> complex:
    return 1j
f(G, True, True, True)

