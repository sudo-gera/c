
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


void run(int a[20]){
    printf("%i\n",a[0]);
    a[0]=3;
}

int main (int argc, char **argv){
    int a[20];
    a[0]=20;
    run(a);
    printf("%i\n",a[0]);
}
