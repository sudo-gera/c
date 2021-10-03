ax,ay,bx,by=[int(w) for w in input().split()]
from math import *
p=(atan2(abs(ax*by-ay*bx),ax*bx+ay*by))
print(p)
# print(p/pi*180)