import curses

# stdscr = curses.initscr()

# def print_char(x, y, char):
#     stdscr.addch(y, x, char)

def print_char(x, y, char):
    print("\033["+str(y)+";"+str(x)+"H"+char)

print_char(0,2,'====')

	#stdscr.getmaxyx()[1]