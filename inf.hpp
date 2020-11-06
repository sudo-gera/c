#include <string>
#include <iostream>
#include <algorithm>
	
class inf{
private:
	struct Ninf{
	public:
		std::string digits;
		void norm(){
			while (digits.size() && digits[digits.size()-1]==0){
				digits.pop_back();
			}
		}
		std::string tostring(){
			std::string e;
			e=digits;
			reverse(e.begin(),e.end());
			for (auto& d : e){
				d+='0';
			}
			return e;
		}
		Ninf(std::string o){
			for (auto &d:o){
				d-='0';
			}
			reverse(o.begin(),o.end());
			digits=o;
			this->norm();
		}
		Ninf(){};
		Ninf add(Ninf o,int s){
			Ninf a;
			int n=0;
			for (long long int t=0; t<digits.size() || t<o.digits.size() || n; t++){
				if (t<digits.size()){
					n+=digits[t];
				}
				if (t<o.digits.size()){
					n+=s*o.digits[t];
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
			for (long long int u=0;u<digits.size();u++){
				for (long long int i=0;i<o.digits.size();i++){
					Ninf s;
					int d=digits[u]*o.digits[i];
					s.digits.push_back(d%10);
					s.digits.push_back(d/10);
					for (long long int w=0;w<i+u;w++){
						s.digits='\0'+s.digits;
					}
					a=a.add(s,1);
				}
			}
			a.norm();
			return a;
		}
		Ninf operator/(Ninf o){
			Ninf b("0");
			Ninf one("1");
			Ninf five("5");
			Ninf e=this->add(one,1);
			while ((e.add(b,-1)).diff(one)==1){
	//			cout<<e<<' '<<b<<endl;
				Ninf c=(e.add(b,1))*five;
				c.digits=std::string(c.digits.begin()+1, c.digits.end());
				if ((c*o).diff(*this)==-1){
					b=c;
				}
				if ((c*o).diff(*this)==1){
					e=c;
				}
				if ((c*o).diff(*this)==0){
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
		Ninf zero("0");
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
		if (sign){
			return stoll(mod.tostring())*sign;
		}else{
			return 0LL;
		}
	}
	inf(std::string o){
		sign=1;
		Ninf zero("0");
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
		std::string t=std::to_string(o);
		inf m(t);
		mod=m.mod;
		sign=m.sign;
		this->norm();
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
			if (mod.diff(o.mod)==1){
				a.mod=mod.add(o.mod,-1);
				a.sign=sign;
			}else if (mod.diff(o.mod)==-1){
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
		a.mod=mod/o.mod;
		a.sign=sign/o.sign;
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
