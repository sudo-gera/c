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

template
    <typename t0=sized<1>
    ,typename t1=sized<1>
    ,typename t2=sized<1>
    ,typename t3=sized<1>
    ,typename t4=sized<1>
    ,typename t5=sized<1>
    ,typename t6=sized<1>
    ,typename t7=sized<1>
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

template<typename...T>
tuple<T...> t2tuple(t<T...> r){
    return make_tuple(
        r.v0,
        r.v1,
        r.v2,
        r.v3,
        r.v4,
        r.v5,
        r.v6,
        r.v7
    );
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
    return clear_tuple(tuple<>(),t2tuple(r));
}

#endif

///////////////////////////////////////////////////end of lib

// #define t pair
// #define v0 first
// #define v1 second

int main(){
    llu n=getint();
    char c=0;
    cin>>c;
    c-='A';
    t<llu,llu>s={c+0LLU,0LLU+getint()-1};
    cin>>c;
    c-='A';
    t<llu,llu>f={c+0LLU,0LLU+getint()-1};

    llu qu=0;
    vector<t<t<llu,llu>,llu>> q;
    map<t<llu,llu>,llu> seen;
    seen[s]=1;
    q.push_back({s,none});
    while (q.size()!=qu){
        auto _t=q[qu++].v0;
        if (_t==f){
            llu y=qu-1;
            vector<t<llu,llu>> ans;
            while (y!=none){
                ans.push_back(q[y].v0);
                y=q[y].v1;
            }
            ans.pop_back();
            cout<<ans.size()<<endl;
            while (ans.size()){
                cout<<char('A'+ans.back().v0)<<ans.back().v1+1<<"\n";
                ans.pop_back();
            }
            cout<<endl;
            return 0;
        }
        auto u=_t;
        u={_t.v0-1,_t.v1-2};
        if (u.v0<n and u.v1<n){
            if (!seen[u]){
                seen[u]=1;
                q.push_back({u,qu-1});
            }
        }
        u={_t.v0-2,_t.v1-1};
        if (u.v0<n and u.v1<n){
            if (!seen[u]){
                seen[u]=1;
                q.push_back({u,qu-1});
            }
        }
        u={_t.v0+1,_t.v1-2};
        if (u.v0<n and u.v1<n){
            if (!seen[u]){
                seen[u]=1;
                q.push_back({u,qu-1});
            }
        }
        u={_t.v0+2,_t.v1-1};
        if (u.v0<n and u.v1<n){
            if (!seen[u]){
                seen[u]=1;
                q.push_back({u,qu-1});
            }
        }
        u={_t.v0-1,_t.v1+2};
        if (u.v0<n and u.v1<n){
            if (!seen[u]){
                seen[u]=1;
                q.push_back({u,qu-1});
            }
        }
        u={_t.v0-2,_t.v1+1};
        if (u.v0<n and u.v1<n){
            if (!seen[u]){
                seen[u]=1;
                q.push_back({u,qu-1});
            }
        }
        u={_t.v0+1,_t.v1+2};
        if (u.v0<n and u.v1<n){
            if (!seen[u]){
                seen[u]=1;
                q.push_back({u,qu-1});
            }
        }
        u={_t.v0+2,_t.v1+1};
        if (u.v0<n and u.v1<n){
            if (!seen[u]){
                seen[u]=1;
                q.push_back({u,qu-1});
            }
        }
    }
}

