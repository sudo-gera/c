import termios
import copy
import sys
# from termios import *

def receive_key_event_unsafe():
    # if you will use it in while(1)
    # you will never stop
    # ctrl+C returns as 3
    fd = sys.stdin.fileno()
    mode = termios.tcgetattr(fd)
    save = copy.copy(mode)
    mode[0] &= ~(termios.BRKINT | termios.ICRNL | termios.INPCK | termios.ISTRIP | termios.IXON)
    mode[1] &= ~(termios.OPOST)
    mode[2] &= ~(termios.CSIZE | termios.PARENB)
    mode[2] |= termios.CS8
    mode[3] &= ~(termios.ECHO | termios.ICANON | termios.IEXTEN | termios.ISIG)
    mode[6][termios.VMIN] = 1
    mode[6][termios.VTIME] = 0
    termios.tcsetattr(fd, termios.TCSAFLUSH, mode)
    c = sys.stdin.buffer.read(1)
    termios.tcsetattr(fd, termios.TCSADRAIN, save)
    return c


def receive_key_event():
    k=receive_key_event_unsafe()
    # stop if
    #   ctrl+shift+@ is 0
    #   ctrl+A is 1
    #   ctrl+B is 2
    #   ctrl+C is 3
    #   ctrl+D is 4
    if k[0] < 5:
        exit(0)
    return k


while True:
    sys.stdout.buffer.write(receive_key_event())
    sys.stdout.flush()