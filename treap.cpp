#include <bits/stdc++.h>
using namespace std;

#include "treap.hpp"


signed main(){
	auto q=treap<string>({"1","2","3"});
	auto w=q;
	assert(q==w);
	assert(vector<string>(q)==vector<string>({"1","2","3"}));
	assert(q.pop_back()=="3");
	assert(vector<string>(q)==vector<string>({"1","2"}));
	assert(q.pop_front()=="1");
	assert(vector<string>(q)==vector<string>({"2"}));
	w.push_back("4");
	assert(vector<string>(w)==vector<string>({"1","2","3","4"}));
	w.push_front("0");
	assert(vector<string>(w)==vector<string>({"0","1","2","3","4"}));
	assert(w<q);
	assert(treap<char>(string("12"))>treap<char>(string("1")));
	w.insert(0,"-1");
	assert(vector<string>(w)==vector<string>({"-1","0","1","2","3","4"}));
	w.insert(w.size(),"6");
	assert(vector<string>(w)==vector<string>({"-1","0","1","2","3","4","6"}));
	w.insert(w.size()-1,"5");
	assert(vector<string>(w)==vector<string>({"-1","0","1","2","3","4","5","6"}));
	assert(vector<string>(w)==vector<string>({"-1","0","1","2","3","4","5","6"}));
	q.erase(0);
	assert(q.empty());
	swap(q,w);
	assert(w.empty());
	assert(vector<string>(q)==vector<string>({"-1","0","1","2","3","4","5","6"}));
	swap(q,w);
	q.insert(0,"1");
	q.insert(0,"0");
	q.insert(2,"2");
	swap(q,w);
	assert(vector<string>(q)==vector<string>({"-1","0","1","2","3","4","5","6"}));
	assert(vector<string>(w)==vector<string>({"0","1","2"}));
	// auto a=q.e;
	// while (a->z()){
	// 	a=a->z();
	// }
	// assert(find_index(a)==0);
	// while (a){
	// 	a=add(a,1);
	// }
	// pr(q.e);
	// for (auto w=q.begin();w!=q.end();++w){
	// 	ic(*w)
	// }
}
