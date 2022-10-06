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

///////////////////////////////////////////////////end of lib

string s;

auto h(string s){
    if (lexicographical_compare(
        s.begin(),s.end(),
        s.rbegin(),s.rend()
    )){
        reverse(s.begin(),s.end());
    }
    llu ss=s.size();
    llu c[256];
    memset(c,0,sizeof(c));
    for (llu w=0;w<ss;++w){
        c[uint8_t(s[w])]=256+w-s.size();
    }
    for (auto&w:s){
        w=c[uint8_t(w)];
    }
    memset(c,0xFF,sizeof(c));
    llu d=0;
    for (llu w=0;w<ss;++w){
        if (c[uint8_t(s.end()[-1-w])]==-1){
            c[uint8_t(s.end()[-1-w])]=255-d;
            ++d;
        }
        s.end()[-1-w]=c[uint8_t(s.end()[-1-w])];
    }
    assert(ss<33);
    __uint128_t h=ss;
    for (llu w=0;w<ss;++w){
        llu z=(255LLU-uint8_t(s[w]));
        llu x=(32LLU-w);
        assert(z<x);
        h*=x;
        h+=z;
    }
    return h;
}

map<tuple<__uint128_t,llu>,llu> countcache;

llu count(llu b){
    if (!b){
        return 0;
    }
    string a;
    for (llu w=0;w<s.size();++w){
        if ((1LLU<<w)&b){
            a+=s[w];
        }
    }
    auto g=h(a);
    string f="";
    for (auto&w:bin_repr(uint8_t(b))){
        f=str()+"\x1b[3"+char(w+1)+"m"+w+"\x1b[0m"+f;
    }
    // ic(a,g,f);
    if (countcache.count({g,b})){
        return 0;
    }
    if (countcache.count({g,0})){
        countcache[{g,b}]=0;
        return countcache[{g,0}];
    }
    llu z=1;
    string d=a;
    reverse(d.begin(),d.end());
    llu r=(a==d);
    while (z<=b){
        if (z&b){
            r+=count(b^z);
        }
        z*=2;
    }
    countcache[{g,0}]=r;
    countcache[{g,b}]=r;
    f="";
    // for (auto&w:bin_repr(uint8_t(b))){
    //     f=str()+"\x1b[3"+char(w+1)+"m"+w+"\x1b[0m"+f;
    // }
    // ic(a,g,f,r);
    return r;




    // string g="";
    // for (auto&w:bin_repr(uint8_t(b))){
    //     g=str()+"\x1b[3"+char(w+1)+"m"+w+"\x1b[0m"+g;
    // }
    // ic(s,"\t",g);
    // static map<tuple<string,llu>,llu> cache;
    // if (cache.count({s,-1})){
    //     if (cache.count({s,b})){
    //         return 0;
    //     }else{
    //         return cache[{s,b}];
    //     }
    // }
        
    // string a;
    // for (llu w=0;w<s.size();++w){
    //     if ((1LLU<<w)&b){
    //         a+=b[w];
    //     }
    // }
    // string d=a;
    // reverse(d.begin(),d.end());
    // llu r=(a==d);
    // for (llu w=0;w<s.size();++w){
    //     if ((1LLU<<w)&b){
    //         r+=count
    //     }
    // }
    



    // string g="";
    // for (auto&w:bin_repr(uint8_t(b))){
    //     g=str()+"\x1b[3"+char(w+1)+"m"+w+"\x1b[0m"+g;
    // }
    // ic(s,"\t",g);
    // cache(llu,s,b);
    // string a=s;
    // reverse(a.begin(),a.end());
    // llu r=(a==s);
    // if (s.size()>1){
    //     a=string(s.begin()+1,s.end());
    //     llu z=1;
    //     while ((z&b)==0){
    //         z*=2;
    //     }
    //     r+=count(a,b^z);
    //     z*=2;
    //     for (llu w=0;w<a.size();++w){
    //         a[w]=s[w+1];
    //         while ((z&b)==0){
    //             z*=2;
    //         }
    //         r+=count(a,b^z);
    //         z*=2;
    //     }
    // }
    // g="";
    // for (auto&w:bin_repr(uint8_t(b))){
    //     g=str()+"\x1b[3"+char(w+1)+"m"+w+"\x1b[0m"+g;
    // }
    // ic(s,"\t",g,r);
    // cache[{s,b}]=0;
    // return r;
}


int main(){
    // int c=0;
    // while ((c=getchar())!=EOF)
    // {
    //     s+=c;
    // }
    cin>>s;
    // s=zip(s);
    // cout<<print_one(h(s))<<endl;
    // cout<<s;
    // ic(vector<llu>(s.begin(),s.end()))
    print(count((1LLU<<s.size())-1));
}