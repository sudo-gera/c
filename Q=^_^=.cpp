// #include <bits/stdc++.h>
// using namespace std;

// #define cat(q, w) q##w
// #define unique_name(q) cat(_unique_name_, q)

// #define recursive_loop(...)                                                        \
//     for (                                                                          \
//         struct {                                                                   \
//             decltype(tie(__VA_ARGS__)) _tie;                                       \
//             vector<pair<decltype(make_tuple(__VA_ARGS__)), void *>> call_stack;    \
//             void *to_return_ptr;                                                   \
//         } _rec{                                                                    \
//             tie(__VA_ARGS__),                                                      \
//             {{{}, &&start}},                                                       \
//         };                                                                         \
//         not({                                                                      \
//             start:                                                                 \
//             _rec.call_stack.empty();                                               \
//         });                                                                        \
//         assert(((void)"end without return", 0))                                    \
//     )

// #define call(...)                                                                  \
//     {                                                                              \
//         _rec.call_stack.push_back({_rec._tie, &&unique_name(__LINE__)});           \
//         _rec._tie = decltype(_rec.call_stack[0].first){__VA_ARGS__};               \
//         goto start;                                                                \
//         unique_name(__LINE__) : {}                                                 \
//     }

// #define ret()                                                                      \
//     {                                                                              \
//         _rec._tie = _rec.call_stack.back().first;                                  \
//         _rec.to_return_ptr = _rec.call_stack.back().second;                        \
//         _rec.call_stack.pop_back();                                                \
//         goto *_rec.to_return_ptr;                                                  \
//     }

// #define none 9000000000000000000

// struct node{
//     size_t len=0;
//     size_t link=none;
//     size_t index=none;
//     map<int,size_t> next;
//     // map<pair<size_t,size_t>,size_t> elink;
//     vector<pair<pair<size_t,size_t>,size_t>> elink;
//     pair<size_t,size_t> frag={none,none};
//     bool term=0;
//     operator node*(){
//         return this;
//     }
// };

// struct sa{
//     vector<node> nodes=decltype(nodes)(1);

//     size_t last=0;

//     size_t add_count=0;

//     string s;

//     void add(int c){
//         nodes.emplace_back(node{nodes[last].len+1});
//         size_t cur=nodes.size()-1;
//         nodes[cur].index=add_count++;
//         size_t p=last;
//         while (p!=none and not nodes[p].next.count(c)){
//             nodes[p].next[c]=cur;
//             p=nodes[p].link;
//         }
//         if (p==none){
//             nodes[cur].link=0;
//         }else{
//             size_t q=nodes[p].next[c];
//             if (nodes[p].len+1==nodes[q].len){
//                 nodes[cur].link=q;
//             }else{
//                 nodes.emplace_back(nodes[q]);
//                 size_t clone=nodes.size()-1;
//                 nodes[clone].len=nodes[p].len+1;
//                 while (p!=none and nodes[p].next[c]==q){
//                     nodes[p].next[c]=clone;
//                     p=nodes[p].link;
//                 }
//                 nodes[q].link=nodes[cur].link=clone;
//             }
//         }
//         last=cur;
//     }

//     void make_add(){
//         for (auto w:s){
//             add(w);
//         }
//     }

//     void make_term(){
//         size_t p=last;
//         while (p!=none){
//             nodes[p].term=1;
//             p=nodes[p].link;
//         }
//     }

//     void make_frag(){
//         for (size_t q=0;q<s.size();++q){
//             if (nodes[0].next.count(s[q]) and nodes[nodes[0].next[s[q]]].frag.first==none){
//                 nodes[nodes[0].next[s[q]]].frag.second = 1+(nodes[nodes[0].next[s[q]]].frag.first=q);
//             }
//         }
//         size_t cur=0;
//         decltype(nodes[0].next.begin()) q;
//         recursive_loop(cur,q){
//             if (cur){
//                 for (q=nodes[cur].next.begin();q!=nodes[cur].next.end();++q){
//                     if (nodes[q->second].len==nodes[cur].len+1){
//                         nodes[q->second].frag=nodes[cur].frag;
//                         nodes[q->second].frag.second++;
//                     }
//                 }
//             }
//             for (q=nodes[cur].next.begin();q!=nodes[cur].next.end();++q){
//                 call(q->second,q);
//             }
//             ret();
//         }
//     }

