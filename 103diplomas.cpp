#include <stdio.h>
#include <stdlib.h>

int64_t root(int64_t q){
	int64_t o=-1;
	int64_t p=q+1;
	while (p-o>1){
		int64_t c=(p+o)/2;
		int64_t s=c*c;
		if(s>q){
			p=c;
		}
		else if (s<q){
			o=c;
		}
		else{
			p=c;
			o=c;
		}
	}
	return o;
}

int main(){
	int64_t w,h,n;
	scanf("%lli%lli%lli",&w,&h,&n);
	int64_t ph=(root(w)+1)*(root(n)+1)/root(h);
	int64_t lh=(root(w))*(root(n))/(root(h)+1);
	int64_t pw=(root(w)+1)*(root(n)+1)/root(h);
	int64_t lw=(root(w))*(root(n))/(root(h)+1);
	// int64_t pw=root(h)*root(n)/root(w);
	int64_t r=uint64_t(-1)/2-1;
	// int64_t lh=0;
	// int64_t lw=0;
	for(;(ph+lh)*(pw)<n;++lh){}
	for(;(ph)*(pw+lw)<n;++lw){}
	for(int ih=0;ih<lh+1;++ih){
		for(int iw=0;iw<lw+1;++iw){
			if ((ph+ih)*(pw+iw)>=n){
				int y=(ph+ih)*h>(pw+iw)*w?(ph+ih)*h:(pw+iw)*w;
				printf("%i\n", y);
				r=r>y?y:r;
			}
		}
	}
	printf("%lli\n",r);
	printf("%lli %lli\n",pw,ph);
	printf("%lli %lli\n",lw,lh);
}