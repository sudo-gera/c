#include <cstring>
#include <iterator>
struct utf8iterator{
    unsigned char* ptr = nullptr;
    template<typename CHAR_PTR = char*, unsigned char = static_cast<unsigned char>(typename std::iterator_traits<CHAR_PTR>::value_type())>
    utf8iterator(CHAR_PTR ptr = nullptr):
        ptr((unsigned char*)&*ptr)
    {}
    unsigned size()const{
        unsigned symbol = *ptr;
        return 13 / (10 - (symbol & symbol * 2) / 32);
    }
    auto& operator++(){
        ptr += size();
        return *this;
    }
    auto& operator--(){
        while ((*--ptr & 192) == 128){}
        return *this;
    }
    auto operator++(int){
        auto tmp = *this;
        ++*this;
        return tmp;
    }
    auto operator--(int){
        auto tmp = *this;
        --*this;
        return tmp;
    }
    friend bool operator==(utf8iterator left, utf8iterator right){
        return left.ptr == right.ptr;
    }
    auto operator*()const{
        char32_t res = 0;
        unsigned len = size();
        std::memmove(&res, ptr, len);
        std::swap(((char*)&res)[0], ((char*)&res)[3]);
        std::swap(((char*)&res)[1], ((char*)&res)[2]);
        // unsigned first_len = len == 1 ? len : len+1;
        unsigned first_len = 2 * len - (len-1)*8/9 - 1;
        res = res & 0xff'ff'ff'00u | (res & 0x00'00'00'3fu) << 2;
        res = res & 0xff'ff'00'00u | (res & 0x00'00'3f'ffu) << 2;
        res = res & 0xff'00'00'00u | (res & 0x00'3f'ff'ffu) << 2;
        res = res & 0x00'00'00'00u | (res & 0x3f'ff'ff'ffu) << first_len;
        res >>= 6 + first_len;
        res >>= 6 * (4-len);
        return res;
    }
    using value_type = char32_t;
};

#if defined(__INCLUDE_LEVEL__) and __INCLUDE_LEVEL__ == 0
#include <string>
#include <iostream>
int main(){
    std::string s = "";
    for (auto it = utf8iterator(s.begin()); it != utf8iterator(s.end()); ++it){
        std::cout << size_t(*it) << std::endl;
    }
}
#endif
