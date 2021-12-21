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
	T*addq=nullptr;
	size_t size=0;
	size_t qsize=0;
	tree(T*d,T*q):data(d),addq(q){}
	void add(const T&q){
		addq[qsize++]=q;
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
	size_t q;
	scanf("%zu",&q);
	char*s=new int[30];
	auto a=tree<ssize_t,std::less<ssize_t>>(new ssize_t[q],new ssize_t[q]);
	for (size_t w=0;w<q;++w){
		scanf("%s",s);
		if (s[0]=='i'){
			ssize_t t;
			scanf("%zi",&t);
			a.add(t);
		}else
		if (s[0]=='g'){
			printf("%zi",a.data[1]);
		}else
		if (s[0]=='e'){
			printf("%zi",a.data[1]);
			a.remove();
		}else
		if (s[0]=='d'){
			size_t t;
			scanf("%zu",&t);
			a.addq[t-1];
			
		}else
	}
}
