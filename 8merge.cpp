#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <inttypes.h>

int main(int argc, char const *argv[])
{
	// int a[4`000`000];
	int n;
	scanf("%i",&n);
	int*a=new int[2*n];
	for (int q=0;q<n;++q){
		scanf("%i",a+q);
	}
	// int s[n+1];
	for (int q=0;q<n;++q){
		scanf("%i",a+n+q);
	}
	std::sort(a,a+n+n);
	int64_t s=0;
	for (int q=0;q<n*2;q+=2){
		s+=a[q];
	}
	delete[] a;
	printf("%" PRId64 "\n",s%1000000000);
	return 0;
}
