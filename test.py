def call(*q):
    print(q)
def run():
    import test
    test.__call__=call
class d:
    def __call__(*a):
        print(a)