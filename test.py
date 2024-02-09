import ast

try:
    ast.parse('''
q=0
w=0
"
"
''')
except Exception as _e:
    e=_e
for q in dir(e):
    if q[0]!='_':
        print(f'{q} = {repr(getattr(e, q))}')

