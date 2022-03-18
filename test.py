from h import *
class a:
	def __init__(s):
		s.is_deleted=0
	def __del__(s):
		print('has',id(s.o),s.o.is_deleted)
		print('deleted',id(s),s.is_deleted)
		s.is_deleted=1

def run():
	q=a()
	w=a()
	q.o=w
	w.o=q

for w in range(20):
	run()
print('--')
