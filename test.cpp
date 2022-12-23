#include <array>

constexpr auto f(){
    auto ptr=std::array<int,3>().data();
    ptr[0]=0;
    return ptr;
}

static_assert(f()!=0);

int main(){}

