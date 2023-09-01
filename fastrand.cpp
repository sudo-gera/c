#include <stddef.h>
struct fast_rand{
    size_t state=1;
    constexpr fast_rand(size_t state=1):
        state(state){}
    constexpr auto operator()(){
        state ^= state << 21;
        state ^= state >> 35;
        state ^= state << 4;
        return state;
    }
    constexpr operator size_t(){
        return (*this)();
    }
};

constexpr size_t make_seed(){
    char const* str = __DATE__ __TIME__ __TIMESTAMP__;
    size_t hash=0;
    while (str[0]){
        hash *= 257;
        hash += str[0];
        ++str;
    }
    return hash;
}
