#include <stdio.h>

int run(unsigned int q){
	return q+1;
}

int aaa(long t){
	return t;
}

int bbb(){
	return 0;
}



int main(){
	int (*p)();
	p=run;
	printf("%i",p(9));
	p=aaa;
	printf("%i",p(48));
	p=bbb;
}
