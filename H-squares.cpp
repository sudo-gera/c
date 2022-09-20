#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <assert.h>
using std::cin, std::cout, std::vector, std::string, std::sort, std::pair;
using std::set, std::unordered_set, std::map, std::unordered_map, std::min,std::max;

#ifdef print
#undef print
#endif

#ifdef write
#undef write
#endif

static inline int64_t getint() {
    int sign = 1;
    int c;
    size_t res = 0;
    while (c = getchar_unlocked(), isspace(c))
        ;
    if (c == '-') {
        sign = -1;
    } else {
        res = c - '0';
    }
    while (c = getchar_unlocked(), isdigit(c)) {
        res *= 10;
        res += c - '0';
    }
    return (int64_t)(res)*sign;
}

static inline void putint(uint64_t out) {
    if (out > (1LLU << 63) - 1) {
        putchar_unlocked('-');
        out = 1 + ~out;
    }
    char data[44];
    char *dend = data;
    while (out) {
        *++dend = (unsigned)('0') + out % 10;
        out /= 10;
    }
    if (dend == data) {
        putchar_unlocked('0');
    }
    for (; dend != data; --dend) {
        putchar_unlocked(*dend);
    }
}

static inline void print(uint64_t out) {
    putint(out);
    putchar('\n');
}

static inline void write(uint64_t out) {
    putint(out);
    putchar(' ');
}

using llu=long long unsigned;

///////////////////////////////////////////////////end of lib

llu floor_root(llu q){
	llu r=0;
	llu p=1ULL<<62;
	llu u=0;
    while (p){
		u=r+p;
		if (q >= u) {
			q-=u;
			r+=p;
			r+=p;
        }
		r>>=1;
		p>>=2;
    }
	return r;
}

int main(){
    llu n=getint();
    llu q=n;
    auto r=floor_root(n);
    if (r*r==n){
        print(1);
        return 0;
    }
    for (llu w=1;w<=r;++w){
        llu e=floor_root(q-w*w);
        if (e*e+w*w==n){
            print(2);
            return 0;
        }
    }
    while (q%4==0){
        q/=4;
    }
    if (q%8==7){
        print(4);
    }else{
        print(3);
    }
}