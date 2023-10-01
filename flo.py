from h import *
import sys
import json
import functools

class flo_file:
    def __init__(self, file):
        self.file = file
    def char(self):
        c = self.file.read(1)
        if len(c) == 0:
            raise EOFError
        return c[0]
    def uns(self):
        result = ''
        while True:
            q = self.char()
            q = bin(q+256)[-8:]
            result = q[1:] + result
            if q[0]=='0':
                return int(result,2)
    def int(self):
        q = self.uns()
        return -(q+1)//2 if q%2 else q//2

with open('flo.json') as db_file:
    flo_db = json.load(db_file)
readers = {}

class starts_with:
    def __init__(self, *nums:int):
        self.nums = nums
    def __call__(self, func):
        for num in self.nums:
            readers[num] = func
        return func

@starts_with(106)
class reader_str:
    def __init__(self, file, num):
        self.data = []
        for q in range(file.uns()):
            self.data.append(file.char())
        self.data = bytes(self.data).decode()
    def __repr__(self) -> str:
        return f'flo_str({self.data!r})'

@starts_with(104, 131)
class reader_float:
    def __init__(self, file, num):
        if num == 131:
            file.char()
            file.char()
        self.data = [file.char() for _ in range(8)]
        self.data = ''.join([bin(q+256)[-8:] for q in self.data])
        a=int(self.data[:12],2)
        s=int(self.data[12:],2)
        a-=1023
        f=2**(len(self.data)-12)
        s+=f
        self.d=s*2**a/f
        if num == 131:
            self.d = -self.d
    def __repr__(self) -> str:
        return f'flo_float({self.d})'

@starts_with(0)
class reader_null:
    def __init__(self, file, num):
        pass
    def __repr__(self) -> str:
        return 'flo_null()'

class reader_block:
    def __new__(cls, file, num):
        self = super().__new__(cls)
        self.file = file
        self.num = num
        return self.init()
    def init(self):
        self.id = self.file.int()
        self.x = self.file.int()
        self.y = self.file.int()
        self.args = []
        for _ in range(flo_db[str(self.num)]['arg_count'] - 4):
            val = yield
            self.args.append(val)
        return self

def read(file):
    head = [file.int() for _ in range(8)]
    blocks = []
    block_gens = []
    gen = None
    while True:
        try:
            start = file.int()
        except EOFError:
            break
        if start<1000:
            value = readers[start](file, start)
        else:
            gen = reader_block(file, start)
            block_gens.append(gen)
            value = None
        try:
            gen.send(value)
        except StopIteration as exc:
            block_gens.remove(gen)
            if block_gens:
                gen = block_gens[0]
            else:
                gen = None
            blocks.append(exc.value)
    return blocks


def raw_read(file):
    head = [file.int() for _ in range(8)]
    print(file.int(), file.int(), file.int(), file.int(), end=' ')
    data=b''
    try:
        while 1:
            data+=bytes([file.char()])
    except EOFError:
        pass
    print(binstr(data))

raw_read(flo_file(open(sys.argv[1],'rb')))
for block in read(flo_file(open(sys.argv[1],'rb'))):
    print(block.num, block.x, block.y, block.args)


