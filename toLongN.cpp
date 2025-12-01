typedef struct{
	char *dig;	// массив для хранения числа:
// a[0] * 100^0 + a[1] * 100^1 + .. + a[n - 1] * 100^(n-1)
	int n; 			// размер числа в разрядах
	char sign;	// знак числа
}LongN;

#include <iso646.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
LongN getLongN(char * _s){
    size_t l = strlen(_s);
    char* s = (char*)malloc(l+1);
    memmove(s, _s, l+1);
    LongN data{
        .dig = (char*)calloc(l, 1),
        .n = (int)(l / 2),
        .sign = (s[0] == '-'),
    };
    for (size_t i = 0; i*2 < l; ++i){
        char t = s[i];
        s[i] = s[l-1-i];
        s[l-1-i] = t;
    }
    for (size_t i = 0; i < l; ++i){
        if (i){
            data.dig[i/2] += (s[i]-'0') * 10;
        }else{
            data.dig[i/2] += (s[i]-'0');
        }
    }
    return data;
}

#include <iostream>
int main(){
    auto tmp = getLongN((char*)"-1234567");
    std::cout << (int)tmp.sign << std::endl;
    std::cout << tmp.n << std::endl;
    std::cout << (int)(tmp.dig[0]) << std::endl;
    std::cout << (int)(tmp.dig[1]) << std::endl;
    std::cout << (int)(tmp.dig[2]) << std::endl;
    std::cout << (int)(tmp.dig[3]) << std::endl;
    std::cout << (int)(tmp.dig[4]) << std::endl;
    std::cout << (int)(tmp.dig[5]) << std::endl;
    std::cout << (int)(tmp.dig[6]) << std::endl;
}
