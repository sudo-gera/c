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
#define N 100
struct _Decimal {
    char a[N];   // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;       // наибольшая степень десяти
};
typedef struct _Decimal Decimal;

Decimal zero = {{0}, 0};    // представление 0 в виде структуры
#endif

Decimal add(Decimal a,Decimal s){
	Decimal r;
	a.n+=1;
	s.n+=1;
	for (size_t w=a.n;w<N;++w){
		a.a[w]=0;
	}
	for (size_t w=s.n;w<N;++w){
		s.a[w]=0;
	}
	size_t buff=0;
	for (size_t w=0;w<N;++w){
		buff+=a.a[w];
		buff+=s.a[w];
		r.a[w]=buff%10;
		buff/=10;
	}
	for (long w=N-1;w>=0;--w){
		r.n=w;
		if (r.a[w] != 0){
			break;
		}
	}
	return r;
}


#ifdef HOME
auto to_str(Decimal q){
	str r;
	for (long w=q.n;w>=0;--w){
		r+=(q.a[w]+'0');
	}
	return r;
}

template<>
auto scan_one<Decimal>(){
	let q=scan(str);
	Decimal r;
	r.n=len(q)-1;
	for (size_t w=0;w<len(q);++w){
		r.a[w]=q.end()[-1-w]-'0';
	}
	return r;
}

int main(){
    Decimal a = scan(Decimal);
    Decimal b = scan(Decimal);
    // Decimal a = {{7, 4, 1}, 2};  // set number 147
    // Decimal b = {{3, 1}, 1};     // set number 13
    Decimal res;
    
    res = add(a, b);             // res = a+b = 147+13 = 160
    print(res);                    // print 160
    printf("\n");
    
    return 0;
}
#endif
