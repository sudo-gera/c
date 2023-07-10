content=dict(
    error=[],
    message=[],
)
while 1:
    try:
        n,a=input().split()
    except EOFError:
        break
    else:
        if not n.isdigit() or len(a)<=3:
            n=float(n)
            content['error'].append([n,a])
        else:
            n=int(n)
            content['message'].append([n,a])
print(dict(content['message']))
