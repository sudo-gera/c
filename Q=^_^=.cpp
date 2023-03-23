#include <bits/stdc++.h>
using namespace std;

#define cat(q, w) q##w
#define unique_name(q) cat(_unique_name_, q)

#define recursive_loop(...)                                                        \
    for (                                                                          \
        struct {                                                                   \
            decltype(tie(__VA_ARGS__)) _tie;                                       \
            vector<pair<decltype(make_tuple(__VA_ARGS__)), void *>> call_stack;    \
            void *to_return_ptr;                                                   \
        } _rec{                                                                    \
            tie(__VA_ARGS__),                                                      \
            {{{}, &&start}},                                                       \
        };                                                                         \
        not({                                                                      \
            start:                                                                 \
            _rec.call_stack.empty();                                               \
        });                                                                        \
        assert(((void)"end without return", 0))                                    \
    )

#define call(...)                                                                  \
    {                                                                              \
        _rec.call_stack.push_back({_rec._tie, &&unique_name(__LINE__)});           \
        _rec._tie = decltype(_rec.call_stack[0].first){__VA_ARGS__};               \
        goto start;                                                                \
        unique_name(__LINE__) : {}                                                 \
    }

#define ret()                                                                      \
    {                                                                              \
        _rec._tie = _rec.call_stack.back().first;                                  \
        _rec.to_return_ptr = _rec.call_stack.back().second;                        \
        _rec.call_stack.pop_back();                                                \
        goto *_rec.to_return_ptr;                                                  \
    }

#define none 9000000000000000000

struct node{
    size_t len=0;
    size_t link=none;
    size_t index=none;
    map<int,size_t> next;
    // map<pair<size_t,size_t>,size_t> elink;
    vector<pair<pair<size_t,size_t>,size_t>> elink;
    pair<size_t,size_t> frag={none,none};
    bool term=0;
    operator node*(){
        return this;
    }
};

struct sa{
    vector<node> nodes=decltype(nodes)(1);

    size_t last=0;

    size_t add_count=0;

    string s;

    void add(int c){
        nodes.emplace_back(node{nodes[last].len+1});
        size_t cur=nodes.size()-1;
        nodes[cur].index=add_count++;
        size_t p=last;
        while (p!=none and not nodes[p].next.count(c)){
            nodes[p].next[c]=cur;
            p=nodes[p].link;
        }
        if (p==none){
            nodes[cur].link=0;
        }else{
            size_t q=nodes[p].next[c];
            if (nodes[p].len+1==nodes[q].len){
                nodes[cur].link=q;
            }else{
                nodes.emplace_back(nodes[q]);
                size_t clone=nodes.size()-1;
                nodes[clone].len=nodes[p].len+1;
                while (p!=none and nodes[p].next[c]==q){
                    nodes[p].next[c]=clone;
                    p=nodes[p].link;
                }
                nodes[q].link=nodes[cur].link=clone;
            }
        }
        last=cur;
    }

    void make_add(){
        for (auto w:s){
            add(w);
        }
    }

    void make_term(){
        size_t p=last;
        while (p!=none){
            nodes[p].term=1;
            p=nodes[p].link;
        }
    }

    void make_frag(){
        for (size_t q=0;q<s.size();++q){
            if (nodes[0].next.count(s[q]) and nodes[nodes[0].next[s[q]]].frag.first==none){
                nodes[nodes[0].next[s[q]]].frag.second = 1+(nodes[nodes[0].next[s[q]]].frag.first=q);
            }
        }
        size_t cur=0;
        decltype(nodes[0].next.begin()) q;
        recursive_loop(cur,q){
            if (cur){
                for (q=nodes[cur].next.begin();q!=nodes[cur].next.end();++q){
                    if (nodes[q->second].len==nodes[cur].len+1){
                        nodes[q->second].frag=nodes[cur].frag;
                        nodes[q->second].frag.second++;
                    }
                }
            }
            for (q=nodes[cur].next.begin();q!=nodes[cur].next.end();++q){
                call(q->second,q);
            }
            ret();
        }
    }

    void make_tree(){
        for (size_t q=0;q<nodes.size();++q){
            if (nodes[q].link!=none){
                auto&t=nodes[q];
                auto&tmp=nodes[t.link];
                tmp.elink.push_back({t.frag,q});
            }
        }
    };

