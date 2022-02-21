#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <functional>
#include <iostream>

template <typename T,typename F>
struct tree{
	T*data=nullptr;
	size_t size=0;
	tree(T*d):data(d){}
	void add(const T&q){
		data[1+size++]=q;
		size_t s=size;
		while (s>1 and F{}(data[s],data[s/2])){
			auto t=data[s];
			data[s]=data[s/2];
			data[s/2]=t;
			s/=2;
		}
	}
	void remove(){
		data[1]=data[--size+1];
		size_t s=1;
		while ( s*2+1<size+1 and ( F{}(data[s*2],data[s]) or F{}(data[s*2+1],data[s]) ) ){
			if (F{}(data[2*s+1],data[2*s])){
				auto t=data[s];
				data[s]=data[s*2+1];
				data[s*2+1]=t;
				s=s*2+1;
			}else{
				auto t=data[s];
				data[s]=data[s*2];
				data[s*2]=t;
				s=s*2;
			}
		}
		while ( s*2<size+1 and F{}(data[s*2],data[s]) ){
			auto t=data[s];
			data[s]=data[s*2];
			data[s*2]=t;
			s=s*2;
		}
	}
};

// auto prep=pyfunc(q,w)
// 	// return q[1:][::-1]+['--']+w[1:]

int main(){
	size_t n;
	scanf("%zu",&n);
	auto a=tree<ssize_t,std::greater<ssize_t>>(new ssize_t[n+1]);
	auto s=tree<ssize_t,std::less<ssize_t>>(new ssize_t[n+1]);
	for (size_t w=0;w<n;++w){
		size_t x;
		ssize_t y;
		scanf("%zu",&x);
		if (x){
			if (a.size+s.size==0){
				printf("%i\n",0);
			}else
			printf("%zi\n",a.data[1]);
		}else{
			scanf("%zi",&y);
			if (a.size and y<a.data[1]){
				a.add(y);
			}else{
				s.add(y);
			}
			while (a.size>s.size){
				s.add(a.data[1]);
				a.remove();
			}
			while (s.size>a.size){
				a.add(s.data[1]);
				s.remove();
			}
		}
		// ic(prep(itervect(a.data,a.data+a.size+1),itervect(s.data,s.data+s.size+1)))
	}
	delete[] a.data;
	delete[] s.data;
}
