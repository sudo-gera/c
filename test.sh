a=$'1  2\n3  4'
IFS=$'\n'
python -c $'from sys import *\nprint(argv)' $a
