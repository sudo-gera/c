#include "/home/user/pony/header.hpp"
#if 1
    // #include "/home/user/pony/header.hpp"
    // #define ic(...)

    #include "deque.hpp"

    #include <deque>

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
            std::destroy_at(this);
            std::construct_at(this,std::forward<const item>(oth));
            return *this;
        }
        auto&operator=(item&&oth){
            std::destroy_at(this);
            std::construct_at(this,std::forward<item>(oth));
            return *this;
        }
        ~item(){
            // ic(size_t(this))
            locs-=size_t(this);
            until_throw+=1;
            // if (until_throw==0){throw std::exception();}
            vals-=val;
        }
        operator size_t(){
            return val;
        }
    };


    int _main(){
        // srand(0);
        size_t seed=1679194138;
        // seed=time(0);
        printf("%zu\n",seed);
        srand(seed);

        {
            std::vector<Deque<item>> a_vec(1);
            std::vector<std::deque<size_t>> s_vec(1);
            Deque<item>* a_ptr=a_vec.data();
            std::deque<size_t>* s_ptr=s_vec.data();
            void* cret=&&_2;
            size_t q,w,i,v,e;
            std::deque<size_t> tmp;
        _1:
            Deque<item>&a=*a_ptr;
            std::deque<size_t>&s=*s_ptr;
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
                    i%=(a.size()+1);
                    a.insert_back(i,v);
                    s.insert(s.begin()+i,v);
                }
                if (w==1){
                    i%=(a.size()+1);
                    a.insert_front(i,v);
                    s.insert(s.begin()+i,v);
                }
                if (w==2){
                    i%=(a.size()+1);
                    a.push_back(v);
                    s.push_back(v);
                }
                if (w==3){
                    i%=(a.size()+1);
                    a.push_front(v);
                    s.push_front(v);
                }
                if (w==4){
                    i%=(a.size()+1);
                    a.insert(i+a.begin(),v);
                    s.insert(i+s.begin(),v);
                }
                if (w==5 and a.size()){
                    i%=a.size();
                    a.erase_back(i);
                    s.erase(s.begin()+i);
                }
                if (w==6 and a.size()){
                    i%=a.size();
                    a.erase_front(i);
                    s.erase(s.begin()+i);
                }
                if (w==7 and a.size()){
                    i%=(a.size()+1);
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
                    a.erase(i+a.begin());
                    s.erase(i+s.begin());
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
                    i%=(a_vec.size()+1);
                    a_vec.emplace_back(i,v);
                    s_vec.emplace_back(i,v);
                    a_ptr=&a_vec[i];
                    s_ptr=&s_vec[i];
                    cret=&&_7;
                    goto _1;
                    _7:{}
                }
                if (w==15){
                    i%=(a_vec.size()*2);
                    a.add(i-a.size(),v);
                    s.resize(i,v);
                }
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
                    a_vec[i]=std::move(a_vec[v]);
                    tmp=std::move(s_vec[v]);
                    s_vec[i]=std::move(tmp);
                    a_ptr=&a_vec[i];
                    s_ptr=&s_vec[i];
                    cret=&&_7;
                    goto _9;
                    _9:{}
                }
                if (w==18){
                    std::reverse(a.begin(),a.end());
                    std::reverse(s.begin(),s.end());
                }
                if (w==19 and a.size()){
                    i%=(a.size());
                    assert(std::to_string(a[i])==std::to_string(s[i]));
                }
                {
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
                // for(auto&w:a.items){
                //     ic(w->pos)
                // }

                // if (not (rand()%8)){
                if (1){
                    assert(a_vec.size()==s_vec.size());
                    a.check();
                    assert(a.size()==s.size());
                    for (e=0;e<a.size();++e){
                        // ic(a.begin().elem->pos)
                        assert(a[e]==s[e]);
                    }
                    // ic(a.end().elem->pos)
                    // ic(a.begin().elem->pos)
                    assert(a.end()-a.begin()==a.size());
                    check(a.begin()-2,a.end()+1);
                }
            }
        }
        assert(locs==0);
        assert(vals==0);
        return 0;
    }

auto tmp=_main();

