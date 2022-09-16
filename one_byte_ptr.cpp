#include <unordered_map>
std::unordered_map<void*,void*> one_byte_ptr_mem;
template<typename T>
struct one_byte_ptr{
    uint8_t u=0;
    one_byte_ptr(){}
    one_byte_ptr(T*o){
        one_byte_ptr_mem[this]=o;
    }
    one_byte_ptr(const one_byte_ptr&u){
        one_byte_ptr_mem[this]=one_byte_ptr_mem[&u];
    }
    auto&operator=(const one_byte_ptr&u){
        one_byte_ptr_mem[this]=one_byte_ptr_mem[&u];
    }
    one_byte_ptr(one_byte_ptr&&u){
        one_byte_ptr_mem[this]=one_byte_ptr_mem[&u];
        one_byte_ptr_mem.erase(&u);
    }
    auto&operator=(one_byte_ptr&&u){
        one_byte_ptr_mem[this]=one_byte_ptr_mem[&u];
        one_byte_ptr_mem.erase(&u);
        return*this;
    }
    ~one_byte_ptr(){
        one_byte_ptr_mem.erase(this);
    }
    operator T*(){
        return (T*)(one_byte_ptr_mem[this]);
    }
    auto&operator [](int n){
        return ((T*)(one_byte_ptr_mem[this]))[n];
    }
    auto&operator *(){
        return *(T*)(one_byte_ptr_mem[this]);
    }
    auto operator->(){
        return (T*)(one_byte_ptr_mem[this]);
    }
};
