<<<<<<< HEAD
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
=======
struct s{
    int a[0];
    int s[1];
};


static_assert(sizeof(s)==4);

int main(){
    
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
}
