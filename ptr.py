import inspect
import operator

class Pointer:
    def __init__(self, **args):
        self.__dict__[0] = args
    def __call__(self, mode, *args):
        if not args:
            return Pointer(obj = mode)
        locs = self.__dict__[0]
        func = [
            getattr,
            setattr,
            delattr,
            operator.getitem,
            operator.setitem,
            operator.delitem,
        ]
        if 'key' in locs and 'obj' in locs and 'mode' in locs:
            lmode = locs['mode']
            index = locs['key']
            try:
                index += args[0]
            except Exception:
                pass
            return func[mode%3+lmode*3](locs['obj'], index, *args[1:])
        if 'obj' not in locs:
            frame = inspect.stack()[2].frame
            for d in [frame.f_locals, frame.f_globals, frame.f_builtins]:
                if args[0] in d:
                    return Pointer(obj = d)(mode+3, *args)
        return Pointer(obj = locs['obj'], key = args[0], mode = mode//3)
    def __getattr__(self, key):
        return self(0,key)
    def __setattr__(self, key,val):
        return self(1,key,val)
    def __delattr__(self, key):
        return self(2,key)
    def __getitem__(self, key):
        return self(3, key)
    def __setitem__(self, key, val):
        return self(4,key,val)
    def __delitem__(self, key):
        return self(5,key)





ptr = Pointer()

def test():
    f = 0
    f_ptr = ptr.f
    f_ptr[0] = 2
    assert f == 2 # doesnt work...
    class d:
        pass
    s = d()
    a_ptr = ptr(s).a
    a_ptr[0] = 3
    assert s.a == 3
    q = [10, 11, 12]
    q_ptr = ptr(q)[1]
    q_ptr[-1] = 20
    q_ptr[0] = 21
    q_ptr[1] = 22
    assert q == [20, 21, 22]

if __name__ == '__main__':
    test()
    f = 0
    f_ptr = ptr.f
    f_ptr[0] = 2
    assert f == 2
    class d:
        pass
    s = d()
    a_ptr = ptr(s).a
    a_ptr[0] = 3
    assert s.a == 3
    q = [10, 11, 12]
    q_ptr = ptr(q)[1]
    q_ptr[-1] = 20
    q_ptr[0] = 21
    q_ptr[1] = 22
    assert q == [20, 21, 22]


