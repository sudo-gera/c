#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

int main(){
	int n,m;
	int v[100000];
	int p[100000];
	scanf("%i%i",&n,&m);
	for (int w=0;w<n;++w){
		scanf("%i",v+w);
	}
	for (int w=0;w<m;++w){
		scanf("%i",p+w);
	}
	std::sort(v,v+n);
	for (int w=0;w<m;++w){
		bool breaked=0;
		for (int e=0;e<n;++e){
			auto t=std::lower_bound(v,v+n,v[e]-p[w]);
			if (std::upper_bound(v,v+n,v[e]-p[w])!=t){
				printf("%i %i\n",v[e],*t);
				breaked=1;
				break;
			}
		}
		if (breaked==0){
			printf("Not found\n");
		}
	}
}