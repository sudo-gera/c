from itertools import *
import random
import math
import io

def save_as_bmp(width: int, height: int, pixels: dict[tuple[int, int], list[int]], filepath: str) -> None:


    file = io.BytesIO()
    file.write(b'BM')
    header_ints = [
        54 + 4 * width * height,
        0, 54, 40,
        width, height,
        0x2_00_00_1
    ]
    header_ints += [0] * ( 13 - len(header_ints) )
    header_bytes = b''.join([
        c.to_bytes(4, 'little')
        for c in header_ints
    ])
    file.write(header_bytes)
    for y in range(height):
        for x in range(width):
            pixel = pixels[x, y][::-1] + [255]
            for c in pixel:
                file.write((c % 256).to_bytes(1, 'little'))

    file.seek(0)

    with open(filepath, 'wb') as file_:
        file_.write(file.read())

def norm(x: float) -> float:
    n = math.exp(-1/2*x**2)
    du = 2*math.pi
    d = math.sqrt(du)
    d=1
    return n/d

def main() -> None:
    width = 1680

    height = 1050

    display : dict[tuple[int, int], list[int]] = {}

    for x in range(width):
        for y in range(height):
            display[x, y] = [255, 255, 255]

    for q in range(64):
        col = random.choice(range(width))
        value = random.choice(range(1, 256))
        for x in range(width):
            for y in range(height):
                for c in range(3):
                    display[x, y][c] -= round(norm((x - col)/3) * value)
                        


    save_as_bmp(width, height, display, 'out.bmp')

main()