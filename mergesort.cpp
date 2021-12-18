template <typename T>
void mergesort(T a,size_t n,T d=nullptr){
	size_t nn=1,n_=n;
	while (n_){
		n_>>=1;
		nn<<=1;
	}
	nn>>=1;
	assert(nn==n);
	bool dc=0;
	if (!d){
		d=(decltype(&(a[0])))malloc(sizeof(a[0])*n);
		dc=1;
	}
	for (size_t bs=1;bs<nn;bs<<=1){
		for (size_t w=0;w<nn;w+=bs<<1){
			size_t s=0;
			size_t z=w;
			size_t x=w+bs;
			while (z<bs+w and x<bs+w+bs){
				if (a[z]<a[x]){
					d[s++]=a[z++];
				}else{
					d[s++]=a[x++];
				}
			}
			while (z<bs+w){
				d[s++]=a[z++];
			}
			while (x<bs+w+bs){
				d[s++]=a[x++];
			}
			assert(z==w+bs);
			assert(x==w+bs+bs);
			for (z=0;z<s;++z){
				a[w+z]=d[z];
			}
		}
	}
	if (dc){
		free(d);
	}
}
