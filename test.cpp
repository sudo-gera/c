#include <iostream>

auto f(auto a){
    return 1-a;
}

int main(){
    static_assert(requires{f("");});
}