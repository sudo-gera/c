#include <type_traits>

template<typename T>
constexpr int print_type_f(){
    int unused=0;
    return 1;
}

template<typename T>
using print_type=std::conditional_t<print_type_f<T>(),T,void>;

#define print_type_v(...) (std::conditional_t<1,int,print_type<decltype(__VA_ARGS__)>>(0),__VA_ARGS__)

// -Wunused -Wno-unused-value




template<typename T>
using type=T;

int main(){
    type<print_type<long>> o=0;
}
