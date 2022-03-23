%macro macro_args_read_bbbb 4
regsave
push byte  %1
push byte  %2
push byte  %3
push byte  %4
regnull
pop  dl
pop  cl
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbbb 4
regsave
push word  %1
push byte  %2
push byte  %3
push byte  %4
regnull
pop  dl
pop  cl
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbbb 4
regsave
push dword %1
push byte  %2
push byte  %3
push byte  %4
regnull
pop  dl
pop  cl
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwbb 4
regsave
push byte  %1
push word  %2
push byte  %3
push byte  %4
regnull
pop  dl
pop  cl
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwbb 4
regsave
push word  %1
push word  %2
push byte  %3
push byte  %4
regnull
pop  dl
pop  cl
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwbb 4
regsave
push dword %1
push word  %2
push byte  %3
push byte  %4
regnull
pop  dl
pop  cl
pop  bx
pop eax
%endmacro
%macro macro_args_read_bdbb 4
regsave
push byte  %1
push dword %2
push byte  %3
push byte  %4
regnull
pop  dl
pop  cl
pop ebx
pop  al
%endmacro
%macro macro_args_read_wdbb 4
regsave
push word  %1
push dword %2
push byte  %3
push byte  %4
regnull
pop  dl
pop  cl
pop ebx
pop  ax
%endmacro
%macro macro_args_read_ddbb 4
regsave
push dword %1
push dword %2
push byte  %3
push byte  %4
regnull
pop  dl
pop  cl
pop ebx
pop eax
%endmacro
%macro macro_args_read_bbwb 4
regsave
push byte  %1
push byte  %2
push word  %3
push byte  %4
regnull
pop  dl
pop  cx
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbwb 4
regsave
push word  %1
push byte  %2
push word  %3
push byte  %4
regnull
pop  dl
pop  cx
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbwb 4
regsave
push dword %1
push byte  %2
push word  %3
push byte  %4
regnull
pop  dl
pop  cx
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwwb 4
regsave
push byte  %1
push word  %2
push word  %3
push byte  %4
regnull
pop  dl
pop  cx
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwwb 4
regsave
push word  %1
push word  %2
push word  %3
push byte  %4
regnull
pop  dl
pop  cx
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwwb 4
regsave
push dword %1
push word  %2
push word  %3
push byte  %4
regnull
pop  dl
pop  cx
pop  bx
pop eax
%endmacro
%macro macro_args_read_bdwb 4
regsave
push byte  %1
push dword %2
push word  %3
push byte  %4
regnull
pop  dl
pop  cx
pop ebx
pop  al
%endmacro
%macro macro_args_read_wdwb 4
regsave
push word  %1
push dword %2
push word  %3
push byte  %4
regnull
pop  dl
pop  cx
pop ebx
pop  ax
%endmacro
%macro macro_args_read_ddwb 4
regsave
push dword %1
push dword %2
push word  %3
push byte  %4
regnull
pop  dl
pop  cx
pop ebx
pop eax
%endmacro
%macro macro_args_read_bbdb 4
regsave
push byte  %1
push byte  %2
push dword %3
push byte  %4
regnull
pop  dl
pop ecx
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbdb 4
regsave
push word  %1
push byte  %2
push dword %3
push byte  %4
regnull
pop  dl
pop ecx
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbdb 4
regsave
push dword %1
push byte  %2
push dword %3
push byte  %4
regnull
pop  dl
pop ecx
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwdb 4
regsave
push byte  %1
push word  %2
push dword %3
push byte  %4
regnull
pop  dl
pop ecx
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwdb 4
regsave
push word  %1
push word  %2
push dword %3
push byte  %4
regnull
pop  dl
pop ecx
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwdb 4
regsave
push dword %1
push word  %2
push dword %3
push byte  %4
regnull
pop  dl
pop ecx
pop  bx
pop eax
%endmacro
%macro macro_args_read_bddb 4
regsave
push byte  %1
push dword %2
push dword %3
push byte  %4
regnull
pop  dl
pop ecx
pop ebx
pop  al
%endmacro
%macro macro_args_read_wddb 4
regsave
push word  %1
push dword %2
push dword %3
push byte  %4
regnull
pop  dl
pop ecx
pop ebx
pop  ax
%endmacro
%macro macro_args_read_dddb 4
regsave
push dword %1
push dword %2
push dword %3
push byte  %4
regnull
pop  dl
pop ecx
pop ebx
pop eax
%endmacro
%macro macro_args_read_bbbw 4
regsave
push byte  %1
push byte  %2
push byte  %3
push word  %4
regnull
pop  dx
pop  cl
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbbw 4
regsave
push word  %1
push byte  %2
push byte  %3
push word  %4
regnull
pop  dx
pop  cl
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbbw 4
regsave
push dword %1
push byte  %2
push byte  %3
push word  %4
regnull
pop  dx
pop  cl
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwbw 4
regsave
push byte  %1
push word  %2
push byte  %3
push word  %4
regnull
pop  dx
pop  cl
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwbw 4
regsave
push word  %1
push word  %2
push byte  %3
push word  %4
regnull
pop  dx
pop  cl
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwbw 4
regsave
push dword %1
push word  %2
push byte  %3
push word  %4
regnull
pop  dx
pop  cl
pop  bx
pop eax
%endmacro
%macro macro_args_read_bdbw 4
regsave
push byte  %1
push dword %2
push byte  %3
push word  %4
regnull
pop  dx
pop  cl
pop ebx
pop  al
%endmacro
%macro macro_args_read_wdbw 4
regsave
push word  %1
push dword %2
push byte  %3
push word  %4
regnull
pop  dx
pop  cl
pop ebx
pop  ax
%endmacro
%macro macro_args_read_ddbw 4
regsave
push dword %1
push dword %2
push byte  %3
push word  %4
regnull
pop  dx
pop  cl
pop ebx
pop eax
%endmacro
%macro macro_args_read_bbww 4
regsave
push byte  %1
push byte  %2
push word  %3
push word  %4
regnull
pop  dx
pop  cx
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbww 4
regsave
push word  %1
push byte  %2
push word  %3
push word  %4
regnull
pop  dx
pop  cx
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbww 4
regsave
push dword %1
push byte  %2
push word  %3
push word  %4
regnull
pop  dx
pop  cx
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwww 4
regsave
push byte  %1
push word  %2
push word  %3
push word  %4
regnull
pop  dx
pop  cx
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwww 4
regsave
push word  %1
push word  %2
push word  %3
push word  %4
regnull
pop  dx
pop  cx
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwww 4
regsave
push dword %1
push word  %2
push word  %3
push word  %4
regnull
pop  dx
pop  cx
pop  bx
pop eax
%endmacro
%macro macro_args_read_bdww 4
regsave
push byte  %1
push dword %2
push word  %3
push word  %4
regnull
pop  dx
pop  cx
pop ebx
pop  al
%endmacro
%macro macro_args_read_wdww 4
regsave
push word  %1
push dword %2
push word  %3
push word  %4
regnull
pop  dx
pop  cx
pop ebx
pop  ax
%endmacro
%macro macro_args_read_ddww 4
regsave
push dword %1
push dword %2
push word  %3
push word  %4
regnull
pop  dx
pop  cx
pop ebx
pop eax
%endmacro
%macro macro_args_read_bbdw 4
regsave
push byte  %1
push byte  %2
push dword %3
push word  %4
regnull
pop  dx
pop ecx
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbdw 4
regsave
push word  %1
push byte  %2
push dword %3
push word  %4
regnull
pop  dx
pop ecx
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbdw 4
regsave
push dword %1
push byte  %2
push dword %3
push word  %4
regnull
pop  dx
pop ecx
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwdw 4
regsave
push byte  %1
push word  %2
push dword %3
push word  %4
regnull
pop  dx
pop ecx
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwdw 4
regsave
push word  %1
push word  %2
push dword %3
push word  %4
regnull
pop  dx
pop ecx
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwdw 4
regsave
push dword %1
push word  %2
push dword %3
push word  %4
regnull
pop  dx
pop ecx
pop  bx
pop eax
%endmacro
%macro macro_args_read_bddw 4
regsave
push byte  %1
push dword %2
push dword %3
push word  %4
regnull
pop  dx
pop ecx
pop ebx
pop  al
%endmacro
%macro macro_args_read_wddw 4
regsave
push word  %1
push dword %2
push dword %3
push word  %4
regnull
pop  dx
pop ecx
pop ebx
pop  ax
%endmacro
%macro macro_args_read_dddw 4
regsave
push dword %1
push dword %2
push dword %3
push word  %4
regnull
pop  dx
pop ecx
pop ebx
pop eax
%endmacro
%macro macro_args_read_bbbd 4
regsave
push byte  %1
push byte  %2
push byte  %3
push dword %4
regnull
pop edx
pop  cl
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbbd 4
regsave
push word  %1
push byte  %2
push byte  %3
push dword %4
regnull
pop edx
pop  cl
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbbd 4
regsave
push dword %1
push byte  %2
push byte  %3
push dword %4
regnull
pop edx
pop  cl
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwbd 4
regsave
push byte  %1
push word  %2
push byte  %3
push dword %4
regnull
pop edx
pop  cl
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwbd 4
regsave
push word  %1
push word  %2
push byte  %3
push dword %4
regnull
pop edx
pop  cl
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwbd 4
regsave
push dword %1
push word  %2
push byte  %3
push dword %4
regnull
pop edx
pop  cl
pop  bx
pop eax
%endmacro
%macro macro_args_read_bdbd 4
regsave
push byte  %1
push dword %2
push byte  %3
push dword %4
regnull
pop edx
pop  cl
pop ebx
pop  al
%endmacro
%macro macro_args_read_wdbd 4
regsave
push word  %1
push dword %2
push byte  %3
push dword %4
regnull
pop edx
pop  cl
pop ebx
pop  ax
%endmacro
%macro macro_args_read_ddbd 4
regsave
push dword %1
push dword %2
push byte  %3
push dword %4
regnull
pop edx
pop  cl
pop ebx
pop eax
%endmacro
%macro macro_args_read_bbwd 4
regsave
push byte  %1
push byte  %2
push word  %3
push dword %4
regnull
pop edx
pop  cx
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbwd 4
regsave
push word  %1
push byte  %2
push word  %3
push dword %4
regnull
pop edx
pop  cx
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbwd 4
regsave
push dword %1
push byte  %2
push word  %3
push dword %4
regnull
pop edx
pop  cx
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwwd 4
regsave
push byte  %1
push word  %2
push word  %3
push dword %4
regnull
pop edx
pop  cx
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwwd 4
regsave
push word  %1
push word  %2
push word  %3
push dword %4
regnull
pop edx
pop  cx
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwwd 4
regsave
push dword %1
push word  %2
push word  %3
push dword %4
regnull
pop edx
pop  cx
pop  bx
pop eax
%endmacro
%macro macro_args_read_bdwd 4
regsave
push byte  %1
push dword %2
push word  %3
push dword %4
regnull
pop edx
pop  cx
pop ebx
pop  al
%endmacro
%macro macro_args_read_wdwd 4
regsave
push word  %1
push dword %2
push word  %3
push dword %4
regnull
pop edx
pop  cx
pop ebx
pop  ax
%endmacro
%macro macro_args_read_ddwd 4
regsave
push dword %1
push dword %2
push word  %3
push dword %4
regnull
pop edx
pop  cx
pop ebx
pop eax
%endmacro
%macro macro_args_read_bbdd 4
regsave
push byte  %1
push byte  %2
push dword %3
push dword %4
regnull
pop edx
pop ecx
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbdd 4
regsave
push word  %1
push byte  %2
push dword %3
push dword %4
regnull
pop edx
pop ecx
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbdd 4
regsave
push dword %1
push byte  %2
push dword %3
push dword %4
regnull
pop edx
pop ecx
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwdd 4
regsave
push byte  %1
push word  %2
push dword %3
push dword %4
regnull
pop edx
pop ecx
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwdd 4
regsave
push word  %1
push word  %2
push dword %3
push dword %4
regnull
pop edx
pop ecx
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwdd 4
regsave
push dword %1
push word  %2
push dword %3
push dword %4
regnull
pop edx
pop ecx
pop  bx
pop eax
%endmacro
%macro macro_args_read_bddd 4
regsave
push byte  %1
push dword %2
push dword %3
push dword %4
regnull
pop edx
pop ecx
pop ebx
pop  al
%endmacro
%macro macro_args_read_wddd 4
regsave
push word  %1
push dword %2
push dword %3
push dword %4
regnull
pop edx
pop ecx
pop ebx
pop  ax
%endmacro
%macro macro_args_read_dddd 4
regsave
push dword %1
push dword %2
push dword %3
push dword %4
regnull
pop edx
pop ecx
pop ebx
pop eax
%endmacro
%macro macro_args_read_ 0
macro_args_read_dddd 0, 0, 0, 0,
%endmacro
%macro macro_args_read_b 1
macro_args_read_bddd %1, 0, 0, 0,
%endmacro
%macro macro_args_read_w 1
macro_args_read_wddd %1, 0, 0, 0,
%endmacro
%macro macro_args_read_d 1
macro_args_read_dddd %1, 0, 0, 0,
%endmacro
%macro macro_args_read_bb 2
macro_args_read_bbdd %1, %2, 0, 0,
%endmacro
%macro macro_args_read_wb 2
macro_args_read_wbdd %1, %2, 0, 0,
%endmacro
%macro macro_args_read_db 2
macro_args_read_dbdd %1, %2, 0, 0,
%endmacro
%macro macro_args_read_bw 2
macro_args_read_bwdd %1, %2, 0, 0,
%endmacro
%macro macro_args_read_ww 2
macro_args_read_wwdd %1, %2, 0, 0,
%endmacro
%macro macro_args_read_dw 2
macro_args_read_dwdd %1, %2, 0, 0,
%endmacro
%macro macro_args_read_bd 2
macro_args_read_bddd %1, %2, 0, 0,
%endmacro
%macro macro_args_read_wd 2
macro_args_read_wddd %1, %2, 0, 0,
%endmacro
%macro macro_args_read_dd 2
macro_args_read_dddd %1, %2, 0, 0,
%endmacro
%macro macro_args_read_bbb 3
macro_args_read_bbbd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_wbb 3
macro_args_read_wbbd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_dbb 3
macro_args_read_dbbd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_bwb 3
macro_args_read_bwbd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_wwb 3
macro_args_read_wwbd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_dwb 3
macro_args_read_dwbd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_bdb 3
macro_args_read_bdbd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_wdb 3
macro_args_read_wdbd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_ddb 3
macro_args_read_ddbd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_bbw 3
macro_args_read_bbwd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_wbw 3
macro_args_read_wbwd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_dbw 3
macro_args_read_dbwd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_bww 3
macro_args_read_bwwd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_www 3
macro_args_read_wwwd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_dww 3
macro_args_read_dwwd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_bdw 3
macro_args_read_bdwd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_wdw 3
macro_args_read_wdwd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_ddw 3
macro_args_read_ddwd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_bbd 3
macro_args_read_bbdd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_wbd 3
macro_args_read_wbdd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_dbd 3
macro_args_read_dbdd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_bwd 3
macro_args_read_bwdd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_wwd 3
macro_args_read_wwdd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_dwd 3
macro_args_read_dwdd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_bdd 3
macro_args_read_bddd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_wdd 3
macro_args_read_wddd %1, %2, %3, 0,
%endmacro
%macro macro_args_read_ddd 3
macro_args_read_dddd %1, %2, %3, 0,
%endmacro
