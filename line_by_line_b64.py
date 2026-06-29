import sys
import base64
import typing

mode = sys.argv[1]
prefix = sys.argv[2].encode()

assert mode in ['encode', 'decode']

def binary_io_read1(stream: typing.IO[bytes], l: int) -> bytes:
    return stream.read1(l) # type: ignore

if mode == 'encode':
    to_read = (80 - len(prefix)) // 4 * 3

    while (data := binary_io_read1(sys.stdin.buffer, 2**16)):
        sys.stdout.buffer.write(prefix)
        sys.stdout.buffer.write(base64.b64encode(data))
        sys.stdout.buffer.write(b'\r\n')
        sys.stdout.buffer.flush()

if mode == 'decode':
    while (data := sys.stdin.buffer.readline()):
        sys.stdout.buffer.write(base64.b64decode(data[len(prefix):]))
        sys.stdout.flush()


