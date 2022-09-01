from h import *
# c=0
# def call(path,data):
#     return c(path,data)

def c(path,data):
    a=path
    print(a,data)
    a='http://www.babichev.org/'+a
    print(a,data)
    try:
        a=urlopen(a,data).read()
    except Exception:
        print(format_exc())
    try:
        a=a.decode()
        a=a.replace('www.babichev.org','localhost:1234')
        a=a.replace('https://','http://')
    except Exception:
        pass
    return a

a[0]=c