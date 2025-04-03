<<<<<<< HEAD
#include <stdio.h>

int main() {
    puts("hello world");
    [[gnu::assume(1.0000000000000001 > 1)]];
}
=======
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
>>>>>>> 4c6b4fa7740a2b1a76fa11841a62e32d55433e2b
