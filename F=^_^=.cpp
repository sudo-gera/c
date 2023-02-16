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

template <typename T = void>
struct Scan {
    template <typename Y = T>
    auto operator()() {
        Y val;
        cin >> val;
        return val;
    }
};

template <typename T>
ssize_t Len(T&& q) {
    return static_cast<ssize_t>(q.size());
}

///////////////////////////////////////////////////end of lib

template <typename T>
size_t GetBit(T& val, size_t n) {
    return static_cast<size_t>(val >> n) & 1LLU;
}

template <typename T>
void SetBit(T& val, size_t n, size_t b) {
    val &= static_cast<T>(~(b << n));
    val |= static_cast<T>(b << n);
}

int main() {
    ssize_t n = Scan<ssize_t>()();
    vector<int> a(n);
    generate_n(a.begin(), n, Scan<size_t>());
    string s;
    vector<unsigned> d(n);
    s += "a";
    for (ssize_t q = 1; q < n; ++q) {
        while (Len(s) < q + a[q]) {
            // if (Len(s) < n) {
            //     d[s.size()].clear();
            // }
            s += s.end()[-q];
        }
        if (Len(s) <= q + a[q] and q + a[q] < n) {
            SetBit(d[q + a[q]], s[a[q]] - 'a', 1);
            // Bit(d[q + a[q]])[s[a[q]]-'a']=1;
            // d[q + a[q]].insert(s[a[q]]);
        }
        if (Len(s) == q) {
            for (char c = 'a';; ++c) {
                if (GetBit(d[q], c - 'a') == 0) {
                    // if (d[q].count(c) == 0) {
                    // if (Len(s) < n) {
                    //     d[s.size()].clear();
                    // }
                    s += c;
                    break;
                }
            }
        }
    }
    cout << s << endl;
}
