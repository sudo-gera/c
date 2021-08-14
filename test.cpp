#include <bits/stdc++.h>
using namespace std;

#define pline_ std::cout<<"\x1b[32m"<<__LINE__<<"\x1b[0m";
#define pline pline_ std::cout<<std::endl;

#define print(...) pline_;cout<<": ";print_f(__VA_ARGS__);cout<<endl;
template <typename t>
int print_ff(t a){cout<<a<<' ';return 1;}
template <typename...t>
void print_f(t...a){int s[]={1,print_ff(a)...};}



template<typename T>
class linked{
public:
	int *count=nullptr;
	T *value=nullptr;
	void __init__(T&q){
		value=new T(q);
		count=new int(1);
	}
	linked(T q=T()){
		this->__init__(q);
	}
	void __init__(const linked& o){
		value=o.value;
		count=o.count;
		*count+=1;
	}
	linked(const linked& o){
		this->__init__(o);
	}
	linked&operator=(T q){
		this->__del__();
		this->__init__(q);
		return *this;
	}
	linked&operator=(const linked&q){
		this->__del__();
		this->__init__(q);
		return *this;
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
	~linked(){
		this->__del__();
	}
	template <typename Y>
	bool operator<(const linked<Y> o)const{
		return (*value)<(*o.value);
	}
};

int qq=0;

class test{
public:
	int q;
	test(){
		q=++qq;
		print("con",q);
	}
	template<typename T>
	test(T o){
		q=++qq;
		print("con",q,"with",o);
	}
	test(const test&w){
		q=++qq;
		print("con",q,"from",w.q);
	}
	~test(){
		print("des",q);
	}
	template<typename T>
	int operator=(T o){
		print("set",q,"with",o);
		return 0;
	}
	int operator=(const test&o){
		print("set",q,"from",o.q);
		return 0;
	}
};

int main(){
	set<linked<int>>q;
	q.insert(1);
	q.insert(2);
	q.insert(0);
	for (auto w:q){
		print(*w.value);
	}
}
