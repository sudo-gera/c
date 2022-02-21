#include "d"

namespace json_ns{
	auto skip(const std::string&q,const std::string&w,size_t h=0,size_t c=1){
		while (h<q.size()){
			bool b=0;
			for (const auto&e:w){
				if (q[h]==e){
					b=1;
					break;
				}
			}
			if (!b){
				return h;
			}
			++h;
			if (h==c){
				return h;
			}
		}
		return h;
	}
	auto skip_whitespace(const std::string&q,size_t h=0){
		return skip(q,std::string({9, 10, 13, 32}),h,0);
	}
	auto skip_const(const std::string&q,size_t h=0){
		return skip(q,"truefalsenull",h,0);
	}
	auto skip_number(const std::string&q,size_t h=0){
		return skip(q,"-1234567890.eE",h,0);
	}
	auto skip_string(const std::string&q,size_t h=0){
		auto _h=skip(q,"\"",h);
		if (_h==h){
			return h;
		}
		h=_h;
		_h++;
		while (skip(q,"\"",h)==h and _h!=h){
			_h=h;
			if (skip(q,"\\",h)!=h){
				h+=2;
				h=h>=q.size()?q.size():h;
			}else{
				h+=1;
				h=h>=q.size()?q.size():h;
			}
		}
		h=skip(q,"\"",h,0);
		return h;
	}
	size_t skip_array(const std::string&q,size_t h);
	size_t skip_object(const std::string&q,size_t h);
	auto skip_value(const std::string&q,size_t h=0){
		h=skip_whitespace(q,h);
		h=skip_string(q,h);
		h=skip_number(q,h);
		h=skip_object(q,h);
		h=skip_array(q,h);
		h=skip_const(q,h);
		h=skip_whitespace(q,h);
		return h;
	}
	size_t skip_array(const std::string&q,size_t h=0){
		auto _h=skip(q,"[",h);
		if (_h==h){
			return h;
		}
		h=_h;
		_h++;
		while (skip(q,"]",h,1)==h and h!=_h){
			_h=h;
			h=skip_value(q,h);
			h=skip(q,",",h);
		}
		h=skip(q,"]",h,1);
		return h;
	}
	size_t skip_object(const std::string&q,size_t h=0){
		auto _h=skip(q,"{",h);
		if (_h==h){
			return h;
		}
		h=_h;
		_h++;
		while (skip(q,"}",h)==h and h!=_h){
			_h=h;
			h=skip_value(q,h);
			h=skip(q,":",h);
			h=skip_value(q,h);
			h=skip(q,",",h);
		}
		h=skip(q,"}",h);
		return h;
	}
	enum{
		json_const,json_number,json_string,json_array,json_object
	};
	struct json;
	json loads(const std::string&q);
	struct json{
		int type=0;
		int const_val=0;
		// std::string number_val;
		long long int int_val=0;
		long double float_val=0;
		int int_mode=0;
		std::string string_val;
		std::vector<json> array_val;
		std::map<std::string,json> object_val;
		friend json loads(const std::string&q);
	private:
		json(const std::string&_q,std::stringstream&__f){
			std::string q=_q+__f.str();
			q=strip(q);
			if (skip(q,"ntf")){
				type=json_const;
				if (q[0]=='n'){
					const_val=2;
				}
				if (q[0]=='t'){
					const_val=1;
				}
				if (q[0]=='f'){
					const_val=0;
				}
			}else
			if (skip(q,"1234567890-")){
				type=json_number;
				// number_val=q;
				if (skip(q,"1234567890-",0,0)==q.size()){
					int_val=stoll(q);
					int_mode=1;
				}else{
					float_val=stold(q);
					int_mode=0;
				}
			}else
			if (skip(q,"\"")){
				type=json_string;
				auto h=skip(q,"\"");
				auto _h=h+1;
				while (skip(q,"\"",h)==h and _h!=h){
					_h=h;
					if (skip(q,"\\",h)!=h){
						h+=1;
						if (skip(q,"\"",h)!=h){
							string_val+="\"";
							h+=1;
						}else if (skip(q,"\\",h)!=h){
							string_val+="\\";
							h+=1;
						}else if (skip(q,"/",h)!=h){
							string_val+="/";
							h+=1;
						}else if (skip(q,"b",h)!=h){
							string_val+="\x08";
							h+=1;
						}else if (skip(q,"f",h)!=h){
							string_val+="\x0c";
							h+=1;
						}else if (skip(q,"n",h)!=h){
							string_val+="\n";
							h+=1;
						}else if (skip(q,"r",h)!=h){
							string_val+="\r";
							h+=1;
						}else if (skip(q,"t",h)!=h){
							string_val+="\t";
							h+=1;
						}else if (skip(q,"u",h)!=h and q.size()-h>4){
							char g[4];
							for (auto f=0;f<4;++f){
								g[f]=q[h+4-f];
								if ('0'<=g[f] and g[f]<='9'){
									g[f]-='0';
								}
								if ('a'<=g[f] and g[f]<='f'){
									g[f]-='a'+10;
								}
								if ('A'<=g[f] and g[f]<='F'){
									g[f]-='A'+10;
								}
							}
							string_val+=(*(uint32_t*)(g));
							h+=5;
						}
					}else{
						string_val+=q[h];
						h+=1;
						h=h>=q.size()?q.size():h;
					}
				}
			}else
			if (skip(q,"[")){
				type=json_array;
				auto h=skip(q,"[");
				auto _h=h+1;
				while (h<q.size()-1 and h!=_h){
					_h=h;
					h=skip_value(q,h);
					array_val.push_back(loads(std::string(q.begin()+_h,q.begin()+h)));
					h=skip(q,",",h);
					h=skip_whitespace(q,h);
				}
			}else
			if (skip(q,"{")){
				type=json_object;
				auto h=skip(q,"{");
				auto _h=h+1;
				while (h<q.size()-1 and h!=_h){
					_h=h;
					h=skip_value(q,h);
					auto k=loads(std::string(q.begin()+_h,q.begin()+h));
					h=skip(q,":",h);
					_h=h;
					h=skip_value(q,h);
					auto v=loads(std::string(q.begin()+_h,q.begin()+h));
					h=skip(q,",",h);
					h=skip_whitespace(q,h);
					object_val[k]=v;
				}
			}
		}
	public:
		auto dumps()const{
			if (type==json_const){
				string h[3]={"false","true","null"};
				return h[const_val];
			}
			if (type==json_number){
				// return number_val;
				if (int_mode){
					return to_string(int_val);
				}else{
					return to_string(float_val);
				}
			}
			if (type==json_string){
				auto res=std::string();
				res+='"';
				for (auto&w:string_val){
					if (w<8 or w==11 or 13<w and w<32 or w==127){
						res+="\\u00";
						res+='0'+w/16;
						if ('0'+10<=res.back()){
							res.back()-='0'+10;
							res.back()+='a';
						}
						res+='0'+w%16;
						if ('0'+10<=res.back()){
							res.back()-='0'+10;
							res.back()+='a';
						}
					}else if(w>=32 and w!=34 and w!=92 and w!=127){
						res+=w;
					}else if (w==8){
						res+="\\b";
					}else if (w==9){
						res+="\\t";
					}else if (w==10){
						res+="\\n";
					}else if (w==12){
						res+="\\f";
					}else if (w==13){
						res+="\\r";
					}else if (w==34){
						res+="\\\"";
					}else if (w==92){
						res+="\\\\";
					}else{
						res+="error";
					}
				}
				res+='"';
				return res;
			}
			if (type==json_array){
				auto res=std::string();
				int c=0;
				res+="[";
				for (auto&w:array_val){
					if (c){
						res+=", ";
					}else{
						c=1;
					}
					res+=w.dumps();
				}
				res+="]";
				return res;
			}
			if (type==json_object){
				auto res=std::string();
				int c=0;
				res+="{";
				for (auto&w:object_val){
					if (c){
						res+=", ";
					}else{
						c=1;
					}
					res+=json(w.first).dumps();
					res+=": ";
					res+=w.second.dumps();
				}
				res+="}";
				return res;
			}
			return std::string("error ")+to_string(type);
		}
		operator std::string(){
			if (type==json_string){
				return string_val;
			}else{
				return this->dumps();
			}
		}
		operator long long int(){
			if (int_mode){
				return int_val;
			}else{
				return float_val;
			}
		}
		operator long double(){
			if (int_mode){
				return int_val;
			}else{
				return float_val;
			}
		}
		template <typename T>
		operator std::vector<T>(){
			return std::vector<T>(array_val.begin(),array_val.end());
		}
		template <typename T>
		operator std::map<std::string,T>(){
			return std::map<std::string,T>(object_val.begin(),object_val.end());
		}
		template <typename I,typename T>
		operator std::map<I,T>(){
			std::map<I,T> res;
			for (auto&w:object_val){
				res[json(w.first)]=w.second;
			}
			return res;
		}
		json&operator[](uint64_t q){
			return array_val[q];
		}
		json&operator[](std::string q){
			return object_val[q];
		}
		void __init__(const long long int&q){
			type=json_number;
			int_mode=1;
			int_val=q;
		}
		void __init__(const long int&q){
			type=json_number;
			int_mode=1;
			int_val=q;
		}
		void __init__(const int&q){
			type=json_number;
			int_mode=1;
			int_val=q;
		}
		void __init__(const bool&q){
			type=json_const;
			const_val=q;
		}
		void __init__(){
			type=json_const;
			const_val=2;
		}
		void __init__(const long double&q){
			type=json_number;
			int_mode=0;
			float_val=q;
		}
		void __init__(const std::string&q){
			type=json_string;
			string_val=q;
		}
		void __init__(const char*q){
			type=json_string;
			string_val=q;
		}
		template<typename T>
		void __init__(const std::vector<T>&q){
			type=json_array;
			for (auto&w:q){
				array_val.push_back(w);
			}
		}
		template<typename I,typename T>
		void __init__(const std::map<I,T>&q){
			type=json_object;
			for (auto&w:q){
				object_val[to_string(w.first)]=w.second;
			}
		}
		template <typename...T>
		json(const T&...q){
			this->__init__(q...);
		}
		void clear(){
			type=json_const;
			const_val=2;
			int_val=0;
			float_val=0;
			int_mode=0;
			string_val.clear();
			array_val.clear();
			object_val.clear();
		}
		template <typename T>
		json&operator=(const T&q){
			this->clear();
			this->__init__(q);
			return *this;
		}
		friend auto&operator<<(std::ostream&q,const json&w){
			q<<w.dumps();
			return q;
		}
	};
	json loads(const std::string&q){
		std::stringstream d;
		return json(q,d);
	}
}

using json=json_ns::json;


int main(){
	print(json_ns::loads(" { \" 1 \" : 2 , \" 4 \" : [ 1 , true , 2 , false , 9 , \" \\\" \"] } "));
	// auto h=(json_ns::loads(" { \" 1 \" : 2 , \" 4 \" : [ 1 , true , 2 , false , 9 , \" \\\" \"] } "));
}

