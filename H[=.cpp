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

/// @brief minimal number of bits required to store this number
/// @param n - number to measure
/// @return number of bits
size_t BitLen(size_t n) {
    size_t l = 0;
    while (n) {
        n >>= 1;
        ++l;
    }
    return l;
}

// source: http://e-maxx.ru/algo/fft_multiply

/// @brief perform fast Fourier transform in-place
/// @param a - vector of complex numbers
/// @param invert - indicates if we want inverse transformation
/// @details requires length of a to be the power of 2
void Fft(std::vector<std::complex<double>>& a, bool invert) {
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
        double ang = 2 * M_PI / static_cast<double>(len) * (invert ? -1 : 1);
        std::complex<double> wlen(cos(ang), sin(ang));
        for (size_t i = 0; i < n; i += len) {
            std::complex<double> w(1);
            for (size_t j = 0; j < len / 2; ++j) {
                std::complex<double> u = a[i + j];
                std::complex<double> v = a[i + j + len / 2] * w;
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

/// @brief multiplies two polynomials using fft
/// @param a - first polynomial
/// @param b - second polynomial
/// @param res - place to write the result
/// @details a and b are not required to be same length
/// @details uses optimization with two fft instead of 3
/// @details a and b should be ordered a[0]*x^0+a[1]*x^1+...
void Multiply(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& res) {
    std::vector<std::complex<double>> fa(a.begin(), a.end());
    std::vector<std::complex<double>> fb(b.begin(), b.end());
    size_t n = 1LLU << std::max(BitLen(a.size()), BitLen(b.size()));
    fa.resize(n);
    fb.resize(n);
    for (size_t q = 0; q < n; ++q) {
        fa[q] += fb[q] * std::complex<double>(0, 1);
    }
    Fft(fa, false);
    for (size_t q = 0; q < n; ++q) {
        fb[q] = conj(fa[(n - q) % n]);
    }
    for (size_t q = 0; q < n; ++q) {
        fa[q] = (fa[q] + fb[q]) * (fa[q] - fb[q]) / std::complex<double>(0, 4);
    }
    Fft(fa, true);
    res.resize(fa.size());
    for (size_t i = 0; i < fa.size(); ++i) {
        res[i] = static_cast<int>(llround(fa[i].real()));
    }
    while (not res.empty() and res.back() == 0) {
        res.pop_back();
    }
}

int main() {
    size_t n = 0;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (size_t q = 0; q < n + 1; ++q) {
        std::cin >> a[q];
    }
    reverse(a.begin(), a.end());
    size_t m = 0;
    std::cin >> m;
    std::vector<int> b(m + 1);
    for (size_t q = 0; q < m + 1; ++q) {
        std::cin >> b[q];
    }
    reverse(b.begin(), b.end());
    std::vector<int> c;
    Multiply(a, b, c);
    reverse(c.begin(), c.end());
    std::cout << c.size() - 1 << " ";
    for (auto q : c) {
        std::cout << q << " ";
    }
    std::cout << std::endl;
}
