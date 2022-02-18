#include <iostream>
#include <vector>
using namespace std;
struct way{
	size_t from=-1;
	size_t to=-1;
	size_t valt=-1;
	size_t valm=-1;
};

#define inf size_t(-1)
struct node{
	size_t num=-1;
	size_t closed=0;
	size_t waym=inf;
	size_t wayt=inf;
};
void check(bool q){
	if (not q){
		while (1){
			malloc(1024+q);
		}
	}
}
int main(){
	size_t n,m;
	cin>>n>>m;
	vector<vector<way>> v(n);
	vector<node> e(n);
	for (size_t q=0;q<n;++q){
		e[q].num=q;
		size_t b,e,t,m;
		cin>>b>>e>>t>>m;
		b--;
		e--;
		check(0<=b and b<=v.size());
		check(0<=e and e<=v.size());
		v[b].push_back({b,e,t,m});
		v[e].push_back({e,b,t,m});
	}
	size_t b=0;
	size_t r=size_t(-1);
	while (r-b>1){
		size_t need=(b+r)/2;
		for (size_t w=0;w<n;++w){
			e[w].closed=0;
			e[w].waym=inf;
			e[w].wayt=inf;
		}
		e[0].wayt=0;
		e[0].waym=inf;
		while (1){
			size_t minway=inf;
			size_t minww=inf;
			for (size_t w=0;w<n;++w){
				if (not e[w].closed and e[w].wayt<minway){
					minww=w;
					minway=e[w].wayt;
				}
			}
			if (minww==inf){
				break;
			}
			check(0<=minww and minww<v.size() and minww<e.size());
			for (auto& cv:v[minww]){
				auto&ee=e[cv.to];
				auto&be=e[minww];
				if (cv.valm>=need){
					if (be.wayt+cv.valt<ee.wayt){
						ee.wayt=be.wayt+cv.valt;
						ee.waym=be.waym<cv.valm?be.waym:cv.valm;
						check(ee.waym>=need);
					}
				}
			}
			e[minww].closed=1;
		}
		if (e[n-1].wayt>1440){
			r=need;
		}else{
			b=need;
		}
	}
	cout<<b<3'000'000?0:(b-3'000'000)/100<<endl;
}
