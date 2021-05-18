#include <bits/stdc++.h>
using namespace std;
map<vector<string>,function<any(any,any)>> __add__map;
any input(){
	string a;
	cin>>a;
	return a;
}


any __add__(any a,any s){
	return __add__map[{a.type().name(),s.type().name()}](a,s);
}

any __add__int__int(any a,any s){
	return any_cast<int>(a)+any_cast<int>(s);
}

map<vector<string>,function<any(any,any)>> __mod__map;
any __mod__(any a,any s){
	return __mod__map[{a.type().name(),s.type().name()}](a,s);
}

any __mod__int__int(any a,any s){
	return any_cast<int>(a)%any_cast<int>(s);
}

map<vector<string>,function<any(any,any)>> __eq__map;
any __eq__(any a,any s){
	return __eq__map[{a.type().name(),s.type().name()}](a,s);
}

any __eq__int__int(any a,any s){
	return any_cast<int>(a)==any_cast<int>(s);
}

map<vector<string>,function<any(any)>> __str__map;
any __str__(any a){
	return __str__map[{a.type().name()}](a);
}

any __str__int(any a){
	return to_string(any_cast<int>(a));
}

any __str__str(any a){
	return a;
}

map<vector<string>,function<any(any)>> __int__map;
any __int__(any a){
	return __str__map[{a.type().name()}](a);
}

any __int__str(any a){
	return stoi(any_cast<string>(a));
}

any __int__int(any a){
	return a;
}

int main(){
	__add__map[{typeid(0).name(),typeid(0).name()}]=__add__int__int;
	__mod__map[{typeid(0).name(),typeid(0).name()}]=__mod__int__int;
	__eq__map[{typeid(0).name(),typeid(0).name()}]=__eq__int__int;
	__str__map[{typeid(0).name()}]=__str__int;
	__str__map[{typeid(string()).name()}]=__str__str;
	__int__map[{typeid(0).name()}]=__int__int;
	__int__map[{typeid(string()).name()}]=__int__str;
	any s=__int__(input());
	if (any_cast<int>(__mod__(s,2))){
		s=string("1");
	}
	s=__str__(s);
	cout<<any_cast<string>(s);
}