#include <bits/stdc++.h>
using namespace std;

template<typename...T>
auto print_errors(T&&...a){
    (cout<<...<<a)<<endl;
    exit(1);
}

enum class unused_type : int {};

template <typename T>
string str_type(const T&q) {
    if constexpr (is_same_v<T,unused_type>){
        return "";
    }
    std::string a(__PRETTY_FUNCTION__);
    return std::string(a.begin()+min(37LLU,a.size()-1LLU),a.end()-1);
}

template <typename...T>
std::string str_types(const T&...q) {
    vector<string> a={str_type(q)...};
	std::stringstream _c;
	size_t c=0;
	for (auto &w:a){
        if (w.empty()){
            break;
        }
		if (c++){
			_c<<", ";
		}
		_c<<w;
	}
	return "["+_c.str()+"]";
}

#define try_expr(...)                                                            \
    [&]<                                                                         \
        typename t0 = unused_type,                                               \
        typename t1 = unused_type,                                               \
        typename t2 = unused_type,                                               \
        typename t3 = unused_type,                                               \
        typename t4 = unused_type,                                               \
        typename t5 = unused_type,                                               \
        typename t6 = unused_type,                                               \
        typename t7 = unused_type,                                               \
        typename t8 = unused_type,                                               \
        typename t9 = unused_type,                                               \
        typename t10= unused_type,                                               \
        typename t11= unused_type,                                               \
        typename t12= unused_type,                                               \
        typename t13= unused_type,                                               \
        typename t14= unused_type,                                               \
        typename t15= unused_type                                                \
    >(                                                                           \
        t0 &&v0 = t0(),                                                          \
        t1 &&v1 = t1(),                                                          \
        t2 &&v2 = t2(),                                                          \
        t3 &&v3 = t3(),                                                          \
        t4 &&v4 = t4(),                                                          \
        t5 &&v5 = t5(),                                                          \
        t6 &&v6 = t6(),                                                          \
        t7 &&v7 = t7(),                                                          \
        t8 &&v8 = t8(),                                                          \
        t9 &&v9 = t9(),                                                          \
        t10&&v10= t10(),                                                         \
        t11&&v11= t11(),                                                         \
        t12&&v12= t12(),                                                         \
        t13&&v13= t13(),                                                         \
        t14&&v14= t14(),                                                         \
        t15&&v15= t15()                                                          \
    ) {                                                                          \
        universal tmp;                                                           \
        if constexpr (requires{tmp=(__VA_ARGS__);}) {                            \
            tmp = (__VA_ARGS__);                                                 \
            return tmp;                                                          \
        } else                                                                   \
        if constexpr (requires {(__VA_ARGS__);}) {                               \
            (__VA_ARGS__);                                                       \
        } else {                                                                 \
            print_errors( "Invalid expression: " , #__VA_ARGS__ , " with "       \
                , str_types(v0, v1, v2, v3, v4, v5, v6, v7,                      \
                       v8, v9, v10, v11, v12, v13, v14, v15) );                  \
        }                                                                        \
        return universal();                                                      \
    }

struct universal;

using universal_variant=variant<
    unused_type,
    long long,
    long long unsigned,
    string,
    vector<universal>,
    set<universal>,
    // map<universal,universal>,
    unordered_set<universal>,
    // unordered_map<universal,universal>,
    bool
>;

size_t hash_f(const universal&o);

namespace std{
    template<>
    struct hash<universal>{
        auto operator()(const universal&o)const{
            return hash_f(o);
        }
    };
};

