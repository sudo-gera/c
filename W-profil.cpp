#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <assert.h>
#include <tuple>
#include <numeric>
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort, std::pair;
using std::set, std::unordered_set, std::map, std::unordered_map, std::min, std::max;
using std::tuple, std::tie, std::get, std::make_tuple, std::reduce, std::move, std::swap;

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


llu g(llu a,llu s,llu n){
    while (--n){
        if (a%4==3 and s%4==3 or a%4==0 and s%4==0){
            return 0;
        }
        a/=2;
        s/=2;
    }
    return 1;
}

void f(llu n,llu m,llu nn,vector<llu>&a,vector<llu>&s){
    if (m==1){
        for (llu w=0;w<nn;++w){
            a[w]=1;
        }
        return;
    }
    f(n,m-1,nn,s,a);
    for (llu q=0;q<(1LLU<<n);++q){
        a[q]=0;
        for (llu w=0;w<(1LLU<<n);++w){
            a[q]+=g(q,w,n)*s[w];
        }
    }
}


int main(){
    llu m=getint();
    llu n=getint();
    if (m<n){
        auto t=n;
        n=m;
        m=t;
    }
    llu nn=(1LLU<<n);
    vector<llu>a(nn);
    vector<llu>s(nn);
    f(n,m,nn,a,s);
    llu d=0;
    for (llu w:a){
        d+=w;
    }
    print(d);
}