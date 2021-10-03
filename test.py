def binstr(q):
	from os import popen
	s=popen('./a.out '+str(q)).read().strip()
	s=s.replace('0','a')
	s=s.replace('1','c')
	s=s.replace('a','\x1b[40m+\x1b[0m')
	s=s.replace('c','\x1b[107m+\x1b[0m')
	return s

# for w in range(60):
# 	# print(w,'\t',binstr(2**w-2))
# 	print(w,'\t',binstr(2**w-1))
# 	print(w,'\t',binstr(2**w-0))
# 	print(w,'\t',binstr(2**w+1))
# 	# print(w,'\t',binstr(2**w+2))
print(binstr(2**(-16))