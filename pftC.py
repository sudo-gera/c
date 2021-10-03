try:
	q=input()
	q=''.join([w for w in q if w in '(){}[]<>'])
	opened=[]
	for w in q:
		if w in '([{<':
			opened.append(ord(w))
		else:
			if not opened:
				print('NO')
				exit()
			if w!=dict('() [] {} <>'.split())[chr(opened.pop())]:
				print('NO')
				exit()
	if opened:
		print('NO')
		exit()
	print('YES')
except:
	pass