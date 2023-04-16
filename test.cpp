<<<<<<< HEAD
//#include <bits/stdc++.h>
using namespace std;

int main(){

}
=======
#include "test.hpp"

#if 0

template<size_t n>
struct sized{
  char data[n];
};




#include <string>
#include <deque>
#include <cassert>

size_t locs=0;
size_t vals=0;

size_t until_throw=-1;

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
                // ic(w,e)
                // ic(a[w]-a[e])
                // ic(a[w].elem->pos,a[e].elem->pos)
                // ic(a[w].d->items,a[e].d->items)
                // ic(a[w].d->begin_,a[e].d->begin_)
                // ic(a[w].d->end_,a[e].d->end_)
                // assert(a[w]-a[e]==d);
                // assert(w>=e or  a[w]<a[e]);
                // assert(w<=e or  a[w]>a[e]);
                assert(w==e or a[w]!=a[e]);
                // assert(w>e  or a[w]<=a[e]);
                // assert(w<e  or a[w]>=a[e]);
                assert(w!=e or a[w]==a[e]);
                // assert(a[w]+(-d)==a[e]);
                // assert(a[w]-(d)==a[e]);
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
            // ic(size_t(this))
            vals+=val;
            locs+=size_t(this);
            if (until_throw==0){throw std::exception();}
            until_throw-=1;
        }
        item(const item&oth):
            val(oth.val)
        {
            // ic(size_t(this))
            vals+=val;
            locs+=size_t(this);
            if (until_throw==0){throw std::exception();}
            until_throw-=1;
        }
        item(item&&oth):
            val(oth.val)
        {
            // ic(size_t(this))
            vals+=val;
            locs+=size_t(this);
            if (until_throw==0){throw std::exception();}
            until_throw-=1;
            std::swap(val,oth.val);
        }
        auto&operator=(const item&oth){
            this->~item();
            new(this)item(std::forward<const item>(oth));
            return *this;
        }
        auto&operator=(item&&oth){
            this->~item();
            new(this)item(std::forward<const item>(oth));
            return *this;
        }
        ~item(){
            // ic(size_t(this))
            locs-=size_t(this);
            until_throw+=1;
            // if (until_throw==0){throw std::exception();}
            vals-=val;
        }
        operator size_t()const{
            return val;
        }
    };


    int main(){
        // auto storage=make_unique<StackStorage<9999999>>();
        // StackAllocator<item,decay_t<decltype(*storage)>::len> alloc(*storage);
        // srand(0);
        size_t seed=869704335;
        seed=random_device()();
        printf("%zu\n",seed);
        srand(seed);
        vector<size_t> rands(999999);
        generate_n(rands.begin(),rands.size(),rand);
        auto rptr=rands.begin();
        auto rand=[&]{return *rptr++;};
        {
            std::vector<List<item>> a_vec;
            a_vec.emplace_back();
            std::vector<std::list<size_t>> s_vec;
            s_vec.emplace_back();
            auto* a_ptr=a_vec.data();
            auto* s_ptr=s_vec.data();
            void* cret=&&_2;
            size_t q,w,i,v;
            auto e=a_vec[0].begin();
            auto r=s_vec[0].begin();
        _1:
            auto&a=*a_ptr;
            auto&s=*s_ptr;
            goto *cret;
        _2:
            for (q=0;q<1024;++q){
                assert(&a-&a_vec[0]==&s-&s_vec[0]);
                assert(a.size()==s.size());
                assert(a_vec.size()==s_vec.size());
                w=rand()%20;
                i=rand();
                v=rand();
                ic(q,w,i,v,&a-&a_vec[0],a_vec.size())
                if (w==0){
                    // i%=(a.size()+1);
                    // a.insert_back(i,v);
                    // s.insert(s.begin()+i,v);
                }
                if (w==1){
                    i%=(a.size()+1);
                    // a.insert_front(i,v);
                    // s.insert(s.begin()+i,v);
                }
                if (w==2){
                    i%=(a.size()+1);
                    a.insert(next(a.begin(),i),v);
                    s.insert(next(s.begin(),i),v);
                }
                if (w==3){
                }
                if (w==4){
                    i%=(a.size()+1);
                    // a.insert(i+a.begin(),v);
                    // s.insert(i+s.begin(),v);
                }
                if (w==5){
                    a.push_back(v);
                    s.push_back(v);
                }
                if (w==6){
                    i%=(a.size()+1);
                    a.push_front(v);
                    s.push_front(v);
                }
                if (w==7 and a.size()){
                    a.pop_back();
                    s.pop_back();
                }
                if (w==8 and a.size()){
                    i%=(a.size()+1);
                    a.pop_front();
                    s.pop_front();
                }
                if (w==9 and a.size()){
                    i%=a.size();
                    auto t=next(a.begin(),i);
                    // assert(distance(a.begin(),a.find(*t))==i);
                    // assert(distance(a.find(*t),a.end())==a.size()-i);
                }
                if (w==10){
                    i%=a_vec.size();
                    a_ptr=&a_vec[i];
                    s_ptr=&s_vec[i];
                    cret=&&_3;
                    goto _1;
                    _3:{}
                }
                if (w==11){
                    i%=(a_vec.size()+1);
                    a_vec.emplace_back();
                    s_vec.emplace_back();
                    a_ptr=&a_vec[i];
                    s_ptr=&s_vec[i];
                    cret=&&_4;
                    goto _1;
                    _4:{}
                }
                if (w==12){
                    i%=(a_vec.size()+1);
                    a_vec.emplace_back(a);
                    s_vec.emplace_back(s);
                    a_ptr=&a_vec[i];
                    s_ptr=&s_vec[i];
                    cret=&&_5;
                    goto _1;
                    _5:{}
                }
                if (w==13){
                    i%=(a_vec.size()+1);
                    a_vec.emplace_back(std::move(a));
                    s_vec.emplace_back(std::move(s));
                    a_ptr=&a_vec[i];
                    s_ptr=&s_vec[i];
                    cret=&&_6;
                    goto _1;
                    _6:{}
                }
                if (w==14){
                    // i%=(a_vec.size()+1);
                    // a_vec.emplace_back(i,a.get_allocator());
                    // s_vec.emplace_back(i);
                    // a_ptr=&a_vec[i];
                    // s_ptr=&s_vec[i];
                    // cret=&&_7;
                    // goto _1;
                    // _7:{}
                }
                // if (w==15){
                //     i%=(a_vec.size()*2);
                //     // a.add(i-a.size(),v);
                //     // s.resize(i,v);
                // }
                if (w==16){
                    i%=(a_vec.size());
                    v%=(a_vec.size());
                    a_vec[i]=a_vec[v];
                    s_vec[i]=s_vec[v];
                    a_ptr=&a_vec[i];
                    s_ptr=&s_vec[i];
                    cret=&&_8;
                    goto _1;
                    _8:{}
                }
                if (w==17){
                    i%=(a_vec.size());
                    v%=(a_vec.size());
                    if (i!=v){
                      a_vec[i]=std::move(a_vec[v]);
                      s_vec[i]=std::move(s_vec[v]);
                    }
                    a_ptr=&a_vec[i];
                    s_ptr=&s_vec[i];
                    cret=&&_9;
                    goto _1;
                    _9:{}
                }
                if (w==18){
                    // std::reverse(a.begin(),a.end());
                    // std::reverse(s.begin(),s.end());
                }
                if (w==19 and a.size()){
                    i%=(a.size());
                    assert(std::to_string(*next(a.begin(),i))==std::to_string(*next(s.begin(),i)));
                }
                {
                  List<item>::const_iterator z=a.cbegin();
                  z=a.begin();
                  // List<item>::const_reverse_iterator x;
                  List<item>::const_reverse_iterator x=a.crbegin();
                  x=a.rbegin();
                    // until_throw=4;
                    // try{
                    //     Deque<item> a(8,0);
                    // }catch(...){
                    //     ic()
                    // }
                    // assert(until_throw==4);
                    // until_throw=-1;
                }
                // (vector<decltype(declval<Deque<int>::const_iterator&>()=declval<Deque<int>::iterator&>())>*)(0);
                // (vector<decltype(declval<Deque<int>&>()=declval<const Deque<int>&>())>*)(0);

                // ic(s)
                // ic(a.slice->begin_)
                // ic(a.slice->end_)
                // ic(a.data)

                // if (not (rand()%8)){
                if (1){
                    assert(a_vec.size()==s_vec.size());
                    // a.check();
                    assert(a.size()==s.size());
                    for (e=a.begin(),r=s.begin();e!=a.end() and r!=s.end();++e,++r){
                        // ic(a.begin().elem->pos)
                        assert(*e==*r);
                    }
                    assert(distance(a.begin(),a.end())==(ssize_t)a.size());
                    assert(distance(a.rbegin(),a.rend())==(ssize_t)a.size());
                    check(a.begin(),a.end());
                }
            }
        }
        assert(locs==0);
        assert(vals==0);
        return 0;
    }



