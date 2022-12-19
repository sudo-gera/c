#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>
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
using std::generate, std::generate_n, std::remove_reference_t, std::array;

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
auto clear_tuple(T t=tuple<>(),R r=tuple<>(),typename enable_if<tuple_size<R>::value<=n or  is_same<sized<0>,typename tuple_element<n,R>::type>::value,int>::type =0){
    return t;
}

template<llu n=0,typename T,typename R>
auto clear_tuple(T t=tuple<>(),R r=tuple<>(),typename enable_if<n<tuple_size<R>::value and !is_same<sized<0>,typename tuple_element<n,R>::type>::value,int>::type =0){
    return clear_tuple<n+1>(tuple_cat(t,make_tuple(get<n>(r))),r);
}

template<typename...T>
auto t2tuple(t<T...>r){
    return clear_tuple(tuple<>(),(tuple<T...>&&)(r));
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

void _set(llu&q,llu i,llu v){
    llu y=((uint8_t*)(&q))[i/2];
    if (i%2){
        y=y%16|v*16;
    }else{
        y=y/16%16*16|v;
    }
    ((uint8_t*)(&q))[i/2]=y;
}

llu _get(llu&q,llu i){
    llu y=((uint8_t*)(&q))[i/2];
    if (i%2){
        return y/16;
    }else{
        return y%16;
    }
}

auto get_next(llu q){
    vector<llu> s;
    for (llu w=0;w<3;++w){
        for (llu e=0;e<3;++e){
            if (_get(q,w*3+e)==9){
                llu z=0,x=0;
                z=w-1,x=e;
                if (z<3 and x<3){
                    llu a=q;
                    _set(a,w*3+e,_get(q,z*3+x));
                    _set(a,z*3+x,_get(q,w*3+e));
                    s.push_back(a);
                }
                z=w+1,x=e;
                if (z<3 and x<3){
                    llu a=q;
                    _set(a,w*3+e,_get(q,z*3+x));
                    _set(a,z*3+x,_get(q,w*3+e));
                    s.push_back(a);
                }
                z=w,x=e-1;
                if (z<3 and x<3){
                    llu a=q;
                    _set(a,w*3+e,_get(q,z*3+x));
                    _set(a,z*3+x,_get(q,w*3+e));
                    s.push_back(a);
                }
                z=w,x=e+1;
                if (z<3 and x<3){
                    llu a=q;
                    _set(a,w*3+e,_get(q,z*3+x));
                    _set(a,z*3+x,_get(q,w*3+e));
                    s.push_back(a);
                }
                return s;
            }
        }
    }
    return s;
}


int main(){
    llu n=0;
    {
        string s[3];
        int c=0;
        while ((c=getchar())!='\n' and c!=EOF){
            s[0]+=c;
        }
        while ((c=getchar())!='\n' and c!=EOF){
            s[1]+=c;
        }
        while ((c=getchar())!='\n' and c!=EOF){
            s[2]+=c;
        }

        array<int,12> _q({
            ((s[0][0]-'0'+25)%25),
            ((s[0][1]-'0'+25)%25),
            ((s[0][2]-'0'+25)%25),
            ((s[1][0]-'0'+25)%25),
            ((s[1][1]-'0'+25)%25),
            ((s[1][2]-'0'+25)%25),
            ((s[2][0]-'0'+25)%25),
            ((s[2][1]-'0'+25)%25),
            ((s[2][2]-'0'+25)%25),
        });
        llu q=0;
        _set(q,0,_q[ 0]);
        _set(q,1,_q[ 1]);
        _set(q,2,_q[ 2]);
        _set(q,3,_q[ 3]);
        _set(q,4,_q[ 4]);
        _set(q,5,_q[ 5]);
        _set(q,6,_q[ 6]);
        _set(q,7,_q[ 7]);
        _set(q,8,_q[ 8]);
        n=q;
    }
    map<
        llu,
        t<llu>
    > tree;
    vector<llu> q;
    q.push_back(n);
    tree[n].v0=0;
    llu qg=0;
    while(qg!=q.size()){
        auto z=q[qg++];
        auto x=get_next(z);
        if (z==0x987654321){
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
    cout<<-1<<endl;
}

