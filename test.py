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