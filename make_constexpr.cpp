#include <assert.h>
#include <tuple>
#define FORWARD(val) (std::forward<decltype(val)>(val))

namespace make_constexpr_imps{

template<typename I, typename F, typename R>
struct type_container{

    template<I begin, I len>
    struct invoke_with_constexpr_value{
        static constexpr R work(F&& f, I val) {
            return
            (val < (begin + len / 2)) ?
                invoke_with_constexpr_value<begin, len / 2>::work(FORWARD(f), val)
            :
                invoke_with_constexpr_value<begin + len / 2, len - len/2>::work(FORWARD(f), val);
        }
    };

    template<I begin>
    struct invoke_with_constexpr_value<begin, static_cast<I>(1)>{
        static constexpr R work(F&& f, I) {
            return (R)FORWARD(f)( std::integral_constant<I, begin>() );
        }
    };

    template<I begin>
    struct invoke_with_constexpr_value<begin, static_cast<I>(0)>{
        static constexpr R work(F&& f, I) {
            return (R)FORWARD(f)( std::integral_constant<I, begin>() );
        }
    };

};

};

template<typename R, typename T, T b, T e, typename F>
constexpr R make_constexpr(T n, F&&f){
    static_assert(b <= e, "");
    using container = typename make_constexpr_imps::type_container<T, F, R>;
    using invoker = typename container::template invoke_with_constexpr_value<b, e-b>;
    return (
        assert(b < e), // checking this only at runtime sometimes is useful
        assert(b <= n),
        assert(n <= e),
        invoker::work(FORWARD(f), n)
    );
}

#if __INCLUDE_LEVEL__ == 0
#include <cstdio>

#ifndef TREAP_STD_VER
#if __cplusplus <= 201103L
#define TREAP_STD_VER 11
#elif __cplusplus <= 201402L
#define TREAP_STD_VER 14
#elif __cplusplus <= 201703L
#define TREAP_STD_VER 17
#elif __cplusplus <= 202002L
#define TREAP_STD_VER 20
#else
#define TREAP_STD_VER 23
#endif
#endif // TREAP_STD_VER

#if TREAP_STD_VER > 11
struct adder{
    long long int& result;
    template<typename T>
    constexpr long long int operator()(T n) const {
        return result += (std::integral_constant<long long int, n>());
    }
};
#endif

struct printer{
    template<typename T>
    constexpr long long int operator()(T n) const {
        return printf("%lld\n",(long long int)(std::integral_constant<long long int, n>()));
    }
};

#if TREAP_STD_VER > 11

constexpr bool works(){
    long long int result = 0;
    for (long long int n = -99; n < 100; ++n){
        make_constexpr<void, decltype(n),-99, 100>(n, adder{result});
    }
    assert(result == 0);
    for (long long int n = 0; n < 10; ++n){
        make_constexpr<void, decltype(n),-99, 100>(n, adder{result});
    }
    assert(result == 45);
    return true;
}

static_assert(works(), "");

#endif

constexpr bool print(){
    return make_constexpr<int, long long int, -9, 10>(1, printer{});
}

int main(){
#if TREAP_STD_VER > 11
    assert(works());
#endif
    printf("%i\n", print());
}

#endif
