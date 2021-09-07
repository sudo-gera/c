
#include <bits/stdc++.h>
using namespace std;

#define print(...) cout<<"\x1b[32m"<<__LINE__<<"\x1b[0m"<<": ";print_f(__VA_ARGS__);cout<<endl;
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
	T read(){
		return *value;
	}
};
#define u32string string

				class range{
				public:
					int64_t start,stop,step;
				};
			

range a________range____;
int64_t w____int;
int main(){
	a________range____=range({int64_t(0),int64_t(99),int64_t(1)});
	{_range=(a________range____);for(auto iterator=_range.start,_range.step>0 and iterator<_range.stop or _range.step<0 and iterator>_range.stop){
		w____int=iterator;
		 /*pass*/ 
	}}

return 0;}