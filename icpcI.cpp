#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(){
	size_t n;
	scanf("%zu",&n);
	int x[500000];
	int y[500000];
	for (size_t w=0;w<n;++w){
		scanf("%i",x+w);
		scanf("%i",y+w);
	}
	long double res=0;
	for (size_t w=0;w<n;++w){
		for (size_t e=0;e<w;++e){
			res+=sqrtf((x[w]-x[e])*(x[w]-x[e])+(y[w]-y[e])*(y[w]-y[e]));
		}
	}
	printf("%Lf\n",res);
}
