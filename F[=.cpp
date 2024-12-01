#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

/// @class Fenwick
/// @brief suppors storing an array with operations of incrementing one element and gettng sum of prefix
struct Fenwick {
private:
    std::vector<int64_t> tree_;
    int64_t F(int64_t x){
        return x & (x + 1);
    }
    int64_t G(int64_t x){
        return x | (x + 1);
    }
public:

    /// @brief constructor
    /// @param n - length of sequence
    explicit Fenwick(size_t n = 0) : tree_(n) {}

    /// @brief increment one number
    /// @param to_add - pair of position and what to add
    void operator+=(std::pair<int64_t,int64_t> to_add) {
        for (; to_add.first < static_cast<int64_t>(tree_.size()); to_add.first = G(to_add.first)) {
            tree_[to_add.first] += to_add.second;
        }
    }

    /// @brief get sum on prefix
    /// @param r - upper point of prefix
    /// @return sum
    int64_t operator[](int64_t r) {
        int64_t res = 0;
        for (; r >= 0; r = F(r) - 1) {
            res += tree_[r];
        }
        return res;
    }
};

// sources: https://codeforces.com/blog/entry/91632 https://github.com/maksim1744/programming-library/blob/master/prime_count.cpp

/// @brief struct for dealing with prime counting
class CountPrimesStruct {
    /// @brief stores primes up to n^(2/3)
    std::vector<int64_t> primes;
    /// @brief stores min divizor up to n^(2/3)
    std::vector<int64_t> min_divizor;
    /// @brief counts primes
    int64_t ans=0;
    /// @brief a bit greater than n^(2/3)
    int64_t y=0;
    /// @brief for storing phi results
    std::vector<std::pair<std::pair<int64_t, int64_t>, char>> phi_results;

    void Phi(int64_t n, int64_t a, int64_t sign = 1) {
        if (n == 0) {
            return;
        }
        if (a == -1) {
            ans += n * sign;
            return;
        }
        if (n <= y) {
            phi_results.emplace_back(std::make_pair(n, a), sign);
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
public:
    /// @brief function for counting primes
    /// @param n - count primes until n (including n)
    /// @return count
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
        auto primes_size=static_cast<int64_t>(primes.size());

        int64_t cbrt_n = n / y; // a bit greater than cbrt(n) (required to be cbrt(n) <= y <= sqrt(n))

        // pi(n) -- prime counting function
        // Phi(n, a) -- number of integers from 1 to n which are not divisible by any prime from 0-th to a-th (p0=2)

        // pi(n) = Phi(n, cbrt(n)) + pi(cbrt(n)) - F - 1, where F is the number of composite number of
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
        for (int64_t q = pi_cbrt_n, p = primes_size - 1; ; ++q) {
            while (p >= q and primes[q] * primes[p] > n) {
                --p;
            }
            if (p < q) {
                break;
            }
            ans -= p - q + 1;
        }

        // Phi
        // store all phi_results Phi(m, a) with m < n^2/3, calculate later with Fenwick (sum in a rectangle)
        Phi(n, pi_cbrt_n - 1);
        sort(phi_results.begin(), phi_results.end());
        int64_t ind = 2;
        // the order will be reversed, because prefix sum in a Fenwick is just one query
        Fenwick fw(primes_size);
        for (auto [na, sign] : phi_results) {
            auto [n, a] = na;
            while (ind <= n) {
                fw+={primes_size - 1 - min_divizor[ind++], 1};
            }
            ans += (fw[primes_size - a - 2] + 1) * sign;
        }
        phi_results.clear();
        return ans - 1;
    }
} count_primes_struct;

int main() {
    int64_t n=0;
    std::cin>>n;
    std::cout << count_primes_struct.CountPrimes(n) << std::endl;
}
