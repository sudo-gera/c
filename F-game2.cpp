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

struct game2{
    map<pair<llu,llu>,llu> cache;

    llu find(llu a,llu s){
        // 1 если на доске a x s победит первый иначе 2
        if (a==1){
            return s%2+1;
        }
        if (s==1){
            return a%2+1;
        }
        if (cache.count({a,s})){
            return cache[{a,s}];
        }
        if (find(a-1,s)==2){
            cache[{a,s}]=1;
            return 1;
        }
        if (find(a-1,s-1)==2){
            cache[{a,s}]=1;
            return 1;
        }
        if (find(a,s-1)==2){
            cache[{a,s}]=1;
            return 1;
        }
        cache[{a,s}]=2;
        return 2;
    }
};


int main(){
    auto a=getint(),s=getint();
    // ++a,++s;
    auto p=game2().find(a,s);
    // if (a<=3 or s<=3){
    //     p=3-p;
    // }
    printf(p==1?"F\n":"S\n");
}