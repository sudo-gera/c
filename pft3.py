q=input()
opened=[]
for w in q:
	if w in '([{<':
		opened.append(w)
	else:
		if not opened:
			print('NO')
			exit()
		if w!=dict('() [] {} <>'.split())[opened.pop()]:
			print('NO')
			exit()
if opened:
	print('NO')
	exit()
print('YES')