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
#include <complex>
using std::back_inserter, std::list, std::hash, std::reverse, std::queue;
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::complex;
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

size_t BitLen(size_t n) {
    size_t l = 0;
    while (n) {
        n >>= 1;
        ++l;
    }
    return l;
}

// source: http://e-maxx.ru/algo/fft_multiply

#define PI 3.141592653589793

using Base = complex<double>;

void Fft(vector<Base>& a, bool invert) {
    size_t n = a.size();

    for (size_t i = 1, j = 0; i < n; ++i) {
        size_t bit = n >> 1;
        for (; j >= bit; bit >>= 1) {
            j -= bit;
        }
        j += bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }

    for (size_t len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / static_cast<double>(len) * (invert ? -1 : 1);
        Base wlen(cos(ang), sin(ang));
        for (size_t i = 0; i < n; i += len) {
            Base w(1);
            for (size_t j = 0; j < len / 2; ++j) {
                Base u = a[i + j];
                Base v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (size_t i = 0; i < n; ++i) {
            a[i] /= static_cast<double>(n);
        }
    }
}

void Multiply(const vector<int>& a, const vector<int>& b, vector<int>& res) {
    vector<complex<double>> fa(a.begin(), a.end());
    vector<complex<double>> fb(b.begin(), b.end());
    size_t n = 1;
    while (n < max(a.size(), b.size())) {
        n <<= 1;
    }
    n <<= 1;
    fa.resize(n), fb.resize(n);

    for (size_t q = 0; q < n; ++q) {
        fa[q] += fb[q] * Base(0, 1);
    }
    // ic(fa)
    // ic(fb)
    Fft(fa, false);
    // Fft(fb, false);
    // ic(fa)
    // ic(fb)
    for (size_t q = 0; q < n; ++q) {
        fb[q] = conj(fa[(n - q) % n]);
    }
    // ic(fa)
    // ic(fb)
    for (size_t q = 0; q < n; ++q) {
        fa[q] = (fa[q] + fb[q]) * (fa[q] - fb[q]) / Base(0, 4);
    }
    // ic(fa)
    // ic(fb)
    // for (size_t i = 0; i < n; ++i) {
    // fa[i] = (fa[i]+fb[i])*(fa[i]-fb[i])/4.0;
    // fa[i] = fa[i]*fb[i];
    // }
    Fft(fa, true);

    // while (fa.size() and llround(fa.back().real())==0){
    //     fa.pop_back();
    // }
    // ic(fa)
    res.resize(fa.size());
    for (size_t i = 0; i < fa.size(); ++i) {
        res[i] = static_cast<int>(llround(fa[i].real()));
    }
}

int main() {
    size_t n = scan;
    vector<int> a(n + 1);
    ScanVector(a);
    reverse(a.begin(), a.end());
    size_t m = scan;
    vector<int> b(m + 1);
    ScanVector(b);
    reverse(b.begin(), b.end());
    vector<int> c;
    Multiply(a, b, c);
    while (!c.empty() and c.back() == 0) {
        c.pop_back();
    }
    reverse(c.begin(), c.end());
    cout << c.size() - 1 << " ";
    for (auto q : c) {
        cout << q << " ";
    }
    cout << endl;
}
