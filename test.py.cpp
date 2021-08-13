
#include <bits/stdc++.h>
using namespace std;

#define print(...) cout<<"[32m"<<__LINE__<<"[0m"<<": ";print_f(__VA_ARGS__);cout<<endl;
template <typename t>
int print_ff(t a){cout<<a<<' ';return 1;}
template <typename...t>
void print_f(t...a){int s[]={1,print_ff(a)...};}

template<typename T>
class linked{
public:
	int *count=nullptr;
	T *value=nullptr;
	linked(){}
	linked(T q){
		value=new T(q);
		count=new int(1);
	}
	linked(const linked& o){
		value=o.value;
		count=o.count;
		*count+=1;
	}
	~linked(){
		*count-=1;
		if (*count==0){
			delete count;
			delete value;
		}
	}
};
#define u32string string

				#define to_u8
				#define to_u32
				#define chr
				#define ord
			

linked<vector<u32string>> q____list_L_str_J;
int main(){
	q____list_L_str_J=linked<vector<u32string>>({u32string("1")});
	cout<<to_u8((((*(q____list_L_str_J.value))[int64_t(0)])))<<"\n";

}