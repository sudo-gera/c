class test:
    def __enter__(self):
        return 0
    def __exit__(self,*a):
        print(a)

with test() as t:
    print(t)

