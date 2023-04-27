python -c $'from sys import *\nprint(stdin.buffer.read(),argv)' "$#" "$0" "$@"
