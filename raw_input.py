import termios
import copy
import sys
from termios import *

def receive_key_event_unsafe():
    # if you will use it in while(1)
    # you will never stop
    # ctrl+C returns as 3
    fd=sys.stdin.fileno()
    mode=termios.tcgetattr(fd)
    save=copy.copy(mode)
    mode[0] &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON)
    mode[1] &= ~(OPOST)
    mode[2] &= ~(CSIZE | PARENB)
    mode[2] |= CS8
    mode[3] &= ~(ECHO | ICANON | IEXTEN | ISIG)
    mode[6][VMIN] = 1
    mode[6][VTIME] = 0
    termios.tcsetattr(fd, termios.TCSAFLUSH, mode)
    c=sys.stdin.read(1);
    termios.tcsetattr(fd, termios.TCSADRAIN, save);
    return c;


def receive_key_event():
    k=receive_key_event_unsafe()
    # stop if
    #   ctrl+shift+@ is 0
    #   ctrl+A is 1
    #   ctrl+B is 2
    #   ctrl+C is 3
    #   ctrl+D is 4
    if ord(k[0])<5:
        exit(0)
    return k;


while(1):
    print(receive_key_event(),end='')
    sys.stdout.flush()