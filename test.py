from itertools import *
import random
import math

def save_as_bmp(width: int, height: int, pixels: dict[tuple[int, int], tuple[int, int, int]], filepath: str) -> None:

    with open(filepath, 'wb') as file:
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
                pixel = pixels[x, y][::-1] + (255,)
                for c in pixel:
                    file.write((c % 256).to_bytes(1, 'little'))


def main() -> None:
    width = 1680

    height = 1050

    display : dict[tuple[int, int], tuple[int, int, int]] = {}

    for x in range(width):
        for y in range(height):
            display[x, y] = (255, 255, 255)

    for q in range(40):
        col = random.choice(range(width))
        value = random.choice(range(256))
        for x in range(width):
            for y in range(height):
                if abs(x - col) < value:
                    display[x, y] -= abs(x - col)


    save_as_bmp(width, height, display, 'out.bmp')

main()