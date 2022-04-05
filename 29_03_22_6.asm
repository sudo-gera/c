%include "macro.inc"
start
dget eax
dget ebx
dget ecx
dget edx
dget esi
dget edi
dget ebp
regout
pushad
mov [esp+28],dword 200
regout
popad
regout
stop
