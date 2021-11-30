#include "h"

ima{
	vector<bool> a(9);
	auto q=a.begin();
	while (q!=a.end()){
		*q=1;
		print(static_cast<bool&>(*q))
		++q;
	}
}