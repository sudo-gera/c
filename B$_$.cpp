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
using std::istream, std::ostream, std::integral_constant, std::conditional_t;
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

template <typename T, typename Y>
auto operator<=>(T q, Y w) {
    return (w < q) - (q < w);
}

template <typename T>
bool operator<=>(Vect<T> q, Vect<T> e) {
    return q.tuple() <=> e.tuple();
}

template <typename T>
auto& operator>>(istream& s, Vect<T>& v) {
    s >> v.x >> v.y;
    return s;
}

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

auto Abs(auto a) {
    return a < 0 ? -a : a;
}

int main() {
    size_t n = scan;
    vector<Vect<ssize_t>> a(n);
    ScanVector(a);
    sort(a.begin(), a.end(), [&](auto q, auto e) { return make_tuple(q.x, q.y) < make_tuple(e.x, e.y); });
    sort(a.begin() + 1, a.end(), [&](auto q, auto e) {
        auto w = -(q - a[0]) / (e - a[0]);
        if (w == 0) {
            w = -((q - a[0]).SqAbs() - (e - a[0]).SqAbs());
        }
        return w > 0;
    });
    vector<Vect<ssize_t>> s({a[0], a[1]});
    rotate(a.begin(), a.begin() + 1, a.end());
    for (size_t q = 1; q < a.size(); ++q) {
        while (s.size() > 1 and (s.end()[-2] - s.end()[-1]) / (s.end()[-1] - a[q]) >= 0) {
            s.pop_back();
        }
        s.push_back(a[q]);
    }
    s.pop_back();
    cout << s.size() << endl;
    for (auto w : s) {
        cout << w.x << " " << w.y << "\n";
    }
    ssize_t d = 0;
    for (size_t q = 2; q < s.size(); ++q) {
        d += (s[q - 1] - s[0]) / (s[q] - s[q - 1]);
    }
    d = Abs(d);
    cout << d / 2 << (d % 2 ? ".5" : ".0") << endl;
}
