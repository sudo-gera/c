import sys
import time

bytes_read = 0
while (data := sys.stdin.buffer.read(2**20)):
    bytes_read += len(data)
    to_print = f'{bytes_read:_}'
    # print('\x1b[100C' + to_print + '\x1b[100D'  )
    print('\x1b[100C' + to_print + '\x1b['+ str(len(to_print)) +'D' + '\x1b[100D', end='', file=sys.stderr)
    sys.stderr.flush()
    # print(f'{bytes_read:_}', end='\r', file=sys.stderr)
    sys.stdout.buffer.write(data)
    time.sleep(0.002)
