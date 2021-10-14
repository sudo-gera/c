#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <utility>


int main(){
	size_t n,k;
	scanf("%i%i",&n,&k);
	// k=n;
	auto a=(int64_t*)malloc(sizeof(int64_t)*50000);
	// if (!a){return 0;}
	size_t s=1;
	for (size_t q=0;q<n;++q){
		int64_t w;
		scanf("%lli",&w);
		a[s]=w;
		size_t p=s++;
		while (p>1){
			if (a[p/2]>a[p]){
				std::swap(a[p],a[p/2]);
				p/=2;
			}else{
				break;
			}
		}
		// printf("\x1b[32m");
		// for (size_t q=0;q<k*8;++q){
		// 	if (q==s){
		// 		printf("\x1b[0m");
		// 	}
		// 	printf("%lli ",a[q]);
		// }
		// printf("\n");
		if (s>k+1){
			p=1;
			a[1]=a[s-1];
			while(p<s){
				if (2*p>=s){
					break;
				}
				if (2*p+1>=s){
					if (a[p]>a[2*p]){
						std::swap(a[p],a[2*p]);
						p*=2;
					}else{
						break;
					}
				}else{
					if (a[p]>a[2*p] and a[2*p]<=a[2*p+1]){
						std::swap(a[p],a[2*p]);
						p*=2;
					}else if (a[p]>a[2*p+1] and a[2*p+1]<a[2*p]){
						std::swap(a[p],a[2*p+1]);
						p*=2;
						p+=1;
					}else {
						break;
					}
				}
			}
			s-=1;
		}
		// printf("\x1b[32m");
		// for (size_t q=0;q<k*8;++q){
		// 	if (q==s){
		// 		printf("\x1b[0m");
		// 	}
		// 	printf("%lli ",a[q]);
		// }
		// printf("\n");
	}
	auto d=(int64_t*)malloc(sizeof(int64_t)*50000);
	size_t f=0;
	while(s>1){
		d[f++]=a[1];
		int64_t p=1;
		a[1]=a[s-1];
		while(p<s){
			if (2*p>=s){
				break;
			}
			if (2*p+1>=s){
				if (a[p]>a[2*p]){
					std::swap(a[p],a[2*p]);
					p*=2;
				}else{
					break;
				}
			}else{
				if (a[p]>a[2*p] and a[2*p]<=a[2*p+1]){
					std::swap(a[p],a[2*p]);
					p*=2;
				}else if (a[p]>a[2*p+1] and a[2*p+1]<a[2*p]){
					std::swap(a[p],a[2*p+1]);
					p*=2;
					p+=1;
				}else {
					break;
				}
			}
		}
		s-=1;
	}
	// std::sort(a,a+k+1);
	for (size_t q=0;q<k;++q){
		printf("%lli\n",d[f-1-q]);
	}
}