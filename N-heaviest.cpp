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
#include <string_view>
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::reduce, std::move, std::swap, std::generate, std::generate_n;
using std::back_inserter, std::list, std::hash, std::reverse;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::string_view;

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

///////////////////////////////////////////////////end of lib

#define bisect(b, e, ...)														\
    ({																			\
        int64_t __begin = b;													\
        int64_t __end = e;														\
        assert(__begin <= __end);												\
        while (__begin + 1 < __end) {											\
            int64_t __center = (__begin + __end) / 2;							\
            if (__VA_ARGS__) {													\
                __end = __center;												\
            } else {															\
                __begin = __center;												\
            }																	\
        }																		\
        int64_t __center = __begin;												\
        if (__begin != __end and (__VA_ARGS__)) {								\
            __end = __center;													\
        }																		\
        __end;																	\
    })

llu n=0;
llu m=0;

vector<vector<llu>> a;
vector<vector<llu>> s;

int main(){
    n=getint();
    m=getint();
    generate_n(back_inserter(a),n,[&](){
        vector<llu> s;
        generate_n(back_inserter(s),m,getint);
        return s;
    });
    generate_n(back_inserter(s),n+1,[&](){
        return vector<llu>(m+1);
    });
    for (llu q=0;q<n;++q){
        for (llu w=0;w<m;++w){
            s[q+1][w+1]=s[q+1][w]+s[q][w+1]-s[q][w]+a[q][w];
        }
    }
    // ic(s)
    llu maxsize=bisect(0,n+2,({
        llu r=1;
        for (llu q=__center;q<=n;++q){
            for (llu w=__center;w<=n;++w){
                // ic(q,w,__center)
                if ((s[q][w]-s[q-__center][w]-s[q][w-__center]+s[q-__center][w-__center])==__center*__center){
                    r=0;
                }
            }
        }
        r;
    }));
    print(maxsize-1);
}
