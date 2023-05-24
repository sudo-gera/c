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

struct PolyHash {
    unsigned base = 1000;
    vector<unsigned> powers;
    vector<vector<unsigned>> prefixes;
    explicit PolyHash(unsigned l,unsigned n) {
        powers.push_back(1);
        while (powers.size() < l) {
            powers.push_back(powers.back() * base);
        }
        prefixes.resize(n);
    }
    void Add(string& ss, unsigned s) {
        auto& d = prefixes[s] = vector<unsigned>(ss.size() + 1);
        unsigned l = 1;
        while (l <= ss.size()) {
            d[l] = (d[l - 1] * base + ss[l - 1]);
            ++l;
        }
    }
    unsigned F0(unsigned s, unsigned b, unsigned e) {
        auto& d = prefixes[s];
        return d[e] - d[b] * powers[e - b];
    }
    void F1(unsigned&){
    }
    template<typename...T>
    void F1(unsigned&res,unsigned s1,unsigned b1,unsigned e1,T...o){
        res*=(e1-b1);
        res+=F0(s1,b1,e1);
        F1(res,o...);
    }
    template<typename...T>
    unsigned operator()(T...o){
        unsigned res=0;
        F1(res,o...);
        return res;
    }
};

struct Oth {
    array<unsigned, 10> ff;
    array<unsigned, 10> sf;
    unsigned fs;
    unsigned ss;
};

int main() {
    unsigned n=0;
    cin>>n;
    vector<string> a(n);
    vector<string> s(n);
    auto h = PolyHash(20,2*n);
    for (unsigned q = 0; q < n; ++q) {
        auto& w = a[q];
        auto& e = s[q];
        cin>>w;
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
    cout<<(ans.size());
    cout<<('\n');
    for (auto w : ans) {
        cout<<(w.first + 1);
        cout<<(' ');
        cout<<(w.second + 1);
        cout<<('\n');
    }
}

