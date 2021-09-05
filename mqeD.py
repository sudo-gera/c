# n=input()
# try:
# 	a=[int(w) for w in input().split()]
# except:
# 	a=[int(w) for w in n.split()]	
# from sys import argv
# argv+=[]
# if len(argv)==1:
# 	if len(a)>0:
# 		print(0,end=' ')
# 	if len(a)>1:
# 		print(0,end=' ')
# 	if len(a)>2:
# 		min_index=2
# 		max_index=0
# 		global_max_index=0
# 		print(max(0,a[max_index]-a[min_index]),end=' ')
# 	for w in range(3,len(a)):
# 		if a[w-2]>a[global_max_index]:
# 			global_max_index=w-2
# 		if a[w]<=a[min_index]:
# 			min_index=w
# 		if a[w-2]-a[w]>=a[max_index]-a[min_index]:
# 			min_index=w
# 			max_index=w-2
# 		if a[max_index]-a[min_index]<=a[global_max_index]-a[w]:
# 			max_index=global_max_index
# 			min_index=w

# 		print(max(0,a[max_index]-a[min_index]),end=' ')
# else:
# 	for w in range(len(a)):
# 		print(max([a[e]-a[r] for e in range(w-1) for r in range(e+2,w+1)]+[0]),end=' ')
# print()
n=input()
a=[int(w) for w in input().split()]
if len(a)>0:
	print(0,end=' ')
if len(a)>1:
	print(0,end=' ')
if len(a)>2:
	min_index=2
	max_index=0
	global_max_index=0
	print(max(0,a[max_index]-a[min_index]),end=' ')
for w in range(3,len(a)):
	if a[w-2]>a[global_max_index]:
		global_max_index=w-2
	if a[w]<=a[min_index]:
		min_index=w
	if a[w-2]-a[w]>=a[max_index]-a[min_index]:
		min_index=w
		max_index=w-2
	if a[max_index]-a[min_index]<=a[global_max_index]-a[w]:
		max_index=global_max_index
		min_index=w
	print(max(0,a[max_index]-a[min_index]),end=' ')
print()
