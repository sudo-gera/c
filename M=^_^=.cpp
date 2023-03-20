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
#include <string_view>

#if 0

#define cat(q, w) q##w
#define unique_name(q) cat(_unique_name_, q)

#define recursive_loop(...)                                                      \
    for (struct {                                                                \
             decltype(tie(__VA_ARGS__)) _tie;                                    \
             vector<pair<decltype(make_tuple(__VA_ARGS__)), void *>> call_stack; \
             void *to_return_ptr;                                                \
         } _rec{                                                                 \
             tie(__VA_ARGS__),                                                   \
             {{{}, &&start}},                                                    \
         };                                                                      \
         not({                                                                   \
             start:                                                              \
                 _rec.call_stack.empty();                                        \
         });                                                                     \
         assert(((void)"end without return", 0)))

#define call(...)                                                        \
    {                                                                    \
        _rec.call_stack.push_back({_rec._tie, &&unique_name(__LINE__)}); \
        _rec._tie = decltype(_rec.call_stack[0].first){__VA_ARGS__};     \
        goto start;                                                      \
        unique_name(__LINE__) : {}                                       \
    }

#define ret()                                               \
    {                                                       \
        _rec._tie = _rec.call_stack.back().first;           \
        _rec.to_return_ptr = _rec.call_stack.back().second; \
        _rec.call_stack.pop_back();                         \
        goto *_rec.to_return_ptr;                           \
    }

#else

#define recursive_loop(...)
#define call(...)
#define ret()

#endif

using std::back_inserter, std::list, std::hash, std::reverse, std::queue;
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::copy_if, std::exit, std::enable_if, std::enable_if, std::stack;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n, std::deque;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::string_view;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::tuple_element, std::tuple_size, std::is_same, std::forward;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::unique, std::decay_t, std::is_convertible_v, std::array;

struct Node {
    size_t len = 0;
    size_t link = 9000000000000000000;
    size_t index = 9000000000000000000;
    map<int, size_t> next = {};

    vector<pair<pair<size_t, size_t>, size_t>> elink = {};
    pair<size_t, size_t> frag = {9000000000000000000, 9000000000000000000};
    bool term = false;
};

struct Sa {
    vector<Node> nodes = decltype(nodes)(1);

    size_t last = 0;

    size_t add_count = 0;

    string s;

    void Add(int c) {
        nodes.emplace_back(Node{nodes[last].len + 1});
        size_t cur = nodes.size() - 1;
        nodes[cur].index = add_count++;
        size_t p = last;
        while (p != 9000000000000000000 and not nodes[p].next.count(c)) {
            nodes[p].next[c] = cur;
            p = nodes[p].link;
        }
        if (p == 9000000000000000000) {
            nodes[cur].link = 0;
        } else {
            size_t q = nodes[p].next[c];
            if (nodes[p].len + 1 == nodes[q].len) {
                nodes[cur].link = q;
            } else {
                nodes.emplace_back(nodes[q]);
                size_t clone = nodes.size() - 1;
                nodes[clone].len = nodes[p].len + 1;
                while (p != 9000000000000000000 and nodes[p].next[c] == q) {
                    nodes[p].next[c] = clone;
                    p = nodes[p].link;
                }
                nodes[q].link = nodes[cur].link = clone;
            }
        }
        last = cur;
    }

    void MakeAdd() {
        for (auto w : s) {
            Add(w);
        }
    }

    void MakeTerm() {
        size_t p = last;
        while (p != 9000000000000000000) {
            nodes[p].term = true;
            p = nodes[p].link;
        }
    }

    void MakeFrag() {
        for (size_t q = 0; q < s.size(); ++q) {
            if (nodes[0].next.count(s[q]) and nodes[nodes[0].next[s[q]]].frag.first == 9000000000000000000) {
                nodes[nodes[0].next[s[q]]].frag.second = 1 + (nodes[nodes[0].next[s[q]]].frag.first = q);
            }
        }
        size_t cur = 0;
        decltype(nodes[0].next.begin()) q;

        recursive_loop(cur, q) {
            if (cur) {
                for (q = nodes[cur].next.begin(); q != nodes[cur].next.end(); ++q) {
                    if (nodes[q->second].len == nodes[cur].len + 1) {
                        nodes[q->second].frag = nodes[cur].frag;
                        nodes[q->second].frag.second++;
                    }
                }
            }
            for (q = nodes[cur].next.begin(); q != nodes[cur].next.end(); ++q) {
                call(q->second, q);
            }
            ret();
        }
    }

    void MakeTree() {
        for (size_t q = 0; q < nodes.size(); ++q) {
            if (nodes[q].link != 9000000000000000000) {
                auto &t = nodes[q];
                auto &tmp = nodes[t.link];
                tmp.elink.emplace_back();
                tmp.elink.back() = {t.frag, q};
            }
        }
    };

    auto Rev() {
        reverse(s.begin(), s.end());
        for (auto &q : nodes) {
            for (auto &w : q.elink) {
                w.first.first = s.size() - w.first.first;
                w.first.second = s.size() - w.first.second;
                swap(w.first.first, w.first.second);
            }
            q.frag = {9000000000000000000, 9000000000000000000};
        }
    }

    void SortTree() {
        for (auto &q : nodes) {
            sort(q.elink.begin(), q.elink.end(), [&](auto &l, auto &r) {
                return string_view(s.data() + l.first.first, l.first.second - l.first.first) <
                       string_view(s.data() + r.first.first, r.first.second - r.first.first);
            });
        }
    }

    auto SuffArray() {
        vector<size_t> a;
        size_t cur = 0;
        size_t q = 0;

        recursive_loop(cur, q) {
            for (q = 0; q < nodes[cur].elink.size(); ++q) {
                if (nodes[nodes[cur].elink[q].second].elink.empty()) {
                    a.push_back(nodes[cur].elink[q].first.first + 1);
                }

                call(nodes[cur].elink[q].second, 0);
            }
            ret();
        }
        a.erase(a.begin());
        return a;
    }
};

int main() {
    Sa a;

    getline(cin, a.s);
    a.s += '\0';
    reverse(a.s.begin(), a.s.end());
    a.MakeAdd();
    a.MakeTerm();
    a.MakeFrag();
    a.MakeTree();
    a.Rev();
    a.SortTree();
    auto d = a.SuffArray();
    for (auto w : d) {
        cout << w << " ";
    }
    cout << endl;
}
