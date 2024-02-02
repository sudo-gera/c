import sys
import functools
import difflib
import os

@functools.lru_cache(1)
def process_one_key(key):
    try:
        a = []
        while 1:
            value = yield
            a.append(value)
            yield
    finally:
        a.sort(key=len)
        if len(a) == 2:
            # os.remove(a[0])
            for w in a:
                print(f'{w}'.rjust(len(a[1])))
            print()

os.chdir('../Music')
for line in sys.stdin:
    line = line[:-1]
    *key, value = line.split(' ', 2)
    key = ' '.join(key)
    assert key + ' ' + value == line
    processor = process_one_key(key)
    processor.send(None)
    processor.send(value)
