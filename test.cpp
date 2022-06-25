#include "unordered_set.h"
using namespace std;

int main(){
	UnorderedSet<long> a(1);
	a.Insert(0);
	a.Insert(1);
	ic(a.Find(0))
	ic(a.Find(1))
	ic(a.Find(2))
	a.Erase(1);
	ic(a.Find(0))
	ic(a.Find(1))
	ic(a.Find(2))
}
