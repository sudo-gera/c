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
using std::max_element, std::abs;
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

template <typename T>
struct Vect;

template <typename T>
auto operator*(Vect<T>, T);

template <typename T>
auto operator*(Vect<T>, Vect<T>);

template <typename T>
struct Vect {
    T x = 0;
    T y = 0;
    auto& operator*=(T e) {
        *this = *this * e;
        return *this;
    }
    auto& operator+=(Vect<T> e) {
        *this = *this + e;
        return *this;
    }
    Vect operator-() const {
        return {-x, -y};
    }
    auto tuple() {  // NOLINT
        return make_tuple(x, y);
    }
    auto SqAbs() {
        return x * x + y * y;
    }
};

template <typename T>
auto operator*(Vect<T> q, Vect<T> w) {
    return q.x * w.x + q.y * w.y;
}

template <typename T>
auto operator/(Vect<T> q, Vect<T> w) {
    return q.x * w.y - q.y * w.x;
}

template <typename T>
auto operator*(Vect<T> q, T e) {
    return Vect{q.x * e + q.y * e};
}

template <typename T>
auto operator*(T q, Vect<T> e) {
    return Vect{q * e.x + q * e.y};
}

template <typename T>
auto operator+(Vect<T> q, Vect<T> w) {
    return Vect{q.x + w.x, q.y + w.y};
}

template <typename T>
auto operator-(Vect<T> q, Vect<T> w) {
    return Vect<T>{q.x - w.x, q.y - w.y};
}

auto Sign(auto t) {
    return (t > 0) - (t < 0);
}

auto Abs(auto a){
    return a<0?-a:a;
}

int main() {
    Vect<ssize_t> a = {Scan(), Scan()};
    Vect<ssize_t> s = {Scan(), Scan()};
    Vect<ssize_t> d = {Scan(), Scan()};
    Vect<ssize_t> f = {Scan(), Scan()};
    if (Sign((s - a) / (d - a)) * Sign((s - a) / (f - a)) < 0 and
        Sign((d - f) / (a - f)) * Sign((d - f) / (s - f)) < 0) {
        cout << 0 << endl;
        return 0;
    }
    vector<tuple<Vect<ssize_t>, Vect<ssize_t>, Vect<ssize_t>>> z = {
        {a, s, d},
        {a, s, f},
        {d, f, a},
        {d, f, s},
    };
    vector<double> x;
    transform(z.begin(), z.end(), back_inserter(x), [&](auto&& t) {
        return apply(
            [](auto&& a, auto&& b, auto&& c) -> long double {
                if ((a - b) * (a - c) <= 0) {
                    return (a - c).SqAbs();
                }
                if ((b - a) * (b - c) <= 0) {
                    return (b - c).SqAbs();
                }
                return Abs((a - b) / (a - c)) * Abs((a - b) / (a - c)) / 1. / (a - b).SqAbs();
            },
            t);
    });
    // ic(x)
    printf("%18.9lf\n", sqrt(*min_element(x.begin(), x.end())));
}
