#if __has_include("d")
#include "d"
#endif
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
void helper(unsigned*begin, unsigned*end,unsigned digit_index){
	if (begin==end){
		return;
	}
	unsigned offsets[65536+1];
	memset(offsets,0,sizeof(offsets));
	for (unsigned* i =begin;i!=end;++i){
		unsigned val = ((uint16_t*)i)[digit_index];
		offsets[val] += 1;
	}
	unsigned sum = 0;
	for (unsigned i=0;i<65536+1;++i){
		unsigned t=offsets[i];
		offsets[i] = sum;
		sum += t;
	}
	unsigned* i = begin;
	unsigned next_free[65536+1];
	memcpy(next_free,offsets,sizeof(next_free));
	unsigned cur_block = 0;
	while (cur_block < 65536 - 1){
		if (i >= begin + offsets[cur_block + 1]){
			cur_block += 1;
			continue;
		}
		unsigned radix_val = ((uint16_t*)i)[digit_index];
		if (radix_val == cur_block){
			i += 1;
			continue;
		}
		unsigned*swap_to = begin + next_free[radix_val];
		unsigned t=*swap_to;
		*swap_to=*i;
		*i=t;
		next_free[radix_val] += 1;
	}
	if (digit_index == 0){
		return;
	}
	for (unsigned i=0;i<65536;++i){
		helper(begin+offsets[i], begin+offsets[i + 1], digit_index - 1);
	}
}

void fast_sort(unsigned*a,unsigned*e){
	helper(a, e, 1);
}

#ifdef HOME
void flag_sort(vector<unsigned>&a_list){
	fast_sort(&a_list[0], &a_list[0]+len(a_list));
}

int main(){
	unsigned n=scan(unsigned);
	vector<unsigned> a(n);
	for (auto&w:a){
		cin>>w;
	}
	auto s=a;
	flag_sort(a);
	sort(s.begin(),s.end());
	if (a!=s){
		print(a)
		print(s)
	}
	assert(a==s);
}
#endif
