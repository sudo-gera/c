#include <stdio.h>

// #define for for (int iterator=0,int&
// #define in  =iterator,int iterend=
// #define range(q) q ;iterator<iterend;++iterator)


int main(){
	// for (int iterator=0,int& w =iterator,int iterend= 10 ;iterator<iterend;++iterator)
	int iterend=10;
	for (int iterator=0,int iterend=10;iterator<iterend;++iterator)
	{
		printf("%i\n",iterator);
	}
}