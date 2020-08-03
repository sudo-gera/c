import time,sys,tty,termios,os
while 1:
 fd = sys.stdin.fileno()
 old_settings = termios.tcgetattr(fd)
 try:
  tty.setraw(sys.stdin.fileno())
  ch = sys.stdin.read(1)
 finally:
  termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
 k=ord(ch)
 q=0
 while k!=0:
  q+=1
  k//=2
 print(ord(ch),2**q,2**q-ord(ch),q,ch)
 if ch == 'p':
  time.sleep(0.1)
  exit()

