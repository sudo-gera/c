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
using std::istream, std::ostream;
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

// template <typename T, typename Y>
// decltype(0 <=> 0) operator<=>(T q, Y w) {
//     return int((w < q) - (q < w)) <=> 0;
// }

template <typename T>
auto operator<(Vect<T> q, Vect<T> e) {
    return q.tuple() < e.tuple();
}
template <typename T>
auto operator>(Vect<T> q, Vect<T> e) {
    return q.tuple() > e.tuple();
}
template <typename T>
auto operator==(Vect<T> q, Vect<T> e) {
    return q.tuple() == e.tuple();
}
template <typename T>
auto operator!=(Vect<T> q, Vect<T> e) {
    return q.tuple() != e.tuple();
}
template <typename T>
auto operator<=(Vect<T> q, Vect<T> e) {
    return q.tuple() <= e.tuple();
}
template <typename T>
auto operator>=(Vect<T> q, Vect<T> e) {
    return q.tuple() >= e.tuple();
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
    return Vect<T>{q.x * e, q.y * e};
}

template <typename T>
auto operator/(Vect<T> q, T e) {
    return Vect<T>{q.x / e, q.y / e};
}

template <typename T>
auto operator*(T q, Vect<T> e) {
    return Vect<T>{q * e.x, q * e.y};
}

template <typename T>
auto operator+(Vect<T> q, Vect<T> w) {
    return Vect<T>{q.x + w.x, q.y + w.y};
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

union H {
    size_t r;
    int f[2];
};

template <typename T>
struct std::hash<Vect<T>> {
    size_t operator()(Vect<T> v) const {
        H h;
        h.f[0] = v.x;
        h.f[1] = v.y;
        return h.r;
    }
};

template <typename T>
auto Atan2(Vect<T> q) {
    return atan2(q.x, q.y);
}

// auto angle(auto q,auto w){
//     auto a=atan2(q.x,q.y);
//     auto s=atan2(w.x,w.y);
//     if ()
// }

int main() {
    size_t n = scan;
    size_t m = scan;
    vector<Vect<int64_t>> a(n);
    vector<Vect<int64_t>> s(m);
    ScanVector(a);
    ScanVector(s);
    for (auto& q : s) {
        q = -q;
    }
    rotate(a.begin(), min_element(a.begin(), a.end()), a.end());
    rotate(s.begin(), min_element(s.begin(), s.end()), s.end());
    vector<Vect<int64_t>> d;
    // source
    // https://neerc.ifmo.ru/wiki/index.php?title=%D0%A1%D1%83%D0%BC%D0%BC%D0%B0_%D0%9C%D0%B8%D0%BD%D0%BA%D0%BE%D0%B2%D1%81%D0%BA%D0%BE%D0%B3%D0%BE_(%D0%BE%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5,_%D0%B2%D1%8B%D1%87%D0%B8%D1%81%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5)
    size_t i = 0;
    size_t j = 0;
    a.push_back(a[0]);
    a.push_back(a[1]);
    s.push_back(s[0]);
    s.push_back(s[1]);
    ic(a)
    ic(s)
    d.push_back(a[0]+s[0]);
    while (i < n or j < m) {
        // d.push_back(a[i] + s[j]);
        // ic(i,j)
        // auto aa = Atan2(a[i + 1] - a[i]);
        // auto sa = Atan2(s[j + 1] - s[j]);
        ic(d)
        auto an = (a[i + 1] - a[i]) / (s[j + 1] - s[j]);
        if (an > 0) {
            auto tmp=d.back()+(s[j + 1] - s[j]);
            ++j;
            ic(tmp-d.back())
            if (d[0]==tmp){
                break;
            }
            d.push_back(tmp);
        }
        if (an < 0) {
            auto tmp=d.back()+(a[i + 1] - a[i]);
            ++i;
            ic(tmp-d.back())
            if (d[0]==tmp){
                break;
            }
            d.push_back(tmp);
        }
        if (an == 0) {
            auto tmp=d.back()+(a[i + 1] - a[i])+(s[j + 1] - s[j]);
            ++i;
            ++j;
            ic(tmp-d.back())
            if (d[0]==tmp){
                break;
            }
            d.push_back(tmp);
        }

        // if (aa < sa) {
        //     ++i;
        // }
        // if (aa > sa) {
        //     ++j;
        // }
        // if (aa == sa) {
        //     ++i;
        //     ++j;
        // }
    }
    auto dist_sq = [](auto&& a, auto&& b, auto&& c) -> long double {
        if ((a - b) * (a - c) <= 0) {
            return (a - c).SqAbs();
        }
        if ((b - a) * (b - c) <= 0) {
            return (b - c).SqAbs();
        }
        return Abs((a - b) / (a - c)) * Abs((a - b) / (a - c)) / 1. / (a - b).SqAbs();
    };
    d.push_back(d[0]);
    vector<long double> f;
    for (size_t q = 1; q < d.size(); ++q) {
        f.push_back(dist_sq(d[q - 1], d[q], Vect<int64_t>{0, 0}));
    }
    auto ans = sqrt(static_cast<double>(*min_element(f.begin(), f.end()))) - 60;
    if (ans < 0) {
        ans = 0;
    }
    cout << ans << endl;
}
