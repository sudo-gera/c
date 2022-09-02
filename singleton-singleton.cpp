#include <bits/stdc++.h>
struct A {
    int64_t t=0;

static A* getA(){
    timeval tv;
    gettimeofday(&tv,nullptr);
    auto r=new A;
    r->t=tv.tv_usec+tv.tv_sec*1000000;
    return r;
}

int64_t time(){
    return t;
}

};