import os
print('\n'*(os.get_terminal_size()[1]))
q=0
a=0
d=''
try:
 while 1:
  print('\x1b[2j\x1b[H')
  print(' '*(os.get_terminal_size()[0]*(os.get_terminal_size()[1]-5)))
  print('\x1b[2j\x1b[H')
  if q%2:
   print('\n'*(q//2)+' '*a+'▄')
  else:
   print('\n'*(q//2)+' '*a+'▀')
  print('\n'*(os.get_terminal_size()[1]-q//2-10))
  print('╔═╗')
  print('║ ║')
  print('╚═╝')
  print('\x1b[2j\x1b[H')
  print('\n'*(os.get_terminal_size()[1]-8))
  d=input('║')
  while d!='':
   f=d[0]
   d=d[1:]
   if f=='w' and q>0:
    q-=1
   if f=='a' and a>0:
    a-=1
   if f=='s' and q<2*os.get_terminal_size()[1]-20:
    q+=1
   if f=='d' and a<os.get_terminal_size()[0]-1:
    a+=1
except KeyboardInterrupt:
 print('\x1b[2j\x1b[H')
