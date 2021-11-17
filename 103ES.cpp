#include <stdio.h>
#include <stdlib.h>


#define dsize (1<<20)

void makepromice(int* data,int l,int r,int x,int fl=0,int fr=dsize){
	if (fl==l and r==fr){
		data[(dsize+l)/(r-l)]+=x;
		return;
	}
	int fc=(fl+fr)/2;
	if (l<fc and fc<r){
		makepromice(data,l,fc,x,fl,fc);
		makepromice(data,fc,r,x,fc,fr);
		return;
	}
	if (l<fc and r<=fc){
		makepromice(data,l,r,x,fl,fc);
		// makepromice(fc,r,x,fc,fr);
		return;
	}
	if (fc<=l and fc<r){
		// makepromice(l,r,x,fl,fc);
		makepromice(data,l,r,x,fc,fr);
		return;
	}
	printf("unknown case %i %i %i %i %i %i\n",__LINE__,l,r,x,fl,fr);
	return;
}

void runpromice(int* data,int*a,int l=0,int r=dsize){
	// printf("%i %i %i\n",__LINE__,l,r);
	for(int w=l;w<r;++w){
		if (w<dsize){
			a[w]+=data[(dsize+l)/(r-l)];
		}
	}
	if (r-l>1){
		int c=(r+l)/2;
		runpromice(data,a,l,c);
		runpromice(data,a,c,r);
	}
}

int main(){
	int n,q;
	scanf("%i%i",&n,&q);
	int a[dsize];
	for(int w=0;w<n;++w){
		scanf("%i",a+w);
	}
	int* data=(int*)malloc(sizeof(int)*(dsize<<1));
	for(int w=0;w<dsize<<1;++w){
		data[w]=0;
	}
	int l,r,x;
	for(int w=0;w<q;++w){
		scanf("%i%i%i",&l,&r,&x);
		++r;
		makepromice(data,l,r,x);
	}
	// for(int w=0;w<dsize<<1;++w){
	// 	printf("%i ",data[w]);
	// }
	// printf("\n");
	runpromice(data,a);
	for (int w=0;w<n;++w){
		printf("%i ",a[w]);
	}
	printf("\n");

}