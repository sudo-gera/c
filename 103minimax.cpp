#include <stdio.h>
#include <stdint.h>

int main(){
	int n,m,l;
	scanf("%i%i%i",&n,&m,&l);
	auto a=new int64_t*[n];
	for (size_t w=0;w<n;++w){
		a[w]=new int64_t[l];
		for (size_t e=0;e<l;++e){
			scanf("%lli",a[w]+e);
			a[w][e]*=10000;
			a[w][e]+=e;
		}
	}
	auto b=new int64_t*[m];
	for (size_t w=0;w<m;++w){
		b[w]=new int64_t[l];
		for (size_t e=0;e<l;++e){
			scanf("%lli",b[w]+e);
			b[w][e]*=10000;
			b[w][e]+=999-e;
		}
	}
	int q;
	scanf("%i",&q);
	for (size_t w=0;w<q;++w){
		int i,j;
		scanf("%i%i",&i,&j);
		size_t z=0,x,c,v=l-1;
		// ic(itervect(a[i-1],a[i-1]+l))
		// ic(itervect(b[j-1],b[j-1]+l))
		while(v-z>2){
			x=(z+z+v)/3;
			c=(z+v+v)/3;
			auto _b=a[i-1][x]>b[j-1][x]?a[i-1][x]:b[j-1][x];
			auto _n=a[i-1][c]>b[j-1][c]?a[i-1][c]:b[j-1][c];
			// ic(z,x,c,v,_b,_n)
			if (_b<_n){
				v=c;
			}
			if (_b>_n){
				z=x;
			}
			if (_b==_n){
				z=x;
				v=c;
			}
		}
		size_t m=1000000000000000;
		size_t k=0;
		for (size_t e=z;e<v+1;++e){
			auto z=a[i-1][e]>b[j-1][e]?a[i-1][e]:b[j-1][e];
			if (z<m){
				k=e+1;
				m=z;
			}
		}
		printf("%zu\n",k);
	}
}