from itertools import *
import random
import math
import io

import numpy as np

def bmp_to_numpy(filepath: str, data: np.ndarray):
    assert len(data.shape) == 3 and data.shape[2] == 4

    height: int
    width: int
    height, width, _ = data.shape

    header = np.zeros(shape=(26,), dtype=np.uint16)
    header[6] = 40
    header[8] = width
    header[10] = height
    header[13] = 32



    # header = np.zeros(shape=(13*4,), dtype=np.uint8)

    # header[12] = 40
    # header[16:24] = list(width.to_bytes(4, 'little') + height.to_bytes(4, 'little'))
    # header[26] = 32

    with open(filepath, 'wb') as file_:
        file_.write(b'BM')
        file_.write(header.tobytes())
        file_.write(data.tobytes())


    # b'BM' + np.

    # file = io.BytesIO()
    # file.write(b'BM')
    # header_ints = np.array([
    #     54 + 4 * width * height,
    #     0, 54, 40,
    #     width, height,
    #     0x2_00_00_1
    # ], dtype=np.uint32)
    # header_ints += [0] * ( 13 - len(header_ints) )
    # header_bytes = b''.join([
    #     c.to_bytes(4, 'little')
    #     for c in header_ints
    # ])
    # file.write(header_bytes)

    # file.write(data.tobytes())

    # file.seek(0)

    # with open(filepath, 'wb') as file_:
    #     file_.write(file.read())


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
    # height = width

    # display : dict[tuple[int, int], list[int]] = {}

    display = np.ndarray(shape=(height, width, 4), dtype=np.uint8)

    for y in range(height):
        for x in range(width):
            display[y, x] = [round(255 * x / width), round(255 * y / height), 255, 255]
            # display[y, x, :] = [x%256, 255, 255, 255]

    # for q in range(64):
    #     col = random.choice(range(width))
    #     value = random.choice(range(1, 256))
    #     for x in range(width):
    #         for y in range(height):
    #             for c in range(3):
                    # display[x, y][c] -= round(norm((x - col)/3) * value)
                        

    bmp_to_numpy('out.bmp', display)

    # save_as_bmp(width, height, display, 'out.bmp')

main()