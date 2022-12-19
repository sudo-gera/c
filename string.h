#include <iostream>
#include <cstring>

class String{
	size_t size=0;
	size_t data_size=0;
	char*str=nullptr;
public:
	String(){
	}
	String(size_t n,char c){
		str=new char[n];
		std::memset(str,c,n);
		size=n;
		data_size=n;
	}
	String(char c){
		str=new char[1];
		str[0]=c;
		size=1;
		data_size=1;
	}
	String(const char*cstr){
		size_t n=strlen(cstr);
		str=new char[n];
		std::memcpy(str,cstr,n);
		size=n;
		data_size=n;
	}
	String(const String&orig){
		str=new char[orig.size];
		std::memcpy(str,orig.str,orig.size);
		size=orig.size;
		data_size=size;
	}
	String&operator=(const String&orig){
		if (orig.str==str){
			return *this;
		}
		if (str) delete[] str;
		str=new char[orig.size];
		std::memcpy(str,orig.str,orig.size);
		size=orig.size;
		data_size=size;
		return *this;
	}
	friend bool operator==(const String&q,const String&e){
		if (q.size!=e.size) return 0;
		return std::memcmp(q.str,e.str,e.size)==0;
	}
	char&operator[](const size_t&index){
		return str[index];
	}
	const char&operator[](const size_t&index)const{
		return str[index];
	}
	~String(){
		delete[] str;
	}
	size_t length()const{
		return size;
	}
	void push_back(char item){
		if (size==data_size){
			auto _s=new char[2*data_size+1];
			std::memcpy(_s,str,size);
			_s[size++]=item;
			delete[] str;
			str=_s;
			data_size=data_size*2+1;
		}else{
			str[size++]=item;
		}
	}
	char pop_back(){
		return str[--size];
	}
	char &front(){
		return str[0];
	}
	char &back(){
		return str[size-1];
	}
	const char &front()const{
		return str[0];
	}
	const char &back()const{
		return str[size-1];
	}
	String&operator+=(const String&e){
		if (size+e.size>data_size){
			data_size=size+(e.size>size?e.size:size);
			auto _s=new char[data_size];
			std::memcpy(_s,str,size);
			std::memcpy(_s+size,e.str,e.size);
			size+=e.size;
			delete[] str;
			str=_s;
		}else{
			std::memmove(str+size,e.str,e.size);
			size+=e.size;
		}
		return *this;
	}
	friend String operator+(const String&q,const String&e){
		String f=q;
		f+=e;
		return f;
	}
	size_t find(const String&o)const{
		for (size_t w=0;w<size-o.size;++w){
			if (memcmp(str+w,o.str,o.size)==0){
				return w;
			}
		}
		return size;
	}
	size_t rfind(const String&o)const{
		for (ssize_t w=size-o.size-1;w>-1;--w){
			if (memcmp(str+w,o.str,o.size)==0){
				return w;
			}
		}
		return size;
	}
	String substr(size_t start,size_t count)const{
		auto a=String(count,'0');
		memcpy(a.str,str+start,count);
		return a;
	}
	bool empty()const{
		return !size;
	}
	void clear(){
		size=0;
		data_size=0;
		delete[] str;
		str=nullptr;
	}
	friend std::ostream&operator<<(std::ostream&stream,const String&e){
		for (size_t w=0;w<e.size;++w){
			stream<<e.str[w];
		}
		return stream;
	}
	friend std::istream&operator>>(std::istream&stream,String&e){
		e.clear();
		do{
			char f;
			stream>>f;
			e.push_back(f);
		}while ( stream.peek()>-1 and !std::isspace(stream.peek()) );
		return stream;
	}
};


#include <type_traits>

namespace std{
	template<typename q,typename w>
	constexpr bool is_assignable_v=std::is_assignable<q,w>::value;
	template<typename q,typename w>
	constexpr bool is_same_v=std::is_same<q,w>::value;
};