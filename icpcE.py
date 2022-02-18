try:
	from h import *
except:
	ic = lambda *a: None if not a else a[0] if len(a) == 1 else a
from itertools import permutations
from functools import reduce
from math import gcd
def main(n):
	if n>72:
		for w in range(1,100):
			if n==reduce(gcd,[int(''.join(e)) for e in permutations(str(w))]):
				print(w)
				return
		print(-1)
		return
	else:
		print({

1:1
,
2:2
,
3:3
,
4:4
,
5:5
,
6:6
,
7:7
,
8:8
,
9:9
,
10:-1
,
11:11
,
12:48
,
13:-1
,
14:-1
,
15:5055
,
16:-1
,
17:-1
,
18:288
,
19:-1
,
20:-1
,
21:7077
,
22:22
,
23:-1
,
24:8088
,
25:-1
,
26:-1
,
27:3699
,
28:-1
,
29:-1
,
30:-1
,
31:-1
,
32:-1
,
33:33
,
34:-1
,
35:-1
,
36:48888
,
37:-1
,
38:-1
,
39:-1
,
40:-1
,
41:-1
,
42:-1
,
43:-1
,
44:44
,
45:-1
,
46:-1
,
47:-1
,
48:-1
,
49:-1
,
50:-1
,
51:-1
,
52:-1
,
53:-1
,
54:-1
,
55:55
,
56:-1
,
57:-1
,
58:-1
,
59:-1
,
60:-1
,
61:-1
,
62:-1
,
63:-1
,
64:-1
,
65:-1
,
66:66
,
67:-1
,
68:-1
,
69:-1
,
70:-1
,
71:-1
,
72:-1
,


		}[n])
		return

		# for w in range(1,10**5):
		# 	if n==reduce(gcd,[int(''.join(e)) for e in permutations(str(w))]):
		# 		print(w)
		# 		return
		# print(-1)
		# return

		# if n<10:
		# 	print(n)
		# 	return
		# if n==10:
		# 	print(-1)
		# 	return
		# print(48)


t=int(input())
for _t in range(t):
	n=int(input())
	main(n)

# for w in range(1,73):
# 	print(w,end=':')
# 	main(w)
# 	print(',')
