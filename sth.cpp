#include <bits/stdc++.h>
#define ff(w,q) for(auto w=0;w<q;++w)
#define fe(w,q) for(auto w:q)
#define append push_back
using namespace std;

string str(int q){return to_string(q);}
string str(string q){return q;}
template <typename t>
string str(vector<t> q){
	string res="(";
	int c=q.size();
	fe(w,q){
		res+=str(w)+(--c?", ":"");
	}
	res+=")";
	return res;
}
template <typename t1,typename t2>
string str(pair<t1,t2> q){
	return string("{"+str(q.first)+": "+str(q.second)+"}");
}

template <typename t1,typename t2>
string str(map<t1,t2> q){
	string res="(";
	int c=q.size();
	fe(w,q){
		res+=str(w)+(--c?", ":"");
	}
	res+=")";
	return res;
}


template <typename... t>
void print(t... a){
	int64_t y=sizeof...(t);
	int64_t printed[sizeof...(t)] = { (std::cout<<(str(a))<<((--y)?" ":""), 0)... };
	std::cout<<std::endl;
}
int main(){
	int n;
	cin>>n;
	vector<vector<int>> q;
	ff(w,n){
		int a,s;
		cin>>a>>s;
		q.append(vector<int>({a,s}));
	}
	vector<pair<vector<int>,vector<vector<int>>>> a;
	fe(w,q){
		fe(e,q){
			auto z=vector<int>({w[0]+e[0],w[1]+e[1],(w[0]-e[0])*(w[0]-e[0])+(w[1]-e[1])*(w[1]-e[1])});
			auto x=vector<decltype(w)>({w,e});
			a.append(pair<vector<int>,vector<vector<int>>>({z,x}));
		}
	}
	map<vector<int>,vector<vector<vector<int>>>> s;
	fe(w,a){
		s[w.first]=vector<vector<vector<int>>>();
	}
	fe(w,a){
		s[w.first].append(w.second);
	}
#define cp(axb,axe,ayb,aye,bxb,bxe,byb,bye) ((axe-axb)*(bye-byb)-(bxe-bxb)*(aye-ayb))
	vector<int> d;
	fe(q,s){
		fe(w,q.second){
			fe(e,q.second){
				d.append(abs(cp(w[0][0],e[0][0],w[0][1],e[0][1],w[0][0],e[1][0],w[0][1],e[1][1])));

			}
		}
	}
	sort(d.begin(), d.end());
	cout<<d[d.size()-1];
}