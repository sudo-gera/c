#pragma once
#include <vector>
#include <algorithm>
#include <utility>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <type_traits>

template<typename type>
struct optional{
    // alignas(type) char data_[sizeof(type)];
    // bool has_=0;
    std::vector<type> vect_;
    auto data(){
        if (vect_.size()){
            return vect_.data();
        }else{
            return (type*)nullptr;
        }
        // if (has_){

        // }
    }
    template<typename...Y>
    auto emplace_back(Y&&...val){
        clear();
        vect_.emplace_back(std::forward<Y>(val)...);
    }
    void clear(){
        vect_.clear();
    }
    ~optional(){
        clear();
    }
};

template<typename type>
struct Deque{
    using front_space=std::integral_constant<size_t,2>;
    using back_space=std::integral_constant<size_t,2>;
    struct item{
        size_t pos;
        optional<type> value;
    };
    std::vector<std::vector<item>> items;
    struct data{
        size_t begin_=0;
        size_t end_=0;
        std::vector<item>* array_;
        size_t size;
    };
    std::vector<data> slice=std::vector<data>(1);
    size_t size()const{
        return slice[0].end_-slice[0].begin_ & items.size()-1;
    }
    void repair_element(size_t index){
        index&=items.size()-1;
        items[index][0].pos=index;
        slice[0].array_=&items[0];
        slice[0].size=items.size();
    }
    void shift_size(size_t shift){
        if (shift){
            std::rotate(items.begin(), items.begin()+(slice[0].begin_ & items.size()-1), items.end());
            slice[0].end_-=slice[0].begin_;
            slice[0].begin_-=slice[0].begin_;
            slice[0].begin_&=items.size()-1;
            slice[0].end_&=items.size()-1;
            items.resize(items.size()<<shift);
            slice[0].array_=items.data();
            for (auto&w:items){
                if (w.empty()){
                    w.emplace_back();
                }
                repair_element(&w-&items[0]);
            }
        }
    }
    void memory_at_least(size_t new_size){
        size_t shift=0;
        if (items.size()==0){
            items.resize(1);
            shift=1;
        }
        while((items.size()<<shift)<new_size){
            shift+=1;
        }
        shift_size(shift);
    }
    template<typename ctype>
    struct iter{
        using orig=std::decay_t<ctype>;
        using difference_type=std::ptrdiff_t;
        using value_type=ctype;
        using pointer=ctype*;
        using reference=ctype&;
        using iterator_category=std::random_access_iterator_tag;
        item* elem=nullptr;
        data* d=nullptr;
        ctype&operator*()const{
            return elem->value.data()[0];
        }
        auto operator->()const{
            return elem->value.data();
        }
        auto&operator+=(size_t off){
            elem = d->array_[elem->pos+off & d->size-1].data();
            return *this;
        }
        auto&operator-=(size_t off){
            (*this)+=-off;
            return *this;
        }
        auto&operator++(){
            (*this)+=1;
            return *this;
        }
        auto&operator--(){
            (*this)-=1;
            return *this;
        }
        auto operator++(int){
            auto tmp=*this;
            ++*this;
            return tmp;
        }
        auto operator--(int){
            auto tmp=*this;
            --*this;
            return tmp;
        }
        auto&operator[](size_t index)const{
            auto tmp=*this;
            tmp+=index;
            return *tmp;
        }
        size_t index()const{
            return (elem->pos-d->begin_+front_space())&d->size-1;
        }
        ssize_t sub(const iter&oth)const{
            return index()-oth.index();
        }
        operator iter<const type>(){
            return {elem,d};
        }
    };
    using iterator=iter<type>;
    using const_iterator=iter<const type>;
    template<typename I>
    using is_iterator=std::enable_if_t<std::is_same_v<std::decay_t<I>,iterator> or std::is_same_v<std::decay_t<I>,const_iterator>,void>;
    template<typename...Y>
    void insert_front(size_t index, Y&&...val){
        if (size()+front_space()+back_space()+1>items.size()){
            memory_at_least(size()+front_space()+back_space()+1);
        }
        items[slice[0].begin_-1&items.size()-1][0].value.emplace_back(std::forward<Y>(val)...);
        slice[0].begin_-=1;
        for (size_t q=slice[0].begin_;q!=index+slice[0].begin_;++q){
            std::swap(items[q & items.size()-1],items[q+1 & items.size()-1]);
        }
        for (size_t q=slice[0].begin_;q!=index+slice[0].begin_+1;++q){
            repair_element(q);
        }
    }
    template<typename...Y>
    void insert_back(size_t index, Y&&...val){
        if (size()+front_space()+back_space()+1>items.size()){
            memory_at_least(size()+front_space()+back_space()+1);
        }
        items[slice[0].end_&items.size()-1][0].value.emplace_back(std::forward<Y>(val)...);
        slice[0].end_+=1;
        for (size_t q=slice[0].end_-1;q!=slice[0].begin_+index;--q){
            std::swap(items[q & items.size()-1],items[q-1 & items.size()-1]);
        }
        for (size_t q=slice[0].end_-1;q!=slice[0].begin_+index-1;--q){
            repair_element(q);
        }
    }
    iterator begin(){
        return iterator{items[slice[0].begin_&items.size()-1].data(),slice.data()};
    }
    iterator end(){
        return begin()+size();
    }
    const_iterator cbegin()const{
        return begin();
    }
    const_iterator cend()const{
        return end();
    }
    const_iterator begin()const{
        return iterator{(item*)items[slice[0].begin_&items.size()-1].data(),(data*)slice.data()};
    }
    const_iterator end()const{
        return begin()+size();
    }
    auto rbegin(){
        return std::reverse_iterator(end());
    }
    auto rend(){
        return std::reverse_iterator(begin());
    }
    auto crbegin(){
        return std::reverse_iterator(cend());
    }
    auto crend(){
        return std::reverse_iterator(cbegin());
    }
    auto&operator[](size_t n){
        return begin()[n];
    }
    auto&operator[](size_t n)const{
        return begin()[n];
    }
    auto&at(size_t n){
        if (n>=size()){
            throw std::out_of_range("");
        }
        return begin()[n];
    }
    auto&at(size_t n)const{
        if (n>=size()){
            throw std::out_of_range("");
        }
        return begin()[n];
    }
    void erase_front(size_t index){
        assert(index<size());
        for (size_t q=slice[0].begin_+index;q!=slice[0].begin_;--q){
            std::swap(items[q & items.size()-1],items[q-1 & items.size()-1]);
        }
        items[slice[0].begin_&items.size()-1][0].value.clear();
        for (size_t q=slice[0].begin_+index;q!=slice[0].begin_-1;--q){
            repair_element(q);
        }
        slice[0].begin_++;
    }
    void erase_back(size_t index){
        assert(index<size());
        for (size_t q=slice[0].begin_+index+1;q!=slice[0].end_;++q){
            std::swap(items[q & items.size()-1],items[q-1 & items.size()-1]);
        }
        items[slice[0].end_-1&items.size()-1][0].value.clear();
        for (size_t q=slice[0].begin_+index;q!=slice[0].end_;++q){
            repair_element(q);
        }
        slice[0].end_--;
    }
    void check(){
        assert(size()+4<=items.size());
        for (size_t q=slice[0].begin_;q-slice[0].end_ & items.size()-1;++q){
            assert(items[q&items.size()-1][0].value.data());
        }
        for (size_t q=slice[0].end_;q-slice[0].begin_ & items.size()-1;++q){
            assert(not items[q&items.size()-1][0].value.data());
        }
        for (size_t q=0;q<items.size();++q){
            assert(items[q][0].pos==q);
        }
    }
    template<typename Y=type>
    void push_back(Y&&val){
        insert_back(size(),std::forward<Y>(val));
    }
    template<typename Y=type>
    void push_front(Y&&val){
        insert_front(0,std::forward<Y>(val));
    }
    void pop_back(){
        erase_back(size()-1);
    }
    void pop_front(){
        erase_front(0);
    }
    template<typename Y,typename U=type>
    void insert(const Y&iter,U&&val){
        if (iter-begin()>end()-iter){
            insert_back(iter-begin(),std::forward<U>(val));
        }else{
            insert_front(iter-begin(),std::forward<U>(val));
        }
    }
    template<typename Y>
    void erase(const Y&iter){
        if (iter-begin()>end()-iter){
            erase_back(iter-begin());
        }else{
            erase_front(iter-begin());
        }
    }
    template<typename...Y>
    void recreate(Y&&...val){
        std::destroy_at(this);
        std::construct_at(this,std::forward<Y>(val)...);
    }
    Deque(){
        memory_at_least(front_space()+back_space());
    }
    Deque(const Deque&oth):
        items(oth.items),
        slice(oth.slice)
    {
        for (auto&w:items){
            repair_element(&w-&items[0]);
        }
    }
    Deque(Deque&&oth):
        items(std::move(oth.items)),
        slice(std::move(oth.slice))
    {
        if (this!=&oth){
            oth.recreate();
        }
    }
    template<typename...Y>
    void add(ssize_t len,Y&&...val){
        if (len<0){
            while (len++){
                pop_back();
            }
        }else{
            memory_at_least(len+front_space()+back_space());
            while (len--){
                insert_back(size(),std::forward<Y>(val)...);
            }
        }
    }
    template<typename...Y>
    explicit Deque(size_t len,Y&&...val){
        try{
            add(len,std::forward<Y>(val)...);
        }catch(...){
            recreate();
            items.clear();
            slice.clear();
            throw;
        }
    }
    template<typename Y=type>
    explicit Deque(size_t len,Y&&val){
        try{
            add(len,std::forward<Y>(val));
        }catch(...){
            recreate();
            items.clear();
            slice.clear();
            throw;
        }
    }
    template<typename O,typename=std::enable_if_t<std::is_same_v<std::decay_t<O>,Deque>,void>>
    auto&operator=(O&&oth){
        Deque tmp(std::forward<O>(oth));
        recreate(std::move(tmp));
        return *this;
    }
    auto&operator=(const Deque&oth){
        Deque tmp(std::forward<const Deque>(oth));
        recreate(std::move(tmp));
        return *this;
    }
};




