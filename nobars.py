# # def main():
# if 1:
# 	from time import sleep
# 	sleep(1)
# 	import pygame
# 	clock = pygame.time.Clock()ww111234rf
# 	pygame.init()
# 	pygame.display.set_mode([333,333]).fill([20,20,40])
# 	done = 0
# 	while not done:
# 		pygame.display.update()
# 		for e in pygame.event.get():
# 			print(e)
# 			if e.type == pygame.QUIT or (e.type == pygame.KEYUP and e.key == pygame.K_ESCAPE):
# 				done = 1
# 				break
# 		clock.tick(50)
# 	# pygame.display.quit()
# 	pygame.quit()
# main()

# from pynput.keyboard import Listener
# def run(q):
# 	pass
# 	# print(q)
# listener = Listener(
#     on_press=run,
#     on_release=run)
# listener.start()
# listener.join()

if __name__ == '__main__':
	from pynput.mouse import Controller
	a=Controller()
	from time import *
	scs=[1440,900]
	rect=[6,
		0,	0,
		  0]
	while 1:
		if a.position[1]<rect[0]:
			a.position=(a.position[0],rect[0])
		if a.position[1]<45 and a.position[1]*20>a.position[0]*45:
			a.position=[20,45]
		sleep(0.03)
