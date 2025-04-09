<<<<<<< HEAD
#include <stdio.h>

int main() {
    puts("hello world");
    [[gnu::assume(1.0000000000000001 > 1)]];
}
=======
#include <iostream>

auto f(auto a){
    return 1-a;
}

int main(){
<<<<<<< HEAD
    static_assert(requires{f("");});
}
=======
    int e = 0;
    defer a([&](){std::cout<<"123";});
    return e;
}
>>>>>>> 4c6b4fa7740a2b1a76fa11841a62e32d55433e2b
>>>>>>> c218422038c5dcd63768f5b421dd6406803a2f3d
