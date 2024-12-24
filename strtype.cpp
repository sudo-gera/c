#include <cstdio>
#include <tuple>
#include <array>

namespace type_to_name_impl{

    template<typename T>
    consteval auto pret_func(){
        return std::make_pair(sizeof(__PRETTY_FUNCTION__) - 5, __PRETTY_FUNCTION__);
    }

    template<typename T>
    auto result = []()consteval{
        std::array<char, pret_func<T>().first - pret_func<int>().first + 4> data;
        const char* ptr = pret_func<T>().second + pret_func<int>().first;
        for (size_t c = 0; c < data.size(); ++c){data[c] = ptr[c];}
        data.back() = 0;
        return data;
    }();

};

template<typename T>
const char* type_to_name = type_to_name_impl::result<T>.data();

int main(){
    printf("%s\n",type_to_name<void>);
    printf("%s\n",type_to_name<int>);
    printf("%s\n",type_to_name<char>);
    printf("%s\n",type_to_name<std::tuple<int>>);
}
