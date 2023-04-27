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
        Y val;
        cin >> val;
        return val;
    }
    template <typename Y = T>
    operator Y() {  // NOLINT
        Y val;
        cin >> val;
        return val;
    }
};

///////////////////////////////////////////////////end of lib

pair<ssize_t, ssize_t> Egcd(ssize_t a, ssize_t b) {
    if (b) {
        auto [c, d] = Egcd(b, a % b);
        return {d, c - a / b * d};
    }
    return {(a > 0) - (a < 0), 0};
}

struct Mod {
    ssize_t a = 0;
};

auto operator%(ssize_t a, Mod) {
    return Mod{a};
}

auto operator%(Mod a, ssize_t b) {
    return (a.a % b + b) % b;
}

auto mod = Mod();

int main() {
    ssize_t a = Scan();
    ssize_t b = Scan();
    ssize_t c = Scan();
    ssize_t d = Scan();
    ssize_t e = ((a * d + b * c) % mod % 1'000'000'007 * Egcd(b * d, 1'000'000'007).first) % mod % 1'000'000'007;
    assert((a * d + b * c - b * d % mod % 1'000'000'007 * e) % mod % 1'000'000'007 == 0);
    cout << e << endl;
}
