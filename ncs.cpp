#include <ncurses.h>

int main()
{
    initscr();
    raw();
    noecho();
    int c=0;
    while(c!=3 and c!=48){
     c=getch();
     printw("%i\n",c);
//     mvprintw(0,0,"    ");
//     mvprintw(0,0,"%i",c);
//     mvprintw(0,0,"");
     refresh();
    }
    endwin();
    return 0;
}
