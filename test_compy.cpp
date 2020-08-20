#pragma GCC optimize("Ofast")
#include "stdio.h"
int p(int a,int s){
	return a+s;
}
int m(int a,int s){
	return a-s;
}
int main(){
	int q,e;
	scanf("%i%i",&q,&e);
	for (int w=0;w<e;w++){
//		q=w%2?p(q,w):m(q,w);
		q=w%2?q+w:q-w;
	}
	printf("%i\n",q);
}