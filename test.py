from h import *
@dataclass
class a:
	deleted:int
	oth:int
	def __init__(s):
		s.deleted=0
	def __del__(s):
		print(s.oth)
		s.deleted=1

q=a()
w=a()
q.oth=w
w.oth=q
