from h import *
import sys
import json
import functools
import traceback
import types

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
    flo_db = {int(key):val for key,val in json.load(db_file).items()}
with open('flo_func.json') as db_file:
    flo_func_db = {int(key):val for key,val in json.load(db_file).items()}
readers = {}

def gen_send(gen, *a, **s):
    try:
        gen.send(*a, **s)
    except StopIteration as exc:
        return exc.value

class starts_with:
    def __init__(self, *nums:int):
        self.nums = nums
    def __call__(self, func):
        for num in self.nums:
            readers[num] = func
        return func

class gen_init:
    def __new__(cls, file, num):
        self = super().__new__(cls)
        self.file = file
        self.num = num
        gen = self.__init__()
        if gen is not None:
            yield from gen
        return self

@starts_with(106)
class reader_str(gen_init):
    def __init__(self):
        self.data = []
        for q in range(self.file.uns()):
            self.data.append(self.file.char())
        self.data = bytes(self.data).decode()
    def __repr__(self) -> str:
        return f'flo_str({self.data!r})'

@starts_with(104)
class reader_num(gen_init):
    def __init__(self):
        self.data = [self.file.char() for _ in range(8)]
        self.data = ''.join([bin(q + 256)[-8:] for q in self.data])
        a = int(self.data[:12], 2)
        s = int(self.data[12:], 2)
        a -= 1023
        f = 2**(len(self.data)-12)
        s += f
        self.d = s * 2**a / f
    def __repr__(self) -> str:
        # return f'flo_num({self.d})'
        return f'{self.d}'

@starts_with(131, 113, 125, 134, 139, 140, 126, )
class reader_un_op(gen_init):
    def __init__(self):
        arg = yield
        self.arg = arg
    def __repr__(self) -> str:
        if self.num == 125:
            return f'({self.arg})'
        signs = {
            131: '-',
            113: '~',
            134: '!',
            139: '+',
            140: '++',
            126: '#',
        }
        sign = signs[self.num] if self.num in signs else f'_{self.num}_'
        return f'''{sign}{self.arg}'''

@starts_with(110, 130, 138, 129, 121, 117, 112, 118, 124, 128, 141, 114, 115, 116, 122, 135, 123, 127, 111, 136, 119, 137, )
class reader_bin_op(gen_init):
    def __init__(self):
        left = yield
        self.left = left
        right = yield
        self.right = right
    def __repr__(self) -> str:
        if self.num == 137:
            return f'{self.left}[{self.right}]'
        signs = {
            110: '+',
            112: '&',
            117: '|',
            118: '^',
            121: '/',
            124: '>',
            128: '<',
            129: '%',
            130: '*',
            138: '-',
            141: '//',
            114: '<<',
            115: '>>',
            116: '>>>',
            122: '=',
            135: '!=',
            123: '>=',
            127: '<=',
            111: '&&',
            136: '||',
            119: '++',
        }
        sign = signs[self.num] if self.num in signs else f'_{self.num}_'
        return f'''{self.left} {sign} {self.right}'''

@starts_with(120)
class reader_tern(gen_init):
    def __init__(self):
        condition = yield
        self.condition = condition
        then = yield
        self.then = then
        orelse = yield
        self.orelse = orelse
    def __repr__(self) -> str:
        return f'{self.condition} ? {self.then} : {self.orelse}'

@starts_with(0, 103, 201)
class reader_const(gen_init):
    def __init__(self):
        pass
    def __repr__(self) -> str:
        names = {
            0: 'None',
            202: 'Now',
            103: 'null',
            201: 'Nan',
        }
        name = names[self.num] if self.num in names else f'_{self.num}_'
        return f'flo_const({name})'

@starts_with(*map(int, flo_func_db))
class reader_func(gen_init):
    def __init__(self):
        func = flo_func_db[self.num]
        self.args = []
        if '\u2026' in func['args']:
            arg_count = self.file.uns()
        else:
            arg_count = len(func['args'])
        for arg_num in range(arg_count):
            arg = yield
            if '\u2026' in func['args']:
                arg_name = f"{func['args'][0][:-1]}{arg_num+1}"
            else:
                arg_name = func['args'][arg_num]
            self.args.append([arg_name,arg])
        self.args = dict(self.args)
    def __repr__(self) -> str:
        func_name = flo_func_db[self.num]['name']
        args = ', '.join([f'{q}={w}' for q,w in self.args.items()])
        return f'{func_name}({args})'

class reader_block(gen_init):
    def __init__(self):
        self.id = self.file.int()
        self.x = self.file.int()
        self.y = self.file.int()
        self.args = []
        for _ in range(flo_db[self.num]['arg_count'] - 4):
            val = yield
            self.args.append(val)
        return self

def read(file):
    head = [file.int() for _ in range(8)]
    gens = []
    blocks = []
    value = None
    while True:
        try:
            try:
                start = file.int()
            except EOFError:
                break
            if start < 1000:
                gens.append(readers[start](file, start))
            else:
                gens.append(reader_block(file, start))
            value = gen_send(gens[-1], value)
            while value is not None:
                gens.pop()
                if not gens:
                    break
                value = gen_send(gens[-1], value)
            if not gens:
                blocks.append(value)
                value = None
        except Exception:
            print(traceback.format_exc())
            break
    assert not gens
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
    print(block.num, block.id, block.x, block.y, block.args)