// #else



    #include <type_traits>
    #include <unordered_set>
    #include <algorithm>
    #include <numeric>
    #include <random>
    #include <iostream>
    #include <cassert>
    #include <deque>

    #include "deque.hpp"

    //template <typename T>
    //using Deque = std::deque<T>;

    namespace TestsByMesyarik {

    void test1() {
        Deque<int> d(10, 3);

        d[3] = 5;

        d[7] = 8;

        d[9] = 10;

        std::string s = "33353338310";
        std::string ss;
        Deque<int> dd;

        {
            Deque<int> d2 = d;

            dd = d2;
        }

        d[1] = 2;

        d.at(2) = 1;

        try {
            d.at(10) = 0;
            assert(false);
        } catch (std::out_of_range&) {}

        const Deque<int>& ddd = dd;
        for (size_t i = 0; i < ddd.size(); ++i) {
            ss += std::to_string(ddd[i]);
        }

        assert(s == ss);
    }

    void test2() {
        Deque<int> d(1);

        d[0] = 0;
        
        for (int i = 0; i < 8; ++i) {
            d.push_back(i);
            d.push_front(i);
        }

        for (int i = 0; i < 12; ++i) {
            d.pop_front();
        }
        
        d.pop_back();
        assert(d.size() == 4);

        std::string ss;

        for (size_t i = 0; i < d.size(); ++i) {
            ss += std::to_string(d[i]);
        }
        
        assert(ss == "3456");
    }

    void test3() {
        Deque<int> d;

        for (int i = 0; i < 1000; ++i) {
            for (int j = 0; j < 1000; ++j) {
                
                if (j % 3 == 2) {
                    d.pop_back();
                } else {
                    d.push_front(i*j);
                }

            }
        }

        assert(d.size() == 334'000);

        Deque<int>::iterator left = d.begin() + 100'000;
        Deque<int>::iterator right = d.end() - 233'990;
        while (d.begin() != left) d.pop_front();
        while (d.end() != right) d.pop_back();

        assert(d.size() == 10);

        assert(right - left == 10);

        std::string s;
        for (auto it = left; it != right; ++it) {
            ++*it;
        }
        for (auto it = right - 1; it >= left; --it) {
            s += std::to_string(*it);
        }
        
        assert(s == "51001518515355154401561015695158651595016120162051");
    }

    struct S {
        int x = 0;
        double y = 0.0;
    };

    void test4() {
        
        Deque<S> d(5, {1, 2.0});
        const Deque<S>& cd = d;

        static_assert(!std::is_assignable_v<decltype(*cd.begin()), S>);
        static_assert(std::is_assignable_v<decltype(*d.begin()), S>);
        static_assert(!std::is_assignable_v<decltype(*d.cbegin()), S>);

        static_assert(!std::is_assignable_v<decltype(*cd.end()), S>);
        static_assert(std::is_assignable_v<decltype(*d.end()), S>);
        static_assert(!std::is_assignable_v<decltype(*d.cend()), S>);

        assert(cd.size() == 5);

        auto it = d.begin() + 2;
        auto cit = cd.end() - 3;

        it->x = 5;
        assert(cit->x == 5);

        d.erase(d.begin() + 1);
        d.erase(d.begin() + 3);
        assert(d.size() == 3);

        auto dd = cd;

        dd.pop_back();
        dd.insert(dd.begin(), {3, 4.0});
        dd.insert(dd.begin() + 2, {4, 5.0});

        std::string s;
        for (const auto& x: dd) {
            s += std::to_string(x.x);
        }
        assert(s == "3145");

        std::string ss;
        for (const auto& x: d) {
            ss += std::to_string(x.x);
        }
        assert(ss == "151");
    }

    void test5() {
        Deque<int> d;

        d.push_back(1);
        d.push_front(2);

        auto left_ptr = &*d.begin();
        auto right_ptr = &*(d.end()-1);

        d.push_back(3);
        d.push_front(4);
        auto left = *d.begin();
        auto right = *(d.end()-1);

        for (int i = 0; i < 10'000; ++i) {
            d.push_back(i);
        }
        for (int i = 0; i < 20'000; ++i) {
            d.push_front(i);
        }
        
        std::string s;
        s += std::to_string(left);
        s += std::to_string(right);

        s += std::to_string(*left_ptr);
        s += std::to_string(*right_ptr);
        //for (auto it = left; it <= right; ++it) {
        //    s += std::to_string(*it);
        //}
        assert(s == "4321");
    }

    struct VerySpecialType {
        int x = 0;

        explicit VerySpecialType(int x): x(x) {}
    };

    struct NotDefaultConstructible {
        NotDefaultConstructible() = delete;
        NotDefaultConstructible(const NotDefaultConstructible&) = default;
        NotDefaultConstructible& operator=(const NotDefaultConstructible&) = default;

        NotDefaultConstructible(VerySpecialType v): x(v.x) {}

    public:
        int x = 0;
    };

    void test6() {
        Deque<NotDefaultConstructible> d;
        
        NotDefaultConstructible ndc = VerySpecialType(-1);

        for (int i = 0; i < 1500; ++i) {
            ++ndc.x;
            d.push_back(ndc);
        }

        assert(d.size() == 1500);

        for (int i = 0; i < 1300; ++i) {
            d.pop_front();
        }

        assert(d.size() == 200);

        assert(d[99].x == 1399);

        d[100] = VerySpecialType(0);
        assert(d[100].x == 0);
    }


    struct Explosive {
        int x = 0;
        Explosive(int x): x(x) {}
        Explosive(const Explosive&) {
            if (x) throw std::runtime_error("Boom!");
        }
        Explosive& operator=(const Explosive&) = default;
    };

    void test7() {

        Deque<Explosive> d;
        d.push_back(Explosive(0));

        for (int i = 0; i < 30'000; ++i) {
            auto it = d.begin();
            auto x = it->x;
            size_t sz = d.size();
            try {
                if (i % 2)
                    d.push_back(Explosive(1));
                else
                    d.push_front(Explosive(1));
            } catch (...) {
                assert(it == d.begin());
                assert(d.begin()->x == x);
                assert(d.size() == sz);
            }

            d.push_back(Explosive(0));
        }

    }

    } // tests by mesyarik

    namespace TestsByUnrealf1 {
        struct Fragile {
            Fragile(int durability, int data): durability(durability), data(data) {}
            ~Fragile() = default;
            
            // for std::swap
            Fragile(Fragile&& other): Fragile() {
                *this = other;
            }

            Fragile(const Fragile& other): Fragile() {
                *this = other;
            }

            Fragile& operator=(const Fragile& other) {
                durability = other.durability - 1;
                data = other.data;
                if (durability <= 0) {
                    throw 2;
                }
                return *this;
            }

            int durability;
            int data;
        private:
            Fragile() {

            }
        };

        struct Explosive {
            struct Safeguard {};

            inline static bool exploded = false;

            Explosive(): should_explode(true) {
                throw 1;
            }

            Explosive(Safeguard): should_explode(false) {

            }

            Explosive(const Explosive&): should_explode(true) {
                throw 2;
            }

            //TODO: is this ok..?
            Explosive& operator=(const Explosive&) {return *this;}

            ~Explosive() {
                exploded |= should_explode;
            }

        private:
            const bool should_explode;
        };

        struct DefaultConstructible {
            DefaultConstructible() {
                data = default_data;
            }

            int data = default_data;
            inline static const int default_data = 117;
        };

        struct NotDefaultConstructible {
            NotDefaultConstructible() = delete;
            NotDefaultConstructible(int input): data(input) {}
            int data;

            auto operator<=>(const NotDefaultConstructible&) const = default;
        };

        struct CountedException : public std::exception {

        };

        template<int when_throw>
        struct Counted {
            inline static int counter = 0;

            Counted() {
                ++counter;
                if (counter == when_throw) {
                    --counter;
                    throw CountedException();
                }
            }

            Counted(const Counted&): Counted() { }

            ~Counted() {
                --counter;
            }
        };

        template<typename iter, typename T>
        struct CheckIter{
            using traits = std::iterator_traits<iter>;

            static_assert(std::is_same_v<std::remove_cv_t<typename traits::value_type>, std::remove_cv_t<T>>);
            static_assert(std::is_same_v<typename traits::pointer, T*>);
            static_assert(std::is_same_v<typename traits::reference, T&>);
            static_assert(std::is_same_v<typename traits::iterator_category, std::random_access_iterator_tag>);

            static_assert(std::is_same_v<decltype(std::declval<iter>()++), iter>);
            static_assert(std::is_same_v<decltype(++std::declval<iter>()), iter&>);
            static_assert(std::is_same_v<decltype(std::declval<iter>() + 5), iter>);
            static_assert(std::is_same_v<decltype(std::declval<iter>() += 5), iter&>);

            static_assert(std::is_same_v<decltype(std::declval<iter>() - std::declval<iter>()), typename traits::difference_type>);
            static_assert(std::is_same_v<decltype(*std::declval<iter>()), T&>);
            
            static_assert(std::is_same_v<decltype(std::declval<iter>() < std::declval<iter>()), bool>);
            static_assert(std::is_same_v<decltype(std::declval<iter>() <= std::declval<iter>()), bool>);
            static_assert(std::is_same_v<decltype(std::declval<iter>() > std::declval<iter>()), bool>);
            static_assert(std::is_same_v<decltype(std::declval<iter>() >= std::declval<iter>()), bool>);
            static_assert(std::is_same_v<decltype(std::declval<iter>() == std::declval<iter>()), bool>);
            static_assert(std::is_same_v<decltype(std::declval<iter>() != std::declval<iter>()), bool>);
        };

        void testDefault() {
            Deque<int> defaulted;
            assert((defaulted.size() == 0));
            Deque<NotDefaultConstructible> without_default;
            assert((without_default.size() == 0));
        }

        void testCopy() {
            Deque<NotDefaultConstructible> without_default;
            Deque<NotDefaultConstructible> copy = without_default;
            assert((copy.size() == 0));
        }

        void testWithSize() {
            int size = 17;
            int value = 14;
            Deque<int> simple(size);
            assert((simple.size() == size_t(size)) && std::all_of(simple.begin(), simple.end(), [](int item){ return item == 0; }));
            Deque<NotDefaultConstructible> less_simple(size, value);
            assert((less_simple.size() == size_t(size)) && std::all_of(less_simple.begin(), less_simple.end(), [&](const auto& item){ 
                        return item.data == value; 
            }));
            Deque<DefaultConstructible> default_constructor(size);
            assert(std::all_of(default_constructor.begin(), default_constructor.end(), [](const auto& item) { 
                        return item.data == DefaultConstructible::default_data;
            }));
        }

        void testAssignment(){ 
            Deque<int> first(10, 10);
            Deque<int> second(9, 9);
            first = second;
            assert((first.size() == second.size()) && (first.size() == 9) && std::equal(first.begin(), first.end(), second.begin()));
        }

        void testStaticAsserts() {
            using T1 = int;
            using T2 = NotDefaultConstructible;

            static_assert(std::is_default_constructible_v<Deque<T1>>, "should have default constructor");
            static_assert(std::is_default_constructible_v<Deque<T2>>, "should have default constructor");
            static_assert(std::is_copy_constructible_v<Deque<T1> >, "should have copy constructor");
            static_assert(std::is_copy_constructible_v<Deque<T2> >, "should have copy constructor");
            //static_assert(std::is_constructible_v<Deque<T1>, int>, "should have constructor from int");
            //static_assert(std::is_constructible_v<Deque<T2>, int>, "should have constructor from int");
            static_assert(std::is_constructible_v<Deque<T1>, int, const T1&>, "should have constructor from int and const T&");
            static_assert(std::is_constructible_v<Deque<T2>, int, const T2&>, "should have constructor from int and const T&");

            static_assert(std::is_copy_assignable_v<Deque<T1>>, "should have assignment operator");
            static_assert(std::is_copy_assignable_v<Deque<T2>>, "should have assignment operator");
        }
            
        void testOperatorSubscript() {
            Deque<size_t> defaulted(1300, 43);
            assert((defaulted[0] == defaulted[1280]) && (defaulted[0] == 43));
            assert((defaulted.at(0) == defaulted[1280]) && (defaulted.at(0) == 43));
            int caught = 0;

            try {
                defaulted.at(size_t(-1));
            } catch (std::out_of_range& e) {
                ++caught;
            }

            try {
                defaulted.at(1300);
            } catch (std::out_of_range& e) {
                ++caught;
            }

            assert(caught == 2);
        }

        void testStaticAssertsAccess() {
            Deque<size_t> defaulted;
            const Deque<size_t> constant;
            static_assert(std::is_same_v<decltype(defaulted[0]), size_t&>);
            static_assert(std::is_same_v<decltype(defaulted.at(0)), size_t&>);
            static_assert(std::is_same_v<decltype(constant[0]), const size_t&>);
            static_assert(std::is_same_v<decltype(constant.at(0)), const size_t&>);

            //static_assert(noexcept(defaulted[0]), "operator[] should not throw");
            static_assert(!noexcept(defaulted.at(0)), "at() can throw");

        }


        void testStaticAssertsIterators() {
            CheckIter<Deque<int>::iterator, int> iter;
            std::ignore = iter;
            CheckIter<decltype(std::declval<Deque<int>>().rbegin()), int> reverse_iter;
            std::ignore = reverse_iter;
            CheckIter<decltype(std::declval<Deque<int>>().cbegin()), const int> const_iter;
            std::ignore = const_iter;

            static_assert(std::is_convertible_v<
                    decltype(std::declval<Deque<int>>().begin()), 
                    decltype(std::declval<Deque<int>>().cbegin()) 
                    >, "should be able to construct const iterator from non const iterator");
            static_assert(!std::is_convertible_v<
                    decltype(std::declval<Deque<int>>().cbegin()), 
                    decltype(std::declval<Deque<int>>().begin()) 
                    >, "should NOT be able to construct iterator from const iterator");
        }

        void testIteratorsArithmetic() {
            Deque<int> empty;
            assert((empty.end() - empty.begin()) == 0);
            assert((empty.begin() + 0 == empty.end()) && (empty.end() - 0 == empty.begin()));
            auto iter = empty.begin();
            assert((iter++ == empty.begin()));
            Deque<int> one(1);
            auto iter2 = one.end();
            assert(((--iter2) == one.begin()));

            assert((empty.rend() - empty.rbegin()) == 0);
            assert((empty.rbegin() + 0 == empty.rend()) && (empty.rend() - 0 == empty.rbegin()));
            auto r_iter = empty.rbegin();
            assert((r_iter++ == empty.rbegin()));

            assert((empty.cend() - empty.cbegin()) == 0);
            assert((empty.cbegin() + 0 == empty.cend()) && (empty.cend() - 0 == empty.cbegin()));
            auto c_iter = empty.cbegin();
            assert((c_iter++ == empty.cbegin()));

            Deque<int> d(1000, 3);
            assert(size_t((d.end() - d.begin())) == d.size());
            assert((d.begin() + d.size() == d.end()) && (d.end() - d.size() == d.begin()));
        }

        void testIteratorsComparison() {
            Deque<int> d(1000, 3);

            assert(d.end() > d.begin());
            assert(d.cend() > d.cbegin());
            assert(d.rend() > d.rbegin());
        }

        void testIteratorsAlgorithms() {
            Deque<int> d(1000, 3);

            std::iota(d.begin(), d.end(), 13);
            std::mt19937 g(31415);
            std::shuffle(d.begin(), d.end(), g);
            std::sort(d.rbegin(), d.rbegin() + 500);
            std::reverse(d.begin(), d.end());
            auto sorted_border = std::is_sorted_until(d.begin(), d.end());
            //std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
            //std::cout << std::endl;
            assert(sorted_border - d.begin() == 500);
        }

        void testPushAndPop() {
            Deque<NotDefaultConstructible> d(10000, { 1 });
            auto start_size = d.size();
            
            auto middle = &(*(d.begin() + start_size / 2)); // 5000
            auto& middle_element = *middle;
            auto begin = &(*d.begin());
            auto end = &(*d.rbegin());

            auto middle2 = &(*((d.begin() + start_size / 2) + 2000)); // 7000
            
            // remove 400 elements 
            for (size_t i = 0; i < 400; ++i) {
                d.pop_back();
            }
            
            // begin and middle pointers are still valid
            assert(begin->data == 1);
            assert(middle->data == 1);
            assert(middle_element.data == 1);
            assert(middle2->data == 1);

            end = &*d.rbegin();
            
            // 800 elemets removed in total
            for (size_t i = 0; i < 400; ++i) {
                d.pop_front();
            }

            // and and middle iterators are still valid
            assert(end->data == 1);
            assert(middle->data == 1);
            assert(middle_element.data == 1);
            assert(middle2->data == 1);
            
            // removed 9980 items in total
            for (size_t i = 0; i < 4590; ++i) {
                d.pop_front();
                d.pop_back();
            }

            assert(d.size() == 20);
            assert(middle_element.data == 1);
            assert(middle->data == 1 && middle->data == 1);
            assert(std::all_of(d.begin(), d.end(), [](const auto& item) { return item.data == 1; } ));

            begin = &*d.begin();
            end = &*d.rbegin();

            for (size_t i = 0; i < 5500; ++i) {
                d.push_back({2});
                d.push_front({2});
            }

            assert((*begin).data == 1);
            assert((*end).data == 1);
            assert(d.begin()->data == 2);
            assert(d.size() == 5500 * 2 + 20);
            assert(std::count(d.begin(), d.end(), NotDefaultConstructible{1}) == 20);
            assert(std::count(d.begin(), d.end(), NotDefaultConstructible{2}) == 11000);
        }

        void testInsertAndErase() {
            Deque<NotDefaultConstructible> d(10000, { 1 });
            auto start_size = d.size();
            
            d.insert(d.begin() + start_size / 2, NotDefaultConstructible{2});
            assert(d.size() == start_size + 1);
            d.erase(d.begin() + start_size / 2 - 1);
            assert(d.size() == start_size);

            assert(size_t(std::count(d.begin(), d.end(), NotDefaultConstructible{1})) == start_size - 1);
            assert(std::count(d.begin(), d.end(), NotDefaultConstructible{2}) == 1);

            Deque<NotDefaultConstructible> copy;
            for (const auto& item : d) {
                copy.insert(copy.end(), item);
            }
            // std::copy(d.cbegin(), d.cend(), std::inserter(copy, copy.begin()));
            
            assert(d.size() == copy.size());
            assert(std::equal(d.begin(), d.end(), copy.begin()));
        }

        void testExceptions() {
            try {
                Deque<Counted<17>> d(100);
            } catch (CountedException& e) {
                assert(Counted<17>::counter == 0);
            } catch (...) {
                // should have caught same exception as thrown by Counted
                assert(false);
            }

            try {
                Deque<Explosive> d(100);
            } catch (...) {
                
            }

            try {
                Deque<Explosive> d;
            } catch (...) {
                // no objects should have been created
                assert(false);
            }
            assert(Explosive::exploded == false);

            try {
                Deque<Explosive> d;
                auto safe = Explosive(Explosive::Safeguard{});
                d.push_back(safe);
            } catch (...) {

            }

            // Destructor should not be called for an object
            // with no finihshed constructor
            // the only destructor called - safe explosive with the safeguard
            assert(Explosive::exploded == false);
        }

        void testStrongGuarantee() {
            const size_t size = 20'000;
            const size_t initial_data = 100;
            Deque<Fragile> d(size, Fragile(size, initial_data));

            auto is_intact = [&] {
                return d.size() == size && std::all_of(d.begin(), d.end(), [initial_data](const auto& item) {return item.data == initial_data;} );
            };
            try {
                d.insert(d.begin() + size / 2, Fragile(0, initial_data + 1));
            } catch (...) {
                // have to throw
                assert(is_intact());
            }
            try {
                // for those who like additional copies...
                d.insert(d.begin() + size / 2, Fragile(3, initial_data + 2));
            } catch (...) {
                // might throw depending on the implementation
                // if it DID throw, then deque should be untouched
                assert(is_intact());
            }
        }

    } // namespace TestsByUnrealf1

    int main() {
        
        static_assert(!std::is_same_v<std::deque<TestsByMesyarik::VerySpecialType>,
                Deque<TestsByMesyarik::VerySpecialType>>, "You cannot use std::deque, cheater!");
        static_assert(!std::is_base_of_v<std::deque<TestsByMesyarik::VerySpecialType>,
                Deque<TestsByMesyarik::VerySpecialType>>, "You cannot use std::deque, cheater!");
        
        TestsByMesyarik::test1();
        TestsByMesyarik::test2();
        TestsByMesyarik::test3();
        TestsByMesyarik::test4();
        TestsByMesyarik::test5();
        TestsByMesyarik::test6();
        TestsByMesyarik::test7();

        TestsByUnrealf1::testDefault();
        TestsByUnrealf1::testCopy();
        TestsByUnrealf1::testWithSize();
        TestsByUnrealf1::testAssignment();
        TestsByUnrealf1::testStaticAsserts();
        TestsByUnrealf1::testOperatorSubscript();
        TestsByUnrealf1::testStaticAssertsAccess();
        TestsByUnrealf1::testStaticAssertsIterators();
        TestsByUnrealf1::testIteratorsArithmetic();
        TestsByUnrealf1::testIteratorsComparison();
        TestsByUnrealf1::testIteratorsAlgorithms();
        TestsByUnrealf1::testPushAndPop();
        TestsByUnrealf1::testInsertAndErase();
        TestsByUnrealf1::testExceptions();
        TestsByUnrealf1::testStrongGuarantee();

        std::cout << 0;
    }
#endif
