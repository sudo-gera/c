from h import *

from server_example import *

a=Server()
print(a.port)

while 1:
	print(a.get())
	a.put(0)
