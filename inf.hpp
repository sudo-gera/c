#define inf_included
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
class inf{
private:
	struct Ninf{
	public:
		std::vector<uint32_t> digits;
		inline void norm(){
			while (digits.size() && digits[digits.size()-1]==0){
				digits.pop_back();
			}
		}
		inline std::string tostring(){
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
		inline uint_least64_t toint(){
			uint_least64_t f=0;
			for (uint_least64_t i=0;i<digits.size();i++){
				f+=(uint_least64_t)(digits[i]<<(sizeof(int32_t)*8*i));
			}
			return f;
		}
		inline Ninf(uint_least64_t o){
			digits.clear();
			while (o){
				digits.push_back(o);
				o>>=8*sizeof(int32_t);
			}
		}
		inline Ninf(std::string o){
			digits.clear();
			Ninf dp(1);
			Ninf ten(10);
			reverse(o.begin(), o.end());
			for (uint_least64_t i=0;i<o.size();i++){
				Ninf t(o[i]-'0');
				*this=this->add(t*dp,1);
				dp=dp*ten;
			}
		}
		inline Ninf(){};
		inline Ninf add(Ninf o,int32_t s){
			Ninf a;
			uint_least64_t n=0;
			for (uint_least64_t t=0; t<digits.size() || t<o.digits.size() || n; t++){
				n+=1LL<<(sizeof(int32_t)*8);
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
				n>>=8*sizeof(int32_t);
				n-=1;
			}
			a.norm();
			return a;		
		}
		inline int32_t diff(Ninf o){
			o.norm();
			this->norm();
			if (digits.size()<o.digits.size()){
				return -1;
			}
			if (digits.size()>o.digits.size()){
				return 1;
			}
			for (uint_least64_t t=digits.size()-1;t>=0;t--){
				if(digits[t]<o.digits[t]){
					return -1;
				}
				if(digits[t]>o.digits[t]){
					return 1;
				}
			}
			return 0;
		}
		inline Ninf operator*(Ninf o){
			Ninf a;
			for (uint_least64_t u=0;u<digits.size();u++){
				for (uint_least64_t i=0;i<o.digits.size();i++){
					Ninf s;
					uint_least64_t d=(uint_least64_t)(digits[u])*(uint_least64_t)(o.digits[i]);
					for (uint_least64_t w=0;w<i+u;w++){
						s.digits.push_back(0);
					}
					s.digits.push_back(d);
					s.digits.push_back(d>>8*sizeof(int32_t));
					s.norm();
					a=a.add(s,1);
				}
			}
			a.norm();
			return a;
		}
		inline Ninf operator/(Ninf o){
			Ninf b(0);
			Ninf one(1);
			Ninf five(1LL<<(8*sizeof(int32_t)-1));
			Ninf e=this->add(one,1);
			while ((e.add(b,-1)).diff(one)==1){
				Ninf c=(e.add(b,1))*five;
				c.digits=std::vector<uint32_t>(c.digits.begin()+1, c.digits.end());
				int32_t d=(c*o).diff(*this);
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
	int32_t sign;
	inline void norm(){
		mod.norm();
		Ninf zero(0);
		if (mod.diff(zero)==0){
			sign=0;
		}else if(sign==0){
			sign=1;
		}
	}
	inline int32_t diff(inf o){
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
	friend inline std::string::string(inf o){
		std::string e;
		if (o.sign==0){
			e="0";
		}
		if (o.sign==1){
			e=o.mod.tostring();
		}
		if (o.sign==-1){
			e="-"+o.mod.tostring();
		}
		(*this)=e;
	}
	friend inline int_least64_t operator(int_least64_t)(inf o){
		return sign*mod.toint();
	}
	inline inf(std::string o){
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
	inline inf(){
		sign=0;
	};
	inline inf(int_least64_t o){
		sign=(!!o)*(o<0?-1:1);
		if (o<0){
			o=-o;
		}
		Ninf t(o);
		mod=t;
	}
	friend inline inf inf(std::string o){
		inf a(o);
		return a;
	}
	friend inline inf inf(int_least64_t o){
		inf a(o);
		return a;
	}
	friend inline std::ostream& operator<<(std::ostream& os,inf i){
		os<<i.tostring();
		return os;
	}
	friend inline std::istream& operator>>(std::istream& is,inf&i){
		std::string o;
		is>>o;
		inf t(o);
		i=o;
		i.norm();
		return is;
	}
	inline inf operator+(){
		inf a;
		a.sign=sign;
		a.mod=mod;
		return a;
	}
	inline inf operator+(inf o){
		inf a;
		if (sign==o.sign){
			a.mod=mod.add(o.mod,1);
			a.sign=sign;
		}
		else{
			int32_t d=mod.diff(o.mod);
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
	inline inf operator-(){
		inf a;
		a.mod=mod;
		a.sign=-sign;
		return a;
	}
	inline inf operator-(inf o){
		return *this+(-o);
	}
	inline bool operator<(inf o){
		return this->diff(o)==-1;
	}
	inline bool operator>(inf o){
		return this->diff(o)==1;
	}
	inline bool operator==(inf o){
		return this->diff(o)==0;
	}
	inline bool operator<=(inf o){
		return this->diff(o)!=1;
	}
	inline bool operator>=(inf o){
		return this->diff(o)!=-1;
	}
	inline bool operator!=(inf o){
		return this->diff(o)!=0;
	}
	inline inf operator*(inf o){
		inf a;
		a.mod=mod*o.mod;
		a.sign=sign*o.sign;
		a.norm();
		return a;
	}
	inline inf operator/(inf o){
		inf a;
		a.sign=sign/o.sign;
		a.mod=mod/o.mod;
		a.norm();
		return a;
	}
	inline inf operator%(inf o){
		return *this-*this/o*o;
	}
	inline inf operator+=(inf o){
		inf a;
		a=*this+o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inline inf operator-=(inf o){
		inf a;
		a=*this-o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inline inf operator*=(inf o){
		inf a;
		a=*this*o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inline inf operator/=(inf o){
		inf a;
		a=*this/o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inline inf operator%=(inf o){
		inf a;
		a=*this%o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inline inf operator++(){
		*this+=1;
		return *this;
	}
	inline inf operator--(){
		*this-=1;
		return *this;
	}
	inline inf operator++(int32_t){
		inf a=*this;
		*this+=1;
		return a;
	}
	inline inf operator--(int32_t){
		inf a=*this;
		*this-=1;
		return a;
	}
};
#ifdef replace_int
	using old_int = int;
	#define int = inf
#endif