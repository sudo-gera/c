#include <stdio.h>
#include <bits/stdc++.h>

namespace print{

using namespace std;
using namespace std::literals;

template<typename T>
auto replace(const T&self,const T&old,const T&ne,long maxcount=-1){
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

std::string _popen(std::string q){
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
    return _popen("python3 -c \""+q+"\"");
}

};

using print::python;

int main(){
    std::cout<<python("print(0)")<<std::endl;
}
