#include <bits/stdc++.h>
using namespace std;

using llu=decltype(0LLU);

struct pref{
    unordered_map<char,pref> next;
    string* end=nullptr;
    char c=0;
    pref* prev=nullptr;
    pref* suff=nullptr;
    vector<pref*> rsuf;
    llu vis=0;
    // vector<llu> vis;
};

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


int main(){
    string a;
    cin>>a;
    llu n;
    cin>>n;
    vector<string> s(n);
    unordered_map<string,llu> d;
    unordered_map<string,llu> f;
    for (llu w=0;w<n;++w){
        cin>>s[w];
    }
    pref root;
    for (llu q=0;q<n;++q){
        pref* c=&root;
        for (auto w:s[q]){
            c->next[w].c=w;
            c->next[w].prev=c;
            c=&(c->next[w]);
        }
        ic(s[q],"\x1b["+to_string(((long)c)/256%8+30)+"m",c,"\x1b[0m")
        c->end=&s[q];
    }
    vector<pref*> q({&root});
    llu ql=0;
    while (ql<q.size()){
        pref* c=q[ql++];
        if (c->suff){
            continue;
        }
        if (c!=&root){
            pref* t=c->prev;
            if (t==&root){
                c->suff=&root;
                root.rsuf.push_back(c);
            }else{
                t=t->suff;
                while(t and not t->next.count(c->c)){
                    t=t->suff;
                }
                if (t and t->next.count(c->c)){
                    c->suff=&t->next[c->c];
                    t->next[c->c].rsuf.push_back(c);
                }else{
                    c->suff=&root;
                    root.rsuf.push_back(c);
                }
            }
        }
        for (auto&w:c->next){
            q.push_back(&w.second);
        }
    }
    pref* c=&root;
    for (auto&q:a){
        while (c and c->next.count(q)==0){
            c=c->suff;
        }
        if (c and c->next.count(q)){
            c=&c->next[q];
            c->vis+=1;
            if (c->end and not d.count(c->end[0])){
                d[c->end[0]]=distance(&a[0],&q);
            }
        }else{
            c=&root;
        }
    }
    llu count=0;
    llu rcount=0;
    pref* st=&root;
    llu _w=0;
    pref* w=0;
    recursive_loop(st,count,_w,w){
        for (_w=0;_w<st->rsuf.size();++_w){
            w=st->rsuf[_w];
        // for (auto w:st->rsuf){
            call(w,0,0,0);
            count+=rcount;
        }
        rcount=count+st->vis;
        if (st->end){
            f[st->end[0]]+=rcount;
        }
        ret();
    }
    for (llu w=0;w<n;++w){
        if (f[s[w]]){
            cout<<f[s[w]]<<" "<<d[s[w]]+1-s[w].size()<<"\n";
        }else{
            cout<<"0 0\n";
        }
    }
}










