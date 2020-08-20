q=input()
q=('+'+q.replace('+','0+').replace('-','0-')).split('0')
q=[w[1:][::-1] if '-' in w else w[1:] for w in q]
while 1:
 for w in q:
  if w
