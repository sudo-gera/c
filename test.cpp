#include <bits/stdc++.h>
using namespace std;

auto tree_goto(auto q){
    static unsigned result=-1;
    auto data=(uint8_t*)&result;
    if (result==-1){
        set<long> s;
        for (long w=0;w<64;++w){
            s.insert(w);
        }
        union{
            long*next;
            long self;
            decltype(s.begin()) iter;
        } iters[4]={0,0,0,0};
        iters[0].iter=s.begin();
        iters[1].iter=next(s.begin());
        iters[2].iter=next(s.end(),-2);
        iters[3].iter=next(s.end(),-1);
        vector<tuple<long,long,long>>nums={
            {0,1,1},
            {1,0,0},
            {2,3,2},
        };
        for (long w=0;w<4;++w){
            for (auto [q,e,r]:nums){
                if (iters[q].next[w]==iters[e].self){
                    data[r]=w;
                }
            }
        }
    }
    struct{
        decltype(q) left,parent,right;
    }r{
        (decltype(q)&)(((long*&)q)[data[0]]),
        (decltype(q)&)(((long*&)q)[data[1]]),
        (decltype(q)&)(((long*&)q)[data[2]]),
    };
    return r;
}

// template<typename T>
// struct iter{
//     T iter;
//     long offset=0;
//     void add(long n){
        
//     }
// };


// auto get(auto q){
//     auto left=q;
//     auto parent=q;
//     auto right=q;
//     uint8_t result[4];
//     (unsigned&)result=setup_numbers();
//     (long&)(left)=((long*&)q)[result[0]];
//     (long&)(parent)=((long*&)q)[result[1]];
//     (long&)(right)=((long*&)q)[result[2]];
//     pair t(left,right);
//     pair y(parent,t);
//     return y;
// }

int main(){
    // set<long> s;
    // for (long w=0;w<16;++w){
    //     s.insert(w);
    // }
    // for (auto w=s.begin();w!=s.end()?++w,1:0;){
    //     {
    //         auto e=tree_goto(w).left;
    //         cout<<(w!=s.end()?*w:0)<<" -> "<<(e!=s.end()?*e:0);
    //         cout<<"[color=red]"<<endl;
    //     }
    //     {
    //         auto e=tree_goto(w).parent;
    //         swap(w,e);
    //         cout<<(w?*w:0)<<" -> "<<(e?*e:0);
    //         cout<<"[color=green]"<<endl;
    //         swap(w,e);
    //     }
    //     {
    //         auto e=tree_goto(w).right;
    //         cout<<(w?*w:0)<<" -> "<<(e?*e:0);
    //         cout<<"[color=blue]"<<endl;
    //     }
    // }
    int r=4;
    int*t=&r;
    (uint64_t&)(t)^=1LLU<<55;
    cout<<*t<<endl;
}













