#include <bits/stdc++.h>
using namespace std;

enum class unused_type : int {};

template <typename T>
string str_type(const T&q) {
    if constexpr (is_same_v<T,unused_type>){
        return "";
    }
    std::string a(__PRETTY_FUNCTION__);
    // return a;
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

#define try_expr(...)                                                          \
    [&]<                                                                       \
        typename t0 = unused_type,                                             \
        typename t1 = unused_type,                                             \
        typename t2 = unused_type,                                             \
        typename t3 = unused_type,                                             \
        typename t4 = unused_type,                                             \
        typename t5 = unused_type,                                             \
        typename t6 = unused_type,                                             \
        typename t7 = unused_type                                              \
    >(                                                                         \
        t0&&v0 = t0(),                                                         \
        t1&&v1 = t1(),                                                         \
        t2&&v2 = t2(),                                                         \
        t3&&v3 = t3(),                                                         \
        t4&&v4 = t4(),                                                         \
        t5&&v5 = t5(),                                                         \
        t6&&v6 = t6(),                                                         \
        t7&&v7 = t7()                                                          \
    ) {                                                                        \
        variant tmp;                                                           \
        return tmp;                                                            \
    }

struct universal;

using universal_variant=variant<
    unused_type,
    long long,
    long long unsigned,
    bool,
    string,
    vector<universal>,
    // set<universal>,
    // map<universal,universal>,
    // unordered_set<universal>,
    // unordered_map<universal,universal>,
    size_t
>;

struct universal{
    universal_variant _data;
    template<typename T=long>
    universal(T&&a=0):_data(a){}
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
};

int main(){
    universal a=1,s=2,d="3",f="4";
    a=vector<universal>({3});
    s=vector<universal>({4});
}
