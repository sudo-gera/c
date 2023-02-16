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
#include <memory>
using std::back_inserter, std::list, std::hash, std::reverse;
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::copy_if, std::exit, std::enable_if, std::enable_if;
using std::destroy_at, std::cerr;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n, std::deque;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::tuple_element, std::tuple_size, std::is_same, std::forward;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::unique, std::decay_t, std::is_convertible_v, std::array;

static inline int64_t GetInt() {
    int sign = 1;
    int c = 0;
    unsigned res = 0;
    while (c = getchar_unlocked(), isspace(c)) {
    }
    if (c == '-') {
        sign = -1;
    } else {
        res = c - '0';
    }
    while (c = getchar_unlocked(), isdigit(c)) {
        res *= 10;
        res += c - '0';
    }
    return static_cast<int64_t>(res) * sign;
}

static inline void PutInt(uint64_t out) {
    if (out > (1LLU << 63) - 1) {
        putchar_unlocked('-');
        out = 1 + ~out;
    }
    char data[44];
    char* dend = data;
    while (out) {
        *++dend = static_cast<char>(static_cast<unsigned>('0') + out % 10);
        out /= 10;
    }
    if (dend == data) {
        putchar_unlocked('0');
    }
    for (; dend != data; --dend) {
        putchar_unlocked(*dend);
    }
}

template <typename T = void>
struct Scan {
    template <typename Y = T>
    auto operator()() {
        Y val;
        cin >> val;
        return val;
    }
};

template <typename T>
struct StaticCast {};

template <typename T, typename Y>
auto operator->*(T v, StaticCast<Y>) {
    return static_cast<Y>(v);
}

StaticCast<ssize_t> si;
StaticCast<unsigned> ui;

///////////////////////////////////////////////////end of lib

struct H {
    unsigned base = 1000;
    vector<unsigned> powers;
    vector<vector<unsigned>> data;
    explicit H(unsigned l) {
        if (powers.empty()) {
            powers.push_back(1);
        }
        while (powers.size() < l) {
            powers.push_back(powers.back() * base);
        }
    }
    void Add(string& ss, unsigned s) {
        auto& d = data[s] = vector<unsigned>(ss.size() + 1);
        unsigned l = 1;
        while (l <= ss.size()) {
            d[l] = (d[l - 1] * base + ss[l - 1]);
            ++l;
        }
    }
    unsigned operator()(unsigned s, unsigned b, unsigned e) {
        auto& d = data[s];
        return d[e] - d[b] * powers[e - b];
    }
};

struct Oth {
    array<unsigned, 10> ff;
    array<unsigned, 10> sf;
    unsigned fs;
    unsigned ss;
};

int main() {
    auto h = H(20);
    unsigned n = GetInt();
    vector<string> a(n);
    vector<string> s(n);
    h.data.resize(2 * n);
    for (unsigned q = 0; q < n; ++q) {
        auto& w = a[q];
        auto& e = s[q];
        char data[16];
        fgets(data, 14, stdin);
        auto l = strlen(data);
        w = string(data, data + l - 1);
        e = string(w.rbegin(), w.rend());
        h.Add(w, q);
        h.Add(e, q + n);
    }
    vector<vector<unsigned>> by_hash(n);
    vector<Oth> pref(n);
    for (unsigned w = 0; w < n; ++w) {
        by_hash[h(w, 0, a[w].size()) % n].push_back(w);
        auto& pref_w = pref[w];
        auto u_s = a[w].size();
        for (unsigned e = 0; e < a[w].size(); ++e) {
            if (h(w + n, 0, u_s - e) * h.powers[u_s] + h(w, 0, u_s) ==
                h(w + n, 0, u_s) * h.powers[u_s - e] + h(w, e, u_s)) {
                pref_w.ff[pref_w.fs++] = h(w + n, 0, u_s - e);
            }
        }
        for (unsigned e = 0; e < a[w].size(); ++e) {
            if (h(w, 0, u_s) * h.powers[u_s - e] + h(w + n, e, u_s) ==
                h(w, 0, u_s - e) * h.powers[u_s] + h(w + n, 0, u_s)) {
                pref_w.sf[pref_w.ss++] = h(w + n, e, u_s);
            }
        }
    }
    vector<pair<unsigned, unsigned>> ans({{0U - 1, 0U - 1}});
    for (unsigned q = 0; q < n; ++q) {
        auto& pref_q = pref[q];
        for (unsigned u_w = 0; u_w < pref_q.fs; ++u_w) {
            auto w = pref_q.ff[u_w];
            for (auto e : by_hash[w % n]) {
                ans.emplace_back();
                ans.back() = {e, q};
            }
        }
        for (unsigned u_w = 0; u_w < pref_q.ss; ++u_w) {
            auto w = pref_q.sf[u_w];
            for (auto e : by_hash[w % n]) {
                ans.emplace_back();
                ans.back() = {q, e};
            }
        }
    }
    for (auto& [q, w] : ans) {
        if (q != w) {
            auto t = a[q] + a[w];
            if (t != string(t.rbegin(), t.rend())) {
                q = w = -1;
            }
        } else {
            q = w = -1;
        }
    }
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin() - 1);
    PutInt(ans.size());
    putchar_unlocked('\n');
    for (auto w : ans) {
        PutInt(w.first + 1);
        putchar_unlocked(' ');
        PutInt(w.second + 1);
        putchar_unlocked('\n');
    }
}
