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
using std::copy_if; using std::exit; using std::enable_if; using std::enable_if;
using std::tuple_cat;
#if __cplusplus>=201703L
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
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

using llu=long long unsigned;

#define cache(rt,...)\
    static map<decltype(make_tuple(__VA_ARGS__)),rt> cache;\
    if ((cache).count({__VA_ARGS__})){\
        return (cache)[{__VA_ARGS__}];\
    }

#define none 9000000000000000000LLU

template<llu n>
struct sized{
    char a[n];
};

template<
    typename t0=sized<0>,
    typename t1=sized<0>,
    typename t2=sized<0>,
    typename t3=sized<0>,
    typename t4=sized<0>,
    typename t5=sized<0>,
    typename t6=sized<0>,
    typename t7=sized<0>
>

struct t{
    t0 v0;
    t1 v1;
    t2 v2;
    t3 v3;
    t4 v4;
    t5 v5;
    t6 v6;
    t7 v7;
};

#if __cplusplus>=201703L

template<llu n=0,typename T,typename R>
auto clear_tuple(T t=tuple<>(),R r=tuple<>(),enable_if_t<tuple_size_v<R><=n or  is_same_v<sized<0>,tuple_element_t<n,R>>,int> =0){
    return t;
}

template<llu n=0,typename T,typename R>
auto clear_tuple(T t=tuple<>(),R r=tuple<>(),enable_if_t<n<tuple_size_v<R> and !is_same_v<sized<0>,tuple_element_t<n,R>>,int> =0){
    return clear_tuple<n+1>(tuple_cat(t,make_tuple(get<n>(r))),r);
}

template<typename...T>
auto to_str(t<T...>r){
    return clear_tuple(tuple<>(),(tuple<T...>&&)r);
}

#endif

#define get_bit(a,s)   (((a)[(s)/8LLU/sizeof((a)[0])]>>(s)%(8LLU*sizeof((a)[0])))&1LLU)
#define set_bit(a,s,d) {(a)[(s)/8LLU/sizeof((a)[0])]&=~(1LLU<<(s)%(8LLU*sizeof((a)[0])));(a)[(s)/8LLU/sizeof((a)[0])]+=((d)+0LLU)<<(s)%(8LLU*sizeof((a)[0]));}

///////////////////////////////////////////////////end of lib

int main(){
    llu n=getint(),m=getint();
    vector<string> a;
    for (llu w=0;w<m;++w){
        a.emplace_back();
        cin>>a.back();
    }
    vector<llu> s(26);
    vector<llu> d(26);
    for (llu w=1;w<m;++w){
        for (llu e=0;e<a[w-1].size() and e<a[w].size();++e){
            if (a[w-1][e]!=a[w][e]){
                set_bit(&s[a[w-1][e]-'A'],a[w][e]-'A',1);
                break;
            }
        }
    }
    for (llu w=0;w<m;++w){
        for (llu e=0;e<a[w].size();++e){
            d[a[w][e]-'A']=1;
        }
    }
    for (llu e=0;e<26;++e){
        for (llu q=0;q<26;++q){
            for (llu w=0;w<26;++w){
                if (get_bit(&s[q],w)){
                    s[q]|=s[w];
                }
            }
        }
    }
    vector<llu> l;
    for (llu w=0;w<26;++w){
        if (d[w]){
            l.push_back(w);
        }
    }
    sort(l.begin(),l.end(),[&](auto q,auto w){
        return get_bit(&s[q],w);
    });
    for (auto w:l){
        cout<<char(w+'A');
    }
    cout<<endl;
}
