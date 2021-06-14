
/******************************************************************************/
/*defining string*/
#include<string>

/******************************************************************************/
/*defining any*/
#include<any>

/******************************************************************************/
/*defining vector*/
#include<vector>

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
/*defining iftype*/

				#define python_iftype(a,type_) type_ s;if (a.type()==typeid(std::declval<type_>())){s=std::any_cast<type_>(a);}if (a.type()==typeid(std::declval<type_>()))
		

/******************************************************************************/
/*defining None*/

				class python_NoneType{};
				python_NoneType python_None;
			

/******************************************************************************/
/*defining builtins__wrapper*/

			

/******************************************************************************/
/*defining map*/
#include<map>

/******************************************************************************/
/*defining iostream*/
#include<iostream>

/******************************************************************************/
/*defining debug_str*/

				std::string python_debug_str(std::any a){
					std::string d="type not found";
					{python_iftype(a,int)d=s;}
					{python_iftype(a,std::string)d=s;}
					{python_iftype(a,std::u32string)d=to_u8(s);}
					{python_iftype(a,int)d=std::to_string(s);}
					{python_iftype(a,int64_t)d=std::to_string(s);}
					return d;
				}
		

/******************************************************************************/
/*defining bool*/

			std::any __python__bool(std::any a=python_None){
				{python_iftype(a,python_NoneType){
					return false;
				}
				}
				{python_iftype(a,int){
					return s!=0;
				}
				}
				{python_iftype(a,int64_t){
					return s!=0;
				}
				}
				{python_iftype(a,std::string){
					return s.size()!=0;
				}
				}
				{python_iftype(a,std::u32string){
					return s.size()!=0;
				}
				}
			}
			

/******************************************************************************/
/*defining levels*/

				#define python_level_type_first std::u32string
				#define python_level_type_second std::any
				std::vector<std::map<python_level_type_first,python_level_type_second*>> python_globals;
				#define python_global(q)\
				 	if (python_globals[python_globals.size()-1].find(q) == python_globals[python_globals.size()-1].end()){\
						python_locals[q]=0;\
						python_globals[python_globals.size()-1][q]=&(python_locals[q]);\
					}\
					python_globals[python_globals.size()-1][q]=python_globals[0][q];\
					
				#define python_nonlocal(q)\
				 	if (python_globals[python_globals.size()-1].find(q) == python_globals[python_globals.size()-1].end()){\
						python_locals[q]=0;\
						python_globals[python_globals.size()-1][q]=&(python_locals[q]);\
					}\
					python_globals[python_globals.size()-1][q]=python_globals[python_globals.size()-2][q];
					
				#define python_get(q) (*(python_globals[python_globals.size()-1][q]))

				#define python_set(q) python_set_(q,&python_locals)

				python_level_type_second& python_set_(python_level_type_first q,std::map<python_level_type_first,python_level_type_second> *python_locals_pointer){
					if (python_globals[python_globals.size()-1].find(q) == python_globals[python_globals.size()-1].end()){
						(*python_locals_pointer)[q]=0;
						python_globals[python_globals.size()-1][q]=&((*python_locals_pointer)[q]);
					}
					return *(python_globals[python_globals.size()-1][q]);
				}

				#define python_create_level()\
					python_globals.emplace_back();\
					std::map<python_level_type_first,python_level_type_second> python_locals;

				#define python_delete_level()\
					python_globals.pop_back();
			

////////////////////////////////////////////////////////////////////////////////
//main code
int main(int argc,char **argv){
python_create_level()

/******************************************************************************/
/*defining string*/



/******************************************************************************/
/*defining any*/



/******************************************************************************/
/*defining vector*/



/******************************************************************************/
/*defining unicode_convert*/



/******************************************************************************/
/*defining iftype*/



/******************************************************************************/
/*defining None*/



/******************************************************************************/
/*defining builtins__wrapper*/



/******************************************************************************/
/*defining map*/



/******************************************************************************/
/*defining iostream*/



/******************************************************************************/
/*defining debug_str*/



/******************************************************************************/
/*defining bool*/


/******************************************************************************/
/*defining levels*/



/******************************************************************************/
/*defining string*/


////////////////////////////////////////////////////////////////////////////////
//main code
python_set(std::u32string({113})/*q*/)=int64_t(1);
if(std::any_cast<bool>(__python__bool(python_get(std::u32string({113})/*q*/)))){
	std::cout<<python_debug_str(python_get(std::u32string({113})/*q*/))<<std::endl;
}else{
}
python_set(std::u32string({119})/*w*/)=int64_t(0);
if(std::any_cast<bool>(__python__bool(python_get(std::u32string({119})/*w*/)))){
	std::cout<<python_debug_str(python_get(std::u32string({119})/*w*/))<<std::endl;
}else{
}
python_delete_level()}