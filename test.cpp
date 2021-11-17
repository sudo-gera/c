<<<<<<< HEAD
#include<stdio.h>
int main(){
printf("hello linux terminal\n");}
=======
#include "h"

uint32_t SquareRootRounded(uint32_t a_nInput)
{
    uint32_t q  = a_nInput;
    uint32_t r = 0;
    uint32_t p = 1uL << 30; // The second-to-top bit is set: use 1u << 14 for uint16_t type; use 1uL<<30 for uint32_t type


    // "p" starts at the highest power of four <= than the argument.
    // while (p > q)
    // {
    //     p >>= 2;
    // }

    while (p != 0)
    {
        if (q >= r + p){
            q -= (r + p);
            r +=  2 * p;
        }
        r >>= 1;
        p >>= 2;
    }

    /* Do arithmetic rounding to nearest integer */
    // if (q > r)
    // {
    //     r++;
    // }

    return r;
}

µ{
	// for (w:range(29)){
	// 	print(w,SquareRootRounded(w)*SquareRootRounded(w));
	// }


	print(SquareRootRounded(49));

}


>>>>>>> 5d8df70213d7fc81253b7bfcc6ca5f217e24a294
