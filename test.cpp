#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, char **argv) {
	int step = argc > 1 ? atoi(argv[1]) : 1;
	int size = argc > 2 ? atoi(argv[2]) : 1024*1024*512;
	int *a = new int[size];
	for (int i = 0; i < size; i++) {
		if ((i & 63) == 0) a[i] = rand();
		else		 a[i] = i-a[i-1];
	}
	long long sum = 0;
	clock_t start = clock();
	for (int i = 0; i < size; i += step ) {
		sum += a[i];
	}
	clock_t end = clock();
	printf("sum=%lld time=%.4f\r", sum, (double)(end - start) / CLOCKS_PER_SEC);
	printf("                                                                                   \r");
	{
		auto d=(double)(end - start) / CLOCKS_PER_SEC;
		d*=100;
		auto f=int(d);
		printf("\x1b[92m");
		for (int w=0;w<f;++w){
			printf("#");
		}
		printf("\x1b[0m\n");
		// printf("\n");
	}
	delete [] a;
}
