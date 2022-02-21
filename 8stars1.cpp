#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <vector>

int main(){
	ssize_t n;
	scanf("%zi",&n);
	std::vector<std::vector<std::vector<ssize_t>>> s(n,std::vector<std::vector<ssize_t>>(n,std::vector<ssize_t>(n)));
	while (1){
		ssize_t m;
		scanf("%zi",&m);
		if (m==1){
			ssize_t x,y,z,k;
			scanf("%zi%zi%zi%zi",&x,&y,&z,&k);
			s[x][y][z]+=k;
		}
		else if (m==2){
			ssize_t x1,y1,z1,x2,y2,z2;
			scanf("%zi%zi%zi%zi%zi%zi",&x1,&y1,&z1,&x2,&y2,&z2);
			ssize_t res=0;
			for (ssize_t w=x1;w<x2+1;++w){
				for (ssize_t e=y1;e<y2+1;++e){
					for (ssize_t r=z1;r<z2+1;++r){
						res+=s[w][e][r];
					}
				}
			}
			printf("%zi\n",res);
		}
		else{
			break;
		}
	}
}
