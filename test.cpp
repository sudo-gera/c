#include <concepts>
#include <type_traits>


// E1
template<typename...>
struct type_list {};


// E2
template<class TypeList, typename T>
struct type_list_append;

template<typename... Ts, typename T>
struct type_list_append<type_list<Ts...>, T> {
    using type = type_list<Ts..., T>;
};


// E3
template<unsigned N, typename List>
struct state_t {
    static constexpr unsigned n = N;
    using list = List;
};


namespace {
    struct tu_tag {};           // E4
}


template<
    unsigned N,
    std::same_as<tu_tag> TUTag
>
struct reader {
    friend auto state_func(reader<N, TUTag>);
};


template<
    unsigned N,
    typename List,
    std::same_as<tu_tag> TUTag
>
struct setter {
    // E5
    friend auto state_func(reader<N, TUTag>) {
        return List{};
    }

    static constexpr state_t<N, List> state{};
};


template struct setter<0, type_list<>, tu_tag>;     // E6


// E7
template<
    std::same_as<tu_tag> TUTag,
    auto EvalTag,
    unsigned N = 0
>
[[nodiscard]]
consteval auto get_state() {
    constexpr bool counted_past_n = requires(reader<N, TUTag> r) {
        state_func(r);
    };

    if constexpr (counted_past_n) {
        return get_state<TUTag, EvalTag, N + 1>();
    }
    else {
        // E7.1
        constexpr reader<N - 1, TUTag> r;
        return state_t<N - 1, decltype(state_func(r))>{};
    }
}


// E8
template<
    std::same_as<tu_tag> TUTag = tu_tag,
    auto EvalTag = []{},
    auto State = get_state<TUTag, EvalTag>()
>
using get_list = typename std::remove_cvref_t<decltype(State)>::list;


// E9
template<
    typename T,
    std::same_as<tu_tag> TUTag,
    auto EvalTag
>
[[nodiscard]]
consteval auto append_impl() {
    using cur_state = decltype(get_state<TUTag, EvalTag>());            // E9.1
    using cur_list = typename cur_state::list;
    using new_list = typename type_list_append<cur_list, T>::type;      // E9.2
    setter<cur_state::n + 1, new_list, TUTag> s;                        // E9.3
    return s.state;                                                     // E9.4
}


// E10
template<
    typename T,
    std::same_as<tu_tag> TUTag = tu_tag,
    auto EvalTag = []{},
    auto State = append_impl<T, TUTag, EvalTag>()
>
constexpr auto append = [] { return State; };           // E10.1

// All these assertions pass.

// static_assert(std::same_as<get_list<>, type_list<>>);       // First usage in this translation unit

// auto _1 = append<int>();
// static_assert(std::same_as<get_list<>, type_list<int>>);

// auto _2 = append<float>();
// static_assert(std::same_as<get_list<>, type_list<int, float>>);

#include <any>
#include <string>
#include <tuple>
#include <iostream>
#include <functional>
#include "strtype.cpp"

#define FORWARD(val) (std::forward<decltype(val)>(val))

template<typename T, typename=decltype(append<std::decay_t<T>>())>
auto to_any(T&& value){
    return std::any(FORWARD(value));
}

void visit(std::any& a, auto&& f);

template<typename...Ts, size_t...is>
void visit_impl(std::any& a, auto&& f, type_list<Ts...>, std::index_sequence<is...> = std::make_index_sequence<0>()){
    if constexpr (sizeof...(is) != sizeof...(Ts)){
        return visit_impl(a, FORWARD(f), type_list<Ts...>(), std::make_index_sequence<sizeof...(Ts)>());
    }
    using t=std::tuple<Ts...>;
    // std::cout << strtype<t> << std::endl;
    bool done = false;
    int d[] = {
        [&](){
            // std::cout << a.type().name() << std::endl;
            // std::cout << strtype<std::tuple_element_t<is, t>> << std::endl;
            // std::cout << typeid(std::tuple_element_t<is, t>).name() << std::endl;
            if (done){
                return 0;
            }
            if (auto val = std::any_cast<std::tuple_element_t<is, t>>(&a)){
                std::invoke(FORWARD(f), *val);
                done = true;
            }
            return 0;
        }()...
    };
}

int main(){
    std::any a;
    a = to_any(0);
    visit(a, [](auto& v){std::cout<<v<<std::endl;});
    auto tmp="1";
    a = to_any(tmp);
    visit(a, [](auto& v){std::cout<<v<<std::endl;});
    a = to_any("2");
    visit(a, [](auto& v){std::cout<<v<<std::endl;});
    std::string f="3";
    const auto& g=f;
    a = to_any(g);
    visit(a, [](auto& v){std::cout<<v<<std::endl;});
}

static_assert(std::same_as<get_list<>, type_list< int, const char*, const char*, std::string >>);

void visit(std::any& a, auto&& f){
    visit_impl(a, FORWARD(f), get_list<>());
}
