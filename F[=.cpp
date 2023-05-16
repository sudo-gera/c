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
using std::make_pair;
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

// sources: https://codeforces.com/blog/entry/91632 https://github.com/maksim1744/programming-library/blob/master/prime_count.cpp

// works in 250ms for n=1e11, in ~1s for n=1e12
// O(n^2/3 logn)
// just call CountPrimes(n)
struct CountPrimesStructT {
    vector<int> primes;
    vector<int> mnprimes;
    int64_t ans;
    int64_t y;
    vector<pair<pair<int64_t, int>, char>> queries;

    void Phi(int64_t n, int a, int sign = 1) {
        if (n == 0) {
            return;
        }
        if (a == -1) {
            ans += n * sign;
            return;
        }
        if (n <= y) {
            queries.emplace_back(make_pair(n, a), sign);
            return;
        }
        Phi(n, a - 1, sign);
        Phi(n / primes[a], a - 1, -sign);
    }

    struct Fenwick {
        vector<int> tree;
        int n;

        explicit Fenwick(int n = 0) : n(n) {
            tree.assign(n, 0);
        }

        void Add(int i, int k) {
            for (; i < n; i = (i | (i + 1))) {
                tree[i] += k;
            }
        }

        int Ask(int r) {
            int res = 0;
            for (; r >= 0; r = (r & (r + 1)) - 1) {
                res += tree[r];
            }
            return res;
        }
    };

    int64_t CountPrimes(int64_t n) {
        y = static_cast<int64_t>(pow(static_cast<double>(n), 0.64));
        if (n < 100) {
            y = n;
        }
        primes.clear();
        mnprimes.assign(y + 1, -1);
        ans = 0;
        for (int i = 2; i <= y; ++i) {
            if (mnprimes[i] == -1) {
                mnprimes[i] = static_cast<int>(primes.size());
                primes.push_back(i);
            }
            for (int k = 0; k < static_cast<int>(primes.size()); ++k) {
                int j = primes[k];
                if (i * j > y) {
                    break;
                }
                mnprimes[i * j] = k;
                if (i % j == 0) {
                    break;
                }
            }
        }
        if (n < 100) {
            return static_cast<int64_t>(primes.size());
        }
        int64_t s = n / y;

        // pi(n) -- prime counting function
        // Phi(n, a) -- number of integers from 1 to n which are not divisible by any prime from 0-th to a-th (p0=2)

        // pi(n) = Phi(n, cbrt(n)) + pi(cbrt(n)) - F, where F is the number of composite number of
        // the form p*q, where p >= q >= cbrt(n) (can be counted with two pointers)

        // pi(cbrt(n))
        for (int p : primes) {
            if (p > s) {
                break;
            }
            ans++;
        }

        // F
        int ssz = static_cast<int>(ans);
        int ptr = static_cast<int>(primes.size()) - 1;
        for (int i = ssz; i < static_cast<int>(primes.size()); ++i) {
            while (ptr >= i && static_cast<int64_t>(primes[i]) * primes[ptr] > n) {
                --ptr;
            }
            if (ptr < i) {
                break;
            }
            ans -= ptr - i + 1;
        }

        // Phi
        // store all queries Phi(m, a) with m < n^2/3, calculate later with Fenwick (sum in a rectangle)
        Phi(n, ssz - 1);
        sort(queries.begin(), queries.end());
        int ind = 2;
        int sz = static_cast<int>(primes.size());
        // the order will be reversed, because prefix sum in a Fenwick is just one query
        Fenwick fw(sz);
        for (auto [na, sign] : queries) {
            auto [n, a] = na;
            while (ind <= n) {
                fw.Add(sz - 1 - mnprimes[ind++], 1);
            }
            ans += (fw.Ask(sz - a - 2) + 1) * sign;
        }
        queries.clear();
        return ans - 1;
    }
} count_primes_struct;

int64_t CountPrimes(int64_t n) {
    return count_primes_struct.CountPrimes(n);
}

int main() {
    cout << CountPrimes(scan) << endl;
}
