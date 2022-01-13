#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

int main(){
	size_t n;
	scanf("%zi",&n);
	auto a=new size_t[n];
	auto q=clock();
	for (size_t w=0;w<n;++w){
		a[w]=rand();
	}
	std::sort(a,a+n);
	q=1.0*(clock()-q)/CLOCKS_PER_SEC;
	printf("%ld\n",q);
	printf("%zi\n",a[rand()%n]);
}
