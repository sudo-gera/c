import test2
def run(q):
    print(__file__, q)
    if not q:
        return
    test2.run(q-1)