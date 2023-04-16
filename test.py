<<<<<<< HEAD
from multiprocessing import *
from os import *
=======
<<<<<<< HEAD
for q in range(60):
 for w in range(5):
  a=q*2
  s=q*3
  a-=w
  s-=4-w
  if a*4==s*3:
   print(a+w,s+4-w)

=======
from http.server import BaseHTTPRequestHandler, HTTPServer
import time
>>>>>>> fb9b6ebc3ad7dfa14c9b8b138f084c5747ade6e8

def run(*a):
    print(hash('0'))

if __name__ == '__main__':
    system('''python -c "__import__('test').run()"''')
    run()


# import csv
# with open('/Users/gera/Downloads/flats_moscow.csv', newline='') as csvfile:
#     dialect = csv.Sniffer().sniff(csvfile.read(1024))
#     csvfile.seek(0)
#     reader = list(csv.reader(csvfile, dialect))

<<<<<<< HEAD
# import pandas as pd
# df=pd.read_csv('/Users/gera/Downloads/flats_moscow.csv', delimiter=',')
# a=list(df[df.code == 6][df.brick == 0][df.floor == 1][df.livesp <= 48][df.livesp >= 42].price)
# s=sum(a)/len(a)
# d=[abs(w-s) for w in a]
# print(min(a),max(a),sum(a)/len(a),sum(d)/len(d))
=======
>>>>>>> 4bbbd537e2b77839d1cb2a08cf6fb785695d288b
>>>>>>> fb9b6ebc3ad7dfa14c9b8b138f084c5747ade6e8
