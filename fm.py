def f(a,b):
 if a==b:
  return a
 a,b=max(a,b),min(a,b)
 return f(a-b,b)*a/(a-b)
print(f(3,6))
