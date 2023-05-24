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


struct Fenwick {
private:
    vector<int64_t> tree_;
    int64_t F(int64_t x){
        return x & (x + 1);
    }
    int64_t G(int64_t x){
        return x | (x + 1);
    }
public:

    explicit Fenwick(size_t n = 0) : tree_(n) {}

    void Add(int64_t i, int64_t k) {
        for (; i < static_cast<int64_t>(tree_.size()); i = G(i)) {
            tree_[i] += k;
        }
    }

    int64_t Ask(int64_t r) {
        int64_t res = 0;
        for (; r >= 0; r = F(r) - 1) {
            res += tree_[r];
        }
        return res;
    }
};

// sources: https://codeforces.com/blog/entry/91632 https://github.com/maksim1744/programming-library/blob/master/prime_count.cpp


// works in 250ms for n=1e11, in ~1s for n=1e12
// O(n^2/3 logn)
// just call CountPrimes(n)
struct CountPrimesStructT {
    vector<int64_t> primes;
    vector<int64_t> min_divizor;
    int64_t ans=0;
    int64_t y=0;
    vector<pair<pair<int64_t, int64_t>, char>> queries;

    void Phi(int64_t n, int64_t a, int64_t sign = 1) {
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

    void Sieve(int64_t n){
        primes.clear();
        min_divizor.assign(n + 1, -1);
        ans = 0;
        for (int64_t i = 2; i <= n; ++i) {
            if (min_divizor[i] == -1) {
                min_divizor[i] = static_cast<int64_t>(primes.size());
                primes.push_back(i);
            }
            for (int64_t k = 0; k < static_cast<int64_t>(primes.size()); ++k) {
                int64_t j = primes[k];
                if (i * j > n) {
                    break;
                }
                min_divizor[i * j] = k;
                if (i % j == 0) {
                    break;
                }
            }
        }
    }

    int64_t CountPrimes(int64_t n) {
        if (n < 100) {
            y = n;
        }else{
            y = llroundl(pow(static_cast<double>(n), 0.64));
        }
        Sieve(y);
        if (n < 100) {
            return static_cast<int64_t>(primes.size());
        }
        int64_t cbrt_n = n / y; // a bit smaller than cbrt(n)

        // pi(n) -- prime counting function
        // Phi(n, a) -- number of integers from 1 to n which are not divisible by any prime from 0-th to a-th (p0=2)

        // pi(n) = Phi(n, cbrt(n)) + pi(cbrt(n)) - F, where F is the number of composite number of
        // the form p*q, where p >= q >= cbrt(n) (can be counted with two pointers)

        // pi(cbrt(n))
        for (int64_t p : primes) {
            if (p > cbrt_n) {
                break;
            }
            ans++;
        }

        auto pi_cbrt_n = ans;

        // F is the number of composite number of
        // the form p*q, where p >= q >= cbrt(n) (can be counted with two pointers)
        // int64_t ;
        for (int64_t q = pi_cbrt_n, p = static_cast<int64_t>(primes.size()) - 1; ; ++q) {
            while (p >= q and primes[q] * primes[p] > n) {
                --p;
            }
            if (p < q) {
                break;
            }
            ans -= p - q + 1;
        }

        // Phi
        // store all queries Phi(m, a) with m < n^2/3, calculate later with Fenwick (sum in a rectangle)
        Phi(n, pi_cbrt_n - 1);
        sort(queries.begin(), queries.end());
        int64_t ind = 2;
        // auto sz = static_cast<int64_t>(primes.size());
        // the order will be reversed, because prefix sum in a Fenwick is just one query
        Fenwick fw(primes.size());
        for (auto [na, sign] : queries) {
            auto [n, a] = na;
            while (ind <= n) {
                fw.Add(static_cast<int64_t>(primes.size()) - 1 - min_divizor[ind++], 1);
            }
            ans += (fw.Ask(static_cast<int64_t>(primes.size()) - a - 2) + 1) * sign;
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
