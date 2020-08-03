from os import system as sh
from sys import argv
sh('factor '+argv[1]+' > log')
q=open('log').read()
print(q)
