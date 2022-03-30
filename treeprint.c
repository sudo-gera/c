#include "treeprint.h"
#include "heap.h"

long a[999];
size_t l=0;

void* get_left(void *q){
	long* w=(long *)q;
	w=(w-a+1)*2-1+a;
	if (w-a>=l){
		return 0;
	}else{
		return w;
	}
}

void* get_right(void *q){
	long* w=(long *)q;
	w=(w-a+1)*2+a;
	if (w-a>=l){
		return 0;
	}else{
		return w;
	}
}

void* get_str(void *q){
	long* w=(long *)q;
	char *a=(char*)malloc(99);
	sprintf(a,"%li",*w);
	return a;
}


int main(){
	l=20;
	for (size_t w=0;w<l;++w){
		a[w]=w;
		PushHeap(a,a+w+1);
	}
	treeprint(a,get_left,get_right,get_str);
}
