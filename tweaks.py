from time import sleep as sl
print('1234\r',end='')
sl(2)
print('\x1b[0;33m456\x1b[0m')
