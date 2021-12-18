from h import *
def check_rev_h(q):
	for w in range(len(q)):
		if q[w] in '1380':
			pass
		else:
			return 0
	return 1

def check_rev_v(q):
	for w in range(len(q)):
		if q[w]=='2':
			if q[-1-w]!='5':
				return 0
		elif q[w]=='5':
			if q[-1-w]!='2':
				return 0
		elif q[w]=='0':
			if q[-1-w]!='0':
				return 0
		elif q[w]=='8':
			if q[-1-w]!='8':
				return 0
		else:
			return 0
	return 1;

def check_rev(q):
	return check_rev_h(q) or check_rev_v(q)

# def count_with_zero(pref,count):
# 	res=0;
# 	if check_rev_h(pref):
# 		res+=4**count
# 	if check_rev_v(pref[count:]) and all([w in '5208' for w in pref]):
# 		if count>len(pref):
# 			if (count-len(pref))%2:
# 				res+=4**((count-len(pref))//2)*2
# 			else:
# 				res+=4**((count-len(pref))//2)
# 		else:
# 			res+=1
# 	if check_rev_h(pref) and check_rev_v(pref[count:]) and all([w in '5208' for w in pref]):
# 		res-=2**max((len(pref)+count+1)//2-len(pref),0)
# 	return res

# def count_with_zero1(pref,count):
# 	pref1=int(pref+'0'*count)
# 	pref2=int(pref+'9'*count)+1
# 	c=0
# 	for w in range(pref1,pref2):
# 		c+=bool(check_rev(str(w)))
# 	return c


# while 1:
# 	pref=str(1+int(''.join([ str(randint(0,9)) for w in range(randint(1,20)) ])))
# 	count=randint(0,20-len(pref)+1)
# 	count_with_zero(pref,count)
# 	print('--')
# 	# if count_with_zero(pref,count)!=count_with_zero1(pref,count):
# 	# 	print(pref,count)
# 	# 	exit()

# print(count_with_zero('8',1))
# print(count_with_zero1('8',1))

pref1,pref2=[int(w) for w in input().split()]
pref2+=1
c=0
for w in range(pref1,pref2):
	c+=bool(check_rev(str(w)))
	c%=10**9+7
print(c)

