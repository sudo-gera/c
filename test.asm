%include "best_io.inc"



section .data
    somestring db 'hello'
    freespace times 64 db ' ' ; 64 spaces
    someint dd 256+44 ; = 300
section .text
    start
    ; this code is not optimal way to do things.
    ; it just shows how to use macros.
    ; print hello world:
    putstr    somestring,freespace ; will put 'hello' (without quotes)
    ; freespace is located to the right of 'hello'
    ; so freespace pointer points to end of somestring
    putcstr   ' world' ; will put ' world' (without quotes)
    putchar   10 ; will put enter
    ; print hello world (again)
    putcstr   'hello world',10
    ; print some numbers
    putubyte  [someint] ; 44
    putchar   10 ; new line
    putubyte  [someint+1] ; 1
    putchar   10 ; new line
    putuword  [someint] ; 300
    putchar   10 ; new line
    putuword  [someint+1] ; 1
    putchar   10 ; new line
    printudword [someint] ; 300 with new line
    putcstr   'what is your name?',10
    getstr    freespace,someint ; now freespace is equal to your name
    putstr    somestring,freespace ; will print 'hello'
    putchar   [someint] ; chr(44) is ','
    putchar   ' '
    putstr    freespace,someint
    putchar   10 ; new line
    putcstr   'what is your age?',10
    getdword  [someint] ; now someint is equal to your age
    putcstr     'your age is '
    printudword [someint]
    stop
