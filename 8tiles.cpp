#include <stdio.h>
#include <stdlib.h>

__int128 scan__int(){
	long long int q;
	scanf("%lli",&q);
	return q;
}

void print__int(long long int q){
	printf("%lli\n",q);
}

int main(){
	__int128 w=scan__int(),h=scan__int(),n=scan__int();
	__int128 _b=0;
	__int128 _e=1LL<<62;
	// __int128 _e=1LL<<8;
	while (_e-_b>1){
		__int128 _c=(_b+_e)/2;
		__int128 _d=(_c/w)*(_c/h)-n;
		// ic(_b,_e,_c,_d)
		if (_d>0){
			_e=_c;
		}
		if (_d<0){
			_b=_c;
		}
		if (_d==0){
			_e=_c;
		}
	}
	// ic(_b,_e)
	print__int(_e);
}
