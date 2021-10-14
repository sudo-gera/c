#include "header.hpp"
_std

template <typename T>
void radixsort(T a,size_t n){
	size_t k=100;
	size_t*c=(size_t*)calloc(sizeof(size_t),k);
	ssize_t*b=(ssize_t*)calloc(sizeof(ssize_t),n);
	for(size_t q=0;q<n;++q){
		++c[a[q]];
	}
	for(size_t q=1;q<k;++q){
		c[q]+=c[q-1];
	}
	for(ssize_t q=n-1;q>0;--q){
		--c[a[q]];
		b[c[a[q]]]=a[q];
	}
	for(size_t q=0;q<n;++q){
		a[q]=b[q];
	}
}


_main{
	auto q=vector({11,22,33,44,55,66,77,88});
	radixsort(q.begin(),q.size());
	for (auto w:q){
		write(w,' ');
	}
	print();
}