// int main(){
//     StackStorage<999> ss;
//     StackAllocator<int,999> sa(ss);
//     List<int,StackAllocator<int,999>> l(sa);
//     auto r=l;
// }








#else

#include <chrono>
#include <stdexcept>
#include <string>
#include <list>
#include <vector>
#include <deque>
#include <memory>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <type_traits>
#include <sstream>
#include <cassert>
#include <sys/resource.h>

// #include "stackallocator.h"
//#include "list.h"

//template<typename T, typename Alloc = std::allocator<T>>
//using List = std::list<T, Alloc>;

//template<typename T>
//using StackAllocator = std::allocator<T>;

constexpr size_t STORAGE_SIZE = 200'000'000;
StackStorage<STORAGE_SIZE> STATIC_STORAGE;

template <typename Alloc = std::allocator<int>>
void BasicListTest(Alloc alloc = Alloc()) {
    List<int, Alloc> lst(alloc);

    assert(lst.size() == 0);

    lst.push_back(3);
    lst.push_back(4);
    lst.push_front(2);
    lst.push_back(5);
    lst.push_front(1);

    std::reverse(lst.begin(), lst.end());
    // now lst is 5 4 3 2 1
    
    assert(lst.size() == 5);

    std::string s;
    for (int x: lst) {
        s += std::to_string(x);
    }
    assert(s == "54321");
    //std::cerr << " check 1.1 ok, list contains 5 4 3 2 1" << std::endl;

    auto cit = lst.cbegin();
    std::advance(cit, 3);
    
    lst.insert(cit, 6);
    lst.insert(cit, 7);

    std::advance(cit, -3);
    lst.insert(cit, 8);
    lst.insert(cit, 9);
    // now lst is 5 4 8 9 3 6 7 2 1
    
    assert(lst.size() == 9);

    s.clear();
    for (int x: lst) {
        s += std::to_string(x);
    }
    assert(s == "548936721");
    //std::cerr << " check 1.2 ok, list contains 5 4 8 9 3 6 7 2 1" << std::endl;

    lst.erase(lst.cbegin());
    lst.erase(cit);

    lst.pop_front();
    lst.pop_back();

    const auto copy = lst;
    assert(lst.size() == 5);
    assert(copy.size() == 5);
    // now both lists are 8 9 6 7 2

    s.clear();
    for (int x: lst) {
        s += std::to_string(x);
    }
    assert(s == "89672");
    //std::cerr << " check 1.3 ok, list contains 8 9 6 7 2" << std::endl;
    
    auto rit = lst.rbegin();
    ++rit;
    lst.erase(rit.base());
    assert(lst.size() == 4);

    rit = lst.rbegin();
    *rit = 3;

    // now lst: 8 9 6 3, copy: 8 9 6 7 2
    s.clear();
    for (int x: lst) {
        s += std::to_string(x);
    }
    assert(s == "8963");
    
    assert(copy.size() == 5);

    s.clear();
    for (int x: copy) {
        s += std::to_string(x);
    }
    assert(s == "89672");

    //std::cerr << " check 1.4 ok, list contains 8 9 6 3, another list is still 8 9 6 7 2" << std::endl;

    typename List<int, Alloc>::const_reverse_iterator crit = rit;
    crit = copy.rbegin();
    assert(*crit == 2);

    cit = crit.base();
    std::advance(cit, -2);
    assert(*cit == 7);

}

