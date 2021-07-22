#include <bits/stdc++.h>
using namespace std;

#define pline_ std::cout<<"\x1b[32m"<<__LINE__<<"\x1b[0m";
#define pline pline_ std::cout<<std::endl;

#define print(...) pline_;cout<<": ";print_f(__VA_ARGS__);cout<<endl;
template <typename t>
int print_ff(t a){
	cout<<a<<' ';
	return 1;
}
template <typename...t>
void print_f(t...a){
	int s[]={1,print_ff(a)...};
}


template <typename t>
struct tstore{
	t v;
	bool *c;
	tstore(t q,bool *x){
		v=q;
		c=x;
	}
	~tstore(){
		print(c,*c)
		if (*c){
			(*v)();
		}
	}
};

struct function_store{
	any f;
	bool c;
	template <typename t>
	function_store(t g){
		print(&c,c)
		f=tstore(g,&c);
	}
	function_store(){
	}
	void operator()(){
		c=1;
		print(&c,c)
		{any g=f;}
		c=0;
	}
};

struct a{
	void operator()(){
		cout<<"2"<<endl;
	}
};

void s(){
	cout<<"3"<<endl;
}


int main(){
	function_store q;
	auto f=a();
	q=&s;
	q();
}