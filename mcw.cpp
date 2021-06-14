#include <bits/stdc++.h>
using namespace std;

auto lp=[](auto q){
	return q;
};
int main(){
	int n;
	cin>>n;
	vector<any> s;
	for (int w=0;w<n;w++){
		vector<string> d;
		d.push_back("");
		d.push_back("");
		d.push_back("");
		d.push_back("");
		cin>>d[0];
		cin>>d[1];
		cin>>d[2];
		cin>>d[3];
		d.push_back(to_string(w));
		if(d[2]=="50"){
			s.push_back(d);
		}
	}
	vector<string> asi;
	for(auto &w:s){
		vector<int> g;
		g.push_back(asi.size());
		asi.push_back(any_cast<vector<string>>(w)[0]);
		g.push_back(asi.size());
		asi.push_back(any_cast<vector<string>>(w)[1]);
		g.push_back(stol(any_cast<vector<string>>(w)[2]));
		g.push_back(stol(any_cast<vector<string>>(w)[3]));
		g.push_back(stol(any_cast<vector<string>>(w)[4]));
		w=g;
	}
	sort(s.begin(), s.end(),[](auto _a, auto _s){
		auto a=any_cast<vector<int>> (_a);
		auto s=any_cast<vector<int>> (_s);
		if (a[3]<s[3]){return 1;}if (a[3]>s[3]){return 0;}
		if (a[0]<s[0]){return 1;}if (a[0]>s[0]){return 0;}
		if (a[1]<s[1]){return 1;}if (a[1]>s[1]){return 0;}
		if (a[2]<s[2]){return 1;}if (a[2]>s[2]){return 0;}
		if (a[4]<s[4]){return 1;}if (a[4]>s[4]){return 0;}
		return 0;
	});
	vector <vector <int>> a;
	for(auto &w:s){
		a.push_back(any_cast<vector<int>>(w));
	}
	if (lp(a.size())==0){
		cout<<0<<endl;
	}
	else if (a.size()==1){
		cout<<asi[a[a.size()-1][0]]<<' '<<asi[a[a.size()-1][1]]<<endl;
	}
	else if (a.size()==2 and a[a.size()-1][4]<a[a.size()-2][4]){
		cout<<asi[a[a.size()-1][0]]<<' '<<asi[a[a.size()-1][1]]<<endl;
		cout<<asi[a[a.size()-2][0]]<<' '<<asi[a[a.size()-2][1]]<<endl;
	}
	else if (a.size()==2 and a[a.size()-1][4]>a[a.size()-2][4]){
		cout<<asi[a[a.size()-2][0]]<<' '<<asi[a[a.size()-2][1]]<<endl;
		cout<<asi[a[a.size()-1][0]]<<' '<<asi[a[a.size()-1][1]]<<endl;
	}
	else if (a[lp(a.size())-3][3]==a[-2][3] and a[-2][3]==a[a.size()-1][3]){
		int c=0;
		for (auto w:a){
			if (w[3]==a[a.size()-1][3]){
				c+=1;
			}
		}
		cout<<c<<endl;
	}
	else if (a[a.size()-3][3]==a[a.size()-2][3]){
		cout<<asi[a[a.size()-1][0]]<<' '<<asi[a[a.size()-1][1]]<<endl;
	}
	else if (a[a.size()-1][3]==a[a.size()-2][3] and a[a.size()-1][4]<a[a.size()-2][4]){
		cout<<asi[a[a.size()-1][0]]<<' '<<asi[a[a.size()-1][1]]<<endl;
		cout<<asi[a[a.size()-2][0]]<<' '<<asi[a[a.size()-2][1]]<<endl;
	}
	else if (a[a.size()-1][3]==a[a.size()-2][3] and a[a.size()-1][4]>a[a.size()-2][4]){
		cout<<asi[a[a.size()-2][0]]<<' '<<asi[a[a.size()-2][1]]<<endl;
		cout<<asi[a[a.size()-1][0]]<<' '<<asi[a[a.size()-1][1]]<<endl;
	}else{
		cout<<asi[a[a.size()-1][0]]<<' '<<asi[a[a.size()-1][1]]<<endl;
		cout<<asi[a[a.size()-2][0]]<<' '<<asi[a[a.size()-2][1]]<<endl;
	}
	cout<<"9999999999999"<<endl;
}