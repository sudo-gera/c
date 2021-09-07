from pynput.mouse import Controller
a=Controller()
from time import *
scs=[1440,900]
rect=[6,
	0,	0,
	  0]
while 1:
#	print(list(map(lambda x:str(10**9+round(x,4))[6:],a.position)),end='\n',sep='\t')
	if a.position[1]<rect[0]:
		a.position=(a.position[0],rect[0])
	if a.position[0]+a.position[1]*2<32:
		a.position=(a.position[0],(32-a.position[0])/2)
	if a.position[0]*2+a.position[1]<32:
		a.position=((32-a.position[1])/2,a.position[1])

	# if a.position[1]>scs[1]-rect[3]:
	# 	a.position=(a.position[0],scs[1]-rect[3])
	# if a.position[0]<rect[1]:
	# 	a.position=(rect[1],a.position[1])
	# if a.position[0]>scs[0]-rect[2]:
	# 	a.position=(scs[0]-rect[2],a.position[1])
	sleep(0.03)
