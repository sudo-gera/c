
/******************************************************************************/
/*defining numeric*/
#include<numeric>

/******************************************************************************/
/*defining vector*/
#include<vector>

/******************************************************************************/
/*defining string*/
#include<string>

/******************************************************************************/
/*defining stdc++*/
#include<bits/stdc++.h>

/******************************************************************************/
/*defining initializer_list*/
#include<initializer_list>

/******************************************************************************/
/*defining complex*/
#include<complex>

/******************************************************************************/
/*defining map*/
#include<map>

/******************************************************************************/
/*defining set*/
#include<set>

/******************************************************************************/
/*defining filt*/

				std::string exec(std::string command) {
					char buffer[128];
					std::string result = "";

					// Open pipe to file
					FILE* pipe = popen(command.c_str(), "r");
					if (!pipe) {
						return "popen failed!";
					}

					// read till end of process:
					while (!feof(pipe)) {

						// use buffer to read and add to result
						if (fgets(buffer, 128, pipe) != NULL)
							result += buffer;
					}

					pclose(pipe);
					return result;
				}

				std::string filt(std::string q){
					auto a=exec(std::string("c++filt -t ")+q);
					auto symbs=std::vector<char>(33);
					iota(symbs.begin(),symbs.end(),0);
					while(count(symbs.begin(),symbs.end(),a[0])){
						a=std::string(a.begin()+1,a.end());
					}
					while(count(symbs.begin(),symbs.end(),a[a.size()-1])){
						a=std::string(a.begin(),a.end()-1);
					}
					return a;
				}
			

/******************************************************************************/
/*defining iostream*/
#include<iostream>

/******************************************************************************/
/*defining any*/
#include<any>