struct VerySpecialType {
    int x = 0;
    explicit VerySpecialType(int x): x(x) {}
};

struct NotDefaultConstructible {
    NotDefaultConstructible() = delete;
    NotDefaultConstructible(VerySpecialType x): x(x) {}
    VerySpecialType x;
};

struct Accountant {
    // Some field of strange size
    char arr[40];

    static size_t ctor_calls;
    static size_t dtor_calls;

    static void reset() {
        ctor_calls = 0;
        dtor_calls = 0;
    }

    Accountant() {
        ++ctor_calls;
    }
    Accountant(const Accountant&) {
        ++ctor_calls;
    }

    Accountant& operator=(const Accountant&) {
        // Actually, when it comes to assign one list to another,
        // list can use element-wise assignment instead of destroying nodes and creating new ones
        ++ctor_calls;
        ++dtor_calls;
        return *this;
    }

    Accountant(Accountant&&) = delete;
    Accountant& operator=(Accountant&&) = delete;

    ~Accountant() {
        ++dtor_calls;
    }
};

size_t Accountant::ctor_calls = 0;
size_t Accountant::dtor_calls = 0;

template <typename Alloc = std::allocator<NotDefaultConstructible>>
void TestNotDefaultConstructible(Alloc alloc = Alloc()) {
    List<NotDefaultConstructible, Alloc> lst(alloc);
    assert(lst.size() == 0);
    lst.push_back(VerySpecialType(0));
    assert(lst.size() == 1);
    lst.pop_front();
    assert(lst.size() == 0);
}

