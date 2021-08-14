# r=[[1,2,3],[4,5,6],[7,8,9]]
# e=[q for w in r for q in w]
# for w in e:
# 	print(w)

def run():
	print('run')
	return [1,2,3]

for w in run():
	print(w)