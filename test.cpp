#include <tuple>
#include <type_traits>
#include <cassert>

#include "strtype.cpp"

constexpr auto f(){
    if consteval{
        return 2;
    }else{
        return 3;
    }
}

constexpr auto get_f(){
    auto t = f;
    return t;
}

constexpr auto r = get_f();
static_assert(r() == 2);


int main(){
    const auto t = get_f();
    assert(t() == 3);
    assert(r() == 3);
    
    printf("%s\n", name_of_type<decltype(t)>);
    printf("%s\n", name_of_type<decltype(r)>);
    printf("%p\n", (void*)t);
    printf("%p\n", (void*)r);
}
