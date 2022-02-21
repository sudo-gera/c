#include <bits/stdc++.h>
using namespace std;

auto a=vector<str_view>({"I","II","III","V","X","XIX","XX","XXX","L","C","CXC","CC","CCC","D","M","MCM","MM","MMM"});


struct str_view{
	size_t const size=0;
	char const*const data=nullptr;
	str_view(const char*q):size(strlen(q)),data(q){}
};

str_view slice(str_view a,size_t b,size_t e){
	if (b<0){
		b%=a.size;
	}
	if (d<0){
		d%=a.size;
	}
	return str_view(a+b,e-b);
}

bool startswith(str_view q,str_view e){
	if (e.size>q.size){
		return 0;
	}
	for (size_t w=0;w<e.size;++w){
		if (q.data[w]!=e.data[w]){
			return 0;
		}
	}
	return 1;
}

vector<str_view> res;


void run(str_view s,size_t ai){
	if (ai==a.size()){
		return;
	}
	for (size_t w=0;w<s.size;++w){
		if (startswith(slice(s,w,s.size),a[ai])){
			run(slice(s,))
		}
	}
}

int main(){
	string _s;
	cin>>_s;
	str_view s(_s.c_str());

}
