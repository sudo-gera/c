#define bit_get(a,s)   (((a)[(s)/8/sizeof((a)[0])]>>(s)%(8*sizeof((a)[0])))&1)

#include <stdio.h>

int main(){
	for (long double f=1;f+1!=f;f*=2){
//	for (long double f=-9;f<9;f++){
		f+=1;
		unsigned*p=(unsigned*)&f;
		for (long w=0;w<sizeof(f)*8;++w){
			printf("%i",bit_get(p,w));
		}
		printf(" %Lf\n",f);
		f-=1;
	}
}
