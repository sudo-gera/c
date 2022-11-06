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
using std::generate, std::generate_n, std::remove_reference_t;

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


///////////////////////////////////////////////////end of lib

#define cat(q,w) q##w
#define unique_name(q) cat(_unique_name_,q)

#define setup_recursion(...) \
    struct another_layer{\
        void* return_ptr;\
        layer::return_type rt_str;\
    };\
    vector<pair<layer,another_layer>> call_stack;\
    call_stack.emplace_back();\
    call_stack.push_back({{__VA_ARGS__},{&&end}});\
    void* setup_locals_ret=&&start;\
    setup_locals:\
    auto*locals_pair=&call_stack.back();\
    auto&locals=locals_pair[0].first;\
    auto&another_locals=locals_pair[0].second;\
    auto&last_returned=another_locals.rt_str;\
    auto&to_return=locals_pair[-1].second.rt_str;\
    goto *setup_locals_ret;\
    end:\
    return last_returned;\
    start:


#define call(...)\
    ({\
        {\
            call_stack.push_back({{__VA_ARGS__},{&&unique_name(__LINE__)}});\
            setup_locals_ret=&&start;\
            goto setup_locals;\
        }\
        unique_name(__LINE__):\
        {}\
    })

#define ret(...)\
    {\
        to_return=(__VA_ARGS__);\
        setup_locals_ret=another_locals.return_ptr;\
        call_stack.pop_back();\
        goto setup_locals;\
    }


struct v{
    llu dfs_state=0;
    vector<llu> next;
    ll index_in_stack=none;
    ll higher_possible=none;
    ll higher_possible_if_this_deleted=-none;
};

int dfs(vector<v>&a,llu start){
    if (a[start].dfs_state>=2){
        return 0;
    }
    a[start].index_in_stack=1;
    a[start].higher_possible=1;
    struct layer{
        llu current;
        llu previous;
        llu for_index;
        llu for_iterator;
        llu next_counter;
        using return_type=llu;
    };
    setup_recursion(start,none);
    if (a[locals.current].dfs_state==0){
        a[locals.current].dfs_state=1;
        for (locals.for_index=0;locals.for_index<a[locals.current].next.size();++locals.for_index){
            locals.for_iterator=a[locals.current].next[locals.for_index];
            if (a[locals.for_iterator].dfs_state<2){
                locals.next_counter+=1;
                if (a[locals.for_iterator].index_in_stack==none){
                    a[locals.for_iterator].index_in_stack=call_stack.size();
                    a[locals.for_iterator].higher_possible=call_stack.size();
                    call(locals.for_iterator,locals.current);
                    a[locals.current].higher_possible_if_this_deleted|assign(max)|a[locals.for_iterator].higher_possible;
                    a[locals.current].higher_possible|assign(min)|a[locals.for_iterator].higher_possible;
                    a[locals.for_iterator].index_in_stack=none;
                    a[locals.for_iterator].higher_possible=none;
                    a[locals.for_iterator].higher_possible_if_this_deleted=-none;
                }else{
                    call(locals.for_iterator,locals.current);
                }
            }
        }
        if (call_stack.size()>2 and a[locals.current].index_in_stack==a[locals.current].higher_possible_if_this_deleted or call_stack.size()==2 and locals.next_counter>1){
            a[locals.current].dfs_state=3;
        }else{
            a[locals.current].dfs_state=2;
        }
    }else
    if (a[locals.current].dfs_state==1){
        a[locals.previous].higher_possible|assign(min)|a[locals.current].index_in_stack;
    }
    if (call_stack.size()==2){
        a[start].index_in_stack=none;
        a[start].higher_possible=none;
        a[start].higher_possible_if_this_deleted=-none;
    }
    ret(0);
}


int main(){
    llu n=getint(),m=getint();
    vector<v> a(n);
    for (llu w=0;w<m;++w){
        llu z=getint()-1,x=getint()-1;
        a[z].next.push_back(x);
        a[x].next.push_back(z);
    }
    for (llu w=0;w<n;++w){
        dfs(a,w);
    }
    llu c=0;
    for (llu w=0;w<n;++w){
        if (a[w].dfs_state==3){
            c+=1;
        }
    }
    cout<<c<<endl;
    for (llu w=0;w<n;++w){
        if (a[w].dfs_state==3){
            cout<<w+1<<" ";
        }
    }
    cout<<endl;
}
