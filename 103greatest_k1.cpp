#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <inttypes.h>
#include <string.h>

int main(){
	size_t n,k__;
	scanf("%zu%zu",&n,&k__);
	const size_t kk=0b10000000000000000;
	ssize_t a[kk];
	memset(a,0b10000000,kk*sizeof(ssize_t)); // a[i]<10**18
	size_t r=kk-k__;
	size_t e=0;
	for (;e+r<n;e+=r){
		for (size_t w=0;w<r;++w){
			scanf("%zi",a+w);
		}
		std::sort(a,a+kk);
	}
	r=n-e;
	if (r){
		for (size_t w=0;w<r;++w){
			scanf("%zi",a+w);
		}
		std::sort(a,a+kk);
	}
	for (size_t w=0;w<k__;++w){
		printf("%zi\n",a[kk-1-w]);
	}
}
