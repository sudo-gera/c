#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <type_traits>
#include <assert.h>

#define get_int(res)\
{\
	int8_t sign=1;\
	int c;\
	while (c=getchar_unlocked(),isspace(c)){}\
	if (c=='-'){\
		sign*=-1;\
		res=0;\
	}else{\
		res=c-'0';\
	}\
	while (c=getchar_unlocked(),c!=EOF and !isspace(c)){\
		res*=10;\
		res+=c-'0';\
	}\
	res*=sign;\
}

char put_data[44];

#define put_int(q)\
{\
	unsigned long long t;\
	if (std::is_signed<decltype(q)>::value and q<0){\
		putchar_unlocked('-');\
		t=-q;\
	}else{\
		t=q;\
	}\
	unsigned ds=1;\
	while (t){\
		put_data[ds++]=t%10+'0';\
		t/=10;\
	}\
	for (--ds;ds;--ds){\
		putchar_unlocked(put_data[ds]);\
	}\
}

int main(){
	ssize_t k,n;
	get_int(k)
	get_int(n)
	++n;
	auto v=new ssize_t[n+1];
	for (ssize_t w=1;w<n;++w){
		get_int(v[w])
	}
	for (ssize_t w=2;w<n;++w){
		v[w]+=v[w-1];
	}
#define ic(...)
	--n;
	v[0]=0;
	v[n+1]=size_t(-1)/2;
	ssize_t lower_m=0;
	ssize_t upper_m=v[n];
	while (lower_m+1<upper_m){
		ssize_t mid_m=(lower_m+upper_m)/2;
		ic("trying m=",mid_m)
		ssize_t res_k=0;

		ssize_t curr_pos=0;
		while (curr_pos<n){
			ssize_t lower_pos=curr_pos;
			ssize_t upper_pos=n;
			ic(curr_pos)
			while(upper_pos>lower_pos+1){
				ic(lower_pos,upper_pos)
				ic(itervect(v,v+n+2))
				ssize_t mid_pos=(upper_pos+lower_pos)/2;
				ic("trying pos=",mid_pos)
				ssize_t res=v[mid_pos]-v[curr_pos];
				ic(curr_pos,res,mid_m)
				if (res<mid_m){
					lower_pos=mid_pos;
				}else
				if (res>mid_m){
					upper_pos=mid_pos;
				}else
				if (res==mid_m){
					lower_pos=mid_pos;
					upper_pos=mid_pos;
				}
			}
			++res_k;
			if (v[upper_pos]-v[curr_pos]<=mid_m){
				lower_pos=upper_pos;
			}
			ic(curr_pos,lower_pos,mid_m)
			assert(lower_pos>=curr_pos);
			assert(v[lower_pos]-v[curr_pos]<=mid_m);
			assert(v[lower_pos+1]>v[curr_pos]+mid_m);
			if (lower_pos==curr_pos){
				res_k=size_t(-1)/2;
				curr_pos=n;
			}else{
				curr_pos=lower_pos;
			}
		}

		if (res_k>k){
			lower_m=mid_m;
		}else
		if (res_k<k){
			upper_m=mid_m;
		}else
		if (res_k==k){
			lower_m=mid_m;
			upper_m=mid_m;
		}
	}
	

	put_int(upper_m)
	putchar_unlocked('\n');
	delete[] v;
}
