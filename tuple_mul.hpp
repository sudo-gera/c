#include <tuple>

template<size_t n>
struct inc;

template<typename t1, typename t2>
using tuple_add = decltype(
    std::tuple_cat(
        std::declval<t1>(),
        std::declval<t2>()
    )
);

template<typename t1, typename t2>
struct tuple_mul2_impl;

template<typename t1, typename t2>
using tuple_mul2 = typename tuple_mul2_impl<t1,t2>::type;

template<typename...t2>
struct tuple_mul2_impl<std::tuple<>, std::tuple<t2...>>{
    using type = std::tuple<>;
};

template<typename t, typename...t1, typename...t2>
struct tuple_mul2_impl<std::tuple<t, t1...>, std::tuple<t2...>>{
    using type = tuple_add<
        std::tuple<
            std::pair<t, t2>...
        >,
        tuple_mul2<
            std::tuple<t1...>,
            std::tuple<t2...>
        >
    >;
};

static_assert(std::is_same_v<
    tuple_mul2<
        std::tuple<>,
        std::tuple<>
    >,
    std::tuple<>
>);

static_assert(std::is_same_v<
    tuple_mul2<
        std::tuple<inc<1000>>,
        std::tuple<>
    >,
    std::tuple<>
>);

static_assert(std::is_same_v<
    tuple_mul2<
        std::tuple<>,
        std::tuple<inc<3000>>
    >,
    std::tuple<>
>);

static_assert(std::is_same_v<
    tuple_mul2<
        std::tuple<inc<1000>>,
        std::tuple<inc<3000>>
    >,
    std::tuple<
        std::pair<inc<1000>, inc<3000>>
    >
>);

static_assert(std::is_same_v<
    tuple_mul2<
        std::tuple<inc<1000>, inc<1001>>,
        std::tuple<inc<3000>, inc<3001>>
    >,
    std::tuple<
        std::pair<inc<1000>, inc<3000>>,
        std::pair<inc<1000>, inc<3001>>,
        std::pair<inc<1001>, inc<3000>>,
        std::pair<inc<1001>, inc<3001>>
    >
>);

template<typename...T>
struct tuple_mul_impl;

template<typename...T>
using tuple_mul = typename tuple_mul_impl<T...>::type;

template<>
struct tuple_mul_impl<>{
    using type = std::tuple<
        std::tuple<>
    >;
};

template<typename t>
struct tuple_mul_fix_impl;

template<typename t>
using tuple_mul_fix = typename tuple_mul_fix_impl<t>::type;

template<typename...t1, typename...t2>
struct tuple_mul_fix_impl<std::tuple<std::pair<t1, t2>...>>{
    using type = std::tuple<
        tuple_add<
            std::tuple<t1>,
            t2
        >...
    >;
};

template<typename t1, typename...t2>
struct tuple_mul_impl<t1, t2...>{
    using type = tuple_mul_fix<
        tuple_mul2<
            t1,
            tuple_mul<t2...>
        >
    >;
};

static_assert(std::is_same_v<
    tuple_mul<
        std::tuple<>,
        std::tuple<>
    >,
    std::tuple<>
>);

static_assert(std::is_same_v<
    tuple_mul<
        std::tuple<inc<3000>>,
        std::tuple<inc<1000>>
    >,
    std::tuple<
        std::tuple<inc<3000>, inc<1000>>
    >
>);

static_assert(std::is_same_v<
    tuple_mul<
        std::tuple<inc<1000>, inc<1001>, inc<1002>>,
        std::tuple<inc<3000>, inc<3001>, inc<3002>>,
        std::tuple<inc<2000>,  inc<2001>,  inc<2002> >
    >,
    std::tuple<
        std::tuple<inc<1000>, inc<3000>, inc<2000>>,
        std::tuple<inc<1000>, inc<3000>, inc<2001>>,
        std::tuple<inc<1000>, inc<3000>, inc<2002>>,
        std::tuple<inc<1000>, inc<3001>, inc<2000>>,
        std::tuple<inc<1000>, inc<3001>, inc<2001>>,
        std::tuple<inc<1000>, inc<3001>, inc<2002>>,
        std::tuple<inc<1000>, inc<3002>, inc<2000>>,
        std::tuple<inc<1000>, inc<3002>, inc<2001>>,
        std::tuple<inc<1000>, inc<3002>, inc<2002>>,

        std::tuple<inc<1001>, inc<3000>, inc<2000>>,
        std::tuple<inc<1001>, inc<3000>, inc<2001>>,
        std::tuple<inc<1001>, inc<3000>, inc<2002>>,
        std::tuple<inc<1001>, inc<3001>, inc<2000>>,
        std::tuple<inc<1001>, inc<3001>, inc<2001>>,
        std::tuple<inc<1001>, inc<3001>, inc<2002>>,
        std::tuple<inc<1001>, inc<3002>, inc<2000>>,
        std::tuple<inc<1001>, inc<3002>, inc<2001>>,
        std::tuple<inc<1001>, inc<3002>, inc<2002>>,

        std::tuple<inc<1002>, inc<3000>, inc<2000>>,
        std::tuple<inc<1002>, inc<3000>, inc<2001>>,
        std::tuple<inc<1002>, inc<3000>, inc<2002>>,
        std::tuple<inc<1002>, inc<3001>, inc<2000>>,
        std::tuple<inc<1002>, inc<3001>, inc<2001>>,
        std::tuple<inc<1002>, inc<3001>, inc<2002>>,
        std::tuple<inc<1002>, inc<3002>, inc<2000>>,
        std::tuple<inc<1002>, inc<3002>, inc<2001>>,
        std::tuple<inc<1002>, inc<3002>, inc<2002>>
    >
>);

template<typename t, size_t...idx>
auto tuple_pow_impl_f(std::index_sequence<idx...>){
    return std::declval<
        tuple_mul<
            std::enable_if_t<!(idx*0), t>...
        >*
    >();
}

template<typename t, size_t n>
using tuple_pow = std::decay_t<
    decltype(
        *tuple_pow_impl_f<t>(
            std::make_index_sequence<n>()
        )
    )
>;

static_assert(std::is_same_v<
    tuple_pow<
        std::tuple<inc<1000>, inc<3000>>,
        3
    >,
    std::tuple<
        std::tuple<inc<1000>, inc<1000>, inc<1000>>,
        std::tuple<inc<1000>, inc<1000>, inc<3000>>,
        std::tuple<inc<1000>, inc<3000>, inc<1000>>,
        std::tuple<inc<1000>, inc<3000>, inc<3000>>,

        std::tuple<inc<3000>, inc<1000>, inc<1000>>,
        std::tuple<inc<3000>, inc<1000>, inc<3000>>,
        std::tuple<inc<3000>, inc<3000>, inc<1000>>,
        std::tuple<inc<3000>, inc<3000>, inc<3000>>
    >
>);

