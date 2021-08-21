#include <bits/stdc++.h>
using namespace std;
template<typename T>
class pointer{
	int64_t *count=nullptr;
	T *value=nullptr;
	void __init__(const T&q){
		value=new T(q);
		count=new int64_t(1);
	}
	void __init__(const pointer& o){
		value=o.value;
		count=o.count;
		*count+=1;
	}
	void __del__(){
		if(count){
			*count-=1;
			if (*count==0){
				delete count;
				count=nullptr;
				delete value;
				value=nullptr;
			}
		}
	}
public:
	pointer(const T&q=T()){
		this->__init__(q);
	}
	pointer(const pointer& o){
		this->__init__(o);
	}
	pointer&operator=(const T&q){
		this->__del__();
		this->__init__(q);
		return *this;
	}
	pointer&operator=(const pointer&q){
		this->__del__();
		this->__init__(q);
		return *this;
	}
	~pointer(){
		this->__del__();
	}
	template <typename Y>
	bool operator<(const pointer<Y> o)const{
		return (*value)<(*o.value);
	}
	T&operator*(){
		return *value;
	}
	operator T*(){
		return value;
	}
};

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


int run(){
	return 12;
}

int main(){
	cout<<__LINE__<<endl;
	{
	cout<<__LINE__<<endl;
		const test q;
	cout<<__LINE__<<endl;
		pointer w=q;
	cout<<__LINE__<<endl;
		w=test();
	cout<<__LINE__<<endl;
	}
	cout<<__LINE__<<endl;


	pointer r=run();


}