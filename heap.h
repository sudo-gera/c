#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>
template <typename T>
void heapsort(T*begin,T*end){
	for (T* w = begin; w != end; ++w){
		T* i = w;
		T*j=i-1-(i-begin)/2;
		while (begin < i and *j < *i) {
			T t = *i;
			*i = *j;
			*j = t;
			i = j;
			j=j-1-(j-begin)/2;
		}
	}
	begin--;
	for (T* n = end-1; n != begin;){
		T* i = begin;
		T* c = begin+1;
		T t = *n;
		*n = *c;
		*c = t;
		--n;
		for (;;) {
			i = c;
			T*left = i+(i-begin);
			T*right = left + 1;
			if (left>n){
				break;
			}
			if(*c < *left) {
				c = left;
			}
			if (left < n and *c < *right) {
				c = right;
			}
			if(i==c){
				break;
			}
			T t = *i;
			*i = *c;
			*c = t;
		}
	}
}

void hs(int*a,int n){
	heapsort(a,a+n);
}
