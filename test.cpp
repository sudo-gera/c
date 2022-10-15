#include <bits/stdc++.h>
using namespace std;

struct iholder{

	virtual void f(){}
};

template<typename T>
struct holder:iholder{
	T value;
};

struct _any{
	unique_ptr<iholder> p;
};

int main(){
	_any t{make_unique<holder<int>>()};
}



