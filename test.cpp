#include "vector.h"
using namespace std;
int main(){
	auto t=Vector();
	auto y=vector();
	while (1){
		auto q=rand()%2;
		auto e=rand()%9;
		if (q==0){
			t.Clear();
			y.clear();
		}
		if (q==1){
			t.PushBack(e);
			y.push_back(e);
		}
		if (q==2){
			t.PopBack();
			y.Pop_back();
		}
		if (q==3){
			assert(t.Size()==y.size());
			assert(t.Front()==y.front());
			assert(t.Back()==y.back());
		}
		auto a=t.begin();
		auto s=y.begin();
		for (;a!=t.end() and s!=y.end();++a,++s){
			assert(*a==*s);
		}
		assert(a==t.end() and s==y.end());
	}
}
