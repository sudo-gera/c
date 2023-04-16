from multiprocessing import *
from os import *

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

# import pandas as pd
# df=pd.read_csv('/Users/gera/Downloads/flats_moscow.csv', delimiter=',')
# a=list(df[df.code == 6][df.brick == 0][df.floor == 1][df.livesp <= 48][df.livesp >= 42].price)
# s=sum(a)/len(a)
# d=[abs(w-s) for w in a]
# print(min(a),max(a),sum(a)/len(a),sum(d)/len(d))
