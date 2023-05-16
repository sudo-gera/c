#include <bits/stdc++.h>
using namespace std;

template<size_t n>
struct StackStorage{
    char data[n];
    size_t used=0;
    // constexpr static auto value=n;
    integral_constant<size_t,n> value(){
        return integral_constant<size_t,n>();
    }
    template<typename T>
    auto allocate(size_t l,size_t p){
        auto u=used%p;
        used+=u?p-u:0;
        used+=l;
        return (T*)(data+used-l);
    }
};

template<typename T,size_t n>
struct StackAllocator{
    StackStorage<n>* store=nullptr;
    using value_type=T;
    void deallocate(T* p,size_t l){}
    T* allocate(size_t l){
        return store->template allocate<T>(l*sizeof(T),alignof(T));
    }
    template<typename Y>
    struct rebind{
        using other=StackAllocator<Y,n>;
    };
    StackAllocator(StackStorage<n>& s):store(&s){}
    auto&get_allocator()const{
        return *store;
    }
    template<typename Y>
    StackAllocator(const StackAllocator<Y,n>&oth):store(&oth.get_allocator()){}
};

struct node{
    node* prev=nullptr;
    node* next=nullptr;
};

template<typename T,typename A>
struct List;


template<typename T,typename A=std::allocator<T>>
struct List:A,node{
    struct Node:node{
        T value;
    };
    size_t len=0;
    size_t size()const{
        return len;
    }
    List():node({this,this}){}
    List(A a):A(a),node({this,this}){}
    List(size_t n):node({this,this}){
        try{
            for (size_t q=0;q<n;++q){
                push_back();
            }
        }catch(...){
            this->~List();
            throw;
        }
    }
    List(size_t n,A a):A(a),node({this,this}){
        try{
            for (size_t q=0;q<n;++q){
                push_back();
            }
        }catch(...){
            this->~List();
            throw;
        }
    }
    auto&get_allocator()const{
        return *(A*)this;
    }
    template<typename Y>
    auto get_node_allocator(std::allocator<Y>* =nullptr){
        return allocator<Y>();
    }
    template<typename Y>
    auto get_node_allocator(Y* =nullptr){
        return A::template rebind<Y>::other(this->get_allocator());
    }
    // template<typename Y>
    // auto get_node_allocator(Y*s=nullptr)->decltype(get_node_allocator_1(s)){return get_node_allocator_1(s);}
    // template<typename Y>
    // auto get_node_allocator(Y*s=nullptr)->decltype(get_node_allocator_2(s)){return get_node_allocator_2(s);}
    List(List&&oth):
        A(oth.get_allocator()),
        node({
            oth.prev,
            oth.next
        }),
        len(oth.len)
    {
        oth.prev=oth.next=nullptr;
        oth.len=0;
        next->prev=this;
        prev->next=this;
    }
    List(const List&oth):
        A(oth.get_allocator()),
        node({this,this})
    {
        try{
            for (auto&w:oth){
                push_back(w);
            }
        }catch(...){
            this->~List();
            throw;
        }
    }
    auto&operator=(List&&oth){
        if (&oth!=this){
            this->~List();
            new(this)List(std::forward<decltype(oth)>(oth));
        }
        return *this;
    }
    auto&operator=(const List&oth){
        if (&oth!=this){
            auto tmp=oth;
            swap(tmp,*this);
        }
        return *this;
    }
    ~List(){
        while (len){
            pop_front();
        }
    }
    void check(){
        if (len==0){
            assert(this==next);
            assert(this==prev);
        }else{
            // ic(this)
            // ic(next)
            // ic(prev)
            auto q=next;
            size_t l=0;
            assert(q->prev==this);
            while (q!=this){
                // ic(q)
                // ic(q->next)
                // ic(q->prev)
                assert(q->next->prev==q);
                q=q->next;
                l+=1;
            }
            assert(l==len);
        }
    }
    template<typename Y>
    struct iter{
        using type=T;
        using a=A;
        using value_type=Y;
        using iterator_category=bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using pointer = Y*;
        using reference = Y&;
        node* n=nullptr;
        Y&operator*(){
            return ((Node*)n)->value;
        }
        auto&operator++(){
            n=n->next;
            return *this;
        }
        auto&operator--(){
            n=n->prev;
            return *this;
        }
        operator iter<const T>()const{
            return {n};
        }
        auto operator++(int){
            auto t=*this;
            ++*this;
            return t;
        }
        auto operator--(int){
            auto t=*this;
            --*this;
            return t;
        }
    };
    using iterator=iter<T>;
    using const_iterator=iter<const T>;
    using reverse_iterator=std::reverse_iterator<iter<T>>;
    using const_reverse_iterator=std::reverse_iterator<iter<const T>>;
    template<typename Y,typename U>
    using is_iterator=enable_if_t<
            is_same_v<decay_t<Y>,iter<T>>
        or  is_same_v<decay_t<Y>,iter<const T>>
    ,U>;
    void insert(auto it,auto&&...val){
        auto e=it.n;
        auto q=(--it).n;
        node* w=nullptr;
        T* mem=nullptr;
        try{
            mem=get_node_allocator<Node*>().allocate(1);
            auto w=(node*)new(mem)Node{{q,e},std::forward<decltype(val)>(val)...};
        }catch(...){
            get_node_allocator<Node*>().deallocate(mem,1);
            throw;
        }
        e->prev=w;
        q->next=w;
        len+=1;
    }
    void erase(auto it){
        auto q=(--it).n;
        auto w=(++it).n;
        auto e=(++it).n;
        q->next=e;
        e->prev=q;
        get_node_allocator<Node*>().deallocate(w,1);
        len-=1;
    }
    auto end(){
        return iter<T>{this};
    }
    auto cend()const{
        return iter<const T>{const_cast<node*>(static_cast<const node*>(this))};
    }
    auto end()const{
        return cend();
    }
    auto begin(){
        return ++end();
    }
    auto cbegin()const{
        return ++cend();
    }
    auto begin()const{
        return ++end();
    }
    auto rbegin(){
        return std::reverse_iterator(end());
    }
    auto crbegin()const{
        return std::reverse_iterator(cend());
    }
    auto rbegin()const{
        return std::reverse_iterator(end());
    }
    auto rend(){
        return std::reverse_iterator(begin());
    }
    auto crend()const{
        return std::reverse_iterator(cbegin());
    }
    auto rend()const{
        return std::reverse_iterator(begin());
    }
    void push_back(auto&&...val){
        insert(end(),std::forward<decltype(val)>(val)...);
    }
    void push_front(auto&&...val){
        insert(begin(),std::forward<decltype(val)>(val)...);
    }
    void pop_front(){
        erase(begin());
    }
    void pop_back(){
        erase(--end());
    }
};

template<typename T> auto operator==(T q,T w)->typename List<typename T::type,typename T::a>::template is_iterator<T,bool>{return q.n==w.n;}
template<typename T> auto operator!=(T q,T w)->typename List<typename T::type,typename T::a>::template is_iterator<T,bool>{return q.n!=w.n;}

#if __INCLUDE_LEVEL__==0
int main(){
    auto&l=*new List<int>;
    List<int>::const_iterator t=l.begin();
}
#endif
