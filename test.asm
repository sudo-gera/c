set 1 1

set 9 23
gnz 9 1
	
	cop 10 20
	mod 20 12
	set 9 17
	gnz 9 20

		div 11 12
		dec 12
		mul 11 12
		inc 12

		cop 10 20
		mod 20 12
		set 9 7
		gnz 9 20

			put 10
			div 10 12
			set 9 -8
			gnz 9 1

	jnz 13

get 10

cop 11 10

set 12 2

scl 13
set 8 5
add 13 8
set 9 6
jnz 9 1

set 12 3

cop 14 12
mul 14 12
cmp 14 10
cmp 14 1
inc 14
set 9 --
gnz 9 14

	scl 13
	set 8 5
	add 13 8
	set 9 6
	jnz 9 1

	inc 12
	inc 12

	set 9 20
	gnz 9 1

cop 14 10
cmp 14 1
dec 14
set 9 11
gnz 9 14

	cop 12 10

	scl 13
	set 8 5
	add 13 8
	set 9 6
	jnz 9 1

put 11




















