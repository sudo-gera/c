from __future__ import annotations
from typing import Any
from h import *
import sys
import json
import functools
import traceback
import types
import typing
from collections import defaultdict as dd

class flo_file:
    def __init__(self : flo_file, file : typing.BinaryIO):
        self.file = file
    def char(self : flo_file) -> int:
        c = self.file.read(1)
        if len(c) == 0:
            raise EOFError
        return c[0]
    def uns(self : flo_file) -> int:
        result = ''
        while True:
            q = self.char()
            q = bin(q+256)[-8:]
            result = q[1:] + result
            if q[0]=='0':
                return int(result,2)
    def int(self) -> int:
        q = self.uns()
        return -(q+1)//2 if q%2 else q//2
    def str(self) -> str:
        res = bytearray()
        for q in range(self.uns()):
            res.append(self.char())
        return res.decode()


with open('flo.json') as db_file:
    flo_db = {int(key):val for key,val in json.load(db_file).items()}
with open('flo_func.json') as db_file:
    flo_func_db = {int(key):val for key,val in json.load(db_file).items()}
readers = {}


class starts_with:
    def __init__(self, *nums:int):
        self.nums = nums
    def __call__(self, func):
        for num in self.nums:
            readers[num] = func
        return func

class gen_init:
    def reader_(self, file, num):
        reader = self.reader()
        if reader is not None:
            yield from reader
    def __init__(self, file, num):
        self.file = file
        self.num = num
        self.gen = self.reader_(file, num)
        self.args_read = 0
        self.yargs = []
        self.args_need = next(self.gen, 0)
        if not self.args_need:
            next(self.gen, 0)
            self.gen = None
    def __getattr__(self, name: str) -> Any:
        return f'<?{name}?>'
    def gen_send(self, arg):
        try:
            self.yargs.append(arg)
            self.args_read += 1
            self.args_need -= 1
            if self.args_need == 0:
                self.gen.send(0)
        except StopIteration:
            self.gen = None



@starts_with(16)
class reader_select(gen_init):
    def reader(self):
        self.shared = False
        self.args = self.file.int()
    def __repr__(self):
        return f'select({self.args})'

@starts_with(105)
class reader_fstr(gen_init):
    def reader(self):
        self.shared = False
        num_insertions = self.file.uns() - 1
        self.strs = []
        for q in range(num_insertions + 1):
            data = []
            for q in range(self.file.uns()):
                data.append(self.file.char())
            self.strs.append(bytes(data).decode())
        yield num_insertions
        self.values = self.yargs
        self.file.uns()
    def __repr__(self) -> str:
        res = ''
        for q,w in list(zip(self.strs, self.values)):
            res += repr(q) + '{' + repr(w) + '}'
        res += repr(self.strs[-1])
        return f'fstr({res})'

@starts_with(106)
class reader_str(gen_init):
    def reader(self):
        self.shared = False
        self.data = []
        for q in range(self.file.uns()):
            self.data.append(self.file.char())
        self.data = bytes(self.data).decode()
    def __repr__(self) -> str:
        return f'flo_str({self.data!r})'

@starts_with(102)
class reader_var(gen_init):
    def reader(self):
        self.shared = True
        yield 0
        self.data = []
        for q in range(self.file.uns()):
            self.data.append(self.file.char())
        self.data = bytes(self.data).decode()
    def __repr__(self) -> str:
        return f'flo_var({self.data!r})'

@starts_with(104, 101)
class reader_num(gen_init):
    def reader(self):
        self.shared = False
        self.data = [self.file.char() for _ in range(8)]
        self.data = ''.join([bin(q + 256)[-8:] for q in self.data])
        a = int(self.data[:12], 2)
        s = int(self.data[12:], 2)
        a -= 1023
        f = 2**(len(self.data)-12)
        s += f
        self.d = s * 2**a / f
    def __repr__(self) -> str:
        return f'{self.d}'

@starts_with(131, 113, 125, 134, 139, 140, 126, )
class reader_un_op(gen_init):
    def reader(self):
        self.shared = False
        yield 1
        self.arg = self.yargs[-1]
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
    def reader(self):
        self.shared = False
        yield 2
        self.left, self.right = self.yargs
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
    def reader(self):
        self.shared = False
        yield 3
        self.condition, self.then, self.orelse = self.yargs
    def __repr__(self) -> str:
        return f'{self.condition} ? {self.then} : {self.orelse}'

@starts_with(0, 103, 201, 202, 203, '-2')
class reader_const(gen_init):
    def reader(self):
        self.shared = True
        pass
    def __repr__(self) -> str:
        names = {
            0: 'None',
            202: 'Now',
            103: 'null',
            201: 'Nan',
            203: 'Pi',
        }
        name = names[self.num] if self.num in names else f'_{self.num}_'
        return f'flo_const({name})'

@starts_with(*map(int, flo_func_db))
class reader_func(gen_init):
    def reader(self):
        self.shared = False
        func = flo_func_db[self.num]
        self.args = []
        if '\u2026' in func['args']:
            arg_count = self.file.uns()
        else:
            arg_count = len(func['args'])
        yield arg_count
        for arg_num,arg in enumerate(self.yargs):
            if '\u2026' in func['args']:
                arg_name = f"{func['args'][0][:-1]}{arg_num+1}"
            else:
                arg_name = func['args'][arg_num]
            self.args.append([arg_name,arg])
        self.args = dict(self.args)
    def __repr__(self) -> str:
        func_name = flo_func_db[self.num]['name'] if self.num in flo_func_db else '<?name?>'
        args = list(self.args.items()) if isinstance(self.args, dict) else self.args
        args = ', '.join([f'{q}={w}' for q,w in args]) if isinstance(self.args, list) else self.args
        return f'{func_name}({args})'

class reader_block(gen_init):
    def reader(self):
        self.shared = True
        self.id = self.file.int()
        self.x = self.file.int()
        self.y = self.file.int()
        yield (flo_db[self.num]['arg_count'] - 4)
        self.args = self.yargs
        return self
    # TODO:
    # read last item
    # or it will be read as next arg
    def __repr__(self) -> str:
        if isinstance(self.num, int):
            count = flo_db[self.num]['arg_count'] - 4
        else:
            count = 0
        args = str(self.args) + "?" * (count - len(self.args)) if isinstance(self.args, list) else []
        # return f'block(num = {self.num}, id = {self.id}, x = {self.x}, y = {self.y}, args = {args})'
        # return f'block(id = {self.id})'
        return f'block(id = {self.id}, num = {self.num})'


def get_reader(start):
    if start < 0:
        return readers['-2']
    elif start < 1000:
        return readers[start]
    else:
        return reader_block
    

def read(file):
    head = [file.int() for _ in range(8)]
    gens = []
    blocks = []
    objects = []
    while True:
        try:
            try:
                start = file.int()
            except EOFError:
                break
            gens.append(get_reader(start)(file, start))
            objects.append(gens[-1])

            while gens and gens[-1].gen is None:
                value = gens.pop()
                if value.num >= 1000:
                    blocks.append(value)
                if gens:
                    gens[-1].gen_send(value)
                else:
                    print(value)

        except Exception:
            print(traceback.format_exc(), file=sys.stderr)
            data = file.file.read()
            print(data)
            print(binstr(data))
    assert not gens
    # blocks.sort(key=lambda b:b.id)
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

# raw_read(flo_file(open(sys.argv[1],'rb')))
for block in read(flo_file(open(sys.argv[1],'rb'))):
    print(block.num, block.id, block.x, block.y, block.args)



