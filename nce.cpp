#include <ncurses.h>
#include <string.h>
int main(){
 initscr();
 raw();
 noecho();
 char text[1234567];
 text[0]=0;
 char got=0;
 while (got!=3){
  got=getch();
  char put[2];
  put[0]=got;
  put[1]=0;
  strcat(text,put);
  mvprintw(0,0,"%s",text);
  refresh();
 }
 endwin();
}
