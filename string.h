#include <iostream>
#include <cstring>

#pragma message("inlcuded")



class String{
public:
	String(){
		if (ds){
			str=data[--ds];
		}else{
			str=new char[1073741824];
		}
		d=1073741824;
		s=0;
	}
	String(size_t n,char c){
		if (n>1073741824){
			str=new char[n];
			for (size_t g=0;g<n;++g){
				str[g]=c;
			}
			s=n;
			d=n;
		}else{
			if (ds){
				str=data[--ds];
			}else{
				str=new char[1073741824];
			}
			for (size_t g=0;g<n;++g){
				str[g]=c;
			}
			s=n;
			d=1073741824;
		}
	}
	String(char c){
		if (ds){
			str=data[--ds];
		}else{
			str=new char[1073741824];
		}
		str[0]=c;
		d=1073741824;
		s=1;
	}
	String(const char*a){
		size_t n=strlen(a);
		if (n>1073741824){
			str=new char[n];
			for (size_t g=0;g<n;++g){
				str[g]=a[g];
			}
			s=n;
			d=n;
		}else{
			if (ds){
				str=data[--ds];
			}else{
				str=new char[1073741824];
			}
			for (size_t g=0;g<n;++g){
				str[g]=a[g];
			}
			s=n;
			d=1073741824;
		}
	}
	String(const String&o){
		if (o.s>1073741824){
			str=new char[o.s];
			for (size_t g=0;g<o.s;++g){
				str[g]=o.str[g];
			}
			s=o.s;
			d=s;
		}else{
			if (ds){
				str=data[--ds];
			}else{
				str=new char[1073741824];
			}
			for (size_t g=0;g<o.s;++g){
				str[g]=o.str[g];
			}
			s=o.s;
			d=1073741824;
		}
	}
	String&operator=(const String&o){
		if (d==1073741824){
			data[ds++]=str;
		}else{
			delete[] str;
		}
		str=new char[o.s>1073741824?o.s:1073741824];
		for (size_t g=0;g<o.s;++g){
			str[g]=o.str[g];
		}
		s=o.s;
		d=s>1073741824?s:1073741824;
		return *this;
	}
	friend bool operator==(const String&t,const String&o){
		if (t.s!=o.s) return 0;
		for (size_t g=0;g<t.s;++g){
			if (t.str[g]!=o.str[g]){
				return 0;
			};
		}
		return 1;
	}
	char&operator[](const int64_t&p){
		return str[(p%s+s)%s];
	}
	const char&operator[](const int64_t&p)const{
		return str[(p%s+s)%s];
	}
	~String(){
		if (d==1073741824){
			data[ds++]=str;
		}else{
			delete[] str;
		}
	}
	size_t length()const{
		return s;
	}
	void push_back(const char&g){
		if (s==d){
			auto _s=new char[2*d+1];
			for (size_t g=0;g<s;++g){
				_s[g]=str[g];
			}
			_s[s++]=g;
			if (d==1073741824){
				data[ds++]=str;
			}else{
				delete[] str;
			}
			str=_s;
			d*=2;
		}else{
			str[s++]=g;
		}
	}
	char pop_back(){
		return str[--s];
	}
	char &front(){
		return str[0];
	}
	char &back(){
		return str[s-1];
	}
	const char &front()const{
		return str[0];
	}
	const char &back()const{
		return str[s-1];
	}
	String&operator+=(const String&o){
		if (s+o.s>d){
			auto _s=new char[s+o.s];
			for (size_t g=0;g<s;++g){
				_s[g]=str[g];
			}
			for (size_t g=0;g<o.s;++g){
				_s[s+g]=o.str[g];
			}
			s+=o.s;
			if (d==1073741824){
				data[ds++]=str;
			}else{
				delete[] str;
			}
			str=_s;
			d=s;
		}else{
			for (size_t g=0;g<o.s;++g){
				str[s+g]=o.str[g];
			}
			s+=o.s;
		}
		return *this;
	}
	friend String operator+(const String&t,const String&o){
		String f=t;
		f+=o;
		return f;
	}	
	size_t find(const String&o)const{
		for (size_t w=0;w<s-o.s;++w){
			bool f=1;
			for (size_t e=0;e<o.s;++e){
				f&=(str[w+e]==o.str[e]);
			}
			if (f) return w;
		}
		return s;
	}
	size_t rfind(const String&o)const{
		for (ssize_t w=s-o.s-1;w>-1;--w){
			bool f=1;
			for (size_t e=0;e<o.s;++e){
				f&=(str[w+e]==o.str[e]);
			}
			if (f) return w;
		}
		return s;
	}
	String substr(size_t start,size_t count)const{
		auto a=String(count,'0');
		for (size_t d=start;d<start+count;++d){
			a.str[d]=str[start+d];
		}
		return a;
	}
	bool empty()const{
		return !s;
	}
	void clear(){
		s=0;
		d=0;
		delete[] str;
		str=nullptr;
	}
	friend auto&operator>>(std::istream&c,String&t){
		while (!std::isspace(c.peek())){
			char f;
			c>>f;
			t.push_back(f);
		}
		return c;
	}
	friend auto&operator<<(std::ostream&c,const String&t){
		for (size_t w=0;w<t.s;++w){
			c<<t.str[w];
		}
		return c;
	}
private:
	size_t s=0;
	size_t d=0;
	char*str=nullptr;
	static char** data;
	static size_t ds;
};

char** String::data=new char*[1073741824];
size_t String::ds=0;