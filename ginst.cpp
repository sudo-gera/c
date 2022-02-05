#include <stdlib.h>
#include <string>
#include <filesystem>

auto subl="/mnt/c/Program Files/Sublime Text 3/sublime_text.exe";
auto wsubl="C:/Program Files/Sublime Text 3/sublime_text.exe";

std::string popen(std::string q){
	std::string s;
	auto pipe=popen(q.c_str(), "r");
	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(pipe)) != EOF) { // standard C I/O file reading loop
		s+=c;
	}
	pclose(pipe);
	// print(s);
	return s;
}

std::string replace(std::string q,std::string w,std::string e){
	std::string res;
	uint64_t a=0;
	while (a<uint64_t(len(q))){
		if (q.find(w,a)==a){
			res+=e;
			a+=w.size();
		}else{
			res+=q[a];
			++a;
		}
	}
	return res;
}

std::string python(std::string q){
	q=replace(q,"\\","\\\\");
	q=replace(q,"\"","\\\"");
	q=replace(q,"`","\\`");
	q=replace(q,"$","\\$");
	return popen("wsl python3 -c \""+q+"\"");
}

struct pyfunc_s{
	std::string f;
	std::string q;
	auto&operator=(const std::string&q){
		f="def pyfunc("+f+"):\n"+q;
		return *this;
	}
	pyfunc_s(std::string _f):f(_f){}
	template <typename...T>
	auto operator()(const T&...a){
		q="from json import *\nprint(dumps(pyfunc(";
		std::vector<int>({add(a)...});
		q+=")))";
		return loads(python(f+"\n\n"+q+"\n\n"));
	}
	pyfunc_s(size_t line,std::string file,std::string _f):f(_f){
		auto h=pyfunc_s("line,file")=
		"	a=open(file).read().splitlines()[line:]\n"
		"	a.append('')\n"
		"	a=a[:a.index([w for w in a if not w.strip().startswith('//')][0])]\n"
		"	a=[w.replace('//','  ',1) for w in a]\n"
		"	a='\\n'.join(a)+'\\n'\n"
		"	return a";
		f="def pyfunc("+f+"):\n"+std::string(h(line,file));
	}
	template<typename T>
	int add(const T&w){
		q+="loads("+dumps(dumps(w))+"),";
		return 0;
	}
};

#define pyfunc(...) pyfunc_s(__LINE__,__FILE__,#__VA_ARGS__);

auto install=pyfunc(file,subl,wsubl)
	// #!/usr/bin/python3
	// from sys import argv
	// from subprocess import run
	// from urllib.request import urlopen
	// import os
	// if not os.geteuid() == 0:
	// 	from pathlib import Path
	// 	open(str(Path.home())+'/g','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/g.py').read())
	// 	run(['chmod','777',str(Path.home())+'/g'])
	// 	open(str(Path.home())+'/v','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/v.py').read())
	// 	run(['chmod','777',str(Path.home())+'/v'])
	// 	open(str(Path.home())+'/b','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/b.py').read())
	// 	run(['chmod','777',str(Path.home())+'/b'])

	// 	run(['sudo','python3',__file__])

	// 	while file[-1] not in '\\/':
	// 		file=file[:-1]
	// 	run([wsubl,file])
	// 	exit()
	// else:
	// 	open('/usr/bin/wind','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/wind/master/wind.py').read())
	// 	run(['chmod','777','/usr/bin/wind'])
	// 	open('/usr/bin/subl','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/subl').read().replace('/mnt/c/Program Files/Sublime Text/subl.exe',subl))
	// 	run(['chmod','777','/usr/bin/subl'])



int main(){	
	install(std::filesystem::absolute(__FILE__),subl,wsubl)
}
