import functools

@functools.lru_cache(1)
def process_one_word(word_arg):
    try:
        while 1:
            word = yield
            print(word, word_arg)
    finally:
        print('finally', word_arg)

a='''
1
1
1
2
2
2
3
3
3
'''.strip().split()

for q in a:
    a = process_one_word(q)
    a.send(None)