/******************************************************************************/
/*defining python_variable*/



				#define fend(q) std::cout<<"line "<<__LINE__<<":\n\tunexpected exit from function"<<std::endl;return make_value(q);

				class python_NoneType{};
				python_NoneType python_None;

				class python_ellipsis{};
				python_ellipsis python_Ellipsis;

				template <typename T=python_NoneType>
				auto make_value(T a=python_None){
					return a;
				}

				#define python_complex				std::complex<double>
				#define python_float				double
				#define python_int					int64_t
				#define python_bool					bool
				#define python_bytearray			std::string
				#define python_bytes				std::string
				#define python_str					std::u32string
				#define python_list					std::vector<var>
				#define python_set					std::set<var>
				#define python_dict					std::map<var,var>
				#define python_NoneType				python_NoneType
				#define python_ellipsis				python_ellipsis




				#define python_iftype(a,...) __VA_ARGS__ s;\
					if (var(a).type()==typeid(std::declval<python_variable<__VA_ARGS__>>())){\
						s=cast(var(a),__VA_ARGS__);\
					}\
					if (var(a).type()==typeid(std::declval<python_variable<__VA_ARGS__>>()))

				#define cast(q,...) (var(q).cast_with_line<__VA_ARGS__>(__LINE__))

				#define super_cast(q,...) cast(__python__##__VA_ARGS__(q),python_##__VA_ARGS__)

				#define print_line() std::cout<<__LINE__<<std::endl;

				template<typename T>
				class python_variable{
				public:
					T*p;
					python_int*c;
					T &value(){
						return *p;
					}
					python_variable(T a=python_int(0)){
						c=new python_int(1);
						p=new T(a);
					}
					python_variable(const python_variable &a){
						p=a.p;
						c=a.c;
						*c+=1;
					}
					python_variable operator=(T a){
						c=new python_int(1);
						p=new T(a);
					}
					python_variable operator=(const python_variable &a){
						p=a.p;
						c=a.c;
						*c+=1;
					}
					~python_variable(){
						*c-=1;
						if (*c==0){
							delete p;
							delete c;
						}
					}
				};

				template <typename T>
				std::any to_var(T q){
					std::any t=python_variable<T>(q);
					return t;
				}

				template <typename T>
				T &from_var(std::any q,python_int line){
					if (q.type()!=typeid(std::declval<python_variable<T>>())){
						std::cout<<"wrong cast"<<std::endl;
						std::cout<<"    line "<<line<<std::endl;
						std::cout<<"    have "<<filt(q.type().name())<<std::endl;
						std::cout<<"    want "<<filt(typeid(std::declval<python_variable<T>>()).name())<<std::endl;
					}
					return std::any_cast<python_variable<T>>(q).value();
				}

				class var{
				public:
					std::any a;
					template<typename t>
					var(t q){
						a=to_var(q);
					}
					var(){
						a=to_var(python_int(0));
					}
					template<typename t>
					var operator=(t q){
						a=to_var(q);
						return *this;
					}
					template<typename t>
					t &cast_with_line(python_int line){
						return from_var<t>(a,line);
					}
					auto&type(){
						return a.type();
					}
					var operator+(var o);
					var operator-(var o);
					var operator+();
					var operator-();
					var operator*(var o);
					var operator/(var o);
					var operator%(var o);
					var operator==(var o);
					var operator!=(var o);
					var operator>(var o);
					var operator<(var o);
					var operator>=(var o);
					var operator<=(var o);
					var operator!();
					var operator&&(var o);
					var operator||(var o);
					var operator~();
					var operator&(var o);
					var operator|(var o);
					var operator^(var o);
					var operator<<(var o);
					var operator>>(var o);
					var operator+=(var o);
					var operator-=(var o);
					var operator*=(var o);
					var operator/=(var o);
					var operator%=(var o);
					var operator&=(var o);	
					var operator|=(var o);
					var operator^=(var o);
					var operator<<=(var o);
					var operator>>=(var o);
					var operator[](var o);
					bool operator<(const var o) const;
				};

				class python_iterate{
				public:
					var orig;
					python_iterate(var q):orig(q){}
					class iterator{
					public:
						var orig;
						var iter;
						iterator(var q):orig(q),iter(q){
							int64_t c=0;
							{python_iftype(orig,python_list){
								iter=cast(orig,decltype(s)).begin();
								c=1;
							}}
							{python_iftype(orig,python_set){
								iter=cast(orig,decltype(s)).begin();
								c=1;
							}}
							{python_iftype(orig,python_dict){
								iter=cast(orig,decltype(s)).begin();
								c=1;
							}}
							{python_iftype(orig,python_str){
								iter=cast(orig,decltype(s)).begin();
								c=1;
							}}
							{python_iftype(orig,python_bytearray){
								iter=cast(orig,decltype(s)).begin();
								c=1;
							}}
							if(!c){
								std::cout<<filt(orig.type().name())<<" is not iterable"<<std::endl;
							}
						}
						
						void operator++(){
							{python_iftype(orig,python_list){
								 ++cast(iter,decltype(s)::iterator);
							}}
							{python_iftype(orig,python_set){
								 ++cast(iter,decltype(s)::iterator);
							}}
							{python_iftype(orig,python_dict){
								 ++cast(iter,decltype(s)::iterator);
							}}
							{python_iftype(orig,python_str){
								 ++cast(iter,decltype(s)::iterator);
							}}
							{python_iftype(orig,python_bytearray){
								 ++cast(iter,decltype(s)::iterator);
							}}
						}
						bool operator!=(iterator o){
							{python_iftype(orig,python_list){
								return cast(iter,decltype(s)::iterator)!=cast(orig,decltype(s)).end();
							}}
							{python_iftype(orig,python_set){
								return cast(iter,decltype(s)::iterator)!=cast(orig,decltype(s)).end();
							}}
							{python_iftype(orig,python_dict){
								return cast(iter,decltype(s)::iterator)!=cast(orig,decltype(s)).end();
							}}
							{python_iftype(orig,python_str){
								return cast(iter,decltype(s)::iterator)!=cast(orig,decltype(s)).end();
							}}
							{python_iftype(orig,python_bytearray){
								return cast(iter,decltype(s)::iterator)!=cast(orig,decltype(s)).end();
							}}
							fend(0)
						}
						var operator*(){
							{python_iftype(orig,python_list){
								return *cast(iter,decltype(s)::iterator);
							}}
							{python_iftype(orig,python_set){
								return *cast(iter,decltype(s)::iterator);
							}}
							{python_iftype(orig,python_dict){
								return (*cast(iter,decltype(s)::iterator)).first;
							}}
							{python_iftype(orig,python_str){
								return python_str({*cast(iter,decltype(s)::iterator)});
							}}
							{python_iftype(orig,python_bytearray){
								return python_bytearray({*cast(iter,decltype(s)::iterator)});
							}}
							fend();
						}
					};
					iterator begin(){
						return iterator(orig);
					}
					iterator end(){
						return iterator(orig);
					}
				};
			

