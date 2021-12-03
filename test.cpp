#include "h"


class test1{
public:
	int g=123;
	// virtual int get();
};

class test2:test1{
public:
	int get(){
		return g;
	}
};


signed main(){
	ic(test2().get())
}