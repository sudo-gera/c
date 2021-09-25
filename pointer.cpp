#include <bits/stdc++.h>
using namespace std;
#include "pointer.hpp"


int qq=0;
class test{
public:
	int q;
	test(){
		q=++qq;
		cout<<"constructor "<<q<<endl;
	}
	template<typename T>
	test(T w){
		q=++qq;
		cout<<"constructor "<<q<<" with "<<w<<endl;
	}
	test(const test&w){
		q=++qq;
		cout<<"constructor "<<q<<" from "<<w.q<<endl;
	}
	template<typename T>
	void operator=(T w){
		cout<<"assign "<<q<<" with "<<w<<endl;
	}
	void operator=(const test&w){
		cout<<"assign "<<q<<" from "<<w.q<<endl;
	}
	~test(){
		cout<<"destructor "<<q<<endl;		
	}
};

template <typename Y>
void ___mergesort(Y qb,Y qe,pointer<vector<typename Y::value_type>> _a=nullptr){
	using T=typename Y::value_type;
	// using T=vector<decltype(qb[0])>;
	// T*a=(T*)_a;
	if (qe-qb<2){
		return;
	}
	bool outs=0;
	if (!_a){
		// a=new T[qe-qb];
		_a=vector<T>(qe-qb);
		outs=1;
	}
	vector<T>&a=*_a;
	___mergesort(qb,qb+(qe-qb)/2,_a);
	___mergesort(qb+(qe-qb)/2,qe,_a);
	size_t asize=0;
	size_t lp=0;
	size_t rp=(qe-qb)/2;
	while (lp<(qe-qb)/2 or rp<(qe-qb)){
		if (lp==(qe-qb)/2){
			a[asize++]=qb[rp++];
		}else
		if (rp==(qe-qb)){
			a[asize++]=qb[lp++];
		}else
		if (qb[lp]>qb[rp]){
			a[asize++]=qb[rp++];
		}else{
			a[asize++]=qb[lp++];
		}
	}
	for (size_t w=0;w<asize;++w){
		qb[w]=a[w];
	}
	if (outs){
		// delete a;
	}
}


int main(){
	vector<int> a({1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0});
	___mergesort(a.begin(),a.end());
	for (auto w:a){
		cout<<w<<' ';
	}
	cout<<'\n';
}