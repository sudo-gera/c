#include <bits/stdc++.h>
using namespace std;

int main(){
	auto a=map<int,int>({{1,2},{3,4}});
	for(auto w:a){
		cout<<w.first<<' '<<w.second<<endl;
		// cout<<w<<' '<<w<<endl;
	}
}