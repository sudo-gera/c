from h import *

try:
	a=Popen([executable,'test2.py'])
	a.wait()
except:
	a.terminate()
	print('--',format_exc())
	pass
