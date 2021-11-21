#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(){
	char *t=0;
	for (size_t w=0;w<9;++w){
		int g=scanf("%ms",&t);
		printf("%as %i\n",t,g);
	}
}
