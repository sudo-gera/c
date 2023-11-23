import functools

@functools.lru_cache(1)
def process_one_word(key):
    count = 0
    try:
        while 1:
            value = yield
            count += int(value)
            yield
    finally:
        print(f'word {key} found {count} times')

a='''
q 100
q 10
q 1
w 200
w 20
w 2
e 300
e 30
e 3
'''.strip().splitlines()

for line in a:
    key, value = line.split()
    a = process_one_word(key)
    a.send(None)
    a.send(value)


