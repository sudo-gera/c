#ifndef M1
#define M1
#endif
M1
#undef M1



const char*a="(
#include "test.txt"
)";

// #ifndef M2
//     #define CAT_(x,y) x##y
//     #define CAT(x,y) CAT_(x,y)
//     #define M1 CAT(R,")
//     #define M2 CAT(",R)
//     #include __FILE__
// #endif


#ifndef M2
#define M2
#endif
M2
#undef M2