#include <bits/stdc++.h>
using namespace std;

#define pline_ std::cout<<"\x1b[32m"<<__LINE__<<"\x1b[0m";
#define pline pline_ std::cout<<std::endl;

#define print(...) pline_;cout<<": ";print_f(__VA_ARGS__);cout<<endl;
template <typename t>
int print_ff(t a){cout<<a<<' ';return 1;}
template <typename...t>
void print_f(t...a){int s[]={1,print_ff(a)...};}


template <typename t>
class pq{
public:
	map<int,int> pi;
	set<pair<vector<int>,t>> c;
	void put(t o,int p){
		if(!pi.count(p)){
			pi[p]=0;
		}else{
			pi[p]+=1;
		}
		c.insert({{-p,pi[p]},o});
	}
	t get(){
		auto q=c.begin();
		c.erase(q);
		return q->second;
	}
	int size(){
		return c.size();
	}
};


int main(){
	auto q=pq<int>();
	q.put(1,1);
	q.put(2,3);
	q.put(3,1);
	q.put(4,2);
	q.put(1,1);
	while(q.size()){
		print(q.get());
	}
}