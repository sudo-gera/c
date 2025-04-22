#include <memory>
#include <functional>
#include <iostream>

// auto f = [](auto& f){f();};

struct defer{
    std::function<void()> f;
    defer(std::function<void()> f):f(f){}
    ~defer(){f();}
};

// std::unique_ptr<std::function<void()>, decltype([](auto&&a){})


int main(){
    auto a = std::unique_ptr<int>(new int(20));
    // auto a = std::make_unique<int>(20);
    defer d([&](){
        std::cout << *a << std::endl;
    });
}
