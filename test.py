<<<<<<< HEAD
from server_example import *
a=Server()
print(get_ips())
print(a.port)
while 1:
	s=a.get()
	try:
		a.put(open(s[0],'rb').read())
	except:
		from traceback import format_exc
		print(format_exc())
=======
<<<<<<< HEAD
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

=======
from lancom import *
>>>>>>> 958edbffff45f5181ed6079b76bc214c68e40101
>>>>>>> 25b0d80edd7bf374a8909a347803a8099de62da4
