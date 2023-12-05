import test1
def run(q):
    print(__file__, q)
    if not q:
        return
    test1.run(q-1)