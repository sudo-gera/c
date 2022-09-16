template<typename T,typename ADD>
struct iterator{
    T p=0;
    long long o=0;
    iterator(){}
    template<typename Y=const T>
    iterator(Y&&r):p(r){}
    auto&operator+=(long long n){
        n+=o;
        o=0;
        while(n){
            auto t=ADD{}(p,n);
            if (!t){
                o+=n/2;
                n-=n/2;
            }else{
                p=t;
                n=o;
                o=0;
            }
        }
        return *this;
    }
    auto&operator-=(long long n){
        return *this+=(-n);
    }
    auto&operator*(){
        *this+=0;
        return *(this->p);
    }
    auto&operator[](long long n){
        auto t=*this;
        t+=n;
        return *t;
    }
    long long can_add(){
        *this+=0;
        auto t=*this;
        t+=1LL<<62;
        return (1LL<<62)-t.o;
    }
    long long can_sub(){
        *this+=0;
        auto t=*this;
        t-=1LL<<62;
        return (1LL<<62)+t.o;
    }
};

template<typename T,typename ADD>
long long operator-(const iterator<T,ADD> q,const iterator<T,ADD> e){
    return q.can_sub()-e.can_sub();
}

template<typename T,typename ADD>
bool operator<(const iterator<T,ADD> q,const iterator<T,ADD> e){
    return q-e<0;
}

template<typename T,typename ADD>
bool operator>(const iterator<T,ADD> q,const iterator<T,ADD> e){
    return q-e>0;
}

template<typename T,typename ADD>
bool operator<=(const iterator<T,ADD> q,const iterator<T,ADD> e){
    return q-e<=0;
}

template<typename T,typename ADD>
bool operator>=(const iterator<T,ADD> q,const iterator<T,ADD> e){
    return q-e>=0;
}

int main(){
    
}