#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

int main(int argc, char const *argv[])
{
	// int a[4`000`000];
	int n;
	scanf("%i",&n);
	int a[2*n];
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
	printf("%i\n",s%1000000000);
	return 0;
}