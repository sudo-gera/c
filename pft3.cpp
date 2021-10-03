#include <bits/stdc++.h>
using namespace std;

int main(){
	string q;
	cin>>q;
	vector<char> opened;
	for (auto w:q){
		if (w=='['){
			opened.push_back(']');
		}else if (w=='('){
			opened.push_back(')');
		}else if (w=='{'){
			opened.push_back('}');
		}else if (w=='<'){
			opened.push_back('>');
		}else if (!opened.size()){
			cout<<"NO\n";
			return 0;
		}else if (w!=opened.back()){
			cout<<"NO\n";
			return 0;
		}
		opened.pop_back();
	}
	if (opened.size()){
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
}