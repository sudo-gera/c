#include <any>
#include <string>
#include <tuple>
#include <functional>
#include <array>
#include <vector>
#include <iostream>
#include <string>

#define FORWARD(val) (std::forward<decltype(val)>(val))

template<typename T>
struct hash;

template<typename T>
concept std_hashable = (
    requires(T val){
        static_cast<size_t>(
            std::hash<T>()(FORWARD(val))
        );
    }
);

template<typename T>
requires(std_hashable<T>)
size_t hash_00(const T&val){
    return std::hash<T>()(val);
}

size_t hash_01(const char* val){
    return std::hash<std::string_view>()(val);
}

template<typename T>
concept for_hashable = (
    requires(T val){
        val.end() != (++val.begin());
        hash<decltype(*val.begin())>()(*val.begin());
    }
);

template<typename T>
requires(for_hashable<std::decay_t<T>>)
size_t hash_02(const T&val){
    size_t res = 0;
    for (auto&&v:val){
        res ^= hash<decltype(v)>()(v);
    }
    return res;
}

template<typename T>
concept tuple_hashable = (
    requires{
        std::tuple_size<T>::value;
    }
);

template<size_t...idx>
size_t get_hash_03(auto&&val, std::index_sequence<idx...>){
    return (
        hash<
            std::tuple_element_t<
                idx,
                std::decay_t<decltype(val)>
            >
        >()(
            std::get<
                idx
            >(
                FORWARD(val)
            )
        ) ^ ... ^ 0
    );
}

template<typename T>
requires(tuple_hashable<std::decay_t<T>>)
size_t hash_03(const T& val){
    return get_hash_03(
        val,
        std::make_index_sequence<
            std::tuple_size_v<T>
        >()
    );
}

template<typename T>
struct hash{
    size_t operator()(const T&val)const{
        if constexpr(requires{hash_00(val);}){
            return hash_00(val);
        }
        if constexpr(requires{hash_01(val);}){
            return hash_01(val);
        }
        if constexpr(requires{hash_02(val);}){
            return hash_02(val);
        }
        if constexpr(requires{hash_03(val);}){
            return hash_03(val);
        }
        // if constexpr(requires{hash_04(val);}){
        //     return hash_04(val);
        // }
    }
};

template<typename T>
size_t h(T&&val){
    return hash<T>()(FORWARD(val));
}

#if defined(__INCLUDE_LEVEL__) and __INCLUDE_LEVEL__ == 0
int main(){
    h(0);
    int t=0;
    h(t);
    h("");
    h(true);
    h(std::string());
    h(std::vector<int>());
    h(std::vector<std::vector<int>>());
    h(std::tuple<int, char>());
    h(std::tuple<>());
    h(std::array<int, 2>());
    h(std::array<int, 1>());
    h(std::array<int, 0>());
    std::cout << hash<int>()(9) << std::endl;
    std::cout << hash<std::vector<int>>()({9}) << std::endl;
    std::cout << hash<std::tuple<int>>()({9}) << std::endl;
    std::cout << hash<std::tuple<int, int>>()({7, 8}) << std::endl;
}
#endif