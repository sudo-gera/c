#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

int main(){
	size_t k,n;
	scanf("%zi%zi",&k,&n);
	auto v=new size_t[n+1];
	for (size_t w=0;w<n;++w){
		scanf("%zi",v+w);
	}
	for (size_t w=1;w<n;++w){
		v[w]+=v[w-1];
	}
	memmove(v+1,v,(n)*sizeof(v[0]));
	v[0]=0;
	size_t _b=v[n]/k;
	size_t _e=v[n];
	while (_e-_b>1){
		size_t m=(_b+_e)/2;
		size_t mm=m;
		ic(_b,_e,m)
		for (size_t mn=1;mn<k;mm+=m,mn+=1){
			size_t _b=0;
			size_t _e=n;
			while (_e-_b>1){
				size_t _c=(_b+_e)/2;
				ssize_t _d=v[_c]-mm;
				ic(_b,_e,_c,_d,mm)
				if (_d>0){
					_e=_c;
				}else
				if (_d<0){
					_b=_c;
				}else
				if (_d==0){
					_e=_c;
					_b=_c;
				}
			}
			if (v[_b]-mm>0){
				mm=v[_b];
			}else{
				mm=v[_e];
			}
		}
		ic(_b,_e,m)
		if (mm<n){
			_b=m;
		}else{
			_e=m;
		}
	}
	ic(itervect(v,v+n+1))
	size_t m=(_b+_e)/2;
	size_t mm=m;
	for (size_t mn=1;mn<k;mm+=m,mn+=1){
		size_t _b=0;
		size_t _e=n;
		while (_e-_b>1){
			size_t _c=(_b+_e)/2;
			ssize_t _d=v[_c]-mm;
			// ic(_b,_e,_c,_d)
			if (_d>0){
				_e=_c;
			}else
			if (_d<0){
				_b=_c;
			}else
			if (_d==0){
				_e=_c;
				_b=_c;
			}
		}
		if (v[_b]-mm>0){
			mm=v[_b];
		}else{
			mm=v[_e];
		}
	}
	if (mm<n){
		printf("%zi\n",_e);
	}else{
		printf("%zi\n",_b);
	}
	delete[] v;
}
