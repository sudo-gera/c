
#define N 100
struct _Decimal {
    char a[N];   // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;       // наибольшая степень десяти
};
typedef struct _Decimal Decimal;

#include <iso646.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
Decimal add (Decimal a, Decimal b){
    a.n += 1;
    b.n += 1;
    memset(a.a + a.n, 0, N-a.n);
    memset(b.a + b.n, 0, N-b.n);
    for (size_t i = 0; i < N; ++i){
        a.a[i] += b.a[i];
        if (a.a[i] >= 10 and i+1 != N){
            a.a[i+1] += 1;
            a.a[i] -= 10;
        }
    }
    a.n = N;
    while (a.n > 1 and a.a[a.n-1] == 0){
        a.n -= 1;
    }
    a.n -= 1;
    return a;
}

int main(){
    Decimal a = {{7, 4, 1}, 2};  // set number 147
    Decimal b = {{3, 1}, 1};     // set number 13
    Decimal res;
    
    res = add(a, b);             // res = a+b = 147+13 = 160
    printf("%i\n", res.n);
    printf("%i\n", res.a[0]);
    printf("%i\n", res.a[1]);
    printf("%i\n", res.a[2]);
    printf("%i\n", res.a[3]);
    assert(res.n == 2);
    assert(res.a[0] == 0);
    assert(res.a[1] == 6);
    assert(res.a[2] == 1);
    
    return 0;
}

