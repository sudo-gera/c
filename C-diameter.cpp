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
#include <functional>
#include <type_traits>
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n;
using std::back_inserter, std::list, std::hash, std::reverse;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::copy_if, std::exit, std::enable_if, std::enable_if;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::tuple_element, std::tuple_size, std::is_same;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::unique;

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
using lli=long long;

#define cache(rt,...)\
    static map<decltype(make_tuple(__VA_ARGS__)),rt> cache;\
    if ((cache).count({__VA_ARGS__})){\
        return (cache)[{__VA_ARGS__}];\
    }

#define none 9000000000000000000

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
// better than tuple
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

template<llu n=0,typename T,typename R>
requires(tuple_size_v<R><=n or  is_same_v<sized<0>*,tuple_element_t<n,R>>)
auto clear_tuple(T t=tuple<>(),R r=tuple<>()){
    return t;
}

template<llu n=0,typename T,typename R>
requires(n<tuple_size_v<R> and !is_same_v<sized<0>*,tuple_element_t<n,R>>)
auto clear_tuple(T t=tuple<>(),R r=tuple<>()){
    return clear_tuple<n+1>(tuple_cat(t,make_tuple(get<n>(r))),r);
}

template<typename...T>
auto t2tuple(t<T...>r){
    return apply([&](auto...a){return tuple(*(a)...);},clear_tuple(tuple<>(),tuple{&r.v0,&r.v1,&r.v2,&r.v3,&r.v4,&r.v5,&r.v6,&r.v7}));
}

template<typename...T>
auto to_str(t<T...>r){
    return t2tuple(r);
}

template<typename...R,typename...Y>bool operator< (t<R...>r,t<Y...>y){return t2tuple(r)< t2tuple(y);}
template<typename...R,typename...Y>bool operator> (t<R...>r,t<Y...>y){return t2tuple(r)> t2tuple(y);}
template<typename...R,typename...Y>bool operator<=(t<R...>r,t<Y...>y){return t2tuple(r)<=t2tuple(y);}
template<typename...R,typename...Y>bool operator>=(t<R...>r,t<Y...>y){return t2tuple(r)>=t2tuple(y);}
template<typename...R,typename...Y>bool operator!=(t<R...>r,t<Y...>y){return t2tuple(r)!=t2tuple(y);}
template<typename...R,typename...Y>bool operator==(t<R...>r,t<Y...>y){return t2tuple(r)==t2tuple(y);}


#ifndef ic
#define ic(...)
#endif

#ifndef eic
#define eic
#endif

/*

a | assign(min) | b;
-- instead of
a = min(a, b);

*/

template<typename T>
struct assign_s{
    T f;
};

template<typename T>
assign_s(T f)->assign_s<T>;

template<typename T,typename Y>
auto operator|(T&&q,assign_s<Y> w){
    return t<remove_reference_t<T>*,assign_s<Y>>{&q,w};
}

template<typename R,typename T,typename Y>
auto operator|(t<R*,assign_s<T>> q,Y&&w){
    q.v0[0]=q.v1.f(q.v0[0],w);
}

#define assign(f) assign_s{[&](auto q,auto w){return (f)(q,w);}}


///////////////////////////////////////////////////end of lib

auto get_distances_from(auto start,auto get_next){
    // auto start=*(llu*)(_start);
    // auto&get_next=*(std::vector<std::vector<t<unsigned long long, unsigned long long>>>*)(_get_next);
    set<t<llu,llu>> f;
    map<llu,t<llu,decltype(f.end())>> d;
    d[start]={0,f.insert({0,start}).first};
    while (not f.empty()){
        auto ptr=f.begin();
        auto w=ptr->v1;
        for (auto&_q:get_next(w)){
            auto [n,q]=make_tuple(_q.v0,_q.v1);
            if (not d.count(n)){
                d[n]={-1LLU,f.insert({-1LLU,n}).first};
            }
            if (d[n].v1==f.end()){
                continue;
            }
            d[n].v0|assign(min)|d[w].v0+q;
            auto node=f.extract(d[n].v1);
            node.value().v0=d[n].v0;
            f.insert(move(node));
        }
        f.erase(ptr);
        d[w].v1=f.end();
    }
    return d;
}

int main(){
    llu n=getint();
    vector<vector<t<llu,llu>>> a(n);
    for (llu q=0;q<n;++q){
        for (llu w=0;w<n;++w){
            llu z=getint();
            if (z!=-1 and q!=w){
                a[q].push_back({w,z});
            }
        }
    }
    t<llu,llu,llu> res={-1LLU,-1LLU,0LLU};
    for (llu q=0;q<n;++q){
        auto d=get_distances_from(q,[&](auto q)->decltype(a[q]){return a[q];});
        ic(d)
        for (auto&w:d){
            if (w.second.v0>res.v2){
                res={q,w.first,w.second.v0};
            }
        }
    }
    cout<<res.v2<<endl;
}
