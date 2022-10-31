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

///////////////////////////////////////////////////end of lib

struct cycle{
    vector<t<llu,vector<llu>>> a;
    vector<llu> loop;

    void dfs(llu start){
        vector<t<llu,llu,llu,llu>> layers;
        layers.push_back({start,none,0,0});
        auto lback=&layers.back();
        goto _dfs;
        _s:
        switch(lback->v2){
            case 0:
            break;
            _dfs:
            // ic(layers)
            // ic(a)
            lback=&layers.back();
            if (a[lback->v0].v0==none){
                a[lback->v0].v0=lback->v1;
                for (lback->v3=0;lback->v3<a[lback->v0].v1.size();++lback->v3){
                    layers.push_back({a[lback->v0].v1[lback->v3],lback->v0,1});
                    goto _dfs;
                    case 1:
                    layers.pop_back();
                    lback=&layers.back();
                }
                a[lback->v0].v0=none+1;
            }else
            if (a[lback->v0].v0==none+1){

            }else{
                llu t=lback->v1;
                loop.resize(0);
                while (t!=lback->v0){
                    loop.push_back(t);
                    t=a[t].v0;
                }
                loop.push_back(t);
            }
            goto _s;
        }
    }
};

int main(){
    cycle y;
    llu n=getint(),m=getint();
    auto&a=y.a;
    auto&loop=y.loop;
    a.resize(n,{none,{}});
    for (llu w=0;w<m;++w){
        llu z=getint()-1,x=getint()-1;
        a[z].v1.emplace_back(x);
    }
    for (llu w=0;w<n;++w){
        y.dfs(w);
        // a.resize(0);
        // a.resize(n,{none,{}});
    }
    if (loop.size()){
        printf("YES\n");
        for (auto w=loop.rbegin();w!=loop.rend();++w){
            cout<<*w+1<<" ";
        }
        cout<<"\n";
    }else{
        printf("NO\n");
    }
}
