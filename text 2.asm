accelerate:
push   ebp
mov    ebp,esp
sub    esp,0x14
fld    DWORD [ebp+0x8]
fldpi
fmul   st0,st1
fstp   DWORD [ebp-0x4]
mov    eax,DWORD [ebp-0x4]
mov    DWORD [ebp-0x14],eax
fld    DWORD [ebp-0x14]
leave  
ret
