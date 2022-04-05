#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>
#include <iostream>
using namespace std;


int main(){
	float f=-39.77f;
	uint8_t*a=(uint8_t*)(&f);
	for (int w=0;w<sizeof(f);++w){
		for (int e=0;e<8;++e){
			uint8_t t=a[w];
			t>>=w;
			t%=2;
			if (t){
				cout<<1;
			}else{
				cout<<0;
			}
		}
	}
}
