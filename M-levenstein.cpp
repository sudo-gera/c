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
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort, std::pair;
using std::set, std::unordered_set, std::map, std::unordered_map, std::min, std::max;
using std::tuple, std::tie, std::get, std::make_tuple, std::reduce, std::move, std::swap;
using std::generate, std::generate_n, std::back_inserter, std::list;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;

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

struct levenstein{

    string a,s;

    map<tuple<llu,llu>,llu> findcache;

    llu find(llu la,llu ls){
        if (findcache.count({la,ls})){
            return findcache[{la,ls}];
        }
        if (la*ls==0){
            return la+ls;
        }
        llu r=0;
        if (a[la-1]==s[ls-1]){
            r=min({find(la-1,ls)+1,find(la,ls-1)+1,find(la-1,ls-1)});
        }else{
            r=min({find(la-1,ls)+1,find(la,ls-1)+1,find(la-1,ls-1)+1});
        }
        findcache[{la,ls}]=r;
        // ic(la,ls,r)
        return r;
    }
};

int main(){
    levenstein l;
    cin>>l.a>>l.s;
    print(l.find(l.a.size(),l.s.size()));
}