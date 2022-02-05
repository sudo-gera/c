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

int main(){
	tree<int,std::less<int>> a(new int[999999]);
	std::set<int> s;
	for (size_t w=0;w<999999;++w){
		auto r=rand();
		if (a.size and r%2){
			assert(a.data[1]==*s.begin());
			a.remove();
			s.erase(s.begin());
		}else{
			a.add(r);
			s.insert(r);
			assert(a.data[1]==*s.begin());
		}
	}
}
