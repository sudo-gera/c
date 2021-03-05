import operator
exec('''
class typed:
	def __init__(s,t,v=None):
		s.t=t
		if v!=None:
			s.v=t(v)
		else:
			s.v=t()
'''+''.join([f'\tdef {w}(s,o):\n\t\treturn typed(type(s.v),operator.{w}(s.v,o.v))\n' for w in dir(operator)])+'''
	def __lshift__(s,v):
		s.v=s.t(v)
	def __str__(s):
		return str(s.v)
	def __repr__(s):
		return repr(s.v)
''')

