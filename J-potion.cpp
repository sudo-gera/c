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
using std::cin; using std::cout; using std::endl; using std::vector; using std::string; using std::sort;
using std::pair; using std::set; using std::unordered_set; using std::map; using std::unordered_map;
using std::min; using std::max; using std::tuple; using std::tie; using std::get; using std::make_tuple;
using std::move; using std::swap; using std::generate; using std::generate_n;
using std::back_inserter; using std::list; using std::hash; using std::reverse;
using std::lower_bound; using std::upper_bound; using std::flush; using std::prev; using std::next;
using std::tuple_size; using std::lexicographical_compare; using std::set_intersection;
using std::copy_if; using std::exit; using std::enable_if; using std::enable_if;
using std::tuple_cat; using std::find; using std::find_if; using std::find_if_not;
using std::ref; using std::cref; using std::reference_wrapper; using std::remove_reference;
using std::tuple_element; using std::tuple_size; using std::is_same;
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
using ll=long long;

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
auto clear_tuple(T t=tuple<>(),R r=tuple<>(),typename enable_if<tuple_size<R>::value<=n or  is_same<sized<0>,typename tuple_element<n,R>::type>::value,int>::type =0)->
  decltype(t){
    return t;
}

template<llu n=0,typename T,typename R>
auto clear_tuple(T t=tuple<>(),R r=tuple<>(),typename enable_if<n<tuple_size<R>::value and !is_same<sized<0>,typename tuple_element<n,R>::type>::value,int>::type =0)->
  decltype(clear_tuple<n+1>(tuple_cat(t,make_tuple(get<n>(r))),r)){
    return clear_tuple<n+1>(tuple_cat(t,make_tuple(get<n>(r))),r);
}

template<typename...T>
auto t2tuple(t<T...>r)->
  decltype(clear_tuple(tuple<>(),(tuple<T...>&&)(r))){
    return clear_tuple(tuple<>(),(tuple<T...>&&)(r));
}

template<typename...T>
auto to_str(t<T...>r)->
  decltype(t2tuple(r)){
    return t2tuple(r);
}

template<llu n>bool operator< (sized<n>r,sized<n>y){return 0;}
template<llu n>bool operator> (sized<n>r,sized<n>y){return 0;}
template<llu n>bool operator<=(sized<n>r,sized<n>y){return 1;}
template<llu n>bool operator>=(sized<n>r,sized<n>y){return 1;}
template<llu n>bool operator!=(sized<n>r,sized<n>y){return 0;}
template<llu n>bool operator==(sized<n>r,sized<n>y){return 1;}

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

a | min_assigner() | b;
-- instead of
a = min(a, b);

*/

struct base_assigner{
    template<typename T>
    using is_assigner=T;
};

template<typename T,typename Y>
auto operator|(T&&q,Y&&w)->typename Y::template is_assigner<t<
    typename remove_reference<T>::type*,
    Y
>>{
    return {&q,w};
}

template<typename T,typename Y>
auto operator|(T&&q,Y&&w)->typename decltype(q.v1)::template is_assigner<void>{
    q.v1(q.v0[0],w);
}


struct min_assigner:base_assigner{
    template<typename T,typename Y>
    auto operator()(T&&q,Y&&w)->void{
        q=min(q,w);
    }
};

struct max_assigner:base_assigner{
    template<typename T,typename Y>
    auto operator()(T&&q,Y&&w)->void{
        q=max(q,w);
    }
};

///////////////////////////////////////////////////end of lib


t<llu,llu> get_next(t<llu,llu> q,t<llu,llu> s){
    if (q.v0>s.v1-q.v1){
        return {q.v0-s.v1+q.v1,s.v1};
    }else{
        return {0,q.v1+q.v0};
    }
}

auto _get_next(t<llu,llu,llu> q,t<llu,llu,llu> s){
    vector<decltype(q)> a;
    t<llu,llu> e;
    t<llu,llu,llu> r;
    e=get_next({q.v0,q.v1},{s.v0,s.v1});
    r={e.v0,e.v1,q.v2};
    if (r!=q){
        a.push_back(r);
    }
    e=get_next({q.v1,q.v0},{s.v1,s.v0});
    r={e.v1,e.v0,q.v2};
    if (r!=q){
        a.push_back(r);
    }
    e=get_next({q.v0,q.v2},{s.v0,s.v2});
    r={e.v0,q.v1,e.v1};
    if (r!=q){
        a.push_back(r);
    }
    e=get_next({q.v2,q.v0},{s.v2,s.v0});
    r={e.v1,q.v1,e.v0};
    if (r!=q){
        a.push_back(r);
    }
    e=get_next({q.v1,q.v2},{s.v1,s.v2});
    r={q.v0,e.v0,e.v1};
    if (r!=q){
        a.push_back(r);
    }
    e=get_next({q.v2,q.v1},{s.v2,s.v1});
    r={q.v0,e.v1,e.v0};
    if (r!=q){
        a.push_back(r);
    }
    return a;
}

int main(){
    llu n=getint(),m=getint(),k=getint(),l=getint();
    // s={n,m,k};
    // q=
    map<
        t<llu,llu,llu>,
        t<llu>
    > tree;
    vector<t<llu,llu,llu>> q;
    q.push_back({n,0,0});
    tree[{n,0,0}].v0=0;
    llu qg=0;
    while(qg!=q.size()){
        auto z=q[qg++];
        auto x=_get_next(z,{n,m,k});
        if (z.v0==l){
            cout<<tree[z].v0<<endl;
            return 0;
        }
        for (auto c:x){
            if (not tree.count(c)){
                tree[c].v0=tree[z].v0+1;
                q.push_back(c);
            }
        }
    }
    cout<<"OOPS"<<endl;
}

