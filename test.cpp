
#include <vector>
#include <iostream>


template<size_t n>
using f=int;

struct leak{
    leak(){
        std::cout << "constructor" << std::endl;
    }
    ~leak(){
        std::cout << "destructor" << std::endl;
    }
    std::vector<leak> a;
    using f=constant_value<int, sizeof(leak)>;
};

int main(){
    std::vector<leak> a(1);
    a[0].a = std::move(a);
}
