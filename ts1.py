from fractions import Fraction
a,s,d,f=list(map(Fraction,input().split()))
if a<=s<=d<=f or a>=s>=d>=f:
    print("YES")
else:
    print("NO")
