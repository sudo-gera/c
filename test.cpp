#include <bits/stdc++.h>
using namespace std;

auto setup_numbers(){
    static unsigned result=-1;
    if (result==-1){
        set<long> s;
        auto data=(uint8_t*)&result;
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
        vector<long[3]> nums={
            {0,1,1},
            {1,0,0},
            {2,3,2},
        };
        for (long w=0;w<4;++w){
            for (auto [q,e,r]:nums){
                if (iters[q].next[w]==iters[e]){
                    data[r]=w;
                }
            }
        }
        cout<<data[0]<<" "<<data[1]<<" "<<data[2]<<endl;












        // long cs[4]={0,0,0,0};
        // for (auto w=s.begin();w!=s.end();++w){
        //     auto y=((long*&)(w));
        //     for (auto e=0;e<4;++e){
        //         for (auto q=s.begin();q!=s.end();++q){
        //             auto t=((long*&)(q));
        //             if (y[e]==(long)(t)){
        //                 cs[e]+=1;
        //             }
        //         }
        //     }
        // }
        // long parent=-1;
        // for (auto e=0;e<4;++e){
        //     if (cs[e]==s.size()-1){
        //         parent=e;
        //     }
        // }
        // long left=-1;
        // {
        //     auto iter=s.begin();
        //     auto y=((long*&)(iter));
        //     ++iter;
        //     auto t=((long*&)(iter));
        //     for (auto e=0;e<4;++e){
        //         if (t[e]==(long)y){
        //             left=e;
        //         }
        //     }
        // }
        // long right=-1;
        // {
        //     auto iter=s.end();
        //     --iter;
        //     auto y=((long*&)(iter));
        //     --iter;
        //     auto t=((long*&)(iter));
        //     for (auto e=0;e<4;++e){
        //         if (t[e]==(long)y){
        //             right=e;
        //         }
        //     }
        // }
        // ((uint8_t*)(&result))[0]=left;
        // ((uint8_t*)(&result))[1]=parent;
        // ((uint8_t*)(&result))[2]=right;
    }
    return result;
}

auto get(auto q){
    auto left=q;
    auto parent=q;
    auto right=q;
    uint8_t result[4];
    (unsigned&)result=setup_numbers();
    (long&)(left)=((long*&)q)[result[0]];
    (long&)(parent)=((long*&)q)[result[1]];
    (long&)(right)=((long*&)q)[result[2]];
    pair t(left,right);
    pair y(parent,t);
    return y;
}

int main(){
    // set<long> s;
    // for (long w=0;w<64;++w){
    //     s.insert(w);
    // }
    setup_numbers();

}













