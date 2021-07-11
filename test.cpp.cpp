#include "/Users/gera/pony/pony.hpp"
using namespace std;
class a{
public:
	int g;
	a(){
		g=rand();
		print('c',g);
	}
	~a(){
		print('d',g);
	}
};

pony_run{
	print(1);
	let d=a();
	print(2);
	let f=a();
	print(3);
}