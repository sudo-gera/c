#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

int main(){
	size_t l,n,k;
	std::cin>>l>>n>>k;
	auto a=new size_t[2*n];
	for (size_t w=0;w<n;++w){
		std::cin>>a[w];
	}
	for (size_t w=0;w<n;++w){
		a[w+n]=a[w]+l;
	}
	size_t mf=1ULL<<63;
	size_t mx=1ULL<<63;
	for (size_t x=0;x<k;++x){
		size_t f=0;
		
	}
}
