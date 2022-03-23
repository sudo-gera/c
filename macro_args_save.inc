%macro macro_args_save_ 0
add esp, 16
sub esp, 16
regload
add esp,16
%endmacro

%macro macro_args_save_b 1
add esp, 17
push byte  al
sub esp, 16
regload
pop byte  %1
add esp,15
%endmacro

%macro macro_args_save_w 1
add esp, 18
push word  ax
sub esp, 16
regload
pop word  %1
add esp,14
%endmacro

%macro macro_args_save_d 1
add esp, 20
push dword eax
sub esp, 16
regload
pop dword %1
add esp,12
%endmacro

%macro macro_args_save_bb 2
add esp, 18
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
add esp,14
%endmacro

%macro macro_args_save_wb 2
add esp, 19
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
add esp,13
%endmacro

%macro macro_args_save_db 2
add esp, 21
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
add esp,11
%endmacro

%macro macro_args_save_bw 2
add esp, 19
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
add esp,13
%endmacro

%macro macro_args_save_ww 2
add esp, 20
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
add esp,12
%endmacro

%macro macro_args_save_dw 2
add esp, 22
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
add esp,10
%endmacro

%macro macro_args_save_bd 2
add esp, 21
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
add esp,11
%endmacro

%macro macro_args_save_wd 2
add esp, 22
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
add esp,10
%endmacro

%macro macro_args_save_dd 2
add esp, 24
push dword ebx
push dword eax
sub esp, 16
regload
<<<<<<< HEAD
add esp,8
pop dword %1
pop dword %2
=======
pop dword %1
pop dword %2
add esp,8
>>>>>>> 4c4fc944b9aa9230b0a5d0b574f5c89b58a7ceb7
%endmacro

%macro macro_args_save_bbb 3
add esp, 19
push byte  cl
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop byte  %3
add esp,13
%endmacro

%macro macro_args_save_wbb 3
add esp, 20
push byte  cl
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop byte  %3
add esp,12
%endmacro

%macro macro_args_save_dbb 3
add esp, 22
push byte  cl
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop byte  %3
add esp,10
%endmacro

%macro macro_args_save_bwb 3
add esp, 20
push byte  cl
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop byte  %3
add esp,12
%endmacro

%macro macro_args_save_wwb 3
add esp, 21
push byte  cl
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop byte  %3
add esp,11
%endmacro

%macro macro_args_save_dwb 3
add esp, 23
push byte  cl
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop byte  %3
add esp,9
%endmacro

%macro macro_args_save_bdb 3
add esp, 22
push byte  cl
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop byte  %3
add esp,10
%endmacro

%macro macro_args_save_wdb 3
add esp, 23
push byte  cl
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop byte  %3
add esp,9
%endmacro

%macro macro_args_save_ddb 3
add esp, 25
push byte  cl
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop byte  %3
add esp,7
%endmacro

%macro macro_args_save_bbw 3
add esp, 20
push word  cx
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop word  %3
add esp,12
%endmacro

%macro macro_args_save_wbw 3
add esp, 21
push word  cx
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop word  %3
add esp,11
%endmacro

%macro macro_args_save_dbw 3
add esp, 23
push word  cx
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop word  %3
add esp,9
%endmacro

%macro macro_args_save_bww 3
add esp, 21
push word  cx
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop word  %3
add esp,11
%endmacro

%macro macro_args_save_www 3
add esp, 22
push word  cx
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop word  %3
add esp,10
%endmacro

%macro macro_args_save_dww 3
add esp, 24
push word  cx
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop word  %3
add esp,8
%endmacro

%macro macro_args_save_bdw 3
add esp, 23
push word  cx
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop word  %3
add esp,9
%endmacro

%macro macro_args_save_wdw 3
add esp, 24
push word  cx
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop word  %3
add esp,8
%endmacro

%macro macro_args_save_ddw 3
add esp, 26
push word  cx
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop word  %3
add esp,6
%endmacro

%macro macro_args_save_bbd 3
add esp, 22
push dword ecx
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop dword %3
add esp,10
%endmacro

%macro macro_args_save_wbd 3
add esp, 23
push dword ecx
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop dword %3
add esp,9
%endmacro

%macro macro_args_save_dbd 3
add esp, 25
push dword ecx
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop dword %3
add esp,7
%endmacro

%macro macro_args_save_bwd 3
add esp, 23
push dword ecx
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop dword %3
add esp,9
%endmacro

%macro macro_args_save_wwd 3
add esp, 24
push dword ecx
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop dword %3
add esp,8
%endmacro

%macro macro_args_save_dwd 3
add esp, 26
push dword ecx
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop dword %3
add esp,6
%endmacro