struct universal{
    universal_variant _data;
    template<typename T=long>
    universal(T&&a=0)
    requires requires{
        universal_variant(a);
    }:_data(a){}
    universal(universal&&o){
        _data=move(o._data);
    }
    universal(const universal&o){
        _data=o._data;
    }
    universal(universal&o){
        _data=o._data;
    }
    auto&operator=(universal&&o){
        _data=move(o._data);
        return *this;
    }
    auto&operator=(universal&o){
        _data=o._data;
        return *this;
    }
    auto&operator=(const universal&o){
        _data=o._data;
        return *this;
    }
    static decltype(auto) _get_data(universal&q){
        return q._data;
    }
    static decltype(auto) _get_data(const universal&q){
        return q._data;
    }
#define add_method(name,expr,cv_status)\
    template<typename...T>\
    decltype(auto) name(T&&...a)cv_status{\
        return visit(try_expr(expr),_data,_get_data(a)...);\
    }
    add_method(size,v0.size(),const);
    add_method(operator+=,v0 += v1,);
    add_method(operator-=,v0 -= v1,);
    add_method(operator*=,v0 *= v1,);
    add_method(operator/=,v0 /= v1,);
    add_method(operator%=,v0 %= v1,);
    add_method(operator|=,v0 |= v1,);
    add_method(operator&=,v0 &= v1,);
    add_method(operator^=,v0 ^= v1,);
    add_method(operator<<=,v0 <<= v1,);
    add_method(operator>>=,v0 >>= v1,);
    add_method(push_back,v0.push_back(v1),);
    add_method(pop_back,v0.pop_back(),);
    add_method(back,v0.back(),);
    add_method(front,v0.front(),);
    add_method(cmp_lt,v0 < v1,const);
    add_method(cmp_gt,v0 > v1,const);
    add_method(cmp_le,v0 <= v1,const);
    add_method(cmp_ge,v0 >= v1,const);
    add_method(cmp_eq,v0 == v1,const);
    add_method(cmp_ne,v0 != v1,const);
    add_method(hash,(long long)(hash(v0)),const);
    add_method(insert,v0.insert(v1),);
    add_method(erase,v0.insert(v1),);
    add_method(count,v0.count(v1),);
    add_method(operator[],v0[v1],);
#undef add_method
};

size_t hash_f(const universal&q){
    return get<long long>(q.hash()._data);
}

auto&operator<<(ostream&ostream,const universal&q){
    visit(try_expr(ostream << v0),q._data);
    return ostream;
}

auto to_str(const universal&o){
    return o._data;
}

decltype(auto) operator+(const universal&q,const universal&e){auto t=q;t+=e;return t;}
decltype(auto) operator-(const universal&q,const universal&e){auto t=q;t-=e;return t;}
decltype(auto) operator*(const universal&q,const universal&e){auto t=q;t*=e;return t;}
decltype(auto) operator/(const universal&q,const universal&e){auto t=q;t/=e;return t;}
decltype(auto) operator%(const universal&q,const universal&e){auto t=q;t%=e;return t;}
decltype(auto) operator|(const universal&q,const universal&e){auto t=q;t|=e;return t;}
decltype(auto) operator&(const universal&q,const universal&e){auto t=q;t&=e;return t;}
decltype(auto) operator^(const universal&q,const universal&e){auto t=q;t^=e;return t;}
decltype(auto) operator>>(const universal&q,const universal&e){auto t=q;t>>=e;return t;}
decltype(auto) operator<<(const universal&q,const universal&e){auto t=q;t<<=e;return t;}
bool operator< (const universal&q,const universal&e){return get<bool>(q.cmp_lt(e)._data);}
bool operator<=(const universal&q,const universal&e){return get<bool>(q.cmp_le(e)._data);}
bool operator> (const universal&q,const universal&e){return get<bool>(q.cmp_gt(e)._data);}
bool operator>=(const universal&q,const universal&e){return get<bool>(q.cmp_ge(e)._data);}
bool operator==(const universal&q,const universal&e){return get<bool>(q.cmp_eq(e)._data);}
bool operator!=(const universal&q,const universal&e){return get<bool>(q.cmp_ne(e)._data);}

int main(){
    universal a=1,s=2,d="3",f="4";
    // ic(a,s,d,f)
    // a+=1;
    // s+=2;
    // ic(a,s,d,f)
    // d+="3";
    // f+="4";
    // ic(a,s,d,f)
    // d=d+48;
    // f+=49;
    // ic(a,s,d,f)
    // a+="3";
    // s+="4";
    // ic(a,s,d,f)

    // ic(a,s,d,f)
    // ic(a<s,s<a,a==a,a<a,a<=a,a>=a)
    // ic(d<f,f<d,d==d,d<d,d<=d,d>=d)

    a=vector<universal>({3,0});
    s=vector<universal>({4,0});

    a.push_back(1);

    a[0]=4;

    // ic(strtype(a._data));

    // cout<<a[0]<<endl;
    // ic(a,a[0])

    for (long w=0;w<a.size();++w){
        cout<<a[w]<<" ";
    }
    cout<<endl;


    // ic(a.size())
    // universal_variant q=1,w=2,e="3",r="4";
    // ic(visit(try_expr(v0+v1),q,w));
    // ic(visit(try_expr(v0+v1),e,r));
    // ic(visit(try_expr(v0+v1),q,r));
    // ic(strtype(try_expr(v0+v1)(1,2)));
}
