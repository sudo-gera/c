#include <algorithm>
#include <any>

struct Any;

struct base_holder{
    virtual ~base_holder(){}
    virtual base_holder* create_copy() = 0;
};

template<typename T>
struct typed_holder:base_holder{
    T value;
    typed_holder(const typed_holder&oth):
        value(oth.value)
    {}
    typed_holder(typed_holder&oth):
        value(oth.value)
    {}
    typed_holder(typed_holder&&oth):
        value(std::move(oth.value))
    {}
    template<typename...Y>
    typed_holder(Y&&...val):
        value(std::forward<std::decay_t<decltype(val)>>(val)...)
    {}
    base_holder* create_copy() override{
        return new typed_holder<T>(*this);
    }
    ~typed_holder()override{}
};

struct Any{
    base_holder* ptr=nullptr;
    Any(){}
    Any(Any&&oth){
        ptr=oth.ptr;
        oth.ptr=nullptr;
    }
    template<typename T>
    Any(T&&val,std::enable_if_t<
        !std::is_same_v<T,Any> and
        !std::is_same_v<T,const Any> and
        !std::is_same_v<T,Any&> and
        !std::is_same_v<T,const Any&> and
        1
        ,int
    > =0){
        ptr=new typed_holder<T>(std::forward<T>(val));
    }
    template<typename Y,typename...T>
    void emplace(T&&...val){
        auto tmp=new typed_holder<Y>(std::forward<T>(val)...);
        this->~Any();
        ptr=tmp;
    }
    void Swap(Any&oth){
        std::swap(ptr,oth.ptr);
    }
    Any(const Any&oth){
        if (&oth!=this){
            ptr=oth.ptr->create_copy();
        }
    }
    template<typename T>
    auto&operator=(T&& oth){
        Any tmp(std::forward<T>(oth));
        this->Swap(tmp);
        return *this;
    }
    ~Any(){
        delete ptr;
        ptr=nullptr;
    }
    bool HasValue()const{
        return ptr;
    }
    void Reset(){
        this->~Any();
    }
};

template <typename T>
T AnyCast(const Any&o){
    if (auto p=dynamic_cast<typed_holder<std::decay_t<T>>*>(o.ptr)){
        return static_cast<T>(p->value);
    }else{
        throw std::bad_any_cast();
    }
}


template <typename T,typename...Y>
Any MakeAny(Y&&...args){
    Any r;
    r.emplace<T>(args...);
    return r;
}



#if __has_include("/Users/gera/c/h")
#ifndef REQUIRE
#define SECTION(...)
#define REQUIRE ic
void run(){
}
    any a=123,s="123"s;
#endif
#endif
