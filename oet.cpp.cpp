////////////////////////////////////////////////////////////////////////////////
//stdc++.h

// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2021 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

// 17.4.1.2 Headers

// C
#ifndef _GLIBCXX_NO_ASSERT
#if __has_include("cassert")
#include <cassert>
#endif
#endif
#if __has_include("cctype")
#include <cctype>
#endif
#if __has_include("cerrno")
#include <cerrno>
#endif
#if __has_include("cfloat")
#include <cfloat>
#endif
#if __has_include("ciso646")
#include <ciso646>
#endif
#if __has_include("climits")
#include <climits>
#endif
#if __has_include("clocale")
#include <clocale>
#endif
#if __has_include("cmath")
#include <cmath>
#endif
#if __has_include("csetjmp")
#include <csetjmp>
#endif
#if __has_include("csignal")
#include <csignal>
#endif
#if __has_include("cstdarg")
#include <cstdarg>
#endif
#if __has_include("cstddef")
#include <cstddef>
#endif
#if __has_include("cstdio")
#include <cstdio>
#endif
#if __has_include("cstdlib")
#include <cstdlib>
#endif
#if __has_include("cstring")
#include <cstring>
#endif
#if __has_include("ctime")
#include <ctime>
#endif
#if __has_include("cwchar")
#include <cwchar>
#endif
#if __has_include("cwctype")
#include <cwctype>
#endif

#if __cplusplus >= 201103L
#if __has_include("ccomplex")
#include <ccomplex>
#endif
#if __has_include("cfenv")
#include <cfenv>
#endif
#if __has_include("cinttypes")
#include <cinttypes>
#endif
#if __has_include("cstdalign")
#include <cstdalign>
#endif
#if __has_include("cstdbool")
#include <cstdbool>
#endif
#if __has_include("cstdint")
#include <cstdint>
#endif
#if __has_include("ctgmath")
#include <ctgmath>
#endif
#if __has_include("cuchar")
#include <cuchar>
#endif
#endif

// C++
#if __has_include("algorithm")
#include <algorithm>
#endif
#if __has_include("bitset")
#include <bitset>
#endif
#if __has_include("complex")
#include <complex>
#endif
#if __has_include("deque")
#include <deque>
#endif
#if __has_include("exception")
#include <exception>
#endif
#if __has_include("fstream")
#include <fstream>
#endif
#if __has_include("functional")
#include <functional>
#endif
#if __has_include("iomanip")
#include <iomanip>
#endif
#if __has_include("ios")
#include <ios>
#endif
#if __has_include("iosfwd")
#include <iosfwd>
#endif
#if __has_include("iostream")
#include <iostream>
#endif
#if __has_include("istream")
#include <istream>
#endif
#if __has_include("iterator")
#include <iterator>
#endif
#if __has_include("limits")
#include <limits>
#endif
#if __has_include("list")
#include <list>
#endif
#if __has_include("locale")
#include <locale>
#endif
#if __has_include("map")
#include <map>
#endif
#if __has_include("memory")
#include <memory>
#endif
#if __has_include("new")
#include <new>
#endif
#if __has_include("numeric")
#include <numeric>
#endif
#if __has_include("ostream")
#include <ostream>
#endif
#if __has_include("queue")
#include <queue>
#endif
#if __has_include("set")
#include <set>
#endif
#if __has_include("sstream")
#include <sstream>
#endif
#if __has_include("stack")
#include <stack>
#endif
#if __has_include("stdexcept")
#include <stdexcept>
#endif
#if __has_include("streambuf")
#include <streambuf>
#endif
#if __has_include("string")
#include <string>
#endif
#if __has_include("typeinfo")
#include <typeinfo>
#endif
#if __has_include("utility")
#include <utility>
#endif
#if __has_include("valarray")
#include <valarray>
#endif
#if __has_include("vector")
#include <vector>
#endif

