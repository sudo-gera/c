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

using llu=unsigned;

///////////////////////////////////////////////////end of lib

struct game{
    // unordered_map<llu,llu> cache;
    vector<llu> cache;

    llu find(llu n){
        if (n==0){
            return 2;
        }
        if (cache[n]){
            return cache[n];
        }
        for (llu w=1;w*w<=n;++w){
            if (find(n-w)==2){
                cache[n]=1;
                return 1;
            }
        }
        cache[n]=2;
        return 2;
    }
};


int main(){
    llu n=getint();
    game g;
    g.cache.resize(n+1);
    for (llu w=0;w<n;++w){
        g.find(w);
    }
    printf(g.find(n)==1?"First\n":"Second\n");

}