%macro macro_args_save_bdd 3
add esp, 25
push dword ecx
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop dword %3
add esp,7
%endmacro

%macro macro_args_save_wdd 3
add esp, 26
push dword ecx
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop dword %3
add esp,6
%endmacro

%macro macro_args_save_ddd 3
add esp, 28
push dword ecx
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop dword %3
add esp,4
%endmacro

%macro macro_args_save_bbbb 4
add esp, 20
push byte  dl
push byte  cl
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop byte  %3
pop byte  %4
add esp,12
%endmacro

%macro macro_args_save_wbbb 4
add esp, 21
push byte  dl
push byte  cl
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop byte  %3
pop byte  %4
add esp,11
%endmacro

%macro macro_args_save_dbbb 4
add esp, 23
push byte  dl
push byte  cl
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop byte  %3
pop byte  %4
add esp,9
%endmacro

%macro macro_args_save_bwbb 4
add esp, 21
push byte  dl
push byte  cl
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop byte  %3
pop byte  %4
add esp,11
%endmacro

%macro macro_args_save_wwbb 4
add esp, 22
push byte  dl
push byte  cl
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop byte  %3
pop byte  %4
add esp,10
%endmacro

%macro macro_args_save_dwbb 4
add esp, 24
push byte  dl
push byte  cl
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop byte  %3
pop byte  %4
add esp,8
%endmacro

%macro macro_args_save_bdbb 4
add esp, 23
push byte  dl
push byte  cl
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop byte  %3
pop byte  %4
add esp,9
%endmacro

%macro macro_args_save_wdbb 4
add esp, 24
push byte  dl
push byte  cl
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop byte  %3
pop byte  %4
add esp,8
%endmacro

%macro macro_args_save_ddbb 4
add esp, 26
push byte  dl
push byte  cl
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop byte  %3
pop byte  %4
add esp,6
%endmacro

%macro macro_args_save_bbwb 4
add esp, 21
push byte  dl
push word  cx
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop word  %3
pop byte  %4
add esp,11
%endmacro

%macro macro_args_save_wbwb 4
add esp, 22
push byte  dl
push word  cx
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop word  %3
pop byte  %4
add esp,10
%endmacro

%macro macro_args_save_dbwb 4
add esp, 24
push byte  dl
push word  cx
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop word  %3
pop byte  %4
add esp,8
%endmacro

%macro macro_args_save_bwwb 4
add esp, 22
push byte  dl
push word  cx
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop word  %3
pop byte  %4
add esp,10
%endmacro

%macro macro_args_save_wwwb 4
add esp, 23
push byte  dl
push word  cx
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop word  %3
pop byte  %4
add esp,9
%endmacro

%macro macro_args_save_dwwb 4
add esp, 25
push byte  dl
push word  cx
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop word  %3
pop byte  %4
add esp,7
%endmacro

%macro macro_args_save_bdwb 4
add esp, 24
push byte  dl
push word  cx
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop word  %3
pop byte  %4
add esp,8
%endmacro

%macro macro_args_save_wdwb 4
add esp, 25
push byte  dl
push word  cx
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop word  %3
pop byte  %4
add esp,7
%endmacro

%macro macro_args_save_ddwb 4
add esp, 27
push byte  dl
push word  cx
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop word  %3
pop byte  %4
add esp,5
%endmacro

%macro macro_args_save_bbdb 4
add esp, 23
push byte  dl
push dword ecx
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop dword %3
pop byte  %4
add esp,9
%endmacro

%macro macro_args_save_wbdb 4
add esp, 24
push byte  dl
push dword ecx
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop dword %3
pop byte  %4
add esp,8
%endmacro

%macro macro_args_save_dbdb 4
add esp, 26
push byte  dl
push dword ecx
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop dword %3
pop byte  %4
add esp,6
%endmacro

%macro macro_args_save_bwdb 4
add esp, 24
push byte  dl
push dword ecx
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop dword %3
pop byte  %4
add esp,8
%endmacro

%macro macro_args_save_wwdb 4
add esp, 25
push byte  dl
push dword ecx
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop dword %3
pop byte  %4
add esp,7
%endmacro

%macro macro_args_save_dwdb 4
add esp, 27
push byte  dl
push dword ecx
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop dword %3
pop byte  %4
add esp,5
%endmacro

%macro macro_args_save_bddb 4
add esp, 26
push byte  dl
push dword ecx
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop dword %3
pop byte  %4
add esp,6
%endmacro

%macro macro_args_save_wddb 4
add esp, 27
push byte  dl
push dword ecx
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop dword %3
pop byte  %4
add esp,5
%endmacro

%macro macro_args_save_dddb 4
add esp, 29
push byte  dl
push dword ecx
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop dword %3
pop byte  %4
add esp,3
%endmacro

