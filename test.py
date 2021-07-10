from functools import total_ordering
@total_ordering
class a:
 def __init__(s,q):
  s.q=q
 def __lt__(s,o):
  return s.q<o.q
print(a(1)<a(2))
print(a(1)==a(2))
print(a(1)>a(2))
print(a(1)>=a(2))
print(a(1)!=a(2))
print(a(1)<=a(2))

