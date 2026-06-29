import sys
import typing
import time
import math

bytes_per_second = abs(float(sys.argv[1]))
start = time.monotonic()
already_printed = 0

def binary_io_read1(stream: typing.IO[bytes], l: int) -> bytes:
    return stream.read1(l) # type: ignore

while (buffer := binary_io_read1(sys.stdin.buffer, 2**16)):

    while buffer:

        can_print_total = math.floor((time.monotonic() - start) * bytes_per_second)
        can_print_now = can_print_total - already_printed
        if can_print_now < 0:
            time.sleep(0.1)
            continue
        data_to_print = buffer[:can_print_now]

        sys.stdout.buffer.write(data_to_print)
        sys.stdout.flush()
        already_printed += len(data_to_print)
        buffer = buffer[len(data_to_print):]

        time.sleep(0.1)
