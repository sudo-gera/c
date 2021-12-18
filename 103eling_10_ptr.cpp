
#if __has_include("h")
#define N 100
struct _Decimal {
    char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
};
typedef struct _Decimal Decimal;

// Decimal zero = {{0}, 0};    // представление 0 в виде структуры
#endif


int is_even (Decimal * a){
    return !(a->a[0]%2);
}


#if __has_include("h")
#include "h"
int main(){
    Decimal a = {{1}, 0};  // set number 147
    int res;
    
    res = is_even(&a);          // res=0 because 147 is NOT even
    printf("%d\n", res);
    
    return 0;
}
#endif