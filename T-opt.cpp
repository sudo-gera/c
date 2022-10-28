#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#ifndef assert
#include <assert.h>
#endif
#include <tuple>
#include <numeric>
#include <list>
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::reduce, std::move, std::swap, std::generate, std::generate_n;
using std::back_inserter, std::list, std::hash, std::reverse;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::tuple_size, std::lexicographical_compare;

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

#define cache(rt,...)\
    static map<decltype(make_tuple(__VA_ARGS__)),rt> cache;\
    if ((cache).count({__VA_ARGS__})){\
        return (cache)[{__VA_ARGS__}];\
    }


#define bit_get(a,s)   (((a)[(s)/8LLU/sizeof((a)[0])]>>(s)%(8LLU*sizeof((a)[0])))&1LLU)
#define bit_set(a,s,d) {(a)[(s)/8LLU/sizeof((a)[0])]&=~(1LLU<<(s)%(8LLU*sizeof((a)[0])));(a)[(s)/8LLU/sizeof((a)[0])]+=((d)+0LLU)<<(s)%(8LLU*sizeof((a)[0]));}












///////////////////////////////////////////////////end of lib

llu n=0,m=0;
vector<vector<llu>> a;
vector<llu> s; 

llu count(__uint128_t free,llu k){
    cache(llu,free,k);
    ic(bin_repr(free),k,' ')
    llu r=-1;
    if (k){
        llu maxp=-1;
        for (llu w=0;w<n;++w){
            if (bit_get((uint8_t*)&free,w)==0){
                maxp=min(maxp,a[w][k-1]);
            }
        }
        for (llu w=0;w<n;++w){
            if (a[w][k-1]<=maxp){
                llu d=0;
                d+=s[w]*bit_get((uint8_t*)&free,w)+a[w][k-1];
                auto t=free;
                bit_set((uint8_t*)&t,w,0);
                d+=count(t,k-1);
                r=min(d,r);
            }
        }
    }else{
        r=0;
    }
    try{
        cache[{free,k}]=r;
    }catch(...){};
    ic(bin_repr(free), k, r)
    return r;
}


int main(){
    n=getint();
    m=getint();
    for (llu w=0;w<n;++w){
        s.push_back(getint());
        a.emplace_back();
        for (llu e=0;e<m;++e){
            a.back().push_back(getint());
        }
    }
    print(count(-1,m));
}