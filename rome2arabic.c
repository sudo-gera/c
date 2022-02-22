#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

int main()
{
    char a[1024];
    int s[1024];
    scanf("%s", a);
    size_t la = strlen(a);
    for (size_t w = 0; w < la; ++w) {
        switch (a[w]) {
        case 'I':
            s[w] = 1;
            break;
        case 'V':
            s[w] = 5;
            break;
        case 'X':
            s[w] = 10;
            break;
        case 'L':
            s[w] = 50;
            break;
        case 'C':
            s[w] = 100;
            break;
        case 'D':
            s[w] = 500;
            break;
        case 'M':
            s[w] = 1000;
            break;
        }
    }
    for (size_t w = 0; w < la; ++w) {
        for (size_t e = w; e < la; e++) {
            if (s[e] > s[w]) {
                s[w] = -s[w];
                break;
            }
        }
    }
    size_t d = 0;
    for (size_t w = 0; w < la; ++w) {
        d += s[w];
    }
    printf("%zu\n", d);
}
	
