#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define print() cout<<__

decltype(0) main(){
	int n,Y,X;
	cin>>n>>Y>>X;
	vector<int> x,y1,y2;
	for (int w=0;w<n;++w){
		x.push_back(0);
		y1.push_back(0);
		y2.push_back(0);
		cin>>x[x.size()-1]>>y1[y1.size()-1]>>y2[y2.size()-1];
	}
	map<int,vector<int>> yb,ye;
	for(int q=0;q<Y+1;++q){
		yb[q]=vector<int>();
		ye[q]=vector<int>();
	}
	for (int w=0;w<n;++w){
		yb[y1[w]].push_back(w);
	}
	for (int w=0;w<n;++w){
		ye[y2[w]].push_back(w);
	}
	multiset<int> z({0,X});
	multiset<vector<int>> ds({{X,0,X}});
	for(int q=0;q<Y+1;++q){
		for(auto w:yb[q]){
			int e=x[w];
			if (!z.count(e)){
				z.insert(e);
				int pre=*(z.lower_bound(e)--);
				int nex=*(z.upper_bound(e));
				ds.insert(vector({e-pre,pre,e}));
				ds.insert(vector({nex-e,e,nex}));
				ds.erase(ds.lower_bound(vector({nex-pre,pre,nex})));
			}
			else{
				z.insert(e);
			}
		}
		cout<<(*(ds.end()--))[0]<<endl;


		for(auto w:ye[q]){
			int e=x[w];
			if (z.lower_bound(e)==--z.upper_bound(e)){
				int pre=*(z.lower_bound(e)--);
				int nex=*(z.upper_bound(e));
				ds.erase(ds.lower_bound(vector({e-pre,pre,e})));
				ds.erase(ds.lower_bound(vector({nex-e,e,nex})));
				ds.insert(vector({nex-pre,pre,nex}));
			}
			z.erase(z.find(w));
		}
	}
}