#if __cplusplus >= 201103L
#if __has_include("array")
#include <array>
#endif
#if __has_include("atomic")
#include <atomic>
#endif
#if __has_include("chrono")
#include <chrono>
#endif
#if __has_include("codecvt")
#include <codecvt>
#endif
#if __has_include("condition_variable")
#include <condition_variable>
#endif
#if __has_include("forward_list")
#include <forward_list>
#endif
#if __has_include("future")
#include <future>
#endif
#if __has_include("initializer_list")
#include <initializer_list>
#endif
#if __has_include("mutex")
#include <mutex>
#endif
#if __has_include("random")
#include <random>
#endif
#if __has_include("ratio")
#include <ratio>
#endif
#if __has_include("regex")
#include <regex>
#endif
#if __has_include("scoped_allocator")
#include <scoped_allocator>
#endif
#if __has_include("system_error")
#include <system_error>
#endif
#if __has_include("thread")
#include <thread>
#endif
#if __has_include("tuple")
#include <tuple>
#endif
#if __has_include("typeindex")
#include <typeindex>
#endif
#if __has_include("type_traits")
#include <type_traits>
#endif
#if __has_include("unordered_map")
#include <unordered_map>
#endif
#if __has_include("unordered_set")
#include <unordered_set>
#endif
#endif

#if __cplusplus >= 201402L
#if __has_include("shared_mutex")
#include <shared_mutex>
#endif
#endif

#if __cplusplus >= 201703L
#if __has_include("any")
#include <any>
#endif
#if __has_include("charconv")
#include <charconv>
#endif
// #include <execution>
#if __has_include("filesystem")
#include <filesystem>
#endif
#if __has_include("optional")
#include <optional>
#endif
#if __has_include("memory_resource")
#include <memory_resource>
#endif
#if __has_include("string_view")
#include <string_view>
#endif
#if __has_include("variant")
#include <variant>
#endif
#endif

#if __cplusplus > 201703L
#if __has_include("barrier")
#include <barrier>
#endif
#if __has_include("bit")
#include <bit>
#endif
#if __has_include("compare")
#include <compare>
#endif
#if __has_include("concepts")
#include <concepts>
#endif
#if __cpp_impl_coroutine
#if __has_include("coroutine")
# include <coroutine>
#endif
#endif
#if __has_include("latch")
#include <latch>
#endif
#if __has_include("numbers")
#include <numbers>
#endif
#if __has_include("ranges")
#include <ranges>
#endif
#if __has_include("span")
#include <span>
#endif
#if __has_include("stop_token")
#include <stop_token>
#endif
#if __has_include("semaphore")
#include <semaphore>
#endif
#if __has_include("source_location")
#include <source_location>
#endif
#if __has_include("syncstream")
#include <syncstream>
#endif
#if __has_include("version")
#include <version>
#endif
#endif


////////////////////////////////////////////////////////////////////////////////
//inf.hpp

