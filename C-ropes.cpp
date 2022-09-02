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


struct ropes
{
    unordered_map<llu,llu> cache1;
    unordered_map<llu,llu> cache2;
    vector<llu> x;

    llu find1(llu n){
        // ic(n)
        if (cache1.count(n)){
            return cache1[n];
        }
        assert (n>=2);
        auto d=find2(n-1)+x[n-1]-x[n-2];
        cache1[n]=d;
        // ic(n,d)
        return d;
    }

    llu find2(llu n){
        // ic(n)
        if (cache2.count(n)){
            return cache2[n];
        }
        assert(n>=1);
        llu d=0;
        if (n==1){
        }else
        if (n==2){
            d=x[n-1]-x[n-2];
        }else{
            assert(n>=3);
            d=std::min(
                find1(n-1),
                find2(n-1)+x[n-1]-x[n-2]
            );
        }
        cache2[n]=d;
        // ic(n,d)
        return d;
    }

};



int main(){
    llu n=getint();
    ropes r;
    for (llu w=0;w<n;++w){
        r.x.push_back(getint());
    }
    sort(r.x.begin(),r.x.end());
    print(r.find1(r.x.size()));
}
