#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <string.h>
#include <ctype.h>

void gen2(int n,int*a){
	if (n==2){
		a[0]=2;
		a[1]=1;
		return;
	}
	int w=0;
	while (w<n){
		a[w]=w+1;
		w+=1;
	}
	w=3;
	while (w<n+1){
		a[w-1]=a[(w-1)/2];
		a[(w-1)/2]=w;
		w+=1;
	}
}

int main(){
	int n;
	scanf("%i",&n);
	int*a=(int*)malloc(sizeof(int*)*n);
	gen2(n,a);
	for (int w=0;w<n;++w){
		printf("%i ",a[w]);
	}
	printf("\n");
	free(a);
}
