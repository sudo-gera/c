#include <cassert>
#include <iostream>
#include <string>
template <typename T>
std::string strtype() {
    std::string a=__PRETTY_FUNCTION__;
    #ifdef __clang__
        assert(a.size() >= 28);
        return std::string(a.begin()+27,a.end()-1);
    #else
        assert(a.size() >= 32);
        a = std::string(a.begin() + 32, a.end());
        for (size_t i = 0; i < a.size(); ++i){
            if (a[i] == ';'){
                a = std::string(a.begin(), a.begin() + i);
                return a;
            }
        }
        assert(false);
    #endif
}

int main(){
    std::cout << strtype<std::string>() << std::endl;
    std::cout << strtype<int>() << std::endl;
    std::cout << strtype<void>() << std::endl;
    std::cout << strtype<void*>() << std::endl;
    std::cout << strtype<decltype(main)>() << std::endl;
}
