#include <type_traits>

template<typename T>
auto f(T q)->std::enable_if_t<!std::is_void_v<decltype(q)>,int>;

template<typename T>
auto f(T q)->std::enable_if_t<!std::is_void_v<decltype(q)>,int>{
	return q;
}

int main(){
    f(0);
}
