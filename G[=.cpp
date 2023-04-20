#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#ifndef assert
#include <cassert>
#endif
#include <tuple>
#include <numeric>
#include <list>
#include <string_view>
#include <cstring>
#include <functional>
#include <type_traits>
#include <deque>
#include <array>
#include <queue>
#include <stack>
#include <random>
#include <string_view>
#include <memory>
using std::back_inserter, std::list, std::hash, std::reverse, std::queue;
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::copy_if, std::exit, std::enable_if, std::enable_if, std::stack;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n, std::deque;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::string_view, std::random_device, std::mt19937, std::mt19937_64;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::tuple_element, std::tuple_size, std::is_same, std::forward;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::uniform_int_distribution, std::make_unique, std::make_shared;
using std::unique, std::decay_t, std::is_convertible_v, std::array;
using std::unique_ptr, std::shared_ptr;

template <typename T = void>
struct Scan {
    template <typename Y = T>
    auto operator()() {
        // Y val;
        // cin >> val;
        // return val;
        return *this;
    }
    template <typename Y = T>
    operator Y() {  // NOLINT
        Y val;
        cin >> val;
        return val;
    }
};

auto scan = Scan();

struct Mod {
    __int128_t a = 0;
};

auto operator%(__int128_t a, Mod) {
    return Mod{a};
}

auto operator%(Mod a, __int128_t b) {
    return (a.a % b + b) % b;
}

auto mod = Mod();

template <typename T>
auto ScanVector(T& x) {
    generate_n(x.begin(), x.size(), scan);
}

///////////////////////////////////////////////////end of lib

__int128_t Fib(__int128_t n, __int128_t m) {
    __int128_t t = 0;
    __int128_t f0 = 0;
    __int128_t f1 = 0;
    t = 1;
    while (t < n) {
        t <<= 1;
    }
    f0 = 0;
    f1 = 1;
    while (t > 1) {
        if (n & t) {
            f1 += f0;
            f0 = f1 - f0;
        }
        tie(f0, f1) = make_tuple(f1 * f0 * 2 - f0 * f0, f0 * f0 + f1 * f1);
        if (m) {
            f0 = f0 % mod % m;
            f1 = f1 % mod % m;
        }
        t >>= 1;
    }
    return n % 2 ? f1 : f0;
}

int main() {
    size_t n = scan;
    size_t q = scan;
    vector<ssize_t> x(n);
    vector<ssize_t> y(n);
    vector<size_t> k(n);
    vector<ssize_t> c(q);
    for (size_t q = 0; q < n; ++q) {
        x[q] = scan;
        y[q] = scan;
        k[q] = scan;
    }
    ScanVector(c);
    for (size_t w = 0; w < q; ++w) {
        __int128_t full_ans = 0;
        for (size_t e = 0; e < n; ++e) {
            if (y[e] - x[e] - c[w] < 0) {
                continue;
            }
            __int128_t ans = Fib(y[e] - x[e] - c[w] + 1, 1'000'000'009);
            full_ans += ans * k[e] % 1'000'000'009;
        }
        cout << static_cast<size_t>(full_ans % 1'000'000'009) << endl;
    }
}
