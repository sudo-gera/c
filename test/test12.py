content=dict(
    error=[],
    message=[],
)
while 1:
    s=input()
    if s=='\exit':
        break
    n,a=s.split()
    if not n.isdigit() or len(a)<=3:
        n=float(n)
        content['error'].append([n,a])
    else:
        n=int(n)
        content['message'].append([n,a])
print(dict(content['message']))
