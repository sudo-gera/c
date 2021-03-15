m=[99999999999,99999999999999]
try:
	q=100
	while 1:
		q+=1
		a='1'*q
		while '111' in a:
			a=a.replace('111','22',1)
			a=a.replace('222','11',1)
		print([a.count('1'),q])
		m=min([m,[a.count('1'),q]])
except:
	from traceback import *
	print(format_exc())
	print(m)