%macro macro_args_save_bbbw 4
add esp, 21
push word  dx
push byte  cl
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop byte  %3
pop word  %4
add esp,11
%endmacro

%macro macro_args_save_wbbw 4
add esp, 22
push word  dx
push byte  cl
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop byte  %3
pop word  %4
add esp,10
%endmacro

%macro macro_args_save_dbbw 4
add esp, 24
push word  dx
push byte  cl
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop byte  %3
pop word  %4
add esp,8
%endmacro

%macro macro_args_save_bwbw 4
add esp, 22
push word  dx
push byte  cl
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop byte  %3
pop word  %4
add esp,10
%endmacro

%macro macro_args_save_wwbw 4
add esp, 23
push word  dx
push byte  cl
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop byte  %3
pop word  %4
add esp,9
%endmacro

%macro macro_args_save_dwbw 4
add esp, 25
push word  dx
push byte  cl
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop byte  %3
pop word  %4
add esp,7
%endmacro

%macro macro_args_save_bdbw 4
add esp, 24
push word  dx
push byte  cl
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop byte  %3
pop word  %4
add esp,8
%endmacro

%macro macro_args_save_wdbw 4
add esp, 25
push word  dx
push byte  cl
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop byte  %3
pop word  %4
add esp,7
%endmacro

%macro macro_args_save_ddbw 4
add esp, 27
push word  dx
push byte  cl
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop byte  %3
pop word  %4
add esp,5
%endmacro

%macro macro_args_save_bbww 4
add esp, 22
push word  dx
push word  cx
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop word  %3
pop word  %4
add esp,10
%endmacro

%macro macro_args_save_wbww 4
add esp, 23
push word  dx
push word  cx
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop word  %3
pop word  %4
add esp,9
%endmacro

%macro macro_args_save_dbww 4
add esp, 25
push word  dx
push word  cx
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop word  %3
pop word  %4
add esp,7
%endmacro

%macro macro_args_save_bwww 4
add esp, 23
push word  dx
push word  cx
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop word  %3
pop word  %4
add esp,9
%endmacro

%macro macro_args_save_wwww 4
add esp, 24
push word  dx
push word  cx
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop word  %3
pop word  %4
add esp,8
%endmacro

%macro macro_args_save_dwww 4
add esp, 26
push word  dx
push word  cx
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop word  %3
pop word  %4
add esp,6
%endmacro

%macro macro_args_save_bdww 4
add esp, 25
push word  dx
push word  cx
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop word  %3
pop word  %4
add esp,7
%endmacro

%macro macro_args_save_wdww 4
add esp, 26
push word  dx
push word  cx
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop word  %3
pop word  %4
add esp,6
%endmacro

%macro macro_args_save_ddww 4
add esp, 28
push word  dx
push word  cx
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop word  %3
pop word  %4
add esp,4
%endmacro

%macro macro_args_save_bbdw 4
add esp, 24
push word  dx
push dword ecx
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop dword %3
pop word  %4
add esp,8
%endmacro

%macro macro_args_save_wbdw 4
add esp, 25
push word  dx
push dword ecx
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop dword %3
pop word  %4
add esp,7
%endmacro

%macro macro_args_save_dbdw 4
add esp, 27
push word  dx
push dword ecx
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop dword %3
pop word  %4
add esp,5
%endmacro

%macro macro_args_save_bwdw 4
add esp, 25
push word  dx
push dword ecx
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop dword %3
pop word  %4
add esp,7
%endmacro

%macro macro_args_save_wwdw 4
add esp, 26
push word  dx
push dword ecx
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop dword %3
pop word  %4
add esp,6
%endmacro

%macro macro_args_save_dwdw 4
add esp, 28
push word  dx
push dword ecx
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop dword %3
pop word  %4
add esp,4
%endmacro

%macro macro_args_save_bddw 4
add esp, 27
push word  dx
push dword ecx
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop dword %3
pop word  %4
add esp,5
%endmacro

%macro macro_args_save_wddw 4
add esp, 28
push word  dx
push dword ecx
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop dword %3
pop word  %4
add esp,4
%endmacro

%macro macro_args_save_dddw 4
add esp, 30
push word  dx
push dword ecx
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop dword %3
pop word  %4
add esp,2
%endmacro

%macro macro_args_save_bbbd 4
add esp, 23
push dword edx
push byte  cl
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop byte  %3
pop dword %4
add esp,9
%endmacro

%macro macro_args_save_wbbd 4
add esp, 24
push dword edx
push byte  cl
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop byte  %3
pop dword %4
add esp,8
%endmacro

%macro macro_args_save_dbbd 4
add esp, 26
push dword edx
push byte  cl
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop byte  %3
pop dword %4
add esp,6
%endmacro

