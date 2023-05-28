#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <array>

/// @class PolyHash
/// @brief simple polynomial hash
/// @details supports hashes of concatenation of substrings
struct PolyHash {
private:
    /// @brief base of polynomial
    unsigned base_ = 1000;
    /// @brief for storing powers of base
    std::vector<unsigned> powers_;
    /// @brief for storing hashes of prefixes
    std::vector<std::vector<unsigned>> prefixes_;
    /// @brief implementation of operator()
    void HashImpl(unsigned&) {
    }
    /// @brief implementation of operator()
    template <typename... T>
    void HashImpl(unsigned& res, unsigned s1, unsigned b1, unsigned e1, T... args) {
        auto& d = prefixes_[s1];
        res *= powers_[e1 - b1];
        res += d[e1] - d[b1] * powers_[e1 - b1];
        HashImpl(res, args...);
    }

public:
    /// @brief constructor
    /// @param l - maximum length of string
    /// @param n - maximum number of strings
    /// @details would be made n locations with indexes 0..n-1
    explicit PolyHash(unsigned l, unsigned n) {
        powers_.push_back(1);
        while (powers_.size() < l) {
            powers_.push_back(powers_.back() * base_);
        }
        prefixes_.resize(n);
    }
    /// @brief get length of a string by its index
    /// @param s - index
    /// @return length
    size_t Size(unsigned s) {
        return prefixes_[s].size() - 1;
    }
    /// @brief get number of strings
    /// @return number of strings
    size_t Size() {
        return prefixes_.size();
    }
    /// @brief add string to hashing
    /// @param ss - string
    /// @param s - index
    void Add(std::string& ss, unsigned s) {
        auto& d = prefixes_[s] = std::vector<unsigned>(ss.size() + 1);
        unsigned l = 1;
        while (l <= ss.size()) {
            d[l] = (d[l - 1] * base_ + ss[l - 1]);
            ++l;
        }
    }
    /// @brief get hash of substirngs
    /// @param args - description of substirngs in format: s1, b1, e2, s2, b2 e2, ...
    /// @details if more than one substrings are given, return value is hash of concatenation of strings
    /// @details note: s1, s2, ... are indexes of strings
    /// @return hash(s1[b1:e1]+s2[b2:e2]+s3[b3:e3]+...)
    template <typename... T>
    unsigned operator()(T... args) {
        unsigned res = 0;
        HashImpl(res, args...);
        return res;
    }
};

/// \class Pairs
/// \brief if there would be a prefix or suffix not longer than given string, its hash is in one of these arrays
/// \details each string would have personal Pairs object
struct Pairs {
    std::array<unsigned, 10> prefix_array;
    std::array<unsigned, 10> suffix_array;
    unsigned prefix_array_size;
    unsigned suffix_array_size;
};

/// @brief find all strings by given hash
/// @param h - PolyHash object
/// @return vector that works like map[hash -> vector of string indexes]
auto CreateBH(PolyHash& h) {
    size_t n=h.Size()/2;
    std::vector<std::vector<unsigned>> by_hash(n);
    for (unsigned w = 0; w < n; ++w) {
        by_hash[h(w, 0, h.Size(w)) % n].push_back(w);
    }
    return by_hash;
}

/// @brief create Pairs objects for each stirng and fill them with values
/// @param h - PolyHash object
/// @return vector of Pairs
auto CreatePairs(PolyHash& h) {
    size_t n=h.Size()/2;
    std::vector<Pairs> pairs(n);
    for (unsigned w = 0; w < pairs.size(); ++w) {
        auto& pair = pairs[w];
        auto len = h.Size(w);
        for (unsigned overlap_len = 0; overlap_len < len; ++overlap_len) {
            if (h(w + n, 0, len - overlap_len, w, 0, len) == h(w + n, 0, len, w, overlap_len, len)) {
                pair.prefix_array[pair.prefix_array_size++] = h(w + n, 0, len - overlap_len);
            }
        }
        for (unsigned overlap_len = 0; overlap_len < len; ++overlap_len) {
            if (h(w, 0, len, w + n, overlap_len, len) == h(w, 0, len - overlap_len, w + n, 0, len)) {
                pair.suffix_array[pair.suffix_array_size++] = h(w + n, overlap_len, len);
            }
        }
    }
    return pairs;
}

/// @brief create almost ans
/// @param by_hash - vector from CreateBH
/// @param pairs - vector from CreatePairs
/// @return vector of pairs of indexes of strings which is almost answer
/// @details this vector would contain (-1,-1) pair, pairs of same strings (q,q), pairs of strings, repetitions, hash equality is not checked
auto CreateAns(std::vector<std::vector<unsigned>> by_hash, std::vector<Pairs>& pairs) {
    size_t n=by_hash.size();
    std::vector<std::pair<unsigned, unsigned>> ans({{0U - 1, 0U - 1}});
    for (unsigned q = 0; q < pairs.size(); ++q) {
        auto& pairs_q = pairs[q];
        for (unsigned i = 0; i < pairs_q.prefix_array_size; ++i) {
            auto hash = pairs_q.prefix_array[i];
            for (auto str : by_hash[hash % n]) {
                ans.emplace_back();
                ans.back() = {str, q};
            }
        }
        for (unsigned i = 0; i < pairs_q.suffix_array_size; ++i) {
            auto hash = pairs_q.suffix_array[i];
            for (auto str : by_hash[hash % n]) {
                ans.emplace_back();
                ans.back() = {q, str};
            }
        }
    }
    return ans;
}

/// @brief replace same pairs (q,q) and pairs which are palindromes only by hashes with (-1,-1) pairs
/// @param ans - from CreateAns
/// @param strings - original vector of strings (for hash checking)
void FilterAns(std::vector<std::pair<unsigned, unsigned>>& ans, std::vector<std::string>& strings) {
    for (auto& [q, w] : ans) {
        if (q != w) {
            auto t = strings[q] + strings[w];
            if (t != std::string(t.rbegin(), t.rend())) {
                q = w = -1;
            }
        } else {
            q = w = -1;
        }
    }
}

int main() {
    unsigned n = 0;
    std::cin >> n;
    std::vector<std::string> strings(n);
    std::vector<std::string> reversed_strings(n);
    auto h = PolyHash(20, 2 * n);
    for (unsigned q = 0; q < n; ++q) {
        auto& w = strings[q];
        auto& e = reversed_strings[q];
        std::cin >> w;
        e = std::string(w.rbegin(), w.rend());
        h.Add(w, q);     // 0...n-1 for normal strings
        h.Add(e, q + n); // n...2n-1 for reversed strings
    }
    auto by_hash = CreateBH(h);
    auto pairs = CreatePairs(h);
    auto ans = CreateAns(by_hash, pairs);
    FilterAns(ans, strings);
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin() - 1);
    std::cout << ans.size() << '\n';
    for (auto w : ans) {
        std::cout << w.first + 1 << ' ' << w.second + 1 << '\n';
    }
}
