
/******************************************************************************/
/*defining string*/
#include<string>

/******************************************************************************/
/*defining Ellipsis*/

				class python_ellipsis{};
				python_ellipsis python_Ellipsis;
			

/******************************************************************************/
/*defining None*/

				class python_NoneType{};
				python_NoneType python_None;
			

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
					return exec(std::string("c++filt -t ")+q);
				}
			

/******************************************************************************/
/*defining vector*/
#include<vector>

/******************************************************************************/
/*defining iostream*/
#include<iostream>

/******************************************************************************/
/*defining any*/
#include<any>

/******************************************************************************/
/*defining python_variable*/


				#define python_complex				std::complex<double>
				#define python_float				double
				#define python_int					int64_t
				#define python_bool					bool
				#define python_bytearray			std::string
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
							{python_iftype(orig,python_list){
								iter=cast(orig,decltype(s)).begin();
							}}
							{python_iftype(orig,python_set){
								iter=cast(orig,decltype(s)).begin();
							}}
							{python_iftype(orig,python_dict){
								iter=cast(orig,decltype(s)).begin();
							}}
							{python_iftype(orig,python_str){
								iter=cast(orig,decltype(s)).begin();
							}}
							{python_iftype(orig,python_bytearray){
								iter=cast(orig,decltype(s)).begin();
							}}
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
							return python_int(0);
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
							return python_int(0);
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
					return python_int(0);
				}
			

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
/*defining unordered_map*/
#include<unordered_map>

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
					return python_int(0);
				}

				bool var::operator<(const var o) const{
						var q=*this;
						var w=o;
						return cmp(q,w)<0;
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
/*complex*/
var _1000000000000000002;
var _1000000000000000003;
var _1000000000000000004(var args, var kwargs){
	python_create_level()
	python_level_set(std::u32string({120})/*x*/)=_1000000000000000002;
	python_level_set(std::u32string({121})/*y*/)=_1000000000000000003;
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
////////////////////////////////////////////////////////////////////////////////
//main code
int main(int argc,char **argv){
python_create_level()

/******************************************************************************/
/*defining string*/



/******************************************************************************/
/*defining Ellipsis*/
python_level_set(std::u32string({69,108,108,105,112,115,105,115})/*Ellipsis*/)=python_Ellipsis;


/******************************************************************************/
/*defining None*/



/******************************************************************************/
/*defining complex*/



/******************************************************************************/
/*defining map*/



/******************************************************************************/
/*defining set*/



/******************************************************************************/
/*defining filt*/



/******************************************************************************/
/*defining vector*/



/******************************************************************************/
/*defining iostream*/



/******************************************************************************/
/*defining any*/



/******************************************************************************/
/*defining python_variable*/



/******************************************************************************/
/*defining builtins_float*/
	python_level_set(std::u32string({102,108,111,97,116})/*float*/)=_1000000000000000001;




/******************************************************************************/
/*defining unicode_convert*/



/******************************************************************************/
/*defining unordered_map*/



/******************************************************************************/
/*defining builtins_complex*/
_1000000000000000002=python_int(0);
_1000000000000000003=python_int(0);
	python_level_set(std::u32string({99,111,109,112,108,101,120})/*complex*/)=_1000000000000000004;




/******************************************************************************/
/*defining levels*/



/******************************************************************************/
/*defining cmp*/


////////////////////////////////////////////////////////////////////////////////
//main code
/*ListComp(
    elt=Name(id='w', ctx=Load()),
    generators=[
        comprehension(
            target=Name(id='w', ctx=Store()),
            iter=Name(id='a', ctx=Load()),
            ifs=[],
            is_async=0),
        comprehension(
            target=Name(id='w', ctx=Store()),
            iter=Name(id='a', ctx=Load()),
            ifs=[],
            is_async=0)])*/;

python_delete_level()}