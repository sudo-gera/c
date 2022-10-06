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

struct labirint{
    vector<string> a;
    map<tuple<pair<llu,llu>,pair<llu,llu>,llu>,llu> countcache;
    llu count(pair<llu,llu> in,pair<llu,llu> out,llu k){
        if (countcache.count({in,out,k})){
            return countcache[{in,out,k}];
        }
        if (k==0){
            return in==out;
        }
        llu r=0;
        if (in.first!=0 and a[in.first-1][in.second]=='.'){
            r+=count({in.first-1,in.second},out,k-1);
        }
        if (in.second!=0 and a[in.first][in.second-1]=='.'){
            r+=count({in.first,in.second-1},out,k-1);
        }
        if (in.first+1!=a.size() and a[in.first+1][in.second]=='.'){
            r+=count({in.first+1,in.second},out,k-1);
        }
        if (in.second+1!=a[0].size() and a[in.first][in.second+1]=='.'){
            r+=count({in.first,in.second+1},out,k-1);
        }
        countcache[{in,out,k}]=r;
        return r;
    }
};

int main(){
    labirint l;
    auto&a=l.a;
    llu n=getint(),m=getint(),k=getint();
    pair<llu,llu> in={-1,-1},out={-1,-1};
    for (llu q=0;q<n;++q){
        a.emplace_back();
        cin>>a[q];
        for (llu w=0;w<m;++w){
            if (a[q][w]=='@'){
                in={q,w};
                a[q][w]='.';
            }
            if (a[q][w]=='#'){
                out={q,w};
                a[q][w]='.';
            }
        }
    }
    cout<<(l.count(in,out,k))<<endl;
}
