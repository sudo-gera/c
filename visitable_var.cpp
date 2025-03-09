#include "tuple_mul.hpp"
#include "strtype.cpp"
#include "make_constexpr.cpp"
#include "hash.cpp"
#include "type_list.hpp"
#include <any>
#include <string>
#include <tuple>
#include <functional>
#include <array>
#include <vector>
#include <iostream>
#include <string>
#include <cassert>
#include <typeindex>
#include <unordered_map>

#define FORWARD(val) (std::forward<decltype(val)>(val))

#define ONE_LINE_LAMBDA(...) ->decltype(auto)requires(requires{__VA_ARGS__;}){return __VA_ARGS__;}

#define AS_LAMBDA(...) [&](auto&&...args)ONE_LINE_LAMBDA((__VA_ARGS__)(FORWARD(args)...))

#define VISIT(f, a) (visit(AS_LAMBDA((f)), (a)))

#define REF_PARTIAL(f, ...) ([&](auto&&...args)ONE_LINE_LAMBDA(f(__VA_ARGS__ __VA_OPT__(,) FORWARD((args))...)))


struct var{
private:
    template<typename T, typename=decltype(append<std::decay_t<T>>())>
    auto append(){}
public:
    std::any value;
    var() = default;
    template<typename T>
    var(T&& val):
        value(FORWARD(val))
    {
        append<T>();
    }
    template<typename T>
    auto& operator=(T&&val){
        value = FORWARD(val);
        append<T>();
        return *this;
    }
    var(const var&) = default;
    var(var&&) = default;
    var& operator=(const var&) = default;
    var& operator=(var&&) = default;
};

template<size_t b, size_t e>
decltype(auto) make_const(size_t n, auto&&f){
    static_assert(b < e);
    assert(b <= n);
    assert(n < e);
    if constexpr(b + 1 == e){
        assert(n == b);
        return std::invoke(FORWARD(f), std::integral_constant<size_t, b>());
    }else{
        constexpr size_t c = (b+e)/2;
        if (n < c){
            return make_const<b, c>(n, FORWARD(f));
        }else{
            return make_const<c, e>(n, FORWARD(f));
        }
    }
}

namespace visit_implementation{


    template<typename...C>
    struct w{
        template<typename F, typename...A>
        static var work(F&&f, A&&...a){
            static_assert(sizeof...(a) == sizeof...(C));
            (std::cout << ... << strtype<C>);
            std::cout << std::endl;
            (std::cout << ... << a.value.type().name()) << std::endl;
            (std::cout << ... << std::any_cast<C*>(&a.value)) << std::endl;
            return FORWARD(f)(
                *std::any_cast<C*>(&a.value)...
            );
        }
    };

    template<typename F, typename...A, typename...T, typename...tt, size_t...TTidx, size_t...Aidx>
    auto& get_map(
        type_list<T...>,
        type_list<std::tuple<tt...>>,
        std::index_sequence<TTidx...>,
        std::index_sequence<Aidx...>
    ){
        using tt_tuple = std::tuple<tt...>;
        using map_key = std::array<
            std::type_index,
            sizeof...(A)
        >;
        using map_val = var(*)(F&&, A&&...);
        auto get_map_pair = [&]<size_t TTid>(std::integral_constant<size_t, TTid>){
            return std::pair<map_key, map_val>{
                map_key{
                    std::type_index(
                        typeid(
                            std::tuple_element_t<Aidx,
                                std::tuple_element_t<TTid, tt_tuple>
                            >
                        )
                    )...
                },
                map_val{
                    static_cast<var(*)(F&&, A&&...)>(
                        w<
                            std::tuple_element_t<Aidx,
                                std::tuple_element_t<TTid, tt_tuple>
                            >...
                        >::template work<
                            F,
                            A...
                        >
                    )
                },
            };
        };
        static std::unordered_map<
            map_key,
            map_val,
            hash<map_key>
        > data = {
            std::pair<map_key, map_val>{
                get_map_pair(std::integral_constant<size_t, TTidx>())
            }...
        };
        return data;
    }

    template<typename F, typename...A, typename...T>
    var visit_impl(type_list<T...> tl, F&& f, A&&...args){
        auto& m = get_map<F,A...>(
            tl,
            type_list<
                tuple_pow<
                    std::tuple<T...>,
                    sizeof...(A)
                >
            >(),
            std::make_index_sequence<
                std::tuple_size_v<
                    tuple_pow<
                        std::tuple<T...>,
                        sizeof...(A)
                    >
                >
            >(),
            std::make_index_sequence<
                sizeof...(args)
            >()
        );
        var arg;
        using map_key = std::array<
            std::type_index,
            sizeof...(A)
        >;
        return m[
            map_key{
                std::type_index(
                    args.value.type()
                )...
            }
        ](FORWARD(f), FORWARD(args)...);
    }
};

var visit_i2(auto&&f, auto&&args, auto tl){
    return visit_implementation::visit_impl(tl, FORWARD(f), FORWARD(args));
}

var visit_i1(auto&&...a);
#define END_OF_CODE var visit_i1(auto&&...a){return visit_i2(FORWARD(a)..., get_list<>());}

var visit(auto&&f, auto&&args){
    return visit_i1(FORWARD(f), FORWARD(args));
}

#if defined(__INCLUDE_LEVEL__) and __INCLUDE_LEVEL__ == 0

auto print = [](auto&&...a)
requires(requires{((std::cout << a, 0) + ... + 0);})
{
    (std::cout << ... << a);
    return 0;
};

int main(){
    var a;
    a = 0;
    visit(print, a);
    // auto tmp="1";
    // a = tmp;
    // // visit(print, a);
    // a = "2";
    // // visit(print, a);
    // std::string f="3";
    // const auto& g=f;
    // a = g;
    // visit(print, a);
    // a = print;
    // try{
    //     visit(print, a);
    // }catch(std::exception& e){
    //     std::cout << e.what() << std::endl;
    // }
}

END_OF_CODE

#endif
