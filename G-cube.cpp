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
using std::set, std::unordered_set, std::map, std::unordered_map;

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

struct cube{
    map<pair<llu,llu>,long double> cache;

    long double find(llu n,llu m){
        if (cache.count({n,m})){
            return cache[{n,m}];
        }
        long double s=0;
        if (n*m==0){
            s=!(n+m);
        }else
        if (m<n or n*6<m){
            s=0;
        }else
        if (n==1){
            s=1./6;
        }else{
            for (llu w=1;w<7;++w){
                s+=find(n-1,m-w)/6.;
            }
        }
        cache[{n,m}]=s;
        return s;
    }
};


int main(){
    llu n=getint(),m=getint();
    printf("%.20Lf\n",cube().find(n,m));
}