template<typename Alloc = std::allocator<Accountant>>
void TestAccountant(Alloc alloc = Alloc()) {
    Accountant::reset();
    
    {
        List<Accountant, Alloc> lst(5, alloc);
        assert(lst.size() == 5);
        assert(Accountant::ctor_calls == 5);

        List<Accountant, Alloc> another = lst;
        assert(another.size() == 5);
        assert(Accountant::ctor_calls == 10);
        assert(Accountant::dtor_calls == 0);

        another.pop_back();
        another.pop_front();
        assert(Accountant::dtor_calls == 2);

        lst = another; // dtor_calls += 5, ctor_calls += 3
        assert(another.size() == 3);
        assert(lst.size() == 3);

        assert(Accountant::ctor_calls == 13);
        assert(Accountant::dtor_calls == 7);
    
    } // dtor_calls += 6
    
    assert(Accountant::ctor_calls == 13);
    assert(Accountant::dtor_calls == 13);
}

struct ThrowingAccountant: public Accountant {
    static bool need_throw;

    int value = 0;

    ThrowingAccountant(int value = 0): Accountant(), value(value) {
        if (need_throw && ctor_calls % 5 == 4)
            throw std::string("Ahahahaha you have been cocknut");
    }

    ThrowingAccountant(const ThrowingAccountant& other): Accountant(), value(other.value) {
        if (need_throw && ctor_calls % 5 == 4)
            throw std::string("Ahahahaha you have been cocknut");
    }

    ThrowingAccountant& operator=(const ThrowingAccountant& other) {
        value = other.value;
        ++ctor_calls;
        ++dtor_calls;
        if (need_throw && ctor_calls % 5 == 4)
            throw std::string("Ahahahaha you have been cocknut");
        return *this;
    }

};

bool ThrowingAccountant::need_throw = false;

