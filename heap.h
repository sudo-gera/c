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

template <typename T>
bool is_less(T q, T w) {
	return q<w;
}


template <typename T> void PushHeap(T *begin, T *end) {
  int i = end - begin;
  while (1 < i && is_less(begin[i / 2 - 1], begin[i - 1])) {
    T t = begin[i - 1];
    begin[i - 1] = begin[i / 2 - 1];
    begin[i / 2 - 1] = t;
    i /= 2;
  }
}
template <typename T> void PopHeap(T *begin, T *end) {
  int i = 0, n = end - begin;
  if (1 < n) {
    T t = *(end - 1);
    *(end - 1) = *begin;
    *begin = t;
    --n;
    int left, right, c = 1;
    while (i < c) {
      if (0 < c) {
        i = c;
      } else {
        c = i;
      }
      left = 2 * i;
      right = 2 * i + 1;
      if (left - 1 < n && is_less(begin[i - 1], begin[left - 1])) {
        c = left;
      }
      if (right - 1 < n && is_less(begin[c - 1], begin[right - 1])) {
        c = right;
      }
      if (i < c) {
        T t = begin[i - 1];
        begin[i - 1] = begin[c - 1];
        begin[c - 1] = t;
      }
    }
  }
}
