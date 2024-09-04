
#include <vector>
#include <iostream>

struct leak{
    leak(){
        std::cout << "constructor" << std::endl;
    }
    ~leak(){
        std::cout << "destructor" << std::endl;
    }
    std::vector<leak> a;
};

int main(){
    std::vector<leak> a(1);
    a[0].a = std::move(a);
}
