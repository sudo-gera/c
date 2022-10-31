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
using std::cin; using std::cout; using std::endl; using std::vector; using std::string; using std::sort;
using std::pair; using std::set; using std::unordered_set; using std::map; using std::unordered_map;
using std::min; using std::max; using std::tuple; using std::tie; using std::get; using std::make_tuple;
using std::move; using std::swap; using std::generate; using std::generate_n;
using std::back_inserter; using std::list; using std::hash; using std::reverse;
using std::lower_bound; using std::upper_bound; using std::flush; using std::prev; using std::next;
using std::tuple_size; using std::lexicographical_compare; using std::set_intersection;
using std::copy_if;

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

int main(){
    llu n=getint(),m=getint();
    vector<tuple<llu,vector<llu>>> a(n);
    for (llu w=0;w<m;++w){
        llu z=getint(),x=getint();
        (get<1>(a[z])).emplace_back(x);
        (get<1>(a[x])).emplace_back(z);
    }
    if (n){
        llu qu=0;
        vector<llu> q(1);
        get<0>(a[0])=1;
        while (q.size()!=qu){
            auto t=q[qu++];
            auto y=get<0>(a[t]);
            for (auto w:get<1>(a[t])){
                if (get<0>(a[w])==y){
                    printf("NO\n");
                    return 0;
                }else
                if (get<0>(a[w])==0){
                    get<0>(a[w])=3-y;
                    q.push_back(w);
                }
            }
        }
    }
    printf("YES\n");
}
