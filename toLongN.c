#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

#if __has_include("d")
#define HOME
#endif

#ifdef HOME
typedef struct{
	char *dig;	// массив для хранения числа:
// a[0] * 100^0 + a[1] * 100^1 + .. + a[n - 1] * 100^(n-1)
	int n; 			// размер числа в разрядах
	char sign;	// знак числа
}LongN;
#endif

LongN getLongN(char * qs){
	LongN r;
	r.sign=0;
	if (qs[0]=='-'){
		r.sign=1;
		qs++;
		// q=str(q.begin()+1,q.end());
	}
	if (qs[0]=='+'){
		qs++;
		// q=str(q.begin()+1,q.end());
	}
	size_t lq=strlen(qs);
	r.n=(lq+1)/2;
	r.dig=(char*)calloc(r.n,1);
	for (size_t w=0;w<lq;++w){
		if (w%2){
			r.dig[w/2]+=(qs[lq-1-w]-'0')*10;
		}else{
			r.dig[w/2]+=(qs[lq-1-w]-'0');
		}
	}
	return r;
}

#ifdef HOME
auto print_one(const LongN qq) {
	const LongN*q=&qq;
	char b[99999] ;
	b[0] = 0 ;
	sprintf(b+strlen(b) , "\x1b[92m%s\x1b[0m" , q -> sign == 1 ? "-" : "+") ;
	int c = 0 ;
	for (int t = q -> n-1 ; t > -1 ; --t) {
		if (c % 2) {
			sprintf(b+strlen(b) , "\x1b[92m") ;
		}
		sprintf(b+strlen(b) , "%i" , q -> dig[t]) ;
		if (c % 2) {
			sprintf(b+strlen(b) , "\x1b[0m") ;
		}
		++c ;
	}
	return str(b) ;
}

// auto to_str(LongN q){
// 	str r;
// 	if (q.sign){
// 		r+='-';
// 	}
// 	for (long w=q.n-1;w>=0;--w){
// 		r+=(q.dig[w]/10+'0');
// 		r+=(q.dig[w]%10+'0');
// 	}
// 	return r;	
// }

template<>
auto scan_one<LongN>(){
	let q=scan(str);
	LongN r;
	r.sign=0;
	const char*qs=q.c_str();
	if (qs[0]=='-'){
		r.sign=1;
		qs++;
		// q=str(q.begin()+1,q.end());
	}
	if (qs[0]=='+'){
		qs++;
		// q=str(q.begin()+1,q.end());
	}
	size_t lq=strlen(qs);
	r.n=(lq+1)/2;
	r.dig=(char*)calloc(r.n,1);
	for (size_t w=0;w<lq;++w){
		if (w%2){
			r.dig[w/2]+=(qs[lq-1-w]-'0')*10;
		}else{
			r.dig[w/2]+=(qs[lq-1-w]-'0');
		}
	}
	return r;
}

int main(){
    LongN a = scan(LongN);
    print(a);
    printf("\n");
    
    return 0;
}
#endif
