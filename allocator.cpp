template<size_t n>
struct StackStorage{
    void* data[n];
    void** head=data;
    StackStorage(){
        
    }
}

template<typename T,size_t n>
struct StackAllocator{

};

