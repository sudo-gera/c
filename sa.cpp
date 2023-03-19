#include <bits/stdc++.h>
using namespace std;


struct node{
    size_t len=0;
    size_t link=-1;
    map<int,size_t> next;
    bool term=0;
    operator node*(){
        return this;
    }
};

struct st{
    
};

struct sa{
    vector<node> nodes=decltype(nodes)(1);

    size_t last=0;

    void add(size_t c){
        nodes.emplace_back(node{nodes[last].len+1});
        size_t cur=nodes.size()-1;
        size_t p=last;
        while (p!=-1 and not nodes[p].next.count(c)){
            nodes[p].next[c]=cur;
            p=nodes[p].link;
        }
        if (p==-1){
            nodes[cur].link=0;
        }else{
            size_t q=nodes[p].next[c];
            if (nodes[p].len+1==nodes[q].len){
                nodes[cur].link=q;
            }else{
                nodes.emplace_back(node{nodes[p].len+1,nodes[q].link,nodes[q].next});
                size_t clone=nodes.size()-1;
                while (p!=-1 and nodes[p].next[c]==q){
                    nodes[p].next[c]=clone;
                    p=nodes[p].link;
                }
                nodes[q].link=nodes[cur].link=clone;
            }
        }
        last=cur;
    }

    void make_term(){
        size_t p=last;
        while (p!=-1){
            nodes[p].term=1;
            p=nodes[p].link;
        }
    }

};

int main(){
    string s;
    cin>>s;
    sa a;
    for (auto&w:s){
        a.add(w);
    }
    a.make_term();
    for (auto&w:a.nodes){
        print(&w-&a.nodes[0],w.term?"[color=green]":"[color=red]");
        print(&w-&a.nodes[0],"->",w.link,"[color=red]");
        for (auto&e:w.next){
            print(&w-&a.nodes[0],"->",e.second,"[label=",(char)(e.first),"]");
        }
    }
}
