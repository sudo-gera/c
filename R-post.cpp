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
#include <string.h>
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::reduce, std::move, std::swap, std::generate, std::generate_n;
using std::back_inserter, std::list, std::hash, std::reverse;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::string_view, std::copy_if, std::exclusive_scan;

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

#define none 9000000000000000000LLU

///////////////////////////////////////////////////end of lib

vector<llu> a;
// vector<llu> s;


using tll=tuple<llu,llu>;

tuple<llu,llu> _count(llu n,llu m,llu e){
    // cache(tll,n,m,e);
    ic(n,m,e)
    tuple<llu,llu> r={0,0};
    if (m and n){
        auto q=_count(n-1,m-1,n-1);
        auto w=_count(n-1,m,  e);
        ic(e,n-1,a)
        llu t=min(
            eic(get<1>(w)==none ?none: a[n-1] - a[get<1>(w)]),
            eic(e==none           ?none: a[e]   - a[n-1])
        );
        t==none or get<0>(w)==none ? get<0>(w)=none : get<0>(w)+=t;
        ic(q,w)
        if (get<0>(q)<=get<0>(w)){
            r={
                get<0>(q),
                n-1
            };
        }else{
            r={
                get<0>(w),
                get<1>(w)
            };
        }
    }else
    if (n==0){
        r={0,none};
    }else
    if (m==0){
        auto w=_count(n-1,m,  e);
        llu t=min(
            get<1>(w)==none ?none: a[n-1] - a[get<1>(w)],
            e==none         ?none: a[e]   - a[n-1]
        );
        t==none or get<0>(w)==none ? get<0>(w)=none : get<0>(w)+=t;
        r={
            get<0>(w),
            get<1>(w)
        };
    }
    ic(n,m,e,r)
    // cache[{n,m,e}]=r;
    return r;
}



int main(){
    llu n=0,m=0;
    n=getint(),m=getint();
    generate_n(back_inserter(a),n,getint);
    sort(a.begin(),a.end());
    // exclusive_scan(a.begin(),a.end(),back_inserter(s),0);
    // s.push_back(a.back()+s.back());
    print(get<0>(_count(n,m,none)));
    // ic(_count(n,m,none))
    llu c=get<1>(_count(n,m,none));
    vector<llu> s;
    while (c!=none){
        s.push_back(a[c]);
        c=get<1>(_count(c,--m,c));
    }
    sort(s.begin(),s.end());
    for (auto w:s){
        write(w);
    }
    putchar(10);
}