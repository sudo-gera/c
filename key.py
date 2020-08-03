import time,sys,tty,termios,os
class _Getch:
    def __call__(self):
            fd = sys.stdin.fileno()
            old_settings = termios.tcgetattr(fd)
            try:
                tty.setraw(sys.stdin.fileno())
                ch = sys.stdin.read(1)
            finally:
                termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
            return ch

os.system('python game.py &')
inkey = _Getch()
while 1:
    k=inkey()
    a=open('key','a')
    a.write(k)
    a.close()
    if k == 'p':
     time.sleep(0.1)
     exit()
