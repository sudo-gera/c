class a:
    def __init__(self):
        print('a')
        self.a=[]

class b(a):
    def __init__(self):
        # super().__init__()
        print('b')
        self.a.append(0)

class c(a):
    def __init__(self):
        print('c')

class d(b, c):
    pass



# b()
print()
d()