#include <bits/stdc++.h>
using namespace std;

template<typename FIRST,typename SECOND>
struct union_pair{
    union underlying{
        constexpr underlying(){}
        constexpr underlying(integral_constant<size_t,1>,auto&&...args):
            first(std::forward<decltype(args)>(args)...){}
        constexpr underlying(integral_constant<size_t,2>,auto&&...args):
            second(std::forward<decltype(args)>(args)...){}
        FIRST first;
        SECOND second;
        constexpr ~underlying(){}
    } value;
    constexpr void _01(auto&&...args){
        value = underlying(integral_constant<size_t,1>());
        // value.~underlying();
        // construct_at(&value, FIRST(std::forward<decltype(args)>(args)...) );
        // construct_at(&value,integral_constant<size_t,1>(),FIRST(std::forward<decltype(args)>(args)...));
        // new (&value)underlying(integral_constant<size_t,1>(),FIRST(std::forward<decltype(args)>(args)...));
        // value=underlying{.first=FIRST(std::forward<decltype(args)>(args)...)};
    }
    constexpr void _02(auto&&...args){
        value=underlying{.second=SECOND(std::forward<decltype(args)>(args)...)};
    }
    constexpr void _10(){
        value.first.~FIRST();
    }
    constexpr void _20(){
        value.second.~SECOND();
    }
    constexpr void _12(auto&&...args){
        _10();
        _02(std::forward<decltype(args)>(args)...);
    }
};

template<size_t n>
struct item{
    tuple_element_t<n-1, tuple<size_t, char*> > value;
    constexpr item(){}
    constexpr ~item(){}
};

constexpr bool test(bool k){
    if (k){
        return true;
    }
    // optional<item<1>> p;
    // union_pair<item<1>,item<2>> p;
    // p._01();
    // auto first = p.value.first;
    // auto second = p.value.second;
    return true;
}

static_assert(test(0));

int main(){}

