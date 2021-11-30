#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>


#if __has_include("h")
// #include "d"
#endif

int main(){
	uint64_t n,k;
	scanf("%lli%lli",&n,&k);
	// uint64_t k_=1LL<<40;
	uint64_t k_=1LL<<18;
	// uint64_t k_=1<<4;
	uint64_t _k=k_>>1;
	int64_t* a=(int64_t*)malloc(k_*sizeof(int64_t));
	int64_t* s=(int64_t*)malloc(k_*sizeof(int64_t));
	while (!a or !s){}
	for (uint64_t w=0;w<k_;++w){
		a[w]=-1001001001001001001;
	}
	for (uint64_t e=0;e<n;e+=_k){
		uint64_t r=n-e<_k?n-e:_k;
		for (uint64_t w=0;w<r;++w){
			scanf("%lli",a+w);
		}
		for (uint64_t bs=1;bs<k_;bs<<=1){
			for (uint64_t w=0;w<k_;w+=bs+bs){
				uint64_t f=w,g=w+bs,h=0;
				while (f<w+bs and g<w+bs+bs){
					s[h++]=a[f]<a[g]?a[f++]:a[g++];
				}
				while (f<w+bs){
					s[h++]=a[f++];
				}
				while (g<w+bs+bs){
					s[h++]=a[g++];
				}
				for (uint64_t j=0;j<h;++j){
					a[w+j]=s[j];
				}
			}
		}
	}
	for (uint64_t w=0;w<k;++w){
		printf("%lli\n",a[k_-1-w]);
	}
	free(a);
	free(s);
}