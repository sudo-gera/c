from urllib.request import urlopen
from multiprocessing import Process
from traceback import format_exc
from time imp
def run():
	try:
		urlopen('http://8.8.8.8').read()
	except KeyboardInterrupt:
		pass
if __name__ == '__main__':
	a=[]
	while 1:
		try:
				a.append(Process(target=run))
				a[-1].start()
		except KeyboardInterrupt:
			for w in a:
				w.kill()
			exit()
		except:
			print(format_exc())