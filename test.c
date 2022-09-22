
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char **argv){
    void* e=0;
    printf("%i\n",__LINE__);
    goto _2;

    _1:
    printf("%i\n",__LINE__);
    if (getchar()-'0'){
        e=&&_3;
    }else{
        e=&&_4;
    }
    printf("%i\n",__LINE__);
    goto *e;

    _2:
    printf("%i\n",__LINE__);
    e=&&_1;
    goto *e;

    _3:
    printf("%i\n",__LINE__);

    _4:
    printf("%i\n",__LINE__);

}
