#include <bits/stdc++.h>

// #include <assert.h>
// #include <tuple>
// #define FORWARD(val) (std::forward<decltype(val)>(val))

// template<std::size_t b, std::size_t e>
// void make_constexpr(std::size_t n, auto&&f){
//     static_assert(b <= e);
//     assert(b <= n);
//     assert(n <= e);
//     assert(b < e); // this edge case is sometimes helpful
//     if constexpr(b + 1 == e){
//         return FORWARD(f)(std::integral_constant<std::size_t, b>());
//     }
//     std::integral_constant<size_t, (b + e) / 2> c;
//     if (n < c){
//         return make_constexpr<b, c>(n, FORWARD(f));
//     }else{
//         return make_constexpr<c, e>(n, FORWARD(f));
//     }
// }




// #define MAX_MUTEX 10

// template<typename iter_t, size_t locks_to_process, size_t locks_count>
// struct aaa{
//     void work(iter_t* begin, iter_t* end, ){
//         if constexpr(locks_to_process == 0){

//         }
//     }
// }




// template<typename iter_t>
// void lock(iter_t begin, iter_t end){
//     using mutex_type = std::remove_reference_t<decltype(*begin)>;
//     std::array<std::unique_lock<mutex_type>, MAX_MUTEX> locks_;
    
//     size_t mutex_count = 0;

//     for (; begin != end; ++begin){
//         locks_[mutex_count++] = std::unique_lock<mutex_type>(*begin);
//     }

//     make_constexpr<0, MAX_MUTEX>(mutex_count, [&](auto mutex_count){
//         std::array<std::unique_lock<mutex_type>, mutex_count> locks;

//         for (size_t i = 0; i < mutex_count; ++i){
//             locks[i] = std::move(locks[i]);
//         }

//         std::apply(
//             [&](auto&&args){
//                 return std::lock(FORWARD(args));
//             },
//             std::tuple_cat(locks)
//         );
//     });
// }

// int main(){
//     std::deque<std::mutex> a(7);
//     lock(a.begin(), a.end());
// }

template<typename tuple_1, typename tuple_2>
using tuple_cat = decltype(
    std::tuple_cat(
        std::declval<tuple_1>(),
        std::declval<tuple_2>()
    )
);

template<size_t start, size_t len>
struct make_tuple_of_integral_constants_impl{
    using type = tuple_cat<
        make_tuple_of_integral_constants_impl<start + len
    >;
};

