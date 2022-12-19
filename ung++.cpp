#include <type_traits>
#include <iostream>

template<typename T>
auto f(T q)->std::enable_if_t<!std::is_void_v<decltype(q)>,int>;

template<typename T>
auto f(T q)->std::enable_if_t<!std::is_void_v<decltype(q)>,int>{
	return q;
}

template<typename T>
auto g(T o)->decltype(f(o)){
    return f(o);
}

char g(...){
    return char(0);
}

template<typename T>
const char*compiler_te="";

template<>
const char*compiler_te<int> ="clang++";

template<>
const char*compiler_te<char> ="g++";

const char*compiler=compiler_te<decltype(g(0))>;

// constexpr bool is_clang = std::is_same<decltype(g(0)),int>::value;

// static_assert(is_clang);

int main(){
    std::cout<<compiler<<std::endl;
    
}
