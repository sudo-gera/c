#include <vector>
#include <ctype.h>
#include <stdexcept>
#include <stdint.h>
#include <iostream>
#include <string>
#include <deque>
#include <cassert>
#include <random>
#include <algorithm>

size_t locs=0;
size_t vals=0;

#include "deque.h"

template<typename T>
void check(T q,T e){
    std::vector<T> a;
    for (auto w=q;w!=e;++w){
        a.push_back(w);
    }
    a.push_back(e);
    for (size_t w=0;w<a.size();++w){
        for (size_t e=0;e<a.size();++e){
            long d=long(w)-long(e);
            assert(a[w]-a[e]==d);
            assert(w>=e or  a[w]<a[e]);
            assert(w<=e or  a[w]>a[e]);
            assert(w==e or a[w]!=a[e]);
            assert(w>e  or a[w]<=a[e]);
            assert(w<e  or a[w]>=a[e]);
            assert(w!=e or a[w]==a[e]);
            assert(a[w]+(-d)==a[e]);
            assert(a[w]-(d)==a[e]);
        }
    }
    auto s=a;
    s.clear();
    for (auto w=e;w!=q;--w){
        s.push_back(w);
    }
    s.push_back(q);
    reverse(s.begin(),s.end());
    assert(a==s);
}


struct item{
    size_t val;
    item(size_t val):
        val(val)
    {
        vals+=val;
        locs+=size_t(this);
    }
    item(const item&oth):
        val(oth.val)
    {
        vals+=val;
        locs+=size_t(this);
    }
    item(item&&oth):
        val(oth.val)
    {
        vals+=val;
        locs+=size_t(this);
        std::swap(val,oth.val);
    }
    auto&operator=(const item&oth){
        std::destroy_at(this);
        new(this)item(std::forward<const item>(oth));
        return *this;
    }
    auto&operator=(item&&oth){
        std::destroy_at(this);
        new(this)item(std::forward<item>(oth));
        return *this;
    }
    ~item(){
        locs-=size_t(this);
        vals-=val;
    }
    operator size_t(){
        return val;
    }
};


int main(){
    size_t seed=1299881216;

    // seed = std::random_device()();

    std::cin>>seed;

    printf("%zu\n",seed);

    {
        std::vector<Deque<item>> a_vec(1);
        std::vector<std::deque<size_t>> s_vec(1);
        Deque<item>* a=a_vec.data();
        std::deque<size_t>* s=s_vec.data();
        size_t q,w,i,v,e;
        std::deque<size_t> tmp;
        std::mt19937_64 generator(seed);
        std::uniform_int_distribution range(0LLU,-1LLU);
        auto rand=[&](){return range(generator);};
        for (q=0;q<512;++q){
            assert(&(*a)-&a_vec[0]==&(*s)-&s_vec[0]);
            assert((*a).size()==(*s).size());
            assert(a_vec.size()==s_vec.size());
            w=rand()%14;
            i=rand();
            v=rand();
            printf("%zu %zu %zu %zu %zu %zu\n",q,w,i,v,&(*a)-&a_vec[0],a_vec.size());
            if (w==0){
                i%=((*a).size()+1);
                (*a).push_back(v);
                (*s).push_back(v);
            }
            if (w==1){
                i%=((*a).size()+1);
                (*a).push_front(v);
                (*s).push_front(v);
            }
            if (w==2){
                i%=((*a).size()+1);
                (*a).insert(i+(*a).begin(),v);
                (*s).insert(i+(*s).begin(),v);
            }
            if (w==3 and (*a).size()){
                i%=((*a).size()+1);
                (*a).pop_back();
                (*s).pop_back();
            }
            if (w==4 and (*a).size()){
                i%=((*a).size()+1);
                (*a).pop_front();
                (*s).pop_front();
            }
            if (w==5 and (*a).size()){
                i%=(*a).size();
                (*a).erase((*a).begin()+i);
                (*s).erase((*s).begin()+i);
            }
            if (w==6){
                i%=a_vec.size();
                a=&a_vec[i];
                s=&s_vec[i];
            }
            if (w==7){
                i%=(a_vec.size()+1);
                a_vec.emplace_back();
                s_vec.emplace_back();
                a=&a_vec[i];
                s=&s_vec[i];
            }
            if (w==8){
                i%=(a_vec.size()+1);
                a_vec.emplace_back((*a));
                s_vec.emplace_back((*s));
                a=&a_vec[i];
                s=&s_vec[i];
            }
            if (w==9){
                i%=(a_vec.size()+1);
                a_vec.emplace_back(i,v);
                s_vec.emplace_back(i,v);
                a=&a_vec[i];
                s=&s_vec[i];
            }
            if (w==10){
                i%=(a_vec.size());
                v%=(a_vec.size());
                a_vec[i]=a_vec[v];
                s_vec[i]=s_vec[v];
                a=&a_vec[i];
                s=&s_vec[i];
            }
            if (w==11){
                i%=(a_vec.size());
                v%=(a_vec.size());
                a_vec[i]=std::move(a_vec[v]);
                tmp=std::move(s_vec[v]);
                s_vec[i]=std::move(tmp);
                s_vec[v].clear();
                for (auto&w:a_vec[v]){
                    s_vec[v].push_back(w);
                }
                a=&a_vec[i];
                s=&s_vec[i];
            }
            if (w==12){
                std::reverse((*a).begin(),(*a).end());
                std::reverse((*s).begin(),(*s).end());
            }
            if (w==13 and (*a).size()){
                i%=((*a).size());
                assert(std::to_string((*a)[i])==std::to_string((*s)[i]));
            }
            assert(a_vec.size()==s_vec.size());
            assert((*a).size()==(*s).size());
            for (e=0;e<(*a).size();++e){
                assert((*a)[e]==(*s)[e]);
            }
            assert((*a).end()-(*a).begin()==(ssize_t)(*a).size());
            check((*a).begin(),(*a).end());
        }
    }
    assert(locs==0);
    assert(vals==0);
    return 0;
}

