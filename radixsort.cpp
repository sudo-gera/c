#include "h"

void radixsort(vector<int64_t>&A){
	n=len(A)
	if (A.size()){
		m=A[0];
		for (size_t w=1;w<n;++w){
			m=m<A[w]?m:A[w];
		}
		for (size_t w=1;w<n;++w){
			A[w]-=m;
		}
		for w in range(len(str(max(A)))+4){
			k=10;
			B=[0]*n;
			C=[0]*k;
			for i in range(k):
				C[i] = 0;
			for i in range(n):
				C[(A[i])/10**w%k] += 1;
			for j in range(1,k):
				C[j] += C[j - 1];
			for i in range(n-1,-1,-1):
				C[(A[i])/10**w%k] -= 1;
				B[C[(A[i])/10**w%k]] = A[i];
			A=B
		}
		for (size_t w=1;w<n;++w){
			A[w]+=m;
		}
	}
	return A
}

ima{

}