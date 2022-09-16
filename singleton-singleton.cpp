#include <bits/stdc++.h>
struct A;

A* create_a();

struct A {
    int64_t t=0;
    static A* getA(){
        return create_a();
    }
    int64_t time(){
        return t;
    }
};

A* create_a(){
    static A* p=0;
    if (p==0){
        p=new A;
        timeval tv;
        gettimeofday(&tv,nullptr);
        p->t=tv.tv_usec+tv.tv_sec*1000000;
    }
    return p;
}
