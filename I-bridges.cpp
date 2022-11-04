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

#if __cplusplus>=201703L //only for debugging



#endif

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

struct vert{
    llu dfs_state=0;
    vector<llu> next;
    ll index_in_stack=none;
    ll higher_possible=none;
    ll higher_possible_if_this_deleted=-none;
};

struct call_layer{
    llu current;
    llu previous;
    llu switch_value;
    llu for_iterator;
    llu next_counter;
};

void dfs(vector<vert>&a,vector<t<llu,llu>>&r,llu start){
    if (a[start].dfs_state>=2){
        return;
    }
    vector<call_layer> l;
    l.push_back({start,none,0,0,0});
    a[start].index_in_stack=0;
    a[start].higher_possible=0;
    auto csb=&l.back();
    goto _dfs;
    _s:
    switch(csb->switch_value){
        case 0:
        a[start].index_in_stack=none;
        a[start].higher_possible=none;
        a[start].higher_possible_if_this_deleted=-none;
        break;
        _dfs:
        csb=&l.back();
        if (a[csb->current].dfs_state==0){
            a[csb->current].dfs_state=1;
            for (csb->for_iterator=0;csb->for_iterator<a[csb->current].next.size();++csb->for_iterator){
                if (a[a[csb->current].next[csb->for_iterator]].dfs_state<2 and a[csb->current].next[csb->for_iterator]!=csb->previous){
                    if (a[a[csb->current].next[csb->for_iterator]].index_in_stack==none){
                        a[a[csb->current].next[csb->for_iterator]].index_in_stack=l.size();
                        a[a[csb->current].next[csb->for_iterator]].higher_possible=l.size();
                    }
                    csb->next_counter+=1;
                    l.push_back({a[csb->current].next[csb->for_iterator],csb->current,1,0,0});
                    goto _dfs;
                    case 1:
                    l.pop_back();
                    csb=&l.back();
                    if (a[a[csb->current].next[csb->for_iterator]].index_in_stack==l.size()){
                        a[csb->current].higher_possible_if_this_deleted|max_assigner()|a[a[csb->current].next[csb->for_iterator]].higher_possible;
                        a[csb->current].higher_possible|min_assigner()|a[a[csb->current].next[csb->for_iterator]].higher_possible;
                        a[a[csb->current].next[csb->for_iterator]].index_in_stack=none;
                        a[a[csb->current].next[csb->for_iterator]].higher_possible=none;
                        a[a[csb->current].next[csb->for_iterator]].higher_possible_if_this_deleted=-none;
                    }
                }
            }
            if (a[csb->current].higher_possible==a[csb->current].index_in_stack){
                r.push_back({csb->current,csb->previous});
            }
            if (l.size()>1 and a[csb->current].index_in_stack==a[csb->current].higher_possible_if_this_deleted or l.size()==1 and csb->next_counter>1){
                a[csb->current].dfs_state=3;
            }else{
                a[csb->current].dfs_state=2;
            }
        }else
        if (a[csb->current].dfs_state==1){
            a[csb->previous].higher_possible|min_assigner()|a[csb->current].index_in_stack;
        }else{

        }
        goto _s;
    }
}


int main(){
    llu n=getint(),m=getint();
    vector<vert> a(n);
    vector<t<llu,llu>> e;
    vector<t<llu,llu>> r;
    for (llu w=0;w<m;++w){
        llu z=getint()-1,x=getint()-1;
        a[z].next.push_back(x);
        a[x].next.push_back(z);
        e.push_back({z,x});
    }
    for (llu w=0;w<n;++w){
        dfs(a,r,w);
    }
    ic(r)
    sort(r.begin(),r.end());
    ic(r)
    llu c=0;
    for (llu w=0;w<m;++w){
        auto y=e[w];
        swap(y.v0,y.v1);
        if (lower_bound(r.begin(),r.end(),e[w])!=upper_bound(r.begin(),r.end(),e[w]) or lower_bound(r.begin(),r.end(),y)!=upper_bound(r.begin(),r.end(),y)){
            c+=1;
        }
    }
    cout<<c<<endl;
    for (llu w=0;w<m;++w){
        auto y=e[w];
        swap(y.v0,y.v1);
        if (lower_bound(r.begin(),r.end(),e[w])!=upper_bound(r.begin(),r.end(),e[w]) or lower_bound(r.begin(),r.end(),y)!=upper_bound(r.begin(),r.end(),y)){
            cout<<w+1<<" ";
        }
    }
    cout<<endl;
}
