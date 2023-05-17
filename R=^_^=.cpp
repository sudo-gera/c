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
auto ScanVector(T &x) {
    generate_n(x.begin(), x.size(), scan);
}

///////////////////////////////////////////////////end of lib

// source: https://github.com/maksim1744/programming-library/blob/master/SuffixArray.cpp

namespace suffix_array {

// linear suffix array
// works in O(n + sigma)
// for strings call SuffixArray(s, ALPHA_SMALL | ALPHA_LARGE) for example,
//     or just SuffixArray(s)
// for vectors call SuffixArray(v, *max_element(v.begin(), v.end())), v[i] has to be at least 1 for all i

// call lcp(string/vector, SuffixArray) for lcp

// const int ALPHA_SMALL = 1;
// const int ALPHA_LARGE = 2;
// const int DIGITS = 4;

vector<int> buf1, buf2, buf3;

vector<int> SuffixArray(vector<int> s, int k) {
    if (s.size() <= 4) {
        vector<int> res(s.size());
        iota(res.begin(), res.end(), 0);
        sort(res.begin(), res.end(), [&](int i1, int i2) {
            if (i1 == i2) {
                return false;
            }
            while (i1 < static_cast<int>(s.size()) && i2 < static_cast<int>(s.size()) && s[i1] == s[i2]) {
                ++i1;
                ++i2;
            }
            if (i1 == static_cast<int>(s.size()) || i2 == static_cast<int>(s.size())) {
                return i1 > i2;
            }
            return s[i1] < s[i2];
        });
        return res;
    }
    int init_size = static_cast<int>(s.size());
    s.resize(s.size() + 3, 0);

    vector<int> triple_inds;
    for (int i = 0; i + 3 <= static_cast<int>(s.size()); ++i) {
        if (i % 3 != 0) {
            triple_inds.push_back(i);
        }
    }

    // sort triples
    for (int it = 2; it >= 0; --it) {
        buf1.assign(k + 1, 0);
        for (int i : triple_inds) {
            buf1[s[i + it]]++;
        }
        for (int i = 1; i < static_cast<int>(buf1.size()); ++i) {
            buf1[i] += buf1[i - 1];
        }
        buf2.resize(triple_inds.size());
        for (int i = static_cast<int>(triple_inds.size()) - 1; i >= 0; --i) {
            buf2[--buf1[s[triple_inds[i] + it]]] = triple_inds[i];
        }
        swap(triple_inds, buf2);
    }

    // assign equivalency classes to triples
    buf2.resize(triple_inds.size());
    buf2[0] = 1;
    for (int i = 1; i < static_cast<int>(triple_inds.size()); ++i) {
        if (s[triple_inds[i]] == s[triple_inds[i - 1]] && s[triple_inds[i] + 1] == s[triple_inds[i - 1] + 1] &&
            s[triple_inds[i] + 2] == s[triple_inds[i - 1] + 2]) {
            buf2[i] = buf2[i - 1];
        } else {
            buf2[i] = buf2[i - 1] + 1;
        }
    }

    // recursively sort triples if there are equal
    if (buf2.back() != static_cast<int>(buf2.size())) {
        int last = buf2.back();
        buf1.resize(s.size());
        for (int i = 0; i < static_cast<int>(triple_inds.size()); ++i) {
            buf1[triple_inds[i]] = buf2[i];
        }
        buf2.clear();
        for (int i = 1; i + 3 <= static_cast<int>(s.size()); i += 3) {
            buf2.push_back(buf1[i]);
        }
        int n1 = static_cast<int>(buf2.size());
        for (int i = 2; i + 3 <= static_cast<int>(s.size()); i += 3) {
            buf2.push_back(buf1[i]);
        }
        triple_inds = SuffixArray(buf2, last);
        for (int &i : triple_inds) {
            {
                if (i * 3 + 1 + 3 <= static_cast<int>(s.size())) {
                    i = i * 3 + 1;
                } else {
                    i = (i - n1) * 3 + 2;
                }
            }
        }
    }

    buf2.clear();
    if (s.size() % 3 == 0) {
        buf2.push_back(static_cast<int>(s.size()) - 3);
    }
    for (int i : triple_inds) {
        if (i % 3 == 1) {
            buf2.push_back(i - 1);
        }
    }

    // sort suffixes with i % 3 = 0
    {
        buf1.assign(k + 1, 0);
        for (int i : buf2) {
            buf1[s[i]]++;
        }
        for (int i = 1; i < static_cast<int>(buf1.size()); ++i) {
            buf1[i] += buf1[i - 1];
        }

        buf3.resize(buf2.size());
        for (int i = static_cast<int>(buf2.size()) - 1; i >= 0; --i) {
            buf3[--buf1[s[buf2[i]]]] = buf2[i];
        }

        swap(buf2, buf3);
    }

    buf1.assign(s.size(), 0);
    for (int i = 0; i < static_cast<int>(triple_inds.size()); ++i) {
        buf1[triple_inds[i]] = i + 1;
    }

    // compare suffixes with i1 % 3 != 0 and i2 % 3 == 0
    auto cmp = [&](int i1, int i2) {
        if (s[i1] != s[i2]) {
            return s[i1] < s[i2];
        }
        ++i1;
        ++i2;
        if (i1 % 3 != 0) {
            return buf1[i1] < buf1[i2];
        }
        if (s[i1] != s[i2]) {
            return s[i1] < s[i2];
        }
        ++i1;
        ++i2;
        return buf1[i1] < buf1[i2];
    };

    // merge suf12 and suf0
    buf3.clear();
    auto &res = buf3;
    res.reserve(s.size());
    int i1 = 0;
    int i2 = 0;
    while (i1 < static_cast<int>(triple_inds.size()) || i2 < static_cast<int>(buf2.size())) {
        bool choose1 = false;
        if (i1 == static_cast<int>(triple_inds.size())) {
            choose1 = false;
        } else if (i2 == static_cast<int>(buf2.size())) {
            choose1 = true;
        } else if (cmp(triple_inds[i1], buf2[i2])) {
            choose1 = true;
        } else {
            choose1 = false;
        }

        if (choose1) {
            if (triple_inds[i1] < init_size) {
                res.push_back(triple_inds[i1]);
            }
            ++i1;
        } else {
            if (buf2[i2] < init_size) {
                res.push_back(buf2[i2]);
            }
            ++i2;
        }
    }

    return res;
}

// vector<int> SuffixArray(const string &s, int mask = 0) {
//     if (mask == 0) {
//         array<int, 256> has;
//         has.fill(0);
//         for (unsigned char c : s) {
//             has[c] = 1;
//         }
//         int last = 0;
//         for (int i = 0; i < 256; ++i) {
//             if (has[i]) {
//                 ++last;
//                 has[i] = last;
//             }
//         }

//         vector<int> v(s.size());
//         for (int i = 0; i < v.size(); ++i) {
//             v[i] = has[(unsigned char)s[i]];
//         }
//         return SuffixArray(v, last);
//     } else {
//         int digit_start = 0;
//         int alpha_large_start = (mask & DIGITS) ? 10 : 0;
//         int alpha_small_start = (mask & ALPHA_LARGE) ? alpha_large_start + 26 : alpha_large_start;

//         vector<int> v(s.size());
//         for (int i = 0; i < s.size(); ++i) {
//             if ('0' <= s[i] && s[i] <= '9')
//                 v[i] = s[i] - '0' + digit_start + 1;
//             else if ('A' <= s[i] && s[i] <= 'Z')
//                 v[i] = s[i] - 'A' + alpha_large_start + 1;
//             else
//                 v[i] = s[i] - 'a' + alpha_small_start + 1;
//         }
//         return SuffixArray(v, alpha_small_start + ((mask & ALPHA_SMALL) ? 26 : 0));
//     }
// }

template <typename T>
vector<int> Lcp(const T &s, const vector<int> &suf_array) {
    int n = s.size();
    vector<int> lcp(n - 1);
    vector<int> ind(n);
    for (int i = 0; i < n; ++i) {
        { ind[suf_array[i]] = i; }
    }
    int last = 1;
    for (int i = 0; i < n; ++i) {
        last = max(last - 1, 0);
        int i_cur = i;
        if (ind[i_cur] != 0) {
            int i_prev = suf_array[ind[i_cur] - 1];
            while (i_cur + last < s.size() && i_prev + last < s.size() && s[i_cur + last] == s[i_prev + last]) {
                ++last;
            }
            lcp[ind[i_cur] - 1] = last;
        }
    }
    return lcp;
}

}  // namespace suffix_array

int main() {
    string s;
    getline(cin, s);
    auto f = s + s + '$';
    vector<int> a(f.begin(), f.end());
    auto d = suffix_array::SuffixArray(a, 128);
    vector<int> g(d.size());
    g.resize(copy_if(d.begin(), d.end(), g.begin(), [&](int t) { return t < static_cast<int>(s.size()); }) - g.begin());
    size_t per = 0;
    if (g.size() > 1) {
        if (string(f.begin() + g[0], f.begin() + g[0] + static_cast<int>(s.size())) ==
            string(f.begin() + g[1], f.begin() + g[1] + static_cast<int>(s.size()))) {
            per = abs(g[0] - g[1]);
            g.resize(unique(g.begin(), g.end(), [&](auto q, auto w) { return abs(q - w) % per == 0; }) - g.begin());
        }
    }
    size_t k = scan;
    k -= 1;
    if (k < g.size()) {
        cout << string(f.begin() + g[k], f.begin() + g[k] + static_cast<int>(s.size())) << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}