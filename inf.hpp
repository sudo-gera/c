#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
class inf{
private:
	struct Ninf{
	public:
		std::vector<unsigned int> digits;
		void norm(){
			while (digits.size() && digits[digits.size()-1]==0){
				digits.pop_back();
			}
		}
		std::string tostring(){
			std::string e;
			Ninf t=*this;
			Ninf m,n;
			Ninf zero(0);
			while (t.diff(zero)){
				for (auto o:digits){
				}
				n=t/10;
				m=(t.add(n*10,-1));
				if (m.digits.size()){
					e.push_back(m.digits[0]+'0');
				}else{
					e.push_back('0');
				}
				t=n;
			}
			reverse(e.begin(), e.end());
			return e;
		}
		unsigned long long int toint(){
			unsigned long long int f=0;
			for (unsigned long long int i=0;i<digits.size();i++){
				f+=(unsigned long long int)(digits[i]<<(sizeof(int)*8*i));
			}
			return f;
		}
		Ninf(unsigned long long int o){
			digits.clear();
			while (o){
				digits.push_back(o);
				o>>=8*sizeof(int);
			}
		}
		Ninf(std::string o){
			digits.clear();
			Ninf dp(1);
			Ninf ten(10);
			reverse(o.begin(), o.end());
			for (unsigned long long int i=0;i<o.size();i++){
				Ninf t(o[i]-'0');
				*this=this->add(t*dp,1);
				dp=dp*ten;
			}
		}
		Ninf(){};
		Ninf add(Ninf o,int s){
			Ninf a;
			unsigned long long int n=0;
			for (unsigned long long int t=0; t<digits.size() || t<o.digits.size() || n; t++){
				n+=1LL<<(sizeof(int)*8);
				if (t<digits.size()){
					n+=digits[t];
				}
				if (t<o.digits.size()){
					if (s>0){
						n+=o.digits[t];
					}else{
						n-=o.digits[t];
					}
				}
				a.digits.push_back(n);
				n>>=8*sizeof(int);
				n-=1;
			}
			a.norm();
			return a;		
		}
		int diff(Ninf o){
			o.norm();
			this->norm();
			if (digits.size()<o.digits.size()){
				return -1;
			}
			if (digits.size()>o.digits.size()){
				return 1;
			}
			for (long long int t=digits.size()-1;t>=0;t--){
				if(digits[t]<o.digits[t]){
					return -1;
				}
				if(digits[t]>o.digits[t]){
					return 1;
				}
			}
			return 0;
		}
		Ninf operator*(Ninf o){
			Ninf a;
			for (unsigned long long int u=0;u<digits.size();u++){
				for (unsigned long long int i=0;i<o.digits.size();i++){
					Ninf s;
					unsigned long long int d=(unsigned long long int)(digits[u])*(unsigned long long int)(o.digits[i]);
					for (long long int w=0;w<i+u;w++){
						s.digits.push_back(0);
					}
					s.digits.push_back(d);
					s.digits.push_back(d>>8*sizeof(int));
					s.norm();
					a=a.add(s,1);
				}
			}
			a.norm();
			return a;
		}
		Ninf operator/(Ninf o){
			Ninf b(0);
			Ninf one(1);
			Ninf five(1LL<<(8*sizeof(int)-1));
			Ninf e=this->add(one,1);
			while ((e.add(b,-1)).diff(one)==1){
				Ninf c=(e.add(b,1))*five;
				c.digits=std::vector<unsigned int>(c.digits.begin()+1, c.digits.end());
				int d=(c*o).diff(*this);
				if (d==-1){
					b=c;
				}
				if (d==1){
					e=c;
				}
				if (d==0){
					b=c;
					e=c;
				}
			}
			b.norm();
			return b;
		}
	};
	Ninf mod;
	int sign;
	void norm(){
		mod.norm();
		Ninf zero(0);
		if (mod.diff(zero)==0){
			sign=0;
		}else if(sign==0){
			sign=1;
		}
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
public:
	std::string tostring(){
		std::string e;
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
		return sign*mod.toint();
	}
	inf(std::string o){
		sign=1;
		Ninf zero(0);
		if (o[0]=='-'){
			sign=-1;
			o=std::string(o.begin()+1, o.end());
		}
		mod=Ninf(o);
		if (mod.diff(zero)==0){
			sign=0;
		}
	}
	inf(){
		sign=0;
	};
	inf(long long int o){
		sign=(!!o)*(o<0?-1:1);
		if (o<0){
			o=-o;
		}
		Ninf t(o);
		mod=t;
	}
	friend inf inf(std::string o){
		inf a(o);
		return a;
	}
	friend inf inf(long long int o){
		inf a(o);
		return a;
	}
	friend std::ostream& operator<<(std::ostream& os,inf i){
		os<<i.tostring();
		return os;
	}
	friend std::istream& operator>>(std::istream& is,inf&i){
		std::string o;
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
			a.mod=mod.add(o.mod,1);
			a.sign=sign;
		}
		else{
			int d=mod.diff(o.mod);
			if (d==1){
				a.mod=mod.add(o.mod,-1);
				a.sign=sign;
			}else if (d==-1){
				a.mod=o.mod.add(mod,-1);
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
		a.norm();
		return a;
	}
	inf operator/(inf o){
		inf a;
		a.sign=sign/o.sign;
		a.mod=mod/o.mod;
		a.norm();
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
