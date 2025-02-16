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
    // std::cout << strtype<T> << std::endl;
    // std::cout << strtype<decltype(get_list<>())> << std::endl;
    return std::any(FORWARD(value));
}

auto _debug_0 = append<void>();
auto _debug_1 = append<std::any>();
auto _debug_2 = append<decltype(_debug_0)>();
auto _debug_3 = append<decltype(_debug_1)>();

void visit(auto&& f, std::any& a);

template<typename T>
struct deref_ptr_impl;

template<typename T>
struct deref_ptr_impl<T*>{
    using type = T;
};

template<typename T>
using deref_ptr = typename deref_ptr_impl<T>::type;

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
                if constexpr (requires(decltype(f) f, decltype(*val) val){FORWARD(f)(FORWARD(val));}){
                    FORWARD(f)(FORWARD(*val));
                    done = true;
                }else{
                    std::string error_message;
                    error_message += "Cannot apply '";
                    error_message += strtype<decltype(f)>;
                    error_message += "' to '";
                    error_message += strtype<deref_ptr<decltype(val)>>;
                    error_message += "'.";
                    throw std::runtime_error{error_message};
                }
            }
            return 0;
        }()...
    };
    if (not done){
        std::string error_message;
        error_message += "visit failed: type $(c++filt -t '";
        error_message += a.type().name();
        error_message += "') not found in list '";
        error_message += strtype<t>;
        error_message += "'.";
        throw std::runtime_error{error_message};
    }
}

struct any{
    std::any value;
    any() = default;
    template<typename T>
    any(T&& val){
        value = to_any(FORWARD(val));
    }
    template<typename T>
    auto& operator=(T&&val){
        value = to_any(FORWARD(val));
        return *this;
    }
    operator std::any(){
        return value;
    }
    operator std::any&(){
        return value;
    }
    operator std::any&&(){
        return std::move(value);
    }
};

#define END_OF_CODE                               \
void visit(auto&& f, std::any& a){                \
    visit_impl(a, FORWARD(f), get_list<>());      \
}                                                 \

#define ONE_LINE_LAMBDA(...) ->decltype(auto)requires(requires{__VA_ARGS__;}){return __VA_ARGS__;}

#define AS_LAMBDA(...) [&](auto&&...args)ONE_LINE_LAMBDA((__VA_ARGS__)(FORWARD(args)...))

#define VISIT(f, a) (visit(AS_LAMBDA((f)), (a)))

#define REF_PARTIAL(f, ...) ([&](auto&&...args)ONE_LINE_LAMBDA(f(__VA_ARGS__ __VA_OPT__(,) FORWARD((args))...)))

any nv_visit(auto&& f, any& arg){
    any res_;
    visit([&](auto&& val)requires(requires{f(FORWARD(val));}){res_ = to_any(f(FORWARD(val)));}, FORWARD(arg));
    return res_;
}

#define NV_VISIT(f, a) (nv_visit([&](auto&& val)ONE_LINE_LAMBDA(f(FORWARD(val))), (a)))

#if defined(__INCLUDE_LEVEL__) and __INCLUDE_LEVEL__ == 0

auto print = [](auto&& val)requires(
    requires{
        std::cout << FORWARD(val) << std::endl;
    }
){
    std::cout << FORWARD(val) << std::endl;
};

int main(){
    any a;
    a = 0;
    visit(print, a);
    auto tmp="1";
    a = tmp;
    visit(print, a);
    a = "2";
    visit(print, a);
    std::string f="3";
    const auto& g=f;
    a = g;
    visit(print, a);
    a = print;
    try{
        visit(print, a);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
}

END_OF_CODE

#endif