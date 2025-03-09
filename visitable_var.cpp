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

std::unordered_map<
    std::type_index,
    const char*
> type_names;

struct var{
private:
    template<typename T, typename=decltype(append<std::decay_t<T>>())>
    auto append(){
        type_names[typeid(std::decay_t<T>)] = strtype<std::decay_t<T>>;
    }
public:
    const char* type_name()const{
        auto name_i = type_names.find(value.type());
        if (name_i != type_names.end()){
            return name_i->second;
        }
        return value.type().name();
    }
    std::any value;
    var() = default;
    // template<typename T>
    // var(T&& val){
    //     *this = FORWARD(val);
    // }
    template<typename T>
    requires(not std::is_same_v<std::decay_t<T>, var>)
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

namespace visit_implementation{


    template<typename...C>
    struct w{
        template<typename F, typename...A>
        static var work(F&&f, A&&...a){
            static_assert(sizeof...(a) == sizeof...(C));
            if constexpr (requires(F&& f, C&...c){FORWARD(f)(FORWARD(c)...);}){
                if constexpr (
                    std::is_void_v<
                        std::decay_t<
                            decltype(
                                FORWARD(f)(
                                    *std::any_cast<C>(&a.value)...
                                )
                            )
                        >
                    >
                ){
                    FORWARD(f)(
                        *std::any_cast<C>(&a.value)...
                    );
                    return {};
                }else{
                    return FORWARD(f)(
                        *std::any_cast<C>(&a.value)...
                    );
                }
            }else{
                std::string message;
                ([&](auto&s){
                    message += s.type_name();
                    message += "', '";
                }(a),...);
                if (not message.empty()){
                    message.pop_back();
                    message.pop_back();
                    message.pop_back();
                    message.pop_back();
                }
                message = 
                    std::string() +
                    "Cannot apply '" +
                    strtype<F&&> +
                    "' to argument list [" + message + "].";
                throw std::runtime_error{message};
            }
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
        using map_key = std::array<
            std::type_index,
            sizeof...(A)
        >;
        auto&& func_i = m.find(
            map_key{
                std::type_index(
                    args.value.type()
                )...
            }
        );
        if (func_i == m.end()){
            size_t i = 0;
            std::string message;
            (void)([&](auto&& arg){
                if (not arg.value.has_value()){
                    message += std::to_string(i);
                    message += ", ";
                }
                return ++i;
            }(args)|...|0);
            if (not message.empty()){
                message.pop_back();
                message.pop_back();
                message = "Several arguments (" + message + ") have no value.";
                throw std::runtime_error(message);
            }
            message = "";
            (void)([&](auto&& arg){
                message += arg.type_name();
                message += "', '";
                return 0;
            }(args)|...|0);
            if (not message.empty()){
                message.pop_back();
                message.pop_back();
                message.pop_back();
                message.pop_back();
            }
            message = "Cannot process types ['" + message + "'] with " + strtype<decltype(tl)> + ".";
            throw std::runtime_error(message);
        }
        return func_i->second(FORWARD(f), FORWARD(args)...);
    }
};

var visit(auto&&f, auto&&...args);
#define END_OF_CODE var visit(auto&&f, auto&&...args){return visit_implementation::visit_impl(get_list<>(), FORWARD(f), FORWARD(args)...);}

#if defined(__INCLUDE_LEVEL__) and __INCLUDE_LEVEL__ == 0

auto print = [](auto&&...a)
requires(requires{((std::cout << a, 0) + ... + 0);})
{
    (void)((std::cout << a << " ", 0)|...|0);
    std::cout << std::endl;
};

int main(){
   var a;
   a = std::vector<int>();
   visit(print, a);
}

END_OF_CODE

static_assert(std::is_same_v<
    get_list<>,
    type_list<>
>);

#endif
