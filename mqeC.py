n=int(input())
a=[int(w) for w in input().split()]
a.sort(reverse=1)
for w in range(len(a)):
	if a[w]<w+1:
		break
else:
	w+=1
print(w)