//     void make_tree(){
//         for (size_t q=0;q<nodes.size();++q){
//             if (nodes[q].link!=none){
//                 auto&t=nodes[q];
//                 auto&tmp=nodes[t.link];
//                 tmp.elink.push_back({t.frag,q});
//             }
//         }
//     };

//     auto rev(){
//         reverse(s.begin(),s.end());
//         for (auto&q:nodes){
//             for (auto&w:q.elink){
//                 w.first.first=s.size()-w.first.first;
//                 w.first.second=s.size()-w.first.second;
//                 swap(w.first.first,w.first.second);
//             }
//             q.frag={none,none};
//             // q.index=none;
//             // q.len=none;
//             // q.link=none;
//             // q.next.clear();
//             // q.term=0;
//         }
//     }

//     void sort_tree(){
//         for (auto&q:nodes){
//             sort(q.elink.begin(),q.elink.end(),[&](auto&l,auto&r){
//                 return
//                     string_view(s.data()+l.first.first,l.first.second-l.first.first)<
//                     string_view(s.data()+r.first.first,r.first.second-r.first.first);
//             });
//         }
//     }

//     auto suff_array(){
//         vector<size_t> a;
//         size_t cur=0;
//         size_t q=0;
//         recursive_loop(cur,q){
//             for (q=0;q<nodes[cur].elink.size();++q){
//                 if (nodes[nodes[cur].elink[q].second].elink.empty()){
//                     a.push_back(nodes[cur].elink[q].first.first+1);
//                 }
//                 // a.push_back(nodes[cur].elink[q].first.first);
//                 call(nodes[cur].elink[q].second,0);
//             }
//             ret();
//         }
//         return a;
//     }


//     // auto suff_array(){
//     //     vector<size_t> a;
//     //     size_t cur=0;
//     //     decltype(nodes[0].elink.begin()) q;
//     //     vector<decltype(nodes[0].elink.begin())> d;
//     //     size_t l=0;
//     //     size_t e=0;
//     //     recursive_loop(cur,q,l,d,e){
//     //         ic(cur,l,nodes[cur].term)
//     //         if (nodes[cur].term){
//     //             a.push_back(l);
//     //         }
//     //         for (q=nodes[cur].elink.begin();q!=nodes[cur].elink.end();++q){
//     //             d.push_back(q);
//     //         }
//     //         sort(d.begin(),d.end(),[&](auto&l,auto&r){
//     //             return string(s.rend()-l->first.second,s.rend()-l->first.first)<string(s.rend()-r->first.second,s.rend()-r->first.first);
//     //             // return s[l->first.second-1]<s[r->first.second-1];
//     //         });
//     //         for (e=0;e<d.size();++e){
//     //             ic(*d[e],l)
//     //             call(d[e]->second,q,l+d[e]->first.second-d[e]->first.first,{},0);
//     //         }
//     //         ret();
//     //     }
//     //     return a;
//     // }
// };

// int main(){
//     sa a;
//     // cin>>a.s;
//     getline(cin,a.s);
//     a.s+='_';
//     reverse(a.s.begin(),a.s.end());
//     a.make_add();
//     a.make_term();
//     a.make_frag();
//     a.make_tree();
//     a.rev();
//     a.sort_tree();
//     // ic(a.suff_array())


