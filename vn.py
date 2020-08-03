m=0
for 1=m<50:
 for 1=n<m+1:
  if ((m+n)*(m+n)*(m+n)+8)%(n*n+m*m):
   print(n,m)
