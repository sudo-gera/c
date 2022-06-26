#include "unordered_set.h"
using namespace std;

// struct a{
// 	using R=int;
// };

// using s=const a;

int main(){
	UnorderedSet<long> a(0);
	for (auto w:range(0,10,2)){
		a.Insert(w);
	}
	a.Rehash(5);
	ic(a.BucketCount())
	for (auto w:range(0,10)){
		if (a.Find(w)){
			ic(a.Bucket(w))
		}
	}

	// wstrtype<s::R>();

}
