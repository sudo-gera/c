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
using std::unique_ptr, std::shared_ptr, std::transform, std::apply;

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

int main() {
    size_t n = scan;
    vector<pair<int, int>> a(n);
    // vector<pair<int,int>> ar(n);
    set<pair<int, int>> s;
    for (size_t q = 0; q < n; ++q) {
        int w = 0;
        int e = 0;
        cin >> w >> e;
        a[q] = {w, e};
        s.insert({w, e});
    }
    // set<array<pair<int, int>, 4>> d;
    size_t c=0;
    for (size_t q = 0; q < n; ++q) {
        for (size_t w = 0; w < n; ++w) {
            if (q != w) {
                if (s.count({a[w].second - a[q].second + a[q].first, a[q].first - a[w].first + a[q].second})) {
                    if (s.count({a[w].second - a[q].second + a[w].first, a[q].first - a[w].first + a[w].second})) {
                        array<pair<int, int>, 4> f = {
                            a[q],
                            a[w],
                            {a[w].second - a[q].second + a[q].first, a[q].first - a[w].first + a[q].second},
                            {a[w].second - a[q].second + a[w].first, a[q].first - a[w].first + a[w].second}};
                        // sort(d.back().begin(), d.back().end());
                        // ic(d.back());
                        sort(f.begin(), f.end());
                        if (f[0]==a[q]){
                            c++;
                        }
                        // d.emplace(array<pair<int, int>, 4>{f[0], f[1], f[2], f[3]});
                    }
                }
            }
        }
    }
    cout<<c<<endl;
    // sort(d.begin(), d.end());
    // d.resize(unique(d.begin(), d.end()) - d.begin());
    // cout << d.size() << endl;
}