void TestExceptionSafety() {
    Accountant::reset();

    ThrowingAccountant::need_throw = true;

    try {
        List<ThrowingAccountant> lst(8);
    } catch (...) {
        assert(Accountant::ctor_calls == 4);
        assert(Accountant::dtor_calls == 4);
    }

    ThrowingAccountant::need_throw = false;
    List<ThrowingAccountant> lst(8);
 
    List<ThrowingAccountant> lst2;
    for (int i = 0; i < 13; ++i) {
        lst2.push_back(i);
    }

    Accountant::reset();
    ThrowingAccountant::need_throw = true;
    
    try {
        auto lst3 = lst2;
    } catch (...) {
        assert(Accountant::ctor_calls == 4);
        assert(Accountant::dtor_calls == 4);         
    }

    Accountant::reset();

    try {
        lst = lst2;
    } catch (...) {
        assert(Accountant::ctor_calls == 4);
        assert(Accountant::dtor_calls == 4);         
        
        // Actually it may not be 8 (although de facto it is), but the only thing we can demand here 
        // is the abscence of memory leaks
        //
        //assert(lst.size() == 8);
    }
}


void TestAlignment() {

    StackStorage<200'000> storage;

    StackAllocator<char, 200'000> charalloc(storage);

    StackAllocator<int, 200'000> intalloc(charalloc);

    auto* pchar = charalloc.allocate(3);
    
    auto* pint = intalloc.allocate(1);

    assert((void*)pchar != (void*)pint);
    
    assert(reinterpret_cast<uintptr_t>(pint) % sizeof(int) == 0);

    charalloc.deallocate(pchar, 3);

    pchar = charalloc.allocate(555);

    intalloc.deallocate(pint, 1);

    StackAllocator<long double, 200'000> ldalloc(charalloc);

    auto* pld = ldalloc.allocate(25);

    assert(reinterpret_cast<uintptr_t>(pld) % sizeof(long double) == 0);

    charalloc.deallocate(pchar, 555);
    ldalloc.deallocate(pld, 25);
}


template <typename T, bool PropagateOnConstruct, bool PropagateOnAssign>
struct WhimsicalAllocator : public std::allocator<T> {
    std::shared_ptr<int> number;

    auto select_on_container_copy_construction() const {
        return PropagateOnConstruct 
            ? WhimsicalAllocator<T, PropagateOnConstruct, PropagateOnAssign>() 
            : *this;
    }

    struct propagate_on_container_copy_assignment
        : std::conditional_t<PropagateOnAssign, std::true_type, std::false_type> 
    {};

    template <typename U>
    struct rebind {
        using other = WhimsicalAllocator<U, PropagateOnConstruct, PropagateOnAssign>;
    };

    WhimsicalAllocator(): number(std::make_shared<int>(counter)) {
        ++counter;
    }

    template <typename U>
    WhimsicalAllocator(const WhimsicalAllocator<U, PropagateOnConstruct, PropagateOnAssign>& another)
            : number(another.number)
    {}

    template <typename U>
    auto& operator=(const WhimsicalAllocator<U, PropagateOnConstruct, PropagateOnAssign>& another) {
        number = another.number;
        return *this;
    }
    
    template <typename U>
    bool operator==(const WhimsicalAllocator<U, PropagateOnConstruct, PropagateOnAssign>& another) const {
        return std::is_same_v<decltype(*this), decltype(another)> 
            && *number == *another.number;
    }

    template <typename U>
    bool operator!=(const WhimsicalAllocator<U, PropagateOnConstruct, PropagateOnAssign>& another) const {
        return !(*this == another);
    }

    static size_t counter;
};

template <typename T, bool PropagateOnConstruct, bool PropagateOnAssign>
size_t WhimsicalAllocator<T, PropagateOnConstruct, PropagateOnAssign>::counter = 0;

