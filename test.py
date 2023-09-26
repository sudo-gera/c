def test():
    a=[]
    def test():
        print(id(a))
    return test
test = test()
for q in dir(test):
    print(q)
    help(test.__getattribute__(q))
# print(dir(test))
# test()





