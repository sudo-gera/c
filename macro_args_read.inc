%macro macro_args_read_bbbb 4
regsave
push byte  %0
push byte  %1
push byte  %2
push byte  %3
regnull
pop  dl
pop  cl
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbbb 4
regsave
push word  %0
push byte  %1
push byte  %2
push byte  %3
regnull
pop  dl
pop  cl
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbbb 4
regsave
push dword %0
push byte  %1
push byte  %2
push byte  %3
regnull
pop  dl
pop  cl
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwbb 4
regsave
push byte  %0
push byte  %1
push byte  %2
push byte  %3
regnull
pop  dl
pop  cl
pop  bl
pop  al
%endmacro
%macro macro_args_read_bdbb 4
regsave
push byte  %0
push byte  %1
push byte  %2
push byte  %3
regnull
pop  dl
pop  cl
pop  bl
pop  al
%endmacro
%macro macro_args_read_bbwb 4
regsave
push byte  %0
push byte  %1
push word  %2
push byte  %3
regnull
pop  dl
pop  cx
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbwb 4
regsave
push word  %0
push byte  %1
push word  %2
push byte  %3
regnull
pop  dl
pop  cx
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbwb 4
regsave
push dword %0
push byte  %1
push word  %2
push byte  %3
regnull
pop  dl
pop  cx
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwwb 4
regsave
push byte  %0
push byte  %1
push word  %2
push byte  %3
regnull
pop  dl
pop  cx
pop  bl
pop  al
%endmacro
%macro macro_args_read_bdwb 4
regsave
push byte  %0
push byte  %1
push word  %2
push byte  %3
regnull
pop  dl
pop  cx
pop  bl
pop  al
%endmacro
%macro macro_args_read_bbdb 4
regsave
push byte  %0
push byte  %1
push dword %2
push byte  %3
regnull
pop  dl
pop ecx
pop  bl
pop  al
%endmacro
%macro macro_args_read_wbdb 4
regsave
push word  %0
push byte  %1
push dword %2
push byte  %3
regnull
pop  dl
pop ecx
pop  bl
pop  ax
%endmacro
%macro macro_args_read_dbdb 4
regsave
push dword %0
push byte  %1
push dword %2
push byte  %3
regnull
pop  dl
pop ecx
pop  bl
pop eax
%endmacro
%macro macro_args_read_bwdb 4
regsave
push byte  %0
push byte  %1
push dword %2
push byte  %3
regnull
pop  dl
pop ecx
pop  bl
pop  al
%endmacro
%macro macro_args_read_bddb 4
regsave
push byte  %0
push byte  %1
push dword %2
push byte  %3
regnull
pop  dl
pop ecx
pop  bl
pop  al
%endmacro
%macro macro_args_read_bbbw 4
regsave
push byte  %0
push word  %1
push byte  %2
push word  %3
regnull
pop  dx
pop  cl
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwbw 4
regsave
push word  %0
push word  %1
push byte  %2
push word  %3
regnull
pop  dx
pop  cl
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwbw 4
regsave
push dword %0
push word  %1
push byte  %2
push word  %3
regnull
pop  dx
pop  cl
pop  bx
pop eax
%endmacro
%macro macro_args_read_bwbw 4
regsave
push byte  %0
push word  %1
push byte  %2
push word  %3
regnull
pop  dx
pop  cl
pop  bx
pop  al
%endmacro
%macro macro_args_read_bdbw 4
regsave
push byte  %0
push word  %1
push byte  %2
push word  %3
regnull
pop  dx
pop  cl
pop  bx
pop  al
%endmacro
%macro macro_args_read_bbww 4
regsave
push byte  %0
push word  %1
push word  %2
push word  %3
regnull
pop  dx
pop  cx
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwww 4
regsave
push word  %0
push word  %1
push word  %2
push word  %3
regnull
pop  dx
pop  cx
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwww 4
regsave
push dword %0
push word  %1
push word  %2
push word  %3
regnull
pop  dx
pop  cx
pop  bx
pop eax
%endmacro
%macro macro_args_read_bwww 4
regsave
push byte  %0
push word  %1
push word  %2
push word  %3
regnull
pop  dx
pop  cx
pop  bx
pop  al
%endmacro
%macro macro_args_read_bdww 4
regsave
push byte  %0
push word  %1
push word  %2
push word  %3
regnull
pop  dx
pop  cx
pop  bx
pop  al
%endmacro
%macro macro_args_read_bbdw 4
regsave
push byte  %0
push word  %1
push dword %2
push word  %3
regnull
pop  dx
pop ecx
pop  bx
pop  al
%endmacro
%macro macro_args_read_wwdw 4
regsave
push word  %0
push word  %1
push dword %2
push word  %3
regnull
pop  dx
pop ecx
pop  bx
pop  ax
%endmacro
%macro macro_args_read_dwdw 4
regsave
push dword %0
push word  %1
push dword %2
push word  %3
regnull
pop  dx
pop ecx
pop  bx
pop eax
%endmacro
%macro macro_args_read_bwdw 4
regsave
push byte  %0
push word  %1
push dword %2
push word  %3
regnull
pop  dx
pop ecx
pop  bx
pop  al
%endmacro
%macro macro_args_read_bddw 4
regsave
push byte  %0
push word  %1
push dword %2
push word  %3
regnull
pop  dx
pop ecx
pop  bx
pop  al
%endmacro
%macro macro_args_read_bbbd 4
regsave
push byte  %0
push dword %1
push byte  %2
push dword %3
regnull
pop edx
pop  cl
pop ebx
pop  al
%endmacro
%macro macro_args_read_wdbd 4
regsave
push word  %0
push dword %1
push byte  %2
push dword %3
regnull
pop edx
pop  cl
pop ebx
pop  ax
%endmacro
%macro macro_args_read_ddbd 4
regsave
push dword %0
push dword %1
push byte  %2
push dword %3
regnull
pop edx
pop  cl
pop ebx
pop eax
%endmacro
%macro macro_args_read_bwbd 4
regsave
push byte  %0
push dword %1
push byte  %2
push dword %3
regnull
pop edx
pop  cl
pop ebx
pop  al
%endmacro
%macro macro_args_read_bdbd 4
regsave
push byte  %0
push dword %1
push byte  %2
push dword %3
regnull
pop edx
pop  cl
pop ebx
pop  al
%endmacro
%macro macro_args_read_bbwd 4
regsave
push byte  %0
push dword %1
push word  %2
push dword %3
regnull
pop edx
pop  cx
pop ebx
pop  al
%endmacro
%macro macro_args_read_wdwd 4
regsave
push word  %0
push dword %1
push word  %2
push dword %3
regnull
pop edx
pop  cx
pop ebx
pop  ax
%endmacro
%macro macro_args_read_ddwd 4
regsave
push dword %0
push dword %1
push word  %2
push dword %3
regnull
pop edx
pop  cx
pop ebx
pop eax
%endmacro
%macro macro_args_read_bwwd 4
regsave
push byte  %0
push dword %1
push word  %2
push dword %3
regnull
pop edx
pop  cx
pop ebx
pop  al
%endmacro
%macro macro_args_read_bdwd 4
regsave
push byte  %0
push dword %1
push word  %2
push dword %3
regnull
pop edx
pop  cx
pop ebx
pop  al
%endmacro
%macro macro_args_read_bbdd 4
regsave
push byte  %0
push dword %1
push dword %2
push dword %3
regnull
pop edx
pop ecx
pop ebx
pop  al
%endmacro
%macro macro_args_read_wddd 4
regsave
push word  %0
push dword %1
push dword %2
push dword %3
regnull
pop edx
pop ecx
pop ebx
pop  ax
%endmacro
%macro macro_args_read_dddd 4
regsave
push dword %0
push dword %1
push dword %2
push dword %3
regnull
pop edx
pop ecx
pop ebx
pop eax
%endmacro
%macro macro_args_read_bwdd 4
regsave
push byte  %0
push dword %1
push dword %2
push dword %3
regnull
pop edx
pop ecx
pop ebx
pop  al
%endmacro
%macro macro_args_read_bddd 4
regsave
push byte  %0
push dword %1
push dword %2
push dword %3
regnull
pop edx
pop ecx
pop ebx
pop  al
%endmacro
