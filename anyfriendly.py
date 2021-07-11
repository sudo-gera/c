anyfile=open('anyfriendly.cpp','w').close()
anyfile=open('anyfriendly.cpp','a')
anyfile.write('''
#include <bits/stdc++.h>
using namespace std;
map<string,string> tns;
template <typename t>
string escname(t q){
	auto f=typeid(q).name();
	string d;
	for(auto w : f){
		if (w=='_'){
			d+="_u";
		}else{
			d+=w;
		}
	}
	return d;
}
#define ldouble (long double)
int main(){
	tns["int"]=escname(int64_t());
	tns["float"]=escname(ldouble());
	tns["str"]=escname(string32_t());
	tns["list"]=escname(vector<any>());
	tns["set"]=escname(set<any>());
	tns["dict"]=escname(map<any,any>());
	tns["bytearray"]=escname(string());
	tns["bytes"]=escname(string());
}
''')
algs=dict()
algs['int']='return to_u32(to_sting(q));'
algs['float']='return to_u32(to_sting(q));'
algs['str']='return q;'
