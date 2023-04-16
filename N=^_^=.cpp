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
using std::back_inserter, std::list, std::hash, std::reverse, std::queue;
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::copy_if, std::exit, std::enable_if, std::enable_if, std::stack;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n, std::deque;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::tuple_element, std::tuple_size, std::is_same, std::forward;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::unique, std::decay_t, std::is_convertible_v, std::array;

template <typename T = void>
struct Scan {
    template <typename Y = T>
    auto operator()() {
        return Scan<Y>();
    }
    template <typename Y = T>
    operator Y() {  // NOLINT
        Y val;
        cin >> val;
        return val;
    }
};

///////////////////////////////////////////////////end of lib

template <typename A, typename S>
auto Lcp(A& a, S& s) {
    size_t n = a.size();
    vector<size_t> d(n);
    vector<size_t> l(n);
    for (size_t q = 0; q < s.size(); ++q) {
        d[a[q]] = q;
    }
    size_t k = 0;
    for (size_t i = 0; i < n; ++i) {
        if (k > 0) {
            k--;
        }
        if (d[i] == n - 1) {
            l[n - 1] = -1;
            k = 0;
        } else {
            size_t j = a[d[i] + 1];
            while (max(i + k, j + k) < n and s[i + k] == s[j + k]) {
                k++;
            }
            l[d[i]] = k;
        }
    }
    l.pop_back();
    return l;
}

int main() {
    size_t n = Scan();
    string s = Scan();
    vector<size_t> a(n);
    generate_n(a.begin(), n, [] { return size_t(Scan()) - 1; });
    auto l = Lcp(a, s);
    for (auto w : l) {
        cout << w << " ";
    }
    cout << endl;
}
