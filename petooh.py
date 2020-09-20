from sys import argv
q=list(argv[1].encode('ASCII'))
q=['Ko'*w+' Kukarek Kudah ' for w in q]
print(''.join(q))
