#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <vector>

// #define get_int(res)\
// {\
// 	int8_t sign=1;\
// 	int c;\
// 	while (c=getchar_unlocked(),isspace(c)){\
// 	}\
// 	if (c=='-'){\
// 		sign*=-1;\
// 		res=0;\
// 	}else{\
// 		res=c-'0';\
// 	}\
// 	while (c=getchar_unlocked(),c!=EOF and !isspace(c)){\
// 		res*=10;\
// 		res+=c-'0';\
// 	}\
// 	res*=sign;\
// }

// char put_data[44];

// #define put_int(_q)\
// {\
// 	auto q=_q;\
// 	unsigned long long t;\
// 	if (std::is_signed<decltype(q)>::value and q<0){\
// 		putchar_unlocked('-');\
// 		t=-q;\
// 	}else{\
// 		t=q;\
// 	}\
// 	unsigned ds=1;\
// 	while (t){\
// 		put_data[ds++]=t%10+'0';\
// 		t/=10;\
// 	}\
// 	if (ds==1){\
// 		putchar_unlocked('0');\
// 	}else{\
// 		for (--ds;ds;ds--){\
// 			putchar_unlocked(put_data[ds]);\
// 		}\
// 	}\
// }

#define put_int(_q)\
{\
	ssize_t q=_q;\
	printf("%zi",q);\
}

#define get_int(_q)\
{\
	ssize_t q;\
	scanf("%zi",&q);\
	_q=q;\
}

ssize_t corner(std::vector<std::vector<std::vector<ssize_t>>>&f,ssize_t _x,ssize_t _y,ssize_t _z){
	ssize_t x,y,z;
	x=_x;
	ssize_t res=0;
	while (x>=0){
		y=_y;
		while(y>=0){
			z=_z;
			while(z>=0){
				res+=f[x][y][z];
				z=z&(z+1);
				z-=1;
			}
			y=y&(y+1);
			y-=1;
		}
		x=x&(x+1);
		x-=1;
	}
	return res;
}

int main(){
	size_t n;
	get_int(n);
	std::vector<std::vector<std::vector<ssize_t>>> f(n,std::vector<std::vector<ssize_t>>(n,std::vector<ssize_t>(n)));
	while (1){
		size_t m;
		get_int(m);
		if (m==1){
			ssize_t x,y,z,k,_x,_y,_z;
			get_int(_x);
			get_int(_y);
			get_int(_z);
			get_int(k);
			x=_x;
			while(x<n){
				y=_y;
				while(y<n){
					z=_z;
					while(z<n){
						f[x][y][z]+=k;
						z=z|(z+1);
					}
					y=y|(y+1);
				}
				x=x|(x+1);
			}
		}else
		if (m==2){
			ssize_t x1,x2,y1,y2,z1,z2;
			get_int(x1);
			get_int(y1);
			get_int(z1);
			get_int(x2);
			get_int(y2);
			get_int(z2);
			put_int(
				corner(f,x2  ,y2  ,z2  )-
				corner(f,x2  ,y2  ,z1-1)+
				corner(f,x2  ,y1-1,z2  )-
				corner(f,x2  ,y1-1,z1-1)+
				corner(f,x1-1,y2  ,z2  )-
				corner(f,x1-1,y2  ,z1-1)+
				corner(f,x1-1,y1-1,z2  )-
				corner(f,x1-1,y1-1,z1-1)
			);
			putchar_unlocked('\n');
		}else{
			break;
		}
	}
}
