#define DBOOST_STACKTRACE_USE_ADDR2LINE
#include <boost/stacktrace.hpp>
#include <iostream>
using namespace std;

int _main(int argc,char**argv){
	std::cout << boost::stacktrace::stacktrace();
	if(argc){
		_main(argc-1,argv);
	}
	return 0;
}
int main(int argc,char**argv){
	_main(argc,argv);
}
