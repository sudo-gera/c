from h import *
# a=open('uran.o').read()
a=run(['objdump','-d','uran.o'],stdout=-1).stdout.read().decode()
print(a)
