ima{
	size_t count=10000000;
	auto primes=(size_t*)malloc(sizeof(size_t)*count);
	size_t pl=1;
	primes[0]=2;
	size_t q=1;
	while (q<count){
		q+=2;
		bool nb=1;
		for (size_t w=0;primes[w]*primes[w]<=q;++w){
			if (q%primes[w]==0){
				nb=0;
				break;
			}
		}
		if (nb){
			primes[pl++]=q;
		}
		if (q%500000==1){
			cerr<<q*100./count<<'\n';
		}
	}
	printf("primes=[");
	for (size_t w=0;w<pl;++w){
		printf("%zi, ",primes[w]);
	}
	printf("]\n");
}
