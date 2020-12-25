#include <iostream>
#define int int64_t
struct a{
 char d[7];
};
decltype(0) main(){
 a* d=0;
 std::cout<<(int)(d)<<'\n';
 d++;
 std::cout<<(int)(d)<<'\n';
 d+=3;
 std::cout<<(int)(d)<<'\n';
}
