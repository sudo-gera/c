#include <bits/stdc++.h>
using namespace std;

using llu=decltype(0LLU);

struct pref{
    unordered_map<char,pref> next;
    bool is_end=0;
    char c=0;
    pref* prev=nullptr;
    pref* suff=nullptr;
};


int main(){
    string a;
    cin>>a;
    llu n;
    cin>>n;
    vector<string> s(n);
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
        c->is_end=1;
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
            }else{
                t=t->suff;
                while(t and not t->next.count(c->c)){
                    t=t->suff;
                }
                if (t and t->next.count(c->c)){
                    c->suff=&t->next[c->c];
                }else{
                    c->suff=&root;
                }
            }
        }
        for (auto&w:c->next){
            q.push_back(&w.second);
        }
    }
    ic(root)
}










