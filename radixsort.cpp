#include "h"

template <typename T>
void radixsort(T a,size_t n){
	if (n){
		auto min=a[0];
		for (size_t w=0;w<n;++w){
			min=a[0]<min?a[0]:min;
		}
		for (size_t w=0;w<n;++w){
			a[0]-=min;
		}
		auto max=a[0];
		for (size_t w=0;w<n;++w){
			max=a[0]>max?a[0]:max;
		}
		size_t k=1<<23;
		ssize_t B[n];
		size_t C[k];
		size_t i=0;
		size_t j=0;
		for(w=0;w<23*3;w+=23){
			for (i=0;i<k;++i){
				C[i] = 0;
			}
			for (i=0;i<n;++i){
				C[(A[i]>>w)&((1<<23)-1)] += 1;
			}
			for j in range(1,k):
				C[j] += C[j - 1];
			for i in range(n-1,-1,-1):
				C[(A[i])//10**w%k] -= 1;
				B[C[(A[i])//10**w%k]] = A[i];			
		}

	}
	

	for (w=1;w)

	for w in range(len(str(max(A)))+4):
		k=10
		B=[0]*n
		C=[0]*k
		for i in range(k):
			C[i] = 0;
		for i in range(n):
			C[(A[i])//10**w%k] += 1;
		for j in range(1,k):
			C[j] += C[j - 1];
		for i in range(n-1,-1,-1):
			C[(A[i])//10**w%k] -= 1;
			B[C[(A[i])//10**w%k]] = A[i];
		A=B
	return A
}

template <typename T>
bool cmp(T q,T w){
	return rand()%2;
}

ima{
	_rand
	auto q=vector({11,22,33,44,55,66,77,88});
	for (auto&d:q){
		swap(d,q[random(q.size())]);
	}
	print(q);
	radixsort(q.begin(),q.size());
	print(q);
}