    auto rev(){
        reverse(s.begin(),s.end());
        for (auto&q:nodes){
            for (auto&w:q.elink){
                w.first.first=s.size()-w.first.first;
                w.first.second=s.size()-w.first.second;
                swap(w.first.first,w.first.second);
            }
            q.frag={none,none};
            // q.index=none;
            // q.len=none;
            // q.link=none;
            // q.next.clear();
            // q.term=0;
        }
    }

    void sort_tree(){
        for (auto&q:nodes){
            sort(q.elink.begin(),q.elink.end(),[&](auto&l,auto&r){
                return
                    string_view(s.data()+l.first.first,l.first.second-l.first.first)<
                    string_view(s.data()+r.first.first,r.first.second-r.first.first);
            });
        }
    }

    auto suff_array(){
        vector<size_t> a;
        size_t cur=0;
        size_t q=0;
        recursive_loop(cur,q){
            for (q=0;q<nodes[cur].elink.size();++q){
                if (nodes[nodes[cur].elink[q].second].elink.empty()){
                    a.push_back(nodes[cur].elink[q].first.first+1);
                }
                // a.push_back(nodes[cur].elink[q].first.first);
                call(nodes[cur].elink[q].second,0);
            }
            ret();
        }
        return a;
    }


    // auto suff_array(){
    //     vector<size_t> a;
    //     size_t cur=0;
    //     decltype(nodes[0].elink.begin()) q;
    //     vector<decltype(nodes[0].elink.begin())> d;
    //     size_t l=0;
    //     size_t e=0;
    //     recursive_loop(cur,q,l,d,e){
    //         ic(cur,l,nodes[cur].term)
    //         if (nodes[cur].term){
    //             a.push_back(l);
    //         }
    //         for (q=nodes[cur].elink.begin();q!=nodes[cur].elink.end();++q){
    //             d.push_back(q);
    //         }
    //         sort(d.begin(),d.end(),[&](auto&l,auto&r){
    //             return string(s.rend()-l->first.second,s.rend()-l->first.first)<string(s.rend()-r->first.second,s.rend()-r->first.first);
    //             // return s[l->first.second-1]<s[r->first.second-1];
    //         });
    //         for (e=0;e<d.size();++e){
    //             ic(*d[e],l)
    //             call(d[e]->second,q,l+d[e]->first.second-d[e]->first.first,{},0);
    //         }
    //         ret();
    //     }
    //     return a;
    // }
};

int main(){
    sa a;
    // cin>>a.s;
    getline(cin,a.s);
    a.s+='\0';
    reverse(a.s.begin(),a.s.end());
    a.make_add();
    a.make_term();
    a.make_frag();
    a.make_tree();
    a.rev();
    a.sort_tree();
    ic(a.suff_array())


    // cout<<"digraph G {"<<endl;
    // for (auto&w:a.nodes){
    //     cout<<&w-&a.nodes[0]<<"[color="<<(w.term?"green":"red")<<",label="
    //         <<"_"<<&w-&a.nodes[0]
    //         <<"_"<<w.len
    //         <<"_"<<w.index
    //         // <<"_"<<w.frag.first
    //         // <<"_"<<w.frag.second
    //             <<"]"<<endl;
    //     cout<<&w-&a.nodes[0]<<"->"<<w.link<<"[color=red]"<<endl;
    //     for (auto&e:w.next){
    //         cout<<&w-&a.nodes[0]<<"->"<<e.second<<"[label="<<(char)(e.first)<<"]"<<endl;
    //     }
    //     for (auto&e:w.elink){
    //         cout<<&w-&a.nodes[0]<<"->"<<e.second<<"[color=blue,label="
    //             <<"_"<<e.first.first
    //             <<"_"<<e.first.second
    //                 <<"]"<<endl;
    //     }
    // }
    // cout<<"}"<<endl;


    // size_t cur=0;
    // size_t q=0;
    // size_t l=0;
    // recursive_loop(cur,q,l){
    //     for (q=0;q<a.nodes[cur].elink.size();++q){
    //         // ic(a.nodes[cur].elink[q],l)
    //         cout<<"\x1b["<<l+1<<"C"<<string(a.s.begin()+a.nodes[cur].elink[q].first.first,a.s.begin()+a.nodes[cur].elink[q].first.second)<<endl;
    //         // cout<<string(a.s.begin()+a.nodes[cur].elink[q].first.first,a.s.begin()+a.nodes[cur].elink[q].first.second)<<endl;
    //         call(a.nodes[cur].elink[q].second,0,l+a.nodes[cur].elink[q].first.second-a.nodes[cur].elink[q].first.first);
    //         // call(a.nodes[cur].elink[q].second,0,0);
    //     }
    //     ret();
    // }
}