%macro macro_args_save_bwbd 4
add esp, 24
push dword edx
push byte  cl
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop byte  %3
pop dword %4
add esp,8
%endmacro

%macro macro_args_save_wwbd 4
add esp, 25
push dword edx
push byte  cl
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop byte  %3
pop dword %4
add esp,7
%endmacro

%macro macro_args_save_dwbd 4
add esp, 27
push dword edx
push byte  cl
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop byte  %3
pop dword %4
add esp,5
%endmacro

%macro macro_args_save_bdbd 4
add esp, 26
push dword edx
push byte  cl
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop byte  %3
pop dword %4
add esp,6
%endmacro

%macro macro_args_save_wdbd 4
add esp, 27
push dword edx
push byte  cl
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop byte  %3
pop dword %4
add esp,5
%endmacro

%macro macro_args_save_ddbd 4
add esp, 29
push dword edx
push byte  cl
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop byte  %3
pop dword %4
add esp,3
%endmacro

%macro macro_args_save_bbwd 4
add esp, 24
push dword edx
push word  cx
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop word  %3
pop dword %4
add esp,8
%endmacro

%macro macro_args_save_wbwd 4
add esp, 25
push dword edx
push word  cx
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop word  %3
pop dword %4
add esp,7
%endmacro

%macro macro_args_save_dbwd 4
add esp, 27
push dword edx
push word  cx
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop word  %3
pop dword %4
add esp,5
%endmacro

%macro macro_args_save_bwwd 4
add esp, 25
push dword edx
push word  cx
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop word  %3
pop dword %4
add esp,7
%endmacro

%macro macro_args_save_wwwd 4
add esp, 26
push dword edx
push word  cx
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop word  %3
pop dword %4
add esp,6
%endmacro

%macro macro_args_save_dwwd 4
add esp, 28
push dword edx
push word  cx
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop word  %3
pop dword %4
add esp,4
%endmacro

%macro macro_args_save_bdwd 4
add esp, 27
push dword edx
push word  cx
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop word  %3
pop dword %4
add esp,5
%endmacro

%macro macro_args_save_wdwd 4
add esp, 28
push dword edx
push word  cx
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop word  %3
pop dword %4
add esp,4
%endmacro

%macro macro_args_save_ddwd 4
add esp, 30
push dword edx
push word  cx
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop word  %3
pop dword %4
add esp,2
%endmacro

%macro macro_args_save_bbdd 4
add esp, 26
push dword edx
push dword ecx
push byte  bl
push byte  al
sub esp, 16
regload
pop byte  %1
pop byte  %2
pop dword %3
pop dword %4
add esp,6
%endmacro

%macro macro_args_save_wbdd 4
add esp, 27
push dword edx
push dword ecx
push byte  bl
push word  ax
sub esp, 16
regload
pop word  %1
pop byte  %2
pop dword %3
pop dword %4
add esp,5
%endmacro

%macro macro_args_save_dbdd 4
add esp, 29
push dword edx
push dword ecx
push byte  bl
push dword eax
sub esp, 16
regload
pop dword %1
pop byte  %2
pop dword %3
pop dword %4
add esp,3
%endmacro

%macro macro_args_save_bwdd 4
add esp, 27
push dword edx
push dword ecx
push word  bx
push byte  al
sub esp, 16
regload
pop byte  %1
pop word  %2
pop dword %3
pop dword %4
add esp,5
%endmacro

%macro macro_args_save_wwdd 4
add esp, 28
push dword edx
push dword ecx
push word  bx
push word  ax
sub esp, 16
regload
pop word  %1
pop word  %2
pop dword %3
pop dword %4
add esp,4
%endmacro

%macro macro_args_save_dwdd 4
add esp, 30
push dword edx
push dword ecx
push word  bx
push dword eax
sub esp, 16
regload
pop dword %1
pop word  %2
pop dword %3
pop dword %4
add esp,2
%endmacro

%macro macro_args_save_bddd 4
add esp, 29
push dword edx
push dword ecx
push dword ebx
push byte  al
sub esp, 16
regload
pop byte  %1
pop dword %2
pop dword %3
pop dword %4
add esp,3
%endmacro

%macro macro_args_save_wddd 4
add esp, 30
push dword edx
push dword ecx
push dword ebx
push word  ax
sub esp, 16
regload
pop word  %1
pop dword %2
pop dword %3
pop dword %4
add esp,2
%endmacro

%macro macro_args_save_dddd 4
add esp, 32
push dword edx
push dword ecx
push dword ebx
push dword eax
sub esp, 16
regload
pop dword %1
pop dword %2
pop dword %3
pop dword %4
add esp,0
%endmacro

