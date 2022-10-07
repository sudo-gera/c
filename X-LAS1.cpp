#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <assert.h>
#include <tuple>
#include <numeric>
#include <list>
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort, std::pair;
using std::set, std::unordered_set, std::map, std::unordered_map, std::min,std::max;
using std::tuple, std::tie, std::get, std::make_tuple, std::reduce, std::move, std::swap;
using std::generate, std::generate_n, std::back_inserter, std::list;

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


int main(){
    llu n=getint();
    vector<long> a;
    generate_n(back_inserter(a),n,getint);
    vector<pair<llu,llu>> d;
    // vector<llu> s;
    for (auto w:a){
        llu m=0;
        llu i=-1;
        // while (s.size() and a[s.back()]<w){
        for (llu q=0;q<d.size();++q){
            if (a[q]<w and d[q].second>m){
                m=d[q].second;
                i=q;
            }
            // s.pop_back();
        }
        // s.push_back(d.size());
        d.push_back({i,m+1});
    }
    // ic(a)
    // ic(s)
    // ic(d)
    llu m=0;
    llu i=-1;
    for (llu w=0;w<d.size();++w){
       if (d[w].second>m){
            m=d[w].second;
            i=w;
        }
    }
    print(m);
    vector<llu> f;
    while (i!=-1){
        f.push_back(i);
        i=d[i].first;
    }
    while(f.size()){
        write(f.back());
        f.pop_back();
    }
    cout<<endl;
}