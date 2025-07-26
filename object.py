class Object(dict):  # allow a.name instead of a['name'] for JSON types
    def __init__(self, *a, **s):
        super().__init__(*a, **s)
        self.__dict__ = self

    @staticmethod
    def __convert(obj, build, Obj):
        if isinstance(obj, dict):
            return Obj({q: build(w) for q,w in obj.items()})
        if isinstance(obj, list):
            return [build(w) for w in obj]
        return obj

    @staticmethod
    def _build(obj):
        return Object.__convert(obj, Object._build, Object)

    @staticmethod
    def _destroy(obj):
        return Object.__convert(obj, Object._destroy, lambda x:x)

if __name__ == '__main__': #tests
    d = {
        'q': [1,2,3],
        'w': 0,
        'e': {
            'e':{
                'e':1
            }
        }
    }
    od = Object._build(d)
    assert od.q == [1,2,3]
    assert od.w == 0
    assert od.e.e.e == 1
    od.e.r = 4
    del od.e.e.e
    d = Object._destroy(od)
    assert d == {
        'q': [1,2,3],
        'w': 0,
        'e': {
            'e':{
            },
            'r': 4
        }
    }
    

