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
    while (c = getchar_unlocked(), isspace(c) and c!=EOF)
        ;
    if (c == '-') {
        sign = -1;
    } else {
        res = c - '0';
    }
    while (c = getchar_unlocked(), isdigit(c) and c!=EOF) {
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

template<typename...T>
t(const T&&...a) -> t<remove_reference_t<T>...>;

template<llu n=0,typename T,typename R>
auto clear_tuple(T t=tuple<>(),R r=tuple<>(),enable_if_t<tuple_size_v<R><=n or  is_same_v<sized<0>,tuple_element_t<n,R>>,int> =0){
    return t;
}

template<llu n=0,typename T,typename R>
auto clear_tuple(T t=tuple<>(),R r=tuple<>(),enable_if_t<n<tuple_size_v<R> and !is_same_v<sized<0>,tuple_element_t<n,R>>,int> =0){
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

#define cat(q, w) q##w
#define unique_name(q) cat(_unique_name_, q)

#define recursive_loop(...)                                                        \
    for (                                                                          \
        struct {                                                                   \
            decltype(tie(__VA_ARGS__)) _tie;                                       \
            vector<pair<decltype(make_tuple(__VA_ARGS__)), void *>> call_stack;    \
            void *to_return_ptr;                                                   \
        } _rec{                                                                    \
            tie(__VA_ARGS__),                                                      \
            {{{}, &&start}},                                                       \
        };                                                                         \
        not({                                                                      \
            start:                                                                 \
            _rec.call_stack.empty();                                               \
        });                                                                        \
        assert(((void)"end without return", 0))                                    \
    )

#define call(...)                                                                  \
    {                                                                              \
        _rec.call_stack.push_back({_rec._tie, &&unique_name(__LINE__)});           \
        _rec._tie = decltype(_rec.call_stack[0].first){__VA_ARGS__};               \
        goto start;                                                                \
        unique_name(__LINE__) : {}                                                 \
    }

#define ret()                                                                      \
    {                                                                              \
        _rec._tie = _rec.call_stack.back().first;                                  \
        _rec.to_return_ptr = _rec.call_stack.back().second;                        \
        _rec.call_stack.pop_back();                                                \
        goto *_rec.to_return_ptr;                                                  \
    }

///////////////////////////////////////////////////end of lib

auto find_cond(auto n,auto a,auto s,auto d,auto h){
    llu time=0;
    [&](){
        for (llu w=0;w<n;++w){
            llu prev=none;
            llu current=w;
            llu for_index=0;
            llu for_value=0;
            recursive_loop(current,prev,for_index,for_value){
                if (d[current].v0==0){
                    d[current].v0=1;
                    for (for_index=0;for_index<a[current].size();++for_index){
                        for_value=a[current][for_index];
                        call(for_value,current,0,0);
                    }
                    d[current].v0=2;
                    d[current].v1=++time;
                }else
                if (d[current].v0==1){
                }else
                if (d[current].v0==2){
                }
                ret();
            }
        }
    }();
    vector<llu> e(n);
    iota(e.begin(),e.end(),0);
    sort(e.begin(),e.end(),[&](auto q,auto e){
        return d[q].v1>d[e].v1;
    });
    vector<vector<llu>> f;
    [&](){
        for (llu w=0;w<n;++w){
            f.emplace_back();
            llu prev=none;
            llu current=e[w];
            llu for_index=0;
            llu for_value=0;
            recursive_loop(current,prev,for_index,for_value){
                if (d[current].v0==2){
                    f.back().push_back(current);
                    d[current].v0=3;
                    for (for_index=0;for_index<s[current].size();++for_index){
                        for_value=s[current][for_index];
                        call(for_value,current,0,0);
                    }
                    d[current].v0=4;
                }else
                if (d[current].v0==3){
                }else
                if (d[current].v0==4){
                }
                ret();
            }
        }
    }();
    vector<llu> g(n);
    for (llu q=0;q<f.size();++q){
        for (llu w=0;w<f[q].size();++w){
            g[f[q][w]]=q;
        }
    }
    for (auto&w:h){
        w.v0=g[w.v0];
        w.v1=g[w.v1];
    }
    sort(h.begin(),h.end());
    h.resize(unique(h.begin(),h.end())-h.begin());
    auto j=h;
    j.resize(0);
    copy_if(h.begin(),h.end(),back_inserter(j),[&](auto q){
        return q.v0!=q.v1;
    });
    vector<llu> k(n,-1);
    llu l=0;
    for (llu w=0;w<f.size();++w){
        if (f[w].size()){
            k[w]=l++;
        }
    }
    for (auto&w:j){
        w.v0=k[w.v0];
        w.v1=k[w.v1];
    }
    vector<vector<llu>> c;
    copy_if(f.begin(),f.end(),back_inserter(c),[&](auto&q){
        return q.size();
    });
    pair v(c,j);
    return v;
}

int main(){
    auto[comps,edges]=({
        llu n=getint();
        vector<vector<llu>> a(n);
        vector<vector<llu>> s(n);
        vector<t<llu,llu>> d(n);
        vector<t<llu,llu>> h;
        for (llu w=0;;++w){
            llu z=getint()-1,x=getint()-1;
            if (z==-50 or x==-50){
                break;
            }
            a[z].push_back(x);
            s[x].push_back(z);
            h.push_back({z,x});
        }
        find_cond(n,a,s,d,h);
    });
    ic(comps)
    ic(edges)
    llu n=comps.size();
    vector<vector<llu>> a(n);
    vector<vector<llu>> s(n);
    vector<t<llu>> d(n);
    for (auto w:edges){
        a[w.v0].push_back(w.v1);
        s[w.v1].push_back(w.v0);
    }
    ic(a)
    ic(s)
    vector<llu> vin;
    set<llu> sin;
    vector<llu> vout;
    set<llu> sout;
    llu count=1;
    for (llu w=0;w<n;++w){
        if (s[w].size()==0){
            vector<llu> q;
            q.push_back(w);
            llu qq=0;
            while(qq!=q.size()){
                auto _t=q[qq++];
                if (d[_t].v0!=count){
                    d[_t].v0=count;
                    if (sout.count(_t)==0 and a[_t].size()==0){
                        vin.push_back(w);
                        sin.insert(w);
                        vout.push_back(_t);
                        sout.insert(_t);
                        break;
                    }
                    for (auto r:a[_t]){
                        q.push_back(r);
                    }
                }
            }
            count+=1;

            // llu _t=w;
            // llu e=0;
            // recursive_loop(_t,e){
            //     if (d[_t].v0!=count){
            //         d[_t].v0=count;
            //         if (sout.count(_t)==0 and a[_t].size()==0){
            //             vin.push_back(w);
            //             sin.insert(w);
            //             vout.push_back(_t);
            //             sout.insert(_t);
            //             break;
            //         }
            //         for (e=0;e<a[_t].size();++e){
            //             call(a[_t][e],0);
            //         }
            //     }
            //     ret();
            // }
            // count+=1;
        }
    }
    ic(vin)
    ic(sin)
    ic(vout)
    ic(sout)
    llu base=-1;
    vector<t<llu,llu>> res;
    for (llu w=1;w<sin.size();++w){
        res.push_back({vout[w-1],vin[w]});
    }
    if (sin.size()){
        base=vin[0];
        res.push_back({vout[sin.size()-1],vin[0]});
    }
    for (auto w:res){
        a[w.v0].push_back(w.v1);
        s[w.v1].push_back(w.v0);
    }
    ic(a)
    ic(s)
    ic(res)
    vin.clear();
    vout.clear();
    for (llu w=0;w<n;++w){
        if (s[w].size()==0){
            vin.push_back(w);
        }
        if (a[w].size()==0){
            vout.push_back(w);
        }
    }
    while(vin.size() and vout.size()){
        res.push_back({vout.back(),vin.back()});
        vin.pop_back();
        vout.pop_back();
    }
    ic(res)
    while (vin.size()){
        res.push_back({base,vin.back()});
        vin.pop_back();
    }
    while (vout.size()){
        res.push_back({vout.back(),base});
        vout.pop_back();
    }
    ic(res)
    cout<<res.size()<<"\n";
    for (auto w:res){
        cout<<comps[w.v0][0]+1<<" "<<comps[w.v1][0]+1<<"\n";
    }
}