void TestWhimsicalAllocator() {
    {
        List<int, WhimsicalAllocator<int, true, true>> lst;

        lst.push_back(1);
        lst.push_back(2);

        auto copy = lst;
        assert(copy.get_allocator() != lst.get_allocator());

        lst = copy;
        assert(copy.get_allocator() == lst.get_allocator());
    }
    {
        List<int, WhimsicalAllocator<int, false, false>> lst;

        lst.push_back(1);
        lst.push_back(2);

        auto copy = lst;
        assert(copy.get_allocator() == lst.get_allocator());

        lst = copy;
        assert(copy.get_allocator() == lst.get_allocator());
    }
    {
        List<int, WhimsicalAllocator<int, true, false>> lst;

        lst.push_back(1);
        lst.push_back(2);

        auto copy = lst;
        assert(copy.get_allocator() != lst.get_allocator());

        lst = copy;
        assert(copy.get_allocator() != lst.get_allocator());
    }
}

template <class List>
int ListPerformanceTest(List&& l) {
    using namespace std::chrono;
    
    std::ostringstream oss;

    auto start = high_resolution_clock::now();
    
    for (int i = 0; i < 1'000'000; ++i) {
        l.push_back(i);
    }
    auto it = l.begin();
    for (int i = 0; i < 1'000'000; ++i) {
        l.push_front(i);
    }
    oss << *it;

    auto it2 = std::prev(it);
    for (int i = 0; i < 2'000'000; ++i) {
        l.insert(it, i);
        if (i % 534'555 == 0) {
            oss << *it;
        }
    }
    oss << *it;

    for (int i = 0; i < 1'500'000; ++i) {
        l.pop_back();
        if (i % 342'985 == 0) oss << *l.rbegin();
    }
    oss << *l.rbegin();
    
    for (int i = 0; i < 1'000'000; ++i) {
        l.erase(it2++);
        if (i % 432'098 == 0) oss << *it2;
    }
    oss << *it2;

    for (int i = 0; i < 1'000'000; ++i) {
        l.pop_front();
    }
    oss << *l.begin();

    for (int i = 0; i < 1'000'000; ++i) {
        l.push_back(i);
    }
    oss << *l.rbegin();

    assert(oss.str() == "00000099999865701331402819710431628058149999904320988641969999991000000999999");

    auto finish = high_resolution_clock::now();
    return duration_cast<milliseconds>(finish - start).count();
}

template <typename Alloc>
void DequeTest() {
    Alloc alloc(STATIC_STORAGE);

    std::deque<char, Alloc> d(alloc);

    d.push_back(1);
    assert(d.back() == 1);

    d.resize(2'500'000, 5);
    assert(d[1'000'000] == 5);

    d.pop_back();
    for (int i = 0; i < 2'000'000; ++i) {
        d.push_back(i % 100);
    }
    
    assert(d.size() == 4'499'999);
    assert(d[4'000'000] == 1);

    for (int i = 0; i < 4'000'000; ++i) {
        d.pop_front();
    }
    
    assert(d[400'000] == 1);
}


template <template<typename, typename> class Container>
void TestPerformance() {

    std::ostringstream oss_first;
    std::ostringstream oss_second;
    
    int first = 0;
    int second = 0;

    {
        StackStorage<STORAGE_SIZE>&storage=*new StackStorage<STORAGE_SIZE>();
        StackAllocator<int, STORAGE_SIZE> alloc(storage);
        
        first = ListPerformanceTest(Container<int, std::allocator<int>>());
        second = ListPerformanceTest(Container<int, StackAllocator<int, STORAGE_SIZE>>(alloc));
        std::ignore = first;
        std::ignore = second;
        first = 0, second = 0;
    }

    double mean_first = 0.0;
    double mean_second = 0.0;
 
    for (int i = 0; i < 3; ++i) {
        first = ListPerformanceTest(Container<int, std::allocator<int>>());
        mean_first += first;
        oss_first << first << " ";

        StackStorage<STORAGE_SIZE>&storage=*new StackStorage<STORAGE_SIZE>();
        StackAllocator<int, STORAGE_SIZE> alloc(storage);
        second = ListPerformanceTest(
                Container<int, StackAllocator<int, STORAGE_SIZE>>(alloc));
        mean_second += second;
        oss_second << second << " ";
    }

    mean_first /= 5;
    mean_second /= 5;

    std::cerr << " Results with std::allocator: " << oss_first.str() 
            << " ms, results with StackAllocator: " << oss_second.str() << " ms " << std::endl;
    
    if (mean_first * 0.9 < mean_second) {
        throw std::runtime_error("StackAllocator expected to be at least 10\% faster than std::allocator, but mean time were "
                + std::to_string(mean_second) + " ms comparing with " + std::to_string(mean_first) + " :((( ...\n");
    }
}



int main() {

    const rlim_t kStackSize = 210 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result != 0) {
        std::cerr << "Failed to get current stack size\n";
        abort();
    }
    
    std::cerr << rl.rlim_cur << '\n';

    if (rl.rlim_cur < kStackSize) {
        rl.rlim_cur = kStackSize;
        result = setrlimit(RLIMIT_STACK, &rl);
        if (result != 0) {
            std::cerr << "Failed to set bigger stack size\n";
            // abort();
        }
        std::cerr << "Stack size is successfully set to " << kStackSize << '\n';
    }

    static_assert(!std::is_assignable_v<decltype(*List<int>().cbegin()), int>);
    static_assert(!std::is_assignable_v<List<int>::iterator, List<int>::const_iterator>);

    static_assert(std::is_same_v<std::iterator_traits<List<int>::iterator>::iterator_category,
            std::bidirectional_iterator_tag>);

    BasicListTest<>();

    std::cerr << "Test 1 (BasicTest) with std::allocator passed. Now will repeat with StackAllocator" << std::endl;

    {
        StackStorage<200'000> storage;
        StackAllocator<int, 200'000> alloc(storage);

        BasicListTest<StackAllocator<int, 200'000>>(alloc);
    }

    std::cerr << "Test 1 with StackAllocator passed." << std::endl;

    TestAccountant<>();
    
    std::cerr << "Test 2 (counting) with std::allocator passed. Now will repeat with StackAllocator" << std::endl;
    
    {
        StackStorage<200'000> storage;
        StackAllocator<int, 200'000> alloc(storage);

        TestAccountant<StackAllocator<Accountant, 200'000>>(alloc);
    }

    std::cerr << "Test 2 with StackAllocator passed." << std::endl;

    TestExceptionSafety();

    std::cerr << "Test 3 (ExceptionSafety) passed." << std::endl;
    
    TestAlignment();
    
    std::cerr << "Test 4 (Alignment) passed." << std::endl;

    TestNotDefaultConstructible<>();
    
    {
        StackStorage<200'000> storage;
        StackAllocator<int, 200'000> alloc(storage);

        TestNotDefaultConstructible<StackAllocator<NotDefaultConstructible, 200'000>>(alloc);
    }

    std::cerr << "Test 5 (NotDefaultConstructible) passed." << std::endl;

    DequeTest<StackAllocator<char, STORAGE_SIZE>>();

    std::cerr << "Test 6 (Deque with StackAllocator) passed." << std::endl;
    
    TestWhimsicalAllocator();
    
    std::cerr << "Test 7 (Allocator Awareness) passed." << std::endl;
    
    std::cerr << "Starting performance test. First, let's test performance of different allocators with std::list." << std::endl;

    TestPerformance<std::list>();

    std::cerr << "Well, looks good! Finally let's test with your List!" << std::endl;

    TestPerformance<List>();

    std::cerr << "Tests passed, my sweetheart!" << std::endl;

    if (std::is_assignable_v<List<int>, std::list<int>> || std::is_assignable_v<std::list<int>, List<int>>) {
        std::cerr << "....but you must use your own List, not std::list!" << std::endl;
        throw std::runtime_error("Bad guy!");
    }

    std::cout << 0;
}


#endif
>>>>>>> 1a9049006131447bbd4ab468c20ecb812ac69d49
