#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <iso646.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <iostream>
using namespace std;

int main(){
	long q[8];
	for (long i = 0; i < 8;++i){
		cin>>q[i];
	}
	auto a=new long*[99];
	for (long i = 0; i < 99;++i){
		a[i]=40+(new long[99]);
	}
	a+=40;
	for (long w=-20;w<=20;++w){
		for (long e=-20;e<=20;++e){
			a[w][e]='.';
		}
	}
	for (long w=0;w<q[0];++w){
		a[-w][0]='#';
	}
	for (long w=0;w<q[1];++w){
		a[-w][w]='#';
	}
	for (long w=0;w<q[2];++w){
		a[0][w]='#';
	}
	for (long w=0;w<q[3];++w){
		a[w][w]='#';
	}
	for (long w=0;w<q[4];++w){
		a[w][0]='#';
	}
	for (long w=0;w<q[5];++w){
		a[w][-w]='#';
	}
	for (long w=0;w<q[6];++w){
		a[0][-w]='#';
	}
	for (long w=0;w<q[7];++w){
		a[-w][-w]='#';
	}
	long u=20,d=20,l=20,r=20;
	while (1){
		long nf=1;
		for (long w=-20;w<=20;++w){
			if (a[-u][w]=='#'){
				nf=0;
				break;
			}
		}
		if (nf){
			u--;
		}else{
			break;
		}
	}
	while (1){
		long nf=1;
		for (long w=-20;w<=20;++w){
			if (a[d][w]=='#'){
				nf=0;
				break;
			}
		}
		if (nf){
			d--;
		}else{
			break;
		}
	}
	while (1){
		long nf=1;
		for (long w=-20;w<=20;++w){
			if (a[w][-l]=='#'){
				nf=0;
				break;
			}
		}
		if (nf){
			l--;
		}else{
			break;
		}
	}
	while (1){
		long nf=1;
		for (long w=-20;w<=20;++w){
			if (a[w][r]=='#'){
				nf=0;
				break;
			}
		}
		if (nf){
			r--;
		}else{
			break;
		}
	}
	for (long w=-u;w<=d;++w){
		for (long e=-l;e<=r;++e){
			putchar(a[w][e]);
		}
		putchar('\n');
	}
}
