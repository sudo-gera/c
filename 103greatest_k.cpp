#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>


int64_t get_int(){
	int64_t res=0;
	int8_t sign=1;
	int c;
	while (c=getchar_unlocked(),isspace(c)){

	}
	if (c=='-'){
		sign*=-1;
	}else{
		res=c-'0';
	}
	while (c=getchar_unlocked(),c!=EOF and !isspace(c)){
		res*=10;
		res+=c-'0';
	}
	return sign*res;
}


int main(){
	size_t n,k__;
	scanf("%zu%zu",&n,&k__);
	const size_t kk=0b1000000000000000;
	ssize_t a[kk];
	memset(a,0b10000000,kk*sizeof(ssize_t)); // a[i]<-10**18
	size_t r=kk-k__;
	int8_t sign;
	int c;
	for (size_t e=0;e<n;e+=r){
		if (e+r>n){
			r=n-e;
		}
		for (size_t w=0;w<r;++w){
			a[w]=0;
			sign=1;
			while (c=getchar_unlocked(),isspace(c)){

			}
			if (c=='-'){
				sign*=-1;
			}else{
				a[w]=c-'0';
			}
			while (c=getchar_unlocked(),c!=EOF and !isspace(c)){
				a[w]*=10;
				a[w]+=c-'0';
			}
			a[w]*=sign;
		}
		std::sort(a,a+kk);
	}
	char data[20];
	size_t ds;
	for (size_t w=0;w<k__;++w){
		auto t=a[kk-1-w];
		if (t<0){
			putchar_unlocked('-');
			t=-t;
		}
		ds=0;
		while (t){
			data[ds++]=t%10+'0';
			t/=10;
		}
		for (size_t e=0;e<ds;++e){
			putchar_unlocked(data[ds-1-e]);
		}
		putchar_unlocked('\n');
	}
}
