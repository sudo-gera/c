#include <bits/stdc++.h>
using namespace std;

#define simple_operations(this_type)                                            \
    auto &operator=(this_type&&oth)noexcept{                                    \
        if (&oth!=this){                                                        \
            std::destroy_at(this);                                              \
            std::construct_at(this,std::move(oth));                             \
        }                                                                       \
        return *this;                                                           \
    }                                                                           \
    void Swap(this_type&oth){                                                   \
        auto t=std::move(oth);                                                  \
        oth=std::move(*this);                                                   \
        *this=std::move(t);                                                     \
    }                                                                           \
    auto&operator=(const this_type&oth){                                        \
        if (&oth!=this){                                                        \
            auto t=oth;                                                         \
            Swap(t);                                                            \
        }                                                                       \
        return *this;                                                           \
    }                                                                           \

struct test;

struct test{
    simple_operations(test);
    int val=-1;
    test(int v=0){
        val=v;
        print("stored",val,"at",this)
    }
    test(const test&oth){
        print("copied",oth.val,"from",&oth,"to",this)
        val=oth.val;
    }
    test(test&&oth){
        print("moved",oth.val,"from",&oth,"to",this)
        val=oth.val;
        oth.val=0;
    }
    ~test(){
        print("deleted",val,"from",this)
    }
};


int main(){
    test q=1,w=2;
    ic()
    q=w;
    ic()
    q=3;
    ic()
    w.Swap(q);
    ic()
    q=std::move(w);
    ic()
}
