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


struct bitmask
{
    llu n=0;
    llu m=0;
    llu find(llu s=0){
        llu o=s;
        // auto y=bin_repr(s);
        // reverse(y.begin(),y.end());
        // ic(y)
        // for (auto u=0;u<n*m;u+=m){
        //     cout<<string(y.begin()+u,y.begin()+u+m)<<endl;;
        // }
        cache(llu,o);
        llu r=0;
        llu q=0,w=0;
        for (q=0;q<n;++q){
            for (w=0;w<m;++w){
                if (bit_get(&s,q*m+w)==0){
                    goto _1;
                }
            }
        }
        // ic()
        _1:
        if (q==n or w==m){
            r=1;
        }else{
            bit_set(&s,q*m+w,1);
            if (w+1 < m and bit_get(&s,q*m+w+1)==0){
                llu t=s;
                bit_set(&t,q*m+w+1,1);
                // ic()
                r+=find(t);
                // ic()
                if (w+2 < m and bit_get(&s,q*m+w+2)==0){
                    bit_set(&t,q*m+w+2,1);
                // ic()
                    r+=find(t);
                // ic()
                }
            }
            if (q+1 < n and bit_get(&s,q*m+m+w)==0){
                llu t=s;
                bit_set(&t,q*m+w+m,1);
                // ic()
                r+=find(t);
                // ic()
                if (q+2 < n and bit_get(&s,q*m+w+m+m)==0){
                    bit_set(&t,q*m+w+m+m,1);
                // ic()
                    r+=find(t);
                // ic()
                }
            }
        }
        // ic()
        cache[{o}]=r;
        // ic(o,r)
        // ic(y,r)
        // for (auto u=0;u<n*m;u+=m){
        //     cout<<string(y.begin()+u,y.begin()+u+m)<<endl;;
        // }
        // static llu rc=0;
        // if (rc++==2){assert_m(0);}
        return r;
    }
};



int main(){
    llu n=getint();
    llu m=getint();
    tie(n,m)=make_tuple(max(n,m),min(n,m));
    print(bitmask{n,m}.find());
}