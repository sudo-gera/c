from time import time
from time import sleep
from sys import argv
y=argv[1]
y=y.split(':')
y=map(int,y)
y=list(y)
y=y[0]*3600+y[1]*60+y[2]
w=y
while 1:
 sleep(0.001)
 t=time()+3*3600
 y=w-t
 y%=3600*24
 t=y
 y=int(y)
 print(y//3600%24,y//60%60,y%60,str(t%1)[2:10],end='\r')
