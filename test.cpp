#include <bits/stdc++.h>
using namespace std;

struct iholder{

	virtual void f(){}
};

template<typename T>
struct holder:iholder{
	T value;
};


int main(){
	unique_ptr q=make_unique<holder<int>>();
}



