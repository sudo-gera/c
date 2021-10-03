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
public:
	pointer(){
	}
	pointer(const T q){
		this->__init__(q);
	}
	pointer(const pointer& o){
		this->__init__(o);
	}
	pointer(const T*o){
		if(o){
			this->__init__(*o);
		}
	}
	pointer&operator=(const T q){
		this->clear();
		this->__init__(q);
		return *this;
	}
	pointer&operator=(const pointer&q){
		this->clear();
		this->__init__(q);
		return *this;
	}
	pointer&operator=(const T*q){
		this->clear();
		if(q){
			this->__init__(*q);
		}
		return *this;
	}
	operator bool(){
		return count;
	}
	void clear(){
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
	~pointer(){
		this->clear();
	}
	template <typename Y>
	bool operator<(const pointer<Y> o)const{
		return (*value)<(*o.value);
	}
	T &operator*(){
		return *value;
	}
	T *operator->(){
		return value;
	}
	operator T*(){
		return value;
	}
	friend ostream&operator<<(ostream&q,const pointer&w){
		q<<w.value;
		return q;
	}
	friend istream&operator>>(istream&q,pointer&w){
		T e;
		q>>e;
		w=e;
		return q;
	}
};

