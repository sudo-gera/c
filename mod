q=2
while 1:
 if set([w**3%q for w in range(q)]) & set([(w**6+3*w**3+3)%q for w in range(q)]):
  pass
 else:
  print(q)
 q+=1
 