//     cout<<"digraph G {"<<endl;
//     for (auto&w:a.nodes){
//         cout<<&w-&a.nodes[0]<<"[color="<<(w.term?"green":"red")<<",label="
//             <<"_"<<&w-&a.nodes[0]
//             <<"_"<<w.len
//             <<"_"<<w.index
//             // <<"_"<<w.frag.first
//             // <<"_"<<w.frag.second
//                 <<"]"<<endl;
//         cout<<&w-&a.nodes[0]<<"->"<<w.link<<"[color=red]"<<endl;
//         for (auto&e:w.next){
//             cout<<&w-&a.nodes[0]<<"->"<<e.second<<"[label="<<(char)(e.first)<<"]"<<endl;
//         }
//         for (auto&e:w.elink){
//             cout<<&w-&a.nodes[0]<<"->"<<e.second<<"[color=blue,label="
//                 <<"_"<<e.first.first
//                 <<"_"<<e.first.second
//                     <<"]"<<endl;
//         }
//     }
//     cout<<"}"<<endl;


//     // size_t cur=0;
//     // size_t q=0;
//     // size_t l=0;
//     // recursive_loop(cur,q,l){
//     //     for (q=0;q<a.nodes[cur].elink.size();++q){
//     //         // ic(a.nodes[cur].elink[q],l)
//     //         cout<<"\x1b["<<l+1<<"C"<<string(a.s.begin()+a.nodes[cur].elink[q].first.first,a.s.begin()+a.nodes[cur].elink[q].first.second)<<endl;
//     //         // cout<<string(a.s.begin()+a.nodes[cur].elink[q].first.first,a.s.begin()+a.nodes[cur].elink[q].first.second)<<endl;
//     //         call(a.nodes[cur].elink[q].second,0,l+a.nodes[cur].elink[q].first.second-a.nodes[cur].elink[q].first.first);
//     //         // call(a.nodes[cur].elink[q].second,0,0);
//     //     }
//     //     ret();
//     // }
// }


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

// source: https://neerc.ifmo.ru/wiki/index.php?title=%D0%A1%D0%B6%D0%B0%D1%82%D0%BE%D0%B5_%D1%81%D1%83%D1%84%D1%84%D0%B8%D0%BA%D1%81%D0%BD%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE

struct Node{
    Node*parent=nullptr;
    size_t length=0;
    vector<Node*> children;
    size_t depth=0;
    Node(Node* p,size_t l):
        parent(p),
        length(l),
        depth(p?p->depth+1:0){}
};

Node*addNextSuffix(Node*previous, size_t length, size_t lcp){
   if (previous->depth == 0 or previous->depth == lcp){           // Добавляем к сыновьям текущей вершины 
      auto added = new Node(previous, length);
      previous->children.push_back(added);
      return added;
   }else{
      if (previous->parent->depth < lcp){                           // Нужно разрезать ребро 
         auto inserted = new Node(previous->parent, lcp);
         previous->parent->children.pop_back();
         previous->parent->children.push_back(inserted);
         inserted->children.push_back(previous);
         previous->parent = inserted;
      }
      return addNextSuffix(previous->parent, length, lcp);
   }
}
Node*buildSuffixTree(vector<int>& suf, vector<int>& lcp, size_t length){
   auto root = new Node(nullptr, 0);
   auto previous = root;
   for (size_t i = 0;i<length;++i){
      previous = addNextSuffix(previous, length - suf[i], lcp[i]);
   }
   return root;
}

void walk(Node* root){
    for (auto q:root->children){
        cout<<root<<"->"<<q<<endl;
        walk(q);
    }
}

int main() {
    string s;
    getline(cin, s);
    s+='_';
    vector<int> a(s.begin(), s.end());
    auto d = suffix_array::SuffixArray(a, 128);
    auto e = suffix_array::Lcp(a, d);
    e.insert(e.begin(),0);
    // ic(d)
    // ic(e)
    auto root=buildSuffixTree(d,e,d.size());
    walk(root);
}