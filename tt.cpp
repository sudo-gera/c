#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int main(){
 struct timeval t;
 gettimeofday(&t,0);
 printf("%li %li\n",t.tv_sec,t.tv_usec);}
