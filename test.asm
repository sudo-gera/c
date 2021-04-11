# a[10]=int(input())
get 10
# a[12]=a[10]
cop 12 10

set 1 1

# def
set 9 28
jnz 9 1
cop 24 10
mod 24 13
set 9 26
jnz 9 24
div 12 13
dec 13
mul 12 13
inc 13
cop 25 10
mod 25 13
set 9 26
jnz 9 25
div 10 13
set 9 19
jnz 9 1
jnz 20 1

# a[13]=2
set 13 2
set 20 33
set 9 11
jnz 9 1
set 13 3
cop 14 13
mul 14 13
cmp 14 10
dec 14
cmp 14 0
inc 14
set 9 48
jnz 9 14
set 9 11
set 20 45
jnz 9 1
add 13 2
set 9 34
jnz 9 1
cop 15 10
dec 15
cmp 15 0
dec 15
set 9 57
jnz 9 15
set 20 57
set 9 11
jnz 9 1
put 12
