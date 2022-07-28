#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>



int main(){
	size_t n,k__,a__,x,y;
	scanf("%zu%zu%zu%zu%zu",&n,&k__,&a__,&x,&y);
	const size_t kk=0b10000000000000000;
	ssize_t a[kk];
	memset(a,0b10000000,kk*sizeof(ssize_t)); // a[i]<-10**18
	size_t r=kk-k__;
	size_t e=0;
	char data[20];
	size_t ds;
	for (;e+r<n;e+=r){
		for (size_t w=0;w<r;++w){
			a__=(a__*x+y)&0x3fffffff;
			a[w]=-a__;
		}
		std::sort(a,a+kk);
	}
	r=n-e;
	if (r){
		for (size_t w=0;w<r;++w){
			a__=(a__*x+y)&0x3fffffff;
			a[w]=-a__;
		}
		std::sort(a,a+kk);
	}
	for (size_t w=0;w<k__;++w){
		printf("%zi\n",-a[kk-1-w]);
	}
}