#define inf_included
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <limits.h>
//#define log(q) std::cout<<#q;for (auto gg:(q).digits){std::cout<<' '<<gg;}std::cout<<'\n';
struct inf{
	struct Zinf{
		struct Ninf{
			std::vector<uint32_t> digits;
			inline void norm(){
				while (digits.size() && digits[digits.size()-1]==0){
					digits.pop_back();
				}
			}
			explicit operator uint_least64_t(){
				uint_least64_t f=0;
				for (uint_least64_t i=0;i<digits.size() and i<sizeof(uint_least64_t)/sizeof(int32_t);i++){
					f+=(uint_least64_t)(digits[i])<<(sizeof(int32_t)*8*i);
				}
				return f;
			}
			explicit operator std::string(){
				std::string e;
				Ninf t=*this;
				Ninf m,n;
				Ninf zero(0);
				Ninf ten(10);
				while (t.diff(zero)){
					n=t/ten;
					m=(t.add(n*ten,-1));
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
				for (int_least64_t t=digits.size()-1;t>=0;t--){
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
						s.digits=std::vector<uint32_t> (u+i);
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
				Ninf c=1;
				Ninf a=0;
				while (digits.size()>=o.digits.size()){
					o=o<<(sizeof(int32_t)*8);
					c=c<<(sizeof(int32_t)*8);
				}
				while (c.diff(0)){
					if (this->diff(o)>-1){
						*this=this->add(o,-1);
						a=a.add(c,1);
					}
					c=c>>1;
					o=o>>1;
				}
				return a;
			}
			inline Ninf operator<<(Ninf o){
				Ninf a=*this;
				Ninf r;
				uint32_t s;
				if(o.diff(sizeof(int32_t)*8)==-1){
					r=0;
				}else if(o.diff(sizeof(int32_t)*8*2)==-1){
					r=1;
				}else{
					r=o/(sizeof(int32_t)*8);
				}
				s=uint_least64_t(o.add(r*sizeof(int32_t)*8,-1));
				if(r.diff(digits.size())==1){
					r=digits.size();
				}
				auto dig=std::vector<uint32_t>();
				Ninf zero(0);
				dig.resize(dig.size()+uint_least64_t(r));
				dig.insert(dig.end(),a.digits.begin(), a.digits.end());
				a.digits=dig;
				a.digits.resize(a.digits.size()+1);
				uint_least64_t t=0;
				uint32_t y=0;
				for(auto d=a.digits.begin();d!=a.digits.end();d++){
					t=(uint_least64_t)(*d);
					t<<=s;
					*d=t;
					*d+=y;
					y=t>>(sizeof(int32_t)*8);
				}

				a.norm();
				return a;
			}
			inline Ninf operator>>(Ninf o){
				Ninf a=*this;
				Ninf r;
				uint32_t s;
				if(o.diff(sizeof(int32_t)*8)==-1){
					r=0;
				}else if(o.diff(sizeof(int32_t)*8*2)==-1){
					r=1;
				}else{
					r=o/(sizeof(int32_t)*8);
				}
				s=uint_least64_t(o.add(r*sizeof(int32_t)*8,-1));
				if(r.diff(digits.size())==1){
					r=digits.size();
				}
				a.digits=std::vector<uint32_t>(a.digits.begin()+uint_least64_t(r),a.digits.end());
				uint_least64_t t=0;
				uint32_t y=0;
				for(auto d=a.digits.rbegin();d!=a.digits.rend();d++){
					t=(uint_least64_t)(*d)<<(sizeof(int32_t)*8);
					t>>=s;
					*d=t>>(sizeof(int32_t)*8);
					*d+=y;
					y=t;
				}
				return a;
			}
		};
		Ninf mod;
		int32_t sign;
		inline void norm(){
			mod.norm();
			Ninf zero(0);
			if (mod.diff(zero)==0){
				sign=0;
			} else if(sign==0){
				mod=zero;
			}
		}
		inline int32_t diff(Zinf o){
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
			return 0;
		}
		explicit operator std::string(){
			std::string e;
			if (sign==0){
				e="0";
			}
			if (sign==1){
				e=std::string(mod);
			}
			if (sign==-1){
				e="-"+std::string(mod);
			}
			return e;
		}
		explicit operator int_least64_t(){
			return sign*uint_least64_t(mod);
		}
		inline Zinf(std::string o){
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
		inline Zinf(){
			sign=0;
		};
		inline Zinf(int_least64_t o){
			sign=(!!o)*(o<0?-1:1);
			int32_t m=0;
			if (o==INT_MIN){
				m=1;
				o+=1;
			}
			if (o<0){
				o=-o;
			}
			Ninf t(o);
			mod=t;
			if (m){
				*this=add(*this,m,-1);
			}
		}
		friend inline Zinf add(Zinf s,Zinf o,int32_t d){
			o.sign*=d;
			Zinf a;
			if (s.sign==o.sign){
				a.mod=s.mod.add(o.mod,1);
				a.sign=s.sign;
			}
			else{
				int32_t d=s.mod.diff(o.mod);
				if (d==1){
					a.mod=s.mod.add(o.mod,-1);
					a.sign=s.sign;
				}else if (d==-1){
					a.mod=o.mod.add(s.mod,-1);
					a.sign=o.sign;
				}else{
					a=Zinf(0);
				}
			}
			return a;
		}
		friend inline Zinf operator-(Zinf s){
			s.sign*=-1;
			return s;
		}
		friend inline Zinf operator*(Zinf s,Zinf o){
			Zinf a;
			a.mod=s.mod*o.mod;
			a.sign=s.sign*o.sign;
			a.norm();
			return a;
		}
		friend inline Zinf operator/(Zinf s,Zinf o){
			Zinf a;
			a.sign=s.sign/o.sign;
			a.mod=s.mod/o.mod;
			a.norm();
			return a;
		}
		friend inline Zinf operator%(Zinf s,Zinf o){
			return add(s,s/o*o,-1);
		}
		friend inline Zinf shift(Zinf s,Zinf o){
			Zinf a=s;
			if (o.diff(0)>0){
				a.mod=a.mod>>o.mod;
			}
			if (o.diff(0)<0){
				a.mod=a.mod<<o.mod;
			}
		}
		friend inline Zinf operator&(Zinf s,Zinf o){
			Zinf a=s;
			while (a.mod.digits.size()>o.mod.digits.size()){
				o.mod.digits.push_back(0);
			}
			while (a.mod.digits.size()<o.mod.digits.size()){
				a.mod.digits.push_back(0);
			}
			for (uint_least64_t f=0;f<o.mod.digits.size();f++){
				a.mod.digits[f]&=o.mod.digits[f];
			}
			a.norm();
			return a;
		}
		friend inline Zinf operator^(Zinf s,Zinf o){
			Zinf a=s;
			while (a.mod.digits.size()>o.mod.digits.size()){
				o.mod.digits.push_back(0);
			}
			while (a.mod.digits.size()<o.mod.digits.size()){
				a.mod.digits.push_back(0);
			}
			for (uint_least64_t f=0;f<o.mod.digits.size();f++){
				a.mod.digits[f]^=o.mod.digits[f];
			}
			a.norm();
			return a;
		}
		friend inline Zinf operator|(Zinf s,Zinf o){
			Zinf a=s;
			while (a.mod.digits.size()>o.mod.digits.size()){
				o.mod.digits.push_back(0);
			}
			while (a.mod.digits.size()<o.mod.digits.size()){
				a.mod.digits.push_back(0);
			}
			for (uint_least64_t f=0;f<o.mod.digits.size();f++){
				a.mod.digits[f]|=o.mod.digits[f];
			}
			a.norm();
			return a;
		}
		friend inline Zinf operator&=(Zinf& s,Zinf o){
			s=s&o;
			auto a=s;
			return a;
		}
		friend inline Zinf operator^=(Zinf& s,Zinf o){
			s=s^o;
			auto a=s;
			return a;
		}
		friend inline Zinf operator|=(Zinf& s,Zinf o){
			s=s|o;
			auto a=s;
			return a;
		}
/*		friend inline Zinf operator>>=(Zinf& s,Zinf o){
			s=shift(s,o);
			auto a=s;
			return a;
		}
		friend inline Zinf operator<<=(Zinf& s,Zinf o){
			s=shift(s,-o);
			auto a=s;
			return a;
		}
*/	};
	int_least64_t sval;
	bool longer;
	Zinf lval;
	inline void norm(){
		if (longer){
			lval.norm();
		}
		if (LLONG_MIN<=lval and lval<=LLONG_MAX){
			sval=int_least64_t(lval);
			lval=0;
			longer=0;
		}
	}
	inline inf(): sval(0), longer(0), lval(0){}
	inline inf(int_least64_t a): sval(a), longer(0), lval(0){}
	inline inf(int_least64_t a,bool s,Zinf d): sval(a), longer(s), lval(d){}
	inline inf(Zinf d): sval(0), longer(0), lval(d){
		this->norm();
	}
	inline inf(std::string o):sval(0), longer(0), lval(o){
		this->norm();
	}
	explicit inline operator Zinf(){
		return longer?lval:Zinf(sval);
	}
	explicit operator bool(){
		return longer?bool(lval.sign):bool(sval);
	}
	explicit operator std::string(){
		return longer?std::string(lval):std::to_string(sval);
	}
	friend inline inf inf(std::string o){
		inf a(o);
		return a;
	}
	explicit operator int_least64_t(){
		return longer?int_least64_t(lval):sval;	
	}
	friend inline std::ostream& operator<<(std::ostream& os,inf i){
		os<<std::string(i);
		return os;
	}
	friend inline std::istream& operator>>(std::istream& is,inf&i){
		std::string o;
		is>>o;
		i=o;
		return is;
	}
	friend inline inf operator+(inf s){
		return s;
	}
	friend inline inf operator-(inf s){
		if (s.longer==0 and s.sval!=LLONG_MIN){
			s.sval= -s.sval;
		}else{
			s=inf(-Zinf(s));
		}
		return s;
	}

	#define oper2(d,f,p)\
	friend inline inf operato##d (inf s,inf o){p}\
	friend inline inf operato##d##= (inf& s,inf o){p}

	#define oper1(d,f,p)\
	friend inline inf operato##d (inf s){p}

	#define coper2(d,f,c)\
	oper2(d,f,\
		if (s.longer==0 and o.longer==0 and (c)){\
			s.sval= s.sval f o.sval;\
		}else{\
			s=inf(Zinf(s) f Zinf(o));\
		}\
		return s;\
	)

	#define coper1(d,f,c)\
	oper1(d,f,\
		if (s.longer==0 and (c)){\
			s.sval = f s.sval;\
		}else{\
			s=inf(f Zinf(s));\
		}\
		return s;\
	)


	coper2(r+,+,
		(o.sval<0 or LLONG_MAX-o.sval>=s.sval) and
		(o.sval>0 or LLONG_MIN-o.sval<=s.sval)
	)
	coper2(r-,-,
		(s.sval<0 or LLONG_MAX-s.sval>=-o.sval) and
		(s.sval>0 or LLONG_MIN-s.sval<=-o.sval)
	)
	coper2(r*,*,
		(s.sval<0 or o.sval<0 or LLONG_MAX/s.sval>=o.sval) and
		(s.sval>0 or o.sval<0 or LLONG_MAX/(-s.sval)>=o.sval) and
		(s.sval<0 or o.sval>0 or LLONG_MAX/s.sval>=-o.sval) and
		(s.sval>0 or o.sval>0 or LLONG_MAX/s.sval<=o.sval)
	)
	coper2(r/,/,1)
	coper2(r%,%,1)
	coper1(r~,~,1)
	oper1(r!,!,
		if (s.longer==0){
			s=inf(!s.sval);
		}else{
			s=inf(!s.lval.sign);
		}
		return s;
	)
	oper2(r<<,<<,
		s=inf({0,1,shift(Zinf(s),-Zinf(o))});
		return s;
	)
	coper2(r>>,>>,1)
	coper2(r&,&,1)
	coper2(r|,|,1)
	coper2(r^,^,1)

	#define cmp(d,f)\
	friend inline bool operato##d(inf s,inf o){\
		return\
			s.longer==0&&o.longer==0?\
				s.sval f o.sval\
			:\
				Zinf(s).diff(Zinf(o)) f 0\
		;\
	}
	cmp(r<,<)
	cmp(r==,==)
	cmp(r>,>)
	cmp(r<=,<=)
	cmp(r!=,!=)
	cmp(r>=,>=)
	friend inline inf operator++(inf& s){
		return s+=1;
	}
	friend inline inf operator--(inf& s){
		return s-=1;
	}
	friend inline inf operator++(inf& s,int32_t){
		inf a=s;
		s+=1;
		return a;
	}
	friend inline inf abs(inf s){
		if (s.longer and s.sval!=LLONG_MIN){
			s.sval=s.sval<0?-s.sval:s.sval;
		}else{
			s.lval=Zinf(s);
			s.lval=s.lval<0?-s.lval:s.lval;
			s.sval=0;
			s.longer=1;
		}
		return s;
	}
};
#ifdef replace_int
	using old_int = int;
	#define int inf
#endif


////////////////////////////////////////////////////////////////////////////////
//str.hpp

#include <string>
bool startswith(std::u32string self,std::u32string edge){
	return (self).rfind(edge,0)==0;
}
bool endswith(std::u32string self, std::u32string edge){
	return (self).find(edge,(self).size()-edge.size())==(self).size()-edge.size();
}

std::u32string to_u32(std::string q){
	std::u32string r;
	for(int64_t w=0;w<q.size();++w){
		if ((q[w]&(0b10000000))==0){
			r.push_back(((int32_t(uint8_t(q[w]))<<0)));
		}
		if ((q[w]&(0b11100000))==0b11000000 and w<q.size()-1){
			r.push_back(((int32_t(uint8_t(q[w]))<<8)+(int32_t(uint8_t(q[w+1]))<<0)));
		}
		if ((q[w]&(0b11110000))==0b11100000 and w<q.size()-2){
			r.push_back(((int32_t(uint8_t(q[w]))<<16)+(int32_t(uint8_t(q[w+1]))<<8)+(int32_t(uint8_t(q[w+2]))<<0)));
		}
		if ((q[w]&(0b11111000))==0b11110000 and w<q.size()-3){
			r.push_back(((int32_t(uint8_t(q[w]))<<24)+(int32_t(uint8_t(q[w+1]))<<16)+(int32_t(uint8_t(q[w+2]))<<8)+(int32_t(uint8_t(q[w+3]))<<0)));
		}
	}
	return r;
}

std::string to_u8(std::u32string q){
	std::string r;
	for(auto w:q){
		if (w&0b11111111000000000000000000000000){
			r.push_back((w&0b11111111000000000000000000000000)>>24);
		}
		if (w&0b111111110000000000000000){
			r.push_back((w&0b111111110000000000000000)>>16);
		}
		if (w&0b1111111100000000){
			r.push_back((w&0b1111111100000000)>>8);
		}
		r.push_back(w&0b11111111);
	}
	return r;
}


std::u32string replace(std::u32string self, std::u32string old,std::u32string ne,int maxcount=-1){
	std::u32string res=to_u32("");
	for (int64_t w=0;w<(self).size();){
		if (maxcount and (self).rfind(old,w)==w){
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
std::vector<std::u32string> split(std::u32string self,std::u32string old,int maxcount=-1){
	auto res=std::vector<std::u32string>();
	res.push_back(std::u32string());
	for (int64_t w=0;w<(self).size();){
		if (maxcount and (self).rfind(old,w)==w){
			res.push_back(std::u32string());
			w+=old.size();
			maxcount=maxcount>0?maxcount-1:maxcount;
		}else{
			res[res.size()-1]+=(self)[w];
			++w;
		}
	}
	return res;
}
std::vector<std::u32string> split(std::u32string self){
	auto res=std::vector<std::u32string>();
	int need_new=1;
	for (int w=0;w<(self).size();++w){
		if (std::u32string({9, 10, 11, 12, 13, 28, 29, 30, 31, 32}).find(std::u32string({(self)[w]}))!=-1){
			need_new=1;
		}else{
			if (need_new){
				res.push_back(std::u32string());
				need_new=0;
			}
			res[res.size()-1]+=(self)[w];
		}
	}
	return res;
}
std::u32string join(std::u32string self,std::vector<std::u32string> a){
	std::u32string res;
	int c=0;
	for (auto d:a){
		if (c){
			res+=self;
		}
		res+=d;
		c=1;
	}
	return res;
}

int64_t chr(int64_t q){
	if(q<(1<<7)){
		return ((q&127)<<0);
	}
	if(q<(1<<11)){
		return 49280+((q&1984)<<2)+((q&63)<<0);
	}
	if(q<(1<<16)){
		return 14712960+((q&61440)<<4)+((q&4032)<<2)+((q&63)<<0);
	}
	if(q<(1<<21)){
		return 4034953344+((q&1835008)<<6)+((q&258048)<<4)+((q&4032)<<2)+((q&63)<<0);
	}
	printf("%lli is too big\n", q);
	return 0;
}

int64_t ord(int64_t q){
	int64_t r=0;
	int w,e;
	for (w=3*8;w>-1;w-=8){
		int started=0;
		for (e=7;e>-1;--e){
			if (started==0 and (q&(1<<(w+e)))==0){
				started=1;
			} else
			if (started){
				r=(r<<1)+!!(q&(1<<(w+e)));
			}
		}
	}
	return r;
}





////////////////////////////////////////////////////////////////////////////////
//frag.hpp

#define stl(a) a.begin(),a.end()
template <typename T>
T frag(T a,int_least64_t s=0,int_least64_t d=0){
	auto f=a.size();
	if (s>f){
		s=f;
	}
	if (s<0){
		s+=f;
	}
	if (s<0){
		s=0;
	}
	if (d<-f){
		d=-f;
	}
	if (d>0){
		d-=f;
	}
	if (d>0){
		d=0;
	}
	return decltype(a)(a.begin()+s,a.end()-s);
}

////////////////////////////////////////////////////////////////////////////////
//range.hpp

template <typename T>
struct range_struct{
	struct range_iterator{
		T val, step;
		inline range_iterator(T v,T s){
			val=v;
			step=s;
		}
		inline bool operator!=(range_iterator o){
			if (step>0 and val>=o.val){
				return false;
			}
			if (step<0 and val<=o.val){
				return false;
			}
			if (step==0 and val==o.val){
				return false;
			}
			return true;
		}
		inline void operator++(){
			val+=step;
		}
		inline T operator*(){
			return val;
		}
	};
	T start, stop, step;
	inline range_iterator begin(){
		range_iterator r(start,step);
		return r;
	}
	inline range_iterator end(){
		range_iterator r(stop,step);
		return r;
	}
};
template <typename Y>
	inline range_struct<Y> range(Y a,Y o,Y e){
		range_struct<Y> r;
		r.start=a;
		r.stop=o;
		r.step=e;
		return r;
	}
template <typename Y>
	inline range_struct<Y> range(Y a,Y o){
		range_struct<Y> r;
		r.start=a;
		r.stop=o;
		r.step=1;
		return r;
	}
template <typename Y>
	inline range_struct<Y> range(Y o){
		range_struct<Y> r;
		r.start=0;
		r.stop=o;
		r.step=1;
		return r;
	}


////////////////////////////////////////////////////////////////////////////////
//funcsynt.hpp

#define def0(fun) auto fun()
#define structor0(fun) fun()
#define def1(fun,a0) template<typename t0> auto inline fun(t0 a0)
#define structor1(fun,a0) template<typename t0> inline fun(t0 a0)
#define def2(fun,a0,a1) template<typename t0,typename t1> auto inline fun(t0 a0,t1 a1)
#define structor2(fun,a0,a1) template<typename t0,typename t1> inline fun(t0 a0,t1 a1)
#define def3(fun,a0,a1,a2) template<typename t0,typename t1,typename t2> auto inline fun(t0 a0,t1 a1,t2 a2)
#define structor3(fun,a0,a1,a2) template<typename t0,typename t1,typename t2> inline fun(t0 a0,t1 a1,t2 a2)
#define def4(fun,a0,a1,a2,a3) template<typename t0,typename t1,typename t2,typename t3> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3)
#define structor4(fun,a0,a1,a2,a3) template<typename t0,typename t1,typename t2,typename t3> inline fun(t0 a0,t1 a1,t2 a2,t3 a3)
#define def5(fun,a0,a1,a2,a3,a4) template<typename t0,typename t1,typename t2,typename t3,typename t4> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4)
#define structor5(fun,a0,a1,a2,a3,a4) template<typename t0,typename t1,typename t2,typename t3,typename t4> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4)
#define def6(fun,a0,a1,a2,a3,a4,a5) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5)
#define structor6(fun,a0,a1,a2,a3,a4,a5) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5)
#define def7(fun,a0,a1,a2,a3,a4,a5,a6) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6)
#define structor7(fun,a0,a1,a2,a3,a4,a5,a6) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6)
#define def8(fun,a0,a1,a2,a3,a4,a5,a6,a7) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7)
#define structor8(fun,a0,a1,a2,a3,a4,a5,a6,a7) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7)
#define def9(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8)
#define structor9(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8)
#define def10(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9)
#define structor10(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9)
#define def11(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10)
#define structor11(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10)
#define def12(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11)
#define structor12(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11)
#define def13(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12)
#define structor13(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12)
#define def14(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13)
#define structor14(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13)
#define def15(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14)
#define structor15(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14)
#define def16(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15)
#define structor16(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15)
#define def17(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16)
#define structor17(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16)
#define def18(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17)
#define structor18(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17)
#define def19(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18)
#define structor19(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18)
#define def20(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19)
#define structor20(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19)
#define def21(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20)
#define structor21(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20)
#define def22(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21)
#define structor22(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21)
#define def23(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22)
#define structor23(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22)
#define def24(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23)
#define structor24(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23)
#define def25(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24)
#define structor25(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24)
#define def26(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25)
#define structor26(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25)
#define def27(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26)
#define structor27(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26)
#define def28(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26,typename t27> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26,t27 a27)
#define structor28(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26,typename t27> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26,t27 a27)
#define def29(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26,typename t27,typename t28> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26,t27 a27,t28 a28)
#define structor29(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26,typename t27,typename t28> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26,t27 a27,t28 a28)
#define def30(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26,typename t27,typename t28,typename t29> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26,t27 a27,t28 a28,t29 a29)
#define structor30(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26,typename t27,typename t28,typename t29> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26,t27 a27,t28 a28,t29 a29)
#define def31(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26,typename t27,typename t28,typename t29,typename t30> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26,t27 a27,t28 a28,t29 a29,t30 a30)
#define structor31(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26,typename t27,typename t28,typename t29,typename t30> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26,t27 a27,t28 a28,t29 a29,t30 a30)
#define def32(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,a31) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26,typename t27,typename t28,typename t29,typename t30,typename t31> auto inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26,t27 a27,t28 a28,t29 a29,t30 a30,t31 a31)
#define structor32(fun,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,a31) template<typename t0,typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8,typename t9,typename t10,typename t11,typename t12,typename t13,typename t14,typename t15,typename t16,typename t17,typename t18,typename t19,typename t20,typename t21,typename t22,typename t23,typename t24,typename t25,typename t26,typename t27,typename t28,typename t29,typename t30,typename t31> inline fun(t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15,t16 a16,t17 a17,t18 a18,t19 a19,t20 a20,t21 a21,t22 a22,t23 a23,t24 a24,t25 a25,t26 a26,t27 a27,t28 a28,t29 a29,t30 a30,t31 a31)


////////////////////////////////////////////////////////////////////////////////
//synt.hpp

#ifdef replace_int
using ___main=old_int;
#else
using ___main=int;
#endif
#define pony_wakeup using namespace std;
#define pony_run void pony()
#define let auto
#define var auto
#define len(q) q.size()
#define append push_back
#define in :
#define while while(
#define do )
#define if if(
#define elif else if
#define for for(auto 
typedef std::u32string str_t;
#define int int64_t
#define float (long double)
#define type(q) decltype(q())
#ifdef inf_included
	using long_int=inf;
#else
	using long_int=int_least64_t;
#endif
#define short_int int_least64_t

std::vector<std::u32string>argv;
std::vector<std::string>__argv;

void pony();

___main main(___main _argc,char**_argv){
	__argv=decltype(__argv)(_argv,_argv+_argc);
	for _arg in __argv do{argv.push_back(to_u32(_arg));}
	pony();
	return 0;
}


#define vect(...) vect_funct({__VA_ARGS__})
template <typename t>
std::vector<t> vect_funct(std::initializer_list<t> a){
	std::vector<t> s(a.begin(),a.end());
	return s;
}

#define vect_by_val(t) vector<decltype(t)>()
#define vect_by_type(t) vector<t>()

std::u32string str(){
	return std::u32string();
}

#define to_make_str(type,code) std::u32string str(type orig){let s=std::stringstream();code;return to_u32(s.str());}

to_make_str(const int8_t,s<<int(orig))
to_make_str(const int16_t,s<<orig)
to_make_str(const int32_t,s<<orig)
to_make_str(const int64_t,s<<orig)
to_make_str(const char,let d=str();d.push_back(char32_t(orig));s<<to_u8(d))
to_make_str(const char16_t,let d=str();d.push_back(char32_t(orig));s<<to_u8(d))
to_make_str(const char32_t,let d=str();d.push_back(char32_t(orig));s<<to_u8(d))
to_make_str(const bool,s<<(orig?"True":"False"))
to_make_str(const char *,s<<orig)
// to_make_str(float,s<<orig)
to_make_str(const std::string,s<<orig)
to_make_str(const std::u32string,s<<to_u8(orig))

template<typename t>
to_make_str(std::vector<t>,s<<"[";let y=len(orig);for w in orig do{s<<w<<((--y)?", ":"");};s<<"]";)

/*#define scan(t) scan_from_type<t>()
template <typename t>
auto scan_from_type(){
	let q=t();
	std::cin>>q;
	return q;
}*/

#define scan(t) scan_f(t())
#define to_make_scan(type,code) auto scan_f(type orig){code;return orig;}

to_make_scan(int64_t,std::cin>>orig)
to_make_scan(char,std::cin>>orig)
to_make_scan(str_t,let d=std::string();std::cin>>d;orig=to_u32(d))
to_make_scan(std::string,std::cin>>orig)
// to_make_scan(float,std::cin>>orig)



#define print(...) print_f(__VA_ARGS__);
template <typename... t>
void print_f(t... a){
	int y=sizeof...(t);
	int dummy[sizeof...(t)] = { (std::cout<<to_u8(str(a))<<((--y)?" ":""), 0)... };
	std::cout<<std::endl;
}

#define write(...) print_nn_f(__VA_ARGS__);
template <typename... t>
void print_nn_f(t... a){
	int dummy[sizeof...(t)] = { (std::cout<<to_u8(str(a))                , 0)... };
}


////////////////////////////////////////////////////////////////////////////////
//the code

using namespace std;
pony_run{
	let ps=vect(int(2));
	for w in range(3,400000) do{
		let isp=1;
		let cp=0;
		while cp<len(ps) and ps[cp]*ps[cp]<=w do{
			if w%ps[cp]==0 do{
				isp=0;
				break;
			}
			++cp;
		}
		if isp do{
			ps.append(w);
		}
	}
	let a=set<int>();
	for w in ps do{
		for e in ps do{
			if w%10==e%10 and w!=e and 264871<=w*e do{
				if w*e <=322989 do{
					a.insert(w*e);
				}else{
					break;
				}
			}
		}
	}
	let f=vect_by_type(int);
	for w in a do{
		f.append(w);
	}
	let rs=int(0);
	for w in f do{
		rs+=w;
	}
	print(rs,int(len(f)));
}