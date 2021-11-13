def run(q):
	q(0)
	return q
@run
def run(q):
		q=str(q)
		try:
			from sys import argv
			from subprocess import run
			from os.path import exists
		except:
			print('\x1b[91mthis file should be started as \x1b[94mpython3 '+__file__+'\x1b[0m')
			exit()
		if not exists('/root/prog'):
			print('\x1b[91mprog file not found\x1b[0m')
			exit()
		run(['chmod','777','/root/prog'])
		return int(run('/root/prog',input=q.encode(),capture_output=1).stdout.decode())
