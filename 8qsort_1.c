#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>

struct data{
	int val;
	char**a;
};

int cmp_data(const void* p1, const void* p2)
{
	struct data d=*(const struct data*)(p1);
	struct data s=*(const struct data*)(p2);
	int q=d.val;
	int w=s.val;
	char**a=d.a;
	if (q<w){
		return (a[w][q]-44);
	}
	if (q>w){
		return (44-a[w][q]);
	}
	return 0;
}

int main()
{
	int n;
	scanf("%i",&n);
	char**a=(char**)malloc(sizeof(char*)*n);
	for (int w=0;w<n;++w){
		a[w]=(char*)malloc(sizeof(char)*(w+2));
		scanf("%s",a[w]);
	}
	struct data*s=(struct data*)malloc(sizeof(struct data)*n);
	for (int w=0;w<n;++w){
		s[w].val=w;
		s[w].a=a;
	}
	qsort(s,n,sizeof(s[0]),cmp_data);
	for (int w=0;w<n;++w){
		printf("%i ",s[w].val-1);
	}
	printf("\n");
}
