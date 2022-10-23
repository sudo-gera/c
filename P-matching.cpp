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
using std::string_view, std::copy_if;

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


template<typename T>
llu h(T&s,llu b,llu e){
    static llu base=8589803521;
    // static llu inv=8590065665;
    static vector<llu> powers;
    static map<T*,vector<llu>> data;
    auto&d=data[&s];
    if (powers.empty()){
        powers.push_back(1);
    }
    while (powers.size()<=e-b){
        powers.push_back(powers.back()*base);
    }
    if (d.empty()){
        d.push_back(0);
    }
    while (d.size()<=e){
        d.push_back(d.back()*base+s[d.size()-1]);
    }
    return d[e]-d[b]*powers[e-b];
}

template<typename T>
llu eq(T&a,llu ab,llu ae,T&s,llu sb,llu se){
    // ic(a,ab,ae,s,sb,se,string(a.begin()+ab,a.begin()+ae),string(s.begin()+sb,s.begin()+se))
    return ((ae-ab==se-sb) and (1 or h(a,ab,ae)==h(s,sb,se)) and memcmp(a.data()+ab,s.data()+sb,ae-ab)==0);
}

struct matching{
    vector<tuple<llu,llu>> p;
    // string _a,_s;
    // auto&a=_a;
    // auto&s=_s;
    string&a,&s;

    llu match(llu q,llu w){
        cache(llu,q,w);
        // ic(a,s,p)
        // ic(q,w)
        auto [oq,ow]=tuple{q,w};
        while (w<p.size() and q+get<1>(p[w])-get<0>(p[w])<=s.size()){
            // ic(w,q)
            // ic(a,s,p)
            if (eq(s,q,q+get<1>(p[w])-get<0>(p[w]),a,get<0>(p[w]),get<1>(p[w]))){
                llu pq=q;
                llu pw=w;
                q+=get<1>(p[w])-get<0>(p[w]);
                w+=1;
                // ic(q,w)
                llu t=0;
                while (q < s.size() and get<1>(p[w-1])+t<a.size() and a[get<1>(p[w-1])+t] == '?' ){
                    // get<1>(p[w-1])+=1;
                    t+=1;
                    q+=1;
                }
                if (match(q,w)){
                    cache[{oq,ow}]=1;
                    return 1;
                }else{
                    q=pq;
                    w=pw;
                    goto _1;
                }
            }else{
                _1:
                if (get<0>(p[w])==0 or a[get<0>(p[w])-1]!='*'){
                    break;
                }
                q+=1;
            }
        }
        if (q==s.size() and w==p.size()){
            cache[{oq,ow}]=1;
            return 1;
        }
        cache[{oq,ow}]=0;
        return 0;
    }
    llu prepare(){
        a="_"+a+"_";
        s="_"+s+"_";
        llu c1=0;
        llu c2=0;
        for (llu w=0;w<a.size();++w){
            if (c1){
                a[w]='?';
                c1-=1;
            }else
            if (c2){
                a[w]=c2 == 1?'*':'&';
                c2-=1;
            }else
            if (a[w]=='?' or a[w]=='*'){
                for (llu q=w;q<a.size() and (a[q]=='*' or a[q]=='?');++q){
                    if (a[q]=='*'){
                        c2+=1;
                    }else{
                        c1+=1;
                    }
                }
                --w;
            }
        }
        auto d=a;
        d.resize(0);
        copy_if(a.begin(),a.end(),back_inserter(d),[&](auto q){
            return q!='&';
        });
        a=d;
        for (llu w=0;w<a.size();++w){
            if (a[w]=='*' or a[w]=='?'){
                if (p.empty()){

                }else{
                    if (get<1>(p.back())==-1){
                        get<1>(p.back())=w;
                    }else{

                    }
                }
            }else{
                if (p.empty()){
                    p.push_back({w,-1});
                }
                if (get<1>(p.back())==-1){

                }else{
                p.push_back({w,-1});
                }
            }
        }
        get<1>(p.back())=a.size();
        // ic(a,s,p)
        llu q=0,w=0;
        llu r=match(q,w);
        return r;   
    }
    llu r;
    matching(string&q,string&w):
        a(q),s(w)
    {
        r=prepare();
    }
};

int main(){
    string q,w;
    cin>>q>>w;
    if (matching(w,q).r){
        cout<<("YES")<<endl;
    }else{
        cout<<("NO")<<endl;
    }
}