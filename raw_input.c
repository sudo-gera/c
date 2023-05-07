#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


int receive_key_event_unsafe(){
    // if you use it in while(1)
    // you will never stop
    // ctrl+C returns as 3
    int fd=fileno(stdin);
    struct termios save,mode;
    tcgetattr(fd,&mode);
    memmove(&save,&mode,sizeof(mode));
    mode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    mode.c_oflag &= ~(OPOST);
    mode.c_cflag &= ~(CSIZE | PARENB);
    mode.c_cflag |= CS8;
    mode.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    mode.c_cc[VMIN] = 1;
    mode.c_cc[VTIME] = 0;
    tcsetattr(fd, TCSAFLUSH, &mode);
    int c=getchar();
    tcsetattr(fd, TCSADRAIN, &save);
    return c;
}


int receive_key_event(){
    int k=receive_key_event_unsafe();
    // stop if
    //   ctrl+shift+@ is 0
    //   ctrl+A is 1
    //   ctrl+B is 2
    //   ctrl+C is 3
    //   ctrl+D is 4
    if (k<5){
        exit(0);
    }
    return k;
}


int main(){
    while(1){
        putchar(receive_key_event());
    }
}
