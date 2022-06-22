#include "vector.h"
using namespace std;

#define G 2

struct z{
	z(){
		ic()
	}
	#if G&1
	z(const z&o){
		ic()
	}
	#endif
	z(z&&o){
		ic()
	}
	#if G&1
	auto&operator=(const z&o){
		ic()
		return *this;
	}
	#endif
	auto&operator=(z&&o){
		ic()
		return *this;
	}
	~z(){
		ic()
	}
};

int main(){
	auto t=Vector<Vector<long>>();
	t.Reserve(9);
	ic(t.Capacity());
	ic((long unsigned int)0)

	// t.Resize(1,{});
	// auto y=Vector<z>();
// #if G&2
// 	const
// #endif
// 	auto e=z();
// 	y.PushBack(e);


}
