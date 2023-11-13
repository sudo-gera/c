#include <cstring>
#include <iterator>
#include <cstddef>
struct utf8iterator{
    unsigned char* ptr = nullptr;
    template<typename CHAR_PTR = char*,
        unsigned char = static_cast<unsigned char>(
            typename std::iterator_traits<CHAR_PTR>::value_type()
        )
    >
    utf8iterator(CHAR_PTR ptr = nullptr):
        ptr(reinterpret_cast<unsigned char*>(&*ptr))
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
        res = (res & 0x00'ff'00'ff) << 8  | (res & 0x3f'00'3f'00) >> 6;
        res = (res & 0x00'00'ff'ff) << 16 | (res & 0x3f'3f'00'00) >> 12;
        res &= -1U >> (5 * len - 1) / 4;
        res >>= 30 - 6 * len;
        return res;
    }
    operator char*()const{
        return reinterpret_cast<char*>(ptr);
    }
    using difference_type = std::ptrdiff_t;
    using value_type = char32_t;
    using pointer = const char32_t*;
    using reference = const char32_t&;
    using iterator_category = std::bidirectional_iterator_tag;
};

#if defined(__INCLUDE_LEVEL__) and __INCLUDE_LEVEL__ == 0
#include <string>
#include <iostream>
int main(){
    std::string s = "က𐀀œ0`";
    for (auto it = utf8iterator(s.begin()); it != utf8iterator(s.end()); ++it){
        std::cout << size_t(*it) << std::endl;
    }
}
#endif
