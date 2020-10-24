//#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
struct Ninf{
	std::string digits;
	void norm(){
		while (digits.size() && digits[digits.size()-1]==0){
			digits.pop_back();
		}
	}
	string tostring(){
		string e;
		e=digits;
		reverse(e.begin(),e.end());
		for (auto& d : e){
			d+='0';
		}
		return e;
	}
	long long int toint(){
		long long int a=0;
//		sscanf(this->tostring().c_str(),"%Li",&a);
		a=stoi(this->tostring());
		return a;
	}
	Ninf(string o){
		for (auto &d:o){
			d-='0';
		}
		reverse(o.begin(),o.end());
		digits=o;
		this->norm();
	}
	Ninf(){};
	Ninf(long long int o){
//		char t[99];
//		sprintf(t,"%Li",o);
		string t=to_string(o);
		digits=Ninf(t).digits;
		this->norm();
	}
	friend Ninf Ninf(string o){
		Ninf a(o);
		return a;
	}
	friend Ninf Ninf(long long int o){
		Ninf a(o);
		return a;
	}
	friend ostream& operator<<(ostream& os,Ninf i){
		os<<i.tostring();
		return os;
	}
	friend istream& operator>>(istream& is,Ninf&i){
		string o;
		is>>o;
		Ninf t(o);
		i=o;
		i.norm();
		return is;
	}
	Ninf operator+(Ninf o){
		Ninf a;
		int n=0;
		for (size_t t=0; t<digits.size() || t<o.digits.size() || n; t++){
			if (t<digits.size()){
				n+=digits[t];
			}
			if (t<o.digits.size()){
				n+=o.digits[t];
			}
			a.digits.push_back(n%10);
			n/=10;
		}
		a.norm();
		return a;
	}
	Ninf operator-(Ninf o){
		Ninf a;
		int n=0;
		for (size_t t=0; t<digits.size() || t<o.digits.size() || n; t++){
			if (t<digits.size()){
				n+=digits[t];
			}
			if (t<o.digits.size()){
				n-=o.digits[t];
			}
			a.digits.push_back((n+10)%10);
			n+=10;
			n/=10;
			n-=1;
		}
		a.norm();
		return a;
	}
	int diff(Ninf o){
		if (digits.size()<o.digits.size()){
			return -1;
		}
		if (digits.size()>o.digits.size()){
			return 1;
		}
		for (size_t t=digits.size()-1;t>-1;t--){
			if(digits[t]<o.digits[t]){
				return -1;
			}
			if(digits[t]>o.digits[t]){
				return 1;
			}
		}
		return 0;
	}
	bool operator<(Ninf o){
		return this->diff(o)==-1;
	}
	bool operator>(Ninf o){
		return this->diff(o)==1;
	}
	bool operator==(Ninf o){
		return this->diff(o)==0;
	}
	bool operator<=(Ninf o){
		return this->diff(o)!=1;
	}
	bool operator>=(Ninf o){
		return this->diff(o)!=-1;
	}
	bool operator!=(Ninf o){
		return this->diff(o)!=0;
	}
	Ninf operator*(Ninf o){
		Ninf a;
		for (size_t u=0;u<digits.size();u++){
			for (size_t i=0;i<o.digits.size();i++){
				Ninf s(digits[u]*o.digits[i]);
				for (size_t w=0;w<i+u;w++){
					s.digits='\0'+s.digits;
				}
				a+=s;
			}
		}
		return a;
	}
	Ninf operator/(Ninf o){
		Ninf b(0);
		Ninf e=*this+Ninf(1);
		while (e-b>1){
			Ninf c=(e+b)*Ninf(5);
			c.digits=string(c.digits.begin()+1, c.digits.end());
			if (c*o<*this){
				b=c;
			}
			if (c*o>*this){
				e=c;
			}
			if (c*o==*this){
				b=c;
				e=c;
			}
		}
		return b;
	}
	Ninf operator%(Ninf o){
		return *this-*this/o*o;
	}
	Ninf operator+=(Ninf o){
		Ninf a;
		a=*this+o;
		digits=a.digits;
		return a;
	}
	Ninf operator-=(Ninf o){
		Ninf a;
		a=*this-o;
		digits=a.digits;
		return a;
	}
	Ninf operator*=(Ninf o){
		Ninf a;
		a=*this*o;
		digits=a.digits;
		return a;
	}
	Ninf operator/=(Ninf o){
		Ninf a;
		a=*this/o;
		digits=a.digits;
		return a;
	}
	Ninf operator%=(Ninf o){
		Ninf a;
		a=*this%o;
		digits=a.digits;
		return a;
	}
};

