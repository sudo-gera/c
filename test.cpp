#include <iostream>

#include <functional>

struct defer:std::function<void()>{
    defer(auto&&...args):std::function<void()>(std::forward<decltype(args)>(args)...){}
    ~defer(){(*this)();}
};

int main(){
    int e = 0;
    defer a([&](){std::cout<<"123";});
    return e;
}