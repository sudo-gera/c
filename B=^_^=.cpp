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
using std::back_inserter, std::list, std::hash, std::reverse;
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::copy_if, std::exit, std::enable_if, std::enable_if;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::tuple_element, std::tuple_size, std::is_same, std::forward;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::unique, std::decay_t, std::is_convertible_v;

static inline int64_t GetInt() {
    int sign = 1;
    int c = 0;
    size_t res = 0;
    while (c = getchar_unlocked(), isspace(c)) {
    }
    if (c == '-') {
        sign = -1;
    } else {
        res = c - '0';
    }
    while (c = getchar_unlocked(), isdigit(c)) {
        res *= 10;
        res += c - '0';
    }
    return static_cast<int64_t>(res) * sign;
}

template <typename T>
ssize_t Len(T&& q) {
    return static_cast<ssize_t>(q.size());
}

///////////////////////////////////////////////////end of lib

int main() {
    ssize_t n = GetInt();
    vector<int> p(n);
    generate_n(p.begin(), n, GetInt);
    string s = "a";
    for (ssize_t q = 1; q < n; ++q) {
        if (p[q]) {
            s += s[p[q] - 1];
        } else {
            for (s += "a";; ++s.back()) {
                ssize_t k = p[q - 1];
                while (k > 0 and s[q] != s[k]) {
                    k = p[k - 1];
                }
                if (s[q] == s[k]) {
                    k++;
                }
                if (p[q] == k) {
                    break;
                }
            }
        }
    }
    if (n == 0) {
        s = "";
    }
    cout << s << endl;
}

