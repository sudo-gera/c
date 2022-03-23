%macro macro_args_save_bbbb 4
sub esp 36
push byte  %1
push byte  %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbbb 4
sub esp 37
push word  %1
push byte  %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbbb 4
sub esp 39
push dword %1
push byte  %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbb 3
sub esp 35
push byte  %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwbb 4
sub esp 37
push byte  %1
push word  %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwbb 4
sub esp 38
push word  %1
push word  %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwbb 4
sub esp 40
push dword %1
push word  %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbb 3
sub esp 36
push word  %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bdbb 4
sub esp 39
push byte  %1
push dword %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wdbb 4
sub esp 40
push word  %1
push dword %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_ddbb 4
sub esp 42
push dword %1
push dword %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbb 3
sub esp 38
push dword %2
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bb 2
sub esp 34
push byte  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbwb 4
sub esp 37
push byte  %1
push byte  %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbwb 4
sub esp 38
push word  %1
push byte  %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbwb 4
sub esp 40
push dword %1
push byte  %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwb 3
sub esp 36
push byte  %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwwb 4
sub esp 38
push byte  %1
push word  %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwwb 4
sub esp 39
push word  %1
push word  %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwwb 4
sub esp 41
push dword %1
push word  %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwb 3
sub esp 37
push word  %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bdwb 4
sub esp 40
push byte  %1
push dword %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wdwb 4
sub esp 41
push word  %1
push dword %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_ddwb 4
sub esp 43
push dword %1
push dword %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwb 3
sub esp 39
push dword %2
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wb 2
sub esp 35
push word  %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbdb 4
sub esp 39
push byte  %1
push byte  %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbdb 4
sub esp 40
push word  %1
push byte  %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbdb 4
sub esp 42
push dword %1
push byte  %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bdb 3
sub esp 38
push byte  %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwdb 4
sub esp 40
push byte  %1
push word  %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwdb 4
sub esp 41
push word  %1
push word  %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwdb 4
sub esp 43
push dword %1
push word  %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wdb 3
sub esp 39
push word  %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bddb 4
sub esp 42
push byte  %1
push dword %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wddb 4
sub esp 43
push word  %1
push dword %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dddb 4
sub esp 45
push dword %1
push dword %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_ddb 3
sub esp 41
push dword %2
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_db 2
sub esp 37
push dword %3
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_b 1
sub esp 33
push byte  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbbw 4
sub esp 37
push byte  %1
push byte  %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbbw 4
sub esp 38
push word  %1
push byte  %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbbw 4
sub esp 40
push dword %1
push byte  %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbw 3
sub esp 36
push byte  %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwbw 4
sub esp 38
push byte  %1
push word  %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwbw 4
sub esp 39
push word  %1
push word  %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwbw 4
sub esp 41
push dword %1
push word  %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbw 3
sub esp 37
push word  %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bdbw 4
sub esp 40
push byte  %1
push dword %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wdbw 4
sub esp 41
push word  %1
push dword %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_ddbw 4
sub esp 43
push dword %1
push dword %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbw 3
sub esp 39
push dword %2
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bw 2
sub esp 35
push byte  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbww 4
sub esp 38
push byte  %1
push byte  %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbww 4
sub esp 39
push word  %1
push byte  %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbww 4
sub esp 41
push dword %1
push byte  %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bww 3
sub esp 37
push byte  %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwww 4
sub esp 39
push byte  %1
push word  %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwww 4
sub esp 40
push word  %1
push word  %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwww 4
sub esp 42
push dword %1
push word  %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_www 3
sub esp 38
push word  %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bdww 4
sub esp 41
push byte  %1
push dword %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wdww 4
sub esp 42
push word  %1
push dword %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_ddww 4
sub esp 44
push dword %1
push dword %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dww 3
sub esp 40
push dword %2
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_ww 2
sub esp 36
push word  %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbdw 4
sub esp 40
push byte  %1
push byte  %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbdw 4
sub esp 41
push word  %1
push byte  %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbdw 4
sub esp 43
push dword %1
push byte  %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bdw 3
sub esp 39
push byte  %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwdw 4
sub esp 41
push byte  %1
push word  %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwdw 4
sub esp 42
push word  %1
push word  %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwdw 4
sub esp 44
push dword %1
push word  %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wdw 3
sub esp 40
push word  %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bddw 4
sub esp 43
push byte  %1
push dword %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_wddw 4
sub esp 44
push word  %1
push dword %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dddw 4
sub esp 46
push dword %1
push dword %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_ddw 3
sub esp 42
push dword %2
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_dw 2
sub esp 38
push dword %3
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_w 1
sub esp 34
push word  %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbbd 4
sub esp 39
push byte  %1
push byte  %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbbd 4
sub esp 40
push word  %1
push byte  %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbbd 4
sub esp 42
push dword %1
push byte  %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbd 3
sub esp 38
push byte  %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwbd 4
sub esp 40
push byte  %1
push word  %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwbd 4
sub esp 41
push word  %1
push word  %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwbd 4
sub esp 43
push dword %1
push word  %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbd 3
sub esp 39
push word  %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bdbd 4
sub esp 42
push byte  %1
push dword %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wdbd 4
sub esp 43
push word  %1
push dword %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_ddbd 4
sub esp 45
push dword %1
push dword %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbd 3
sub esp 41
push dword %2
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bd 2
sub esp 37
push byte  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbwd 4
sub esp 40
push byte  %1
push byte  %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbwd 4
sub esp 41
push word  %1
push byte  %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbwd 4
sub esp 43
push dword %1
push byte  %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwd 3
sub esp 39
push byte  %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwwd 4
sub esp 41
push byte  %1
push word  %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwwd 4
sub esp 42
push word  %1
push word  %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwwd 4
sub esp 44
push dword %1
push word  %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwd 3
sub esp 40
push word  %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bdwd 4
sub esp 43
push byte  %1
push dword %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wdwd 4
sub esp 44
push word  %1
push dword %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_ddwd 4
sub esp 46
push dword %1
push dword %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwd 3
sub esp 42
push dword %2
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wd 2
sub esp 38
push word  %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bbdd 4
sub esp 42
push byte  %1
push byte  %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wbdd 4
sub esp 43
push word  %1
push byte  %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_dbdd 4
sub esp 45
push dword %1
push byte  %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bdd 3
sub esp 41
push byte  %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bwdd 4
sub esp 43
push byte  %1
push word  %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wwdd 4
sub esp 44
push word  %1
push word  %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_dwdd 4
sub esp 46
push dword %1
push word  %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wdd 3
sub esp 42
push word  %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_bddd 4
sub esp 45
push byte  %1
push dword %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_wddd 4
sub esp 46
push word  %1
push dword %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_dddd 4
sub esp 48
push dword %1
push dword %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_ddd 3
sub esp 44
push dword %2
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_dd 2
sub esp 40
push dword %3
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_d 1
sub esp 36
push dword %4
add esp 32
regload
%endmacro
%macro macro_args_save_ 0
sub esp 32
add esp 32
regload
%endmacro