/******************************************************************************/
/*defining unicode_convert*/

				char32_t chr(int64_t q){
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
					return 0;
				}

				int64_t ord(char32_t q){
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
					for(auto &w:r){
						w=ord(w);
					}
					return r;
				}

				std::string to_u8(std::u32string q){
					for(auto &w:q){
						w=chr(w);
					}	
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
			

/******************************************************************************/
/*defining builtins_float*/

				var __python__float(var q=python_int(0)){
				//	{python_iftype(q,python_str){
				//		return s;
				//	}
				//	}
				//	{python_iftype(q,python_bytearray){
				//		return to_u32(s);
				//	}
				//	}
					{python_iftype(q,python_int){
						return (python_float)(s);
					}
					}
					{python_iftype(q,python_float){
						return s;
					}
					}
					{python_iftype(q,int){
						return (python_float)(s);
					}
					}
					fend()
				}
			

/******************************************************************************/
/*defining builtins_str*/

				var __python__str(var q=python_str()){
					{python_iftype(q,python_str){
						return s;
					}
					}
					{python_iftype(q,python_bytearray){
						python_bytes r="b'";
						for (auto _w:s){
							auto w=(unsigned char)(_w);
							if(w==9){
								r+="\\t";
							}else if(w==10){
								r+="\\n";
							}else if(w==13){
								r+="\\r";
							}else if(w==76){
								r+="\\\\";
							}else if(w>126 or w<32){
								r+=python_bytes({'\\','x',python_bytes("0123456789abcdef")[w/16],python_bytes("0123456789abcdef")[w%16]});
							}else{
								r+=python_bytes({_w});
							}
						}
						r+="'";
						return to_u32(r);
					}
					}
					{python_iftype(q,python_int){
						return to_u32(std::to_string(s));
					}
					}
					{python_iftype(q,python_float){
						return to_u32(std::to_string(s));
					}
					}
					{python_iftype(q,python_complex){
						if (s.imag()<0){
							return to_u32(std::to_string(s.real())+std::to_string(s.imag())+"j");
						}else{
							return to_u32(std::to_string(s.real())+"+"+std::to_string(s.imag())+"j");
						}
					}
					}
					{python_iftype(q,int){
						return to_u32(std::to_string(s));
					}
					}
					{python_iftype(q,python_bool){
						return to_u32(s?"True":"False");
					}
					}
					{python_iftype(q,python_NoneType){
						return to_u32("None");
					}
					}
					{python_iftype(q,python_ellipsis){
						return to_u32("Ellipsis");
					}
					}

					fend()
				}
			

/******************************************************************************/
/*defining builtins_complex*/

			var __python__complex(var q=python_int(0),var w=python_int(0)){
				{python_iftype(q,python_complex){
				}else{
					q=python_complex(cast(__python__float(q),python_float),0);
				}
				}
				{python_iftype(w,python_complex){
				}else{
					w=python_complex(cast(__python__float(w),python_float),0);
				}
				}
				return cast(q,python_complex)+python_complex(0,1)*cast(w,python_complex);
			}
			

/******************************************************************************/
/*defining unordered_map*/
#include<unordered_map>

/******************************************************************************/
/*defining builtins_print*/

				var __python__print(var q=python_list(),var sep=python_str({' '}),var end=python_str({'\n'})){
					auto s=python_str();
					auto _end=cast(__python__str(end),python_str);
					auto _sep=cast(__python__str(sep),python_str);
					auto c=python_int(0);
					{python_iftype(q,python_list){}else{
						q=python_list({q});
					}}
					for (var w:python_iterate(q)){
						s+=(c?_sep:python_str())+cast(__python__str(w),python_str);
						c=c?c:1;
					}
					s+=_end;
					std::cout<<to_u8(s);
					return python_None;
				}
			

/******************************************************************************/
/*defining cmp*/

				python_int cmp(var q,var w){
											{python_iftype(q,python_int){auto qs=s;
							{python_iftype(w,python_int){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_int){auto qs=s;
							{python_iftype(w,python_bool){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_int){auto qs=s;
							{python_iftype(w,python_float){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_int){auto qs=s;
							{python_iftype(w,python_complex){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_bool){auto qs=s;
							{python_iftype(w,python_int){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_bool){auto qs=s;
							{python_iftype(w,python_bool){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_bool){auto qs=s;
							{python_iftype(w,python_float){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_bool){auto qs=s;
							{python_iftype(w,python_complex){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_float){auto qs=s;
							{python_iftype(w,python_int){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_float){auto qs=s;
							{python_iftype(w,python_bool){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_float){auto qs=s;
							{python_iftype(w,python_float){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_float){auto qs=s;
							{python_iftype(w,python_complex){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_complex){auto qs=s;
							{python_iftype(w,python_int){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_complex){auto qs=s;
							{python_iftype(w,python_bool){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_complex){auto qs=s;
							{python_iftype(w,python_float){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

						{python_iftype(q,python_complex){auto qs=s;
							{python_iftype(w,python_complex){auto ws=s;
								auto qa=cast(__python__complex(q),python_complex);
						auto wa=cast(__python__complex(w),python_complex);
						auto z=python_int(qa.real()<wa.real()?-1:(qa.real()>wa.real()?1:0));
						auto x=python_int(qa.imag()<wa.imag()?-1:(qa.imag()>wa.imag()?1:0));
						if (z){
							return z;
						}else{
							return x;
						}
							}}
						}}

					{python_iftype(q,python_int){
						{python_iftype(w,python_float){
						}}
					}}
					{python_iftype(w,python_int){
						{python_iftype(q,python_float){
							return cmp(q,(python_float)(cast(w,python_int)));
						}}
					}}
					if (q.type()!=w.type()){
						return cmp(std::string(q.type().name()),std::string(w.type().name()));
					}
					{python_iftype(w,python_complex){
						auto a=cast(q,decltype(s));
						return cmp(cmp(a.real(),s.real())*4+cmp(a.imag(),s.imag()),python_int(0));
					}}
					{python_iftype(w,python_NoneType){
						return python_int(0);
					}}
					{python_iftype(w,python_ellipsis){
						return python_int(0);
					}}
										{python_iftype(w,python_float){auto ws=s;
						auto qs=cast(q,decltype(ws));
						return python_int(qs<ws?-1:(qs>ws?1:0));
					}}

					{python_iftype(w,python_int){auto ws=s;
						auto qs=cast(q,decltype(ws));
						return python_int(qs<ws?-1:(qs>ws?1:0));
					}}

					{python_iftype(w,python_bool){auto ws=s;
						auto qs=cast(q,decltype(ws));
						return python_int(qs<ws?-1:(qs>ws?1:0));
					}}

					{python_iftype(w,python_bytearray){auto ws=s;
						auto qs=cast(q,decltype(ws));
						return python_int(qs<ws?-1:(qs>ws?1:0));
					}}

					{python_iftype(w,python_str){auto ws=s;
						auto qs=cast(q,decltype(ws));
						return python_int(qs<ws?-1:(qs>ws?1:0));
					}}

					{python_iftype(w,python_list){auto ws=s;
						auto qs=cast(q,decltype(ws));
						return python_int(qs<ws?-1:(qs>ws?1:0));
					}}

					{python_iftype(w,python_set){auto ws=s;
						auto qs=cast(q,decltype(ws));
						return python_int(qs<ws?-1:(qs>ws?1:0));
					}}

					{python_iftype(w,python_dict){auto ws=s;
						auto qs=cast(q,decltype(ws));
						return python_int(qs<ws?-1:(qs>ws?1:0));
					}}

					std::cout<<"failed to compare "<<q.type().name()<<" and "<<w.type().name()<<std::endl;
					fend(0)
				}

				bool var::operator<(const var o) const{
						var q=*this;
						var w=o;
						return cmp(q,w)<0;
					}
			

/******************************************************************************/
/*defining builtins_list*/

				var __python__list(var q=python_list()){
					auto s=python_list();
					for (var w:python_iterate(q)){
						s.push_back(w);
					}
					return s;
				}
			

/******************************************************************************/
/*defining builtins_dict*/

				var __python__dict(var q=python_dict()){
					auto s=python_dict();
					return s;
				}
			

/******************************************************************************/
/*defining builtins_type*/

				var __python__type(var q){
					return to_u32(filt(q.type().name()));
				}
			

/******************************************************************************/
/*defining levels*/

				#define python_level_type_first python_str
				#define python_level_type_second var
				#define convert_first_type to_u8
				std::vector<std::unordered_map<python_level_type_first,python_level_type_second*>> python_globals;
				std::vector<std::unordered_map<python_level_type_first,python_level_type_second>*> python_locals_pointers;
				#define python_global(q)\
				 	if (!python_globals[0].count(q)){\
						(*(python_locals_pointers[0]))[q]=int64_t(0);\
						python_globals[0][q]=&((*(python_locals_pointers[0]))[q]);\
					}\
					python_globals[python_globals.size()-1][q]=python_globals[0][q];

				#define python_nonlocal(q)\
				 	if (!python_globals[python_globals.size()-2].count(q)){\
						(*(python_locals_pointers[python_locals_pointers.size()-2]))[q]=int64_t(0);\
						python_globals[python_globals.size()-2][q]=&((*(python_locals_pointers[python_locals_pointers.size()-2]))[q]);\
					}\
					python_globals[python_globals.size()-1][q]=python_globals[python_globals.size()-2][q];
					
				#define python_level_get(...) python_level_get_with_line(__VA_ARGS__,__LINE__)

				python_level_type_second& python_level_get_with_line(python_level_type_first q,int64_t line){
					for (int64_t w=python_globals.size()-1;w>=0;--w){
						if (python_globals[w].count(q)){
							return *(python_globals[w][q]);
						}
					}
					std::cout<<std::string("line ")<<line<<std::string("\nname ")+convert_first_type(q)+std::string(" is undefined")<<std::endl;
					return *(python_globals[0][q]);
				}

				bool __python__isdefined(python_level_type_first q){
					for (auto w=python_globals.size()-1;w>=0;--w){
						if (python_globals[w].count(q)){
							return true;
						}
					}
					return false;
				}

				python_level_type_second& python_level_set(python_level_type_first q){
					if (!python_globals[python_globals.size()-1].count(q)) {
						(*(python_locals_pointers[python_locals_pointers.size()-1]))[q]=int64_t(0);
						python_globals[python_globals.size()-1][q]=&((*(python_locals_pointers[python_locals_pointers.size()-1]))[q]);
					}
					return *(python_globals[python_globals.size()-1][q]);
				}

				#define python_create_level()\
					python_globals.emplace_back();\
					std::unordered_map<python_level_type_first,python_level_type_second> python_locals;\
					python_locals_pointers.push_back(&python_locals);

				#define python_delete_level()\
					python_globals.pop_back();\
					python_locals_pointers.pop_back();
			

/******************************************************************************/
/*defining func_example*/

				var func_example(var args,var kwargs){fend()}
			

/******************************************************************************/
/*defining builtins_int*/

			var __python__int(var q=python_int(0),var w=python_int(0)){
				{python_iftype(w,python_int){	
				}else{
					w=__python__int(w);					
				}}
								{python_iftype(q,python_int){auto qs=s;
					return python_int(qs);
				}}

				{python_iftype(q,python_float){auto qs=s;
					return python_int(qs);
				}}

				{python_iftype(q,python_bool){auto qs=s;
					return python_int(qs);
				}}

				fend()
			}
			

////////////////////////////////////////////////////////////////////////////////
//before main code
/*float*/
var _1000000000000000001(var args, var kwargs){
	python_create_level()
	if(cast(kwargs,python_dict).count(std::u32string({120})/*x*/)){python_level_set(std::u32string({120})/*x*/)=cast(kwargs,python_dict)[std::u32string({120})/*x*/];}
	if(cast(args,python_list).size()>0){python_level_set(std::u32string({120})/*x*/)=cast(args,python_list)[0];}
	{var to_return=__python__float(python_level_get(std::u32string({120})/*x*/));
	python_delete_level()
	return to_return;}
	{var to_return=python_None;
	python_delete_level()
	return to_return;};
}
/*str*/
var _1000000000000000002(var args, var kwargs){
	python_create_level()
	if(cast(kwargs,python_dict).count(std::u32string({120})/*x*/)){python_level_set(std::u32string({120})/*x*/)=cast(kwargs,python_dict)[std::u32string({120})/*x*/];}
	if(cast(args,python_list).size()>0){python_level_set(std::u32string({120})/*x*/)=cast(args,python_list)[0];}
	{var to_return=__python__str(python_level_get(std::u32string({120})/*x*/));
	python_delete_level()
	return to_return;}
	{var to_return=python_None;
	python_delete_level()
	return to_return;};
}
/*complex*/
var _1000000000000000003;
var _1000000000000000004;
var _1000000000000000005(var args, var kwargs){
	python_create_level()
	python_level_set(std::u32string({120})/*x*/)=_1000000000000000003;
	python_level_set(std::u32string({121})/*y*/)=_1000000000000000004;
	if(cast(kwargs,python_dict).count(std::u32string({120})/*x*/)){python_level_set(std::u32string({120})/*x*/)=cast(kwargs,python_dict)[std::u32string({120})/*x*/];}
	if(cast(kwargs,python_dict).count(std::u32string({121})/*y*/)){python_level_set(std::u32string({121})/*y*/)=cast(kwargs,python_dict)[std::u32string({121})/*y*/];}
	if(cast(args,python_list).size()>0){python_level_set(std::u32string({120})/*x*/)=cast(args,python_list)[0];}
	if(cast(args,python_list).size()>1){python_level_set(std::u32string({121})/*y*/)=cast(args,python_list)[1];}
	{var to_return=__python__complex(python_level_get(std::u32string({120})/*x*/),python_level_get(std::u32string({121})/*y*/));
	python_delete_level()
	return to_return;}
	{var to_return=python_None;
	python_delete_level()
	return to_return;};
}
/*print*/
var _1000000000000000006;
var _1000000000000000007;
var _1000000000000000008(var args, var kwargs){
	python_create_level()
	python_level_set(std::u32string({115,101,112})/*sep*/)=_1000000000000000006;
	python_level_set(std::u32string({101,110,100})/*end*/)=_1000000000000000007;
	if(cast(kwargs,python_dict).count(std::u32string({115,101,112})/*sep*/)){python_level_set(std::u32string({115,101,112})/*sep*/)=cast(kwargs,python_dict)[std::u32string({115,101,112})/*sep*/];}
	if(cast(kwargs,python_dict).count(std::u32string({101,110,100})/*end*/)){python_level_set(std::u32string({101,110,100})/*end*/)=cast(kwargs,python_dict)[std::u32string({101,110,100})/*end*/];}
	python_level_set(std::u32string({113})/*q*/)=python_list();
	if(cast(args,python_list).size()>0){python_level_set(std::u32string({113})/*q*/)=python_list(cast(args,python_list).begin()+0,cast(args,python_list).end());}
	{var to_return=__python__print(python_level_get(std::u32string({113})/*q*/),python_level_get(std::u32string({115,101,112})/*sep*/),python_level_get(std::u32string({101,110,100})/*end*/));
	python_delete_level()
	return to_return;}
	{var to_return=python_None;
	python_delete_level()
	return to_return;};
}
/*list*/
var _1000000000000000009(var args, var kwargs){
	python_create_level()
	if(cast(kwargs,python_dict).count(std::u32string({120})/*x*/)){python_level_set(std::u32string({120})/*x*/)=cast(kwargs,python_dict)[std::u32string({120})/*x*/];}
	if(cast(args,python_list).size()>0){python_level_set(std::u32string({120})/*x*/)=cast(args,python_list)[0];}
	{var to_return=__python__list(python_level_get(std::u32string({120})/*x*/));
	python_delete_level()
	return to_return;}
	{var to_return=python_None;
	python_delete_level()
	return to_return;};
}
/*dict*/
var _1000000000000000010(var args, var kwargs){
	python_create_level()
	if(cast(kwargs,python_dict).count(std::u32string({120})/*x*/)){python_level_set(std::u32string({120})/*x*/)=cast(kwargs,python_dict)[std::u32string({120})/*x*/];}
	if(cast(args,python_list).size()>0){python_level_set(std::u32string({120})/*x*/)=cast(args,python_list)[0];}
	{var to_return=__python__dict(python_level_get(std::u32string({120})/*x*/));
	python_delete_level()
	return to_return;}
	{var to_return=python_None;
	python_delete_level()
	return to_return;};
}
/*type*/
var _1000000000000000011(var args, var kwargs){
	python_create_level()
	if(cast(kwargs,python_dict).count(std::u32string({120})/*x*/)){python_level_set(std::u32string({120})/*x*/)=cast(kwargs,python_dict)[std::u32string({120})/*x*/];}
	if(cast(args,python_list).size()>0){python_level_set(std::u32string({120})/*x*/)=cast(args,python_list)[0];}
	{var to_return=__python__type(python_level_get(std::u32string({120})/*x*/));
	python_delete_level()
	return to_return;}
	{var to_return=python_None;
	python_delete_level()
	return to_return;};
}
/*int*/
var _1000000000000000012(var args, var kwargs){
	python_create_level()
	if(cast(kwargs,python_dict).count(std::u32string({120})/*x*/)){python_level_set(std::u32string({120})/*x*/)=cast(kwargs,python_dict)[std::u32string({120})/*x*/];}
	if(cast(args,python_list).size()>0){python_level_set(std::u32string({120})/*x*/)=cast(args,python_list)[0];}
	{var to_return=__python__int(python_level_get(std::u32string({120})/*x*/));
	python_delete_level()
	return to_return;}
	{var to_return=python_None;
	python_delete_level()
	return to_return;};
}
////////////////////////////////////////////////////////////////////////////////
//main code
int main(int argc,char **argv){
python_create_level()

/******************************************************************************/
/*defining numeric*/



/******************************************************************************/
/*defining vector*/



/******************************************************************************/
/*defining string*/



/******************************************************************************/
/*defining stdc++*/



/******************************************************************************/
/*defining initializer_list*/



/******************************************************************************/
/*defining complex*/



/******************************************************************************/
/*defining map*/



/******************************************************************************/
/*defining set*/



/******************************************************************************/
/*defining filt*/



/******************************************************************************/
/*defining iostream*/



/******************************************************************************/
/*defining any*/



/******************************************************************************/
/*defining python_variable*/
python_level_set(std::u32string({69,108,108,105,112,115,105,115})/*Ellipsis*/)=python_Ellipsis;


/******************************************************************************/
/*defining unicode_convert*/



/******************************************************************************/
/*defining builtins_float*/
	python_level_set(std::u32string({102,108,111,97,116})/*float*/)=_1000000000000000001;




/******************************************************************************/
/*defining builtins_str*/
	python_level_set(std::u32string({115,116,114})/*str*/)=_1000000000000000002;




/******************************************************************************/
/*defining builtins_complex*/
_1000000000000000003=python_int(0);
_1000000000000000004=python_int(0);
	python_level_set(std::u32string({99,111,109,112,108,101,120})/*complex*/)=_1000000000000000005;




/******************************************************************************/
/*defining unordered_map*/



/******************************************************************************/
/*defining builtins_print*/
_1000000000000000006=std::u32string({32})/* */;
_1000000000000000007=std::u32string({10})/*
*/;
	python_level_set(std::u32string({112,114,105,110,116})/*print*/)=_1000000000000000008;




/******************************************************************************/
/*defining cmp*/



/******************************************************************************/
/*defining builtins_list*/
	python_level_set(std::u32string({108,105,115,116})/*list*/)=_1000000000000000009;




/******************************************************************************/
/*defining builtins_dict*/
	python_level_set(std::u32string({100,105,99,116})/*dict*/)=_1000000000000000010;




/******************************************************************************/
/*defining builtins_type*/
	python_level_set(std::u32string({116,121,112,101})/*type*/)=_1000000000000000011;




/******************************************************************************/
/*defining levels*/



/******************************************************************************/
/*defining func_example*/



/******************************************************************************/
/*defining builtins_int*/
	python_level_set(std::u32string({105,110,116})/*int*/)=_1000000000000000012;



////////////////////////////////////////////////////////////////////////////////
//main code
(*cast(python_level_get(std::u32string({112,114,105,110,116})/*print*/),decltype(&func_example)))(python_list({var((*cast(python_level_get(std::u32string({105,110,116})/*int*/),decltype(&func_example)))(python_list({var(python_int(1))}),python_dict({})))}),python_dict({}));

(*cast(python_level_get(std::u32string({116,121,112,101})/*type*/),decltype(&func_example)))(python_list({var(python_int(9))}),python_dict({}));

var f=bool(1);
var g=super_cast(f,int);
std::cout<<to_u8(cast(__python__type(f),python_str))<<std::endl;
std::cout<<to_u8(cast(__python__type(g),python_str))<<std::endl;


python_delete_level()}