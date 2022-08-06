#include "one_byte_ptr.cpp"
#include <iostream>
int main(){
    one_byte_ptr<int> a[300];
    for (int w=0;w<300;++w){
        a[w]=new int(w*w);
    }
    for (int w=0;w<300;++w){
        std::cout<<(uint64_t)(reinterpret_cast<uint8_t&>(a[w]))<<std::endl;
    }
    
}