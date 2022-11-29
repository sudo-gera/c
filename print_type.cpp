#include <type_traits>

template<typename T>
constexpr int print_type_f(){
    int unused=0;
    return 1;
}

template<typename T>
using print_type=std::conditional_t<print_type_f<T>(),T,void>;







template<typename T>
using type=T;

int main(){
    type<print_type<long>> o=0;
}
