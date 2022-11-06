# 1 "test.cpp"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 460 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "test.cpp" 2
# 126 "test.cpp"
template<typename T>
struct assign_s{
    T f;
};

template<typename T,typename Y>
T&& operator|(T&&q,assign_s<Y>e){
    e.f.fun(&q,&e.f.r);
    return q;
}

template<typename T>
assign_s<T> assign_f(T q){
    return assign_s<T>(q);
}
# 172 "test.cpp"
int main(){
    long q=1,w=2;
    q|assign_f(
        (
            {
                struct{
                    void fun(
                        void*ptr_l,void*ptr_r
                    ){
                        auto __t=min (
                            *(
                                typename remove_reference<decltype(w)>::type*
                            )(ptr_l),*(
                                typename remove_reference<decltype(w)>::type*
                            )(ptr_l)
                        );*(
                            typename remove_reference<decltype(w)>::type*
                        )(ptr_l)=__t;
                    };
                    typename remove_reference<decltype(w)>::type r=(w);
                }()
            }
        )
    );
}