template<typename t,typename=typename Deque<typename t::orig>::template is_iterator<t>>
auto operator-(const t&l,const t&r){return l.sub(r);}
template<typename t,typename=typename Deque<typename t::orig>::template is_iterator<t>>
auto operator<(const t&l,const t&r){return l.sub(r)<0;}
template<typename t,typename=typename Deque<typename t::orig>::template is_iterator<t>>
auto operator>(const t&l,const t&r){return l.sub(r)>0;}
template<typename t,typename=typename Deque<typename t::orig>::template is_iterator<t>>
auto operator<=(const t&l,const t&r){return l.sub(r)<=0;}
template<typename t,typename=typename Deque<typename t::orig>::template is_iterator<t>>
auto operator>=(const t&l,const t&r){return l.sub(r)>=0;}
template<typename t,typename=typename Deque<typename t::orig>::template is_iterator<t>>
auto operator==(const t&l,const t&r){return l.sub(r)==0;}
template<typename t,typename=typename Deque<typename t::orig>::template is_iterator<t>>
auto operator!=(const t&l,const t&r){return l.sub(r)!=0;}

template<typename t,typename=typename Deque<typename t::orig>::template is_iterator<t>>
auto operator+(const t&l,ssize_t off){auto tmp=l;tmp+=off;return tmp;}
template<typename t,typename=typename Deque<typename t::orig>::template is_iterator<t>>
auto operator+(ssize_t off,const t&l){auto tmp=l;tmp+=off;return tmp;}
template<typename t,typename=typename Deque<typename t::orig>::template is_iterator<t>>
auto operator-(const t&l,ssize_t off){auto tmp=l;tmp-=off;return tmp;}

