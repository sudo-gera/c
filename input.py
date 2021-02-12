_scan_buffer=[]
def scan(ty=str):
	global _scan_buffer
	if _scan_buffer==[]:
		_scan_buffer=input().split()
	d=ty(_scan_buffer[0])
	_scan_buffer=_scan_buffer[1:]
	return d

##########################################

q=scan(int)
w=scan(int)
e=scan(int)
r=scan(int)
t=scan(int)
y=scan(int)
print(q+w+e+r+t+y)