try:
	q=input()
except:
	q=''
q=''.join([w for w in q if w in '(){}[]<>'])
opened=[]
try:
	for w in q:
		if w in '([{<':
			opened.append(dict('() [] {} <>'.split())[w])
		else:
			if not opened:
				print('NO')
				exit()
			elif w!=opened.pop():
				print('NO')
				exit()
except:
	pass
# if opened:
# 	print('NO')
# else:
# 	print('YES')
print('NO')