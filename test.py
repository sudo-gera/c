from server_example import *
s=Server()
print(s.port)
print(get_ips())
while 1:
	print(s.get())
	s.put('')