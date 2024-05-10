class meta(type):
    def __init__(self, name, bases, namespace):
        print('__init__', name, bases, namespace)
        super().__init__(name, bases, namespace)
        
    def __call__(self):
        new_instance = super().__call__()
        print('call', new_instance)
        return new_instance

class a(metaclass=meta):
    def __new__(cls):
        obj = super().__new__(cls)
        print('new', obj)
        return obj
    
    def __init__(self) -> None:
        print('init', self)
    

s = a()

