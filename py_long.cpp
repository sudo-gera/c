#include <ext/rope>
using __gnu_cxx::rope;

#include <string>
#include <iostream>
using namespace std;

template<typename T>
auto replace(T self,T old,T ne,long maxcount=-1){
	T res;
	for (int64_t w=0;w<self.size();){
		if (maxcount and self.rfind(old,w)==w){
			res+=ne;
			w+=old.size();
			maxcount=maxcount>0?maxcount-1:maxcount;
		}else{
			res+=(self)[w];
			++w;
		}
	}
	return res;
}

std::string popen(std::string q){
	std::string s;
	auto pipe=popen(q.c_str(), "r");
	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(pipe)) != EOF) { // standard C I/O file reading loop
		s+=static_cast<char>(c);
	}
	pclose(pipe);
	return s;
}

std::string python(std::string q){
	q=replace(q,"\\"s,"\\\\"s);
	q=replace(q,"\""s,"\\\""s);
	q=replace(q,"`"s,"\\`"s);
	q=replace(q,"$"s,"\\$"s);
	return popen("python3 -c \""+q+"\"");
}

struct py_long{
    rope<> num;
    // void getnum(){
    //     std::string s(num.begin(),num.end());
    //     num=python(
    //         "s='"+s+"'\n"
    //         "import re\n"
    //         "s=re.split(r'\\b',s)\n"
    //     );
    // }
    py_long(long long t){
        // auto s=std::to_string(t);
        // num.insert(0,s);
    }
    // auto&operation(const py_long&o,string t){
    //     num+=o.num;
    //     rope<string> y;
    //     y.insert(0,t);
    //     num+=y;
    //     return *this;
    // }
    // auto&operator+=(const py_long&o){
    //     return operation(o,"+");
    // }
    // auto&operator-=(const py_long&o){
    //     return operation(o,"-");
    // }
    // auto&operator*=(const py_long&o){
    //     return operation(o,"*");
    // }
    // auto&operator/=(const py_long&o){
    //     return operation(o,"//");
    // }
    // auto&operator%=(const py_long&o){
    //     return operation(o,"%");
    // }
    // operator string()const{
    //     string s(num.begin(),num.end());
    //     return s;
    // }
};


int main(){
    py_long q=9;
    // q+=8;
    // cout<<string(q)<<endl;
}