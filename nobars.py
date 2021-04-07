from pynput.mouse import Controller
a=Controller()
from time import *
while 1:
	if a.position[1]<4:
		a.position=(a.position[0],4)
	sleep(0.01)