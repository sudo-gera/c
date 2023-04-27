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

#define none 9000000000000000000

template <typename T = void>
struct Scan {
    template <typename Y = T>
    auto operator()() {
        Y val;
        cin >> val;
        return val;
    }
    template <typename Y = T>
    operator Y() { // NOLINT
        Y val;
        cin >> val;
        return val;
    }
};

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

///////////////////////////////////////////////////end of lib

size_t Gcd(size_t a, size_t b) {
    return b ? Gcd(b, a % b) : a;
}

int main() {
    size_t n = Scan();
    vector<size_t> a(n);
    generate_n(a.begin(), n, Scan<size_t>());
    size_t not1count = 0;
    for (size_t q = 0; q < n; ++q) {
        not1count += (a[q] != 1);
    }
    if (not1count != n) {
        cout << not1count << endl;
        return 0;
    }
    size_t se = 0;
    size_t minlen = none;
    while (se < n) {
        size_t cgcd = a[se];
        for (; se < n; ++se) {
            cgcd = Gcd(cgcd, a[se]);
            if (cgcd == 1) {
                break;
            }
        }
        if (cgcd == 1) {
            cgcd = a[se];
            size_t sb = se;
            for (; sb != -1LLU; --sb) {
                cgcd = Gcd(cgcd, a[sb]);
                if (cgcd == 1) {
                    break;
                }
            }
            minlen = min(minlen, se - sb + 1);
        }
    }
    if (minlen == none) {
        cout << -1 << endl;
    } else {
        cout << not1count + minlen - 2 << endl;
    }
}