struct inf{
	Ninf mod;
	int sign;
	void norm(){
		mod.norm();
		if (sign==0){
			mod=Ninf(0);
		}
	}
	string tostring(){
		string e;
		if (sign==0){
			e="0";
		}
		if (sign==1){
			e=mod.tostring();
		}
		if (sign==-1){
			e="-"+mod.tostring();
		}
		return e;
	}
	long long int toint(){
		return mod.toint()*sign;
	}
	inf(string o){
		sign=1;
		if (o[0]=='-'){
			sign=-1;
			o=string(o.begin()+1, o.end());
		}
		mod=Ninf(o);
		if (mod==Ninf(0)){
			sign=0;
		}
	}
	inf(){};
	inf(long long int o){
//		char t[99];
//		sprintf(t,"%Li",o);
		string t=to_string(o);
		inf m(t);
		mod=m.mod;
		sign=m.sign;
		this->norm();
	}
	friend inf inf(string o){
		inf a(o);
		return a;
	}
	friend inf inf(long long int o){
		inf a(o);
		return a;
	}
	friend ostream& operator<<(ostream& os,inf i){
		os<<i.tostring();
		return os;
	}
	friend istream& operator>>(istream& is,inf&i){
		string o;
		is>>o;
		inf t(o);
		i=o;
		i.norm();
		return is;
	}
	inf operator+(){
		inf a;
		a.sign=sign;
		a.mod=mod;
		return a;
	}
	inf operator+(inf o){
		inf a;
		if (sign==o.sign){
			a.mod=mod+o.mod;
			a.sign=sign;
		}
		else{
			if (mod > o.mod){
				a.mod=mod-o.mod;
				a.sign=sign;
			}else if (mod < o.mod){
				a.mod=o.mod-mod;
				a.sign=o.sign;
			}else{
				a=inf(0);
			}
		}
		return a;
	}
	inf operator-(){
		inf a;
		a.mod=mod;
		a.sign=-sign;
		return a;
	}
	inf operator-(inf o){
		return *this+(-o);
	}
	int diff(inf o){
		if (sign < o.sign){
			return -1;
		}
		if (sign > o.sign){
			return 1;
		}
		if (sign==0 && 0==o.sign){
			return 0;
		}
		if (sign==1){
			return mod.diff(o.mod);
		}
		if (sign==-1){
			return -mod.diff(o.mod);
		}
	}
	bool operator<(inf o){
		return this->diff(o)==-1;
	}
	bool operator>(inf o){
		return this->diff(o)==1;
	}
	bool operator==(inf o){
		return this->diff(o)==0;
	}
	bool operator<=(inf o){
		return this->diff(o)!=1;
	}
	bool operator>=(inf o){
		return this->diff(o)!=-1;
	}
	bool operator!=(inf o){
		return this->diff(o)!=0;
	}
	inf operator*(inf o){
		inf a;
		a.mod=mod*o.mod;
		a.sign=sign*o.sign;
		return a;
	}
	inf operator/(inf o){
		inf a;
		a.mod=mod/o.mod;
		a.sign=sign*o.sign;
		return a;
	}
	inf operator%(inf o){
		return *this-*this/o*o;
	}
	inf operator+=(inf o){
		inf a;
		a=*this+o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inf operator-=(inf o){
		inf a;
		a=*this-o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inf operator*=(inf o){
		inf a;
		a=*this*o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inf operator/=(inf o){
		inf a;
		a=*this/o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inf operator%=(inf o){
		inf a;
		a=*this%o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inf operator++(){
		*this+=1;
		return *this;
	}
	inf operator--(){
		*this-=1;
		return *this;
	}
	inf operator++(int){
		inf a=*this;
		*this+=1;
		return a;
	}
	inf operator--(int){
		inf a=*this;
		*this-=1;
		return a;
	}
};

int main(){
	Ninf s,d;
	cin>>s>>d;
	cout<<(s/d)<<endl;
}