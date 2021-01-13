#include <bits/stdc++.h>
using namespace std;
#define vect(type,n) (type*)calloc(sizeof(type),n)
auto knt(int n,int m,int* a,int* z){
	int n,m,w,h,j;
	auto s=vect(int*,m+1);
	auto d=vect(int*,m+1);
	for (j=0;j<m+1;j++){
		s[j]=vect(int,n+1);
		d[j]=vect(int,n+1);
	}
	for (h=0;h<n+1;h++){
		for (j=0;j<m+1;j++){
			if (h==0){
				s[j][h]=0;
				d[j][h]=0;
			}else{
				s[j][h]=s[j][h-1];
				d[j][h]=d[j][h-1];
				if (j>=a[h-1]){
					if (s[j][h]<s[j-a[h-1]][h-1]+z[h-1]){
						d[j][h]=d[j-a[h-1]][h-1]+1;
						s[j][h]=s[j-a[h-1]][h-1]+z[h-1];
					}else if (s[j][h]==s[j-a[h-1]][h-1]+z[h-1]){
						if (d[j][h]>d[j-a[h-1]][h-1]+z[h-1]){
							d[j][h]=d[j-a[h-1]][h-1]+1;
						}
					}
				}
			}
		}
	}
	return s;	
}
int main(){
	int s;
	cin>>s;
	int n;
	cin>>n;
	auto p=vect(int,n);
	int w,t;
	for (w=0;w<n;w++){
		cin>>p[w];
	}
	int m;
	cin>>m;
	auto q=vect(int,m);
	for (w=0;w<m;w++){
		cin>>q[w];
	}
	set <int> l;
	set <int> a;
	l.insert(0);
	for (t=0;t<n;t++){
		for (w : l){
			l.insert(w+p[t]);
		}
	}
	a.insert(s);
	for (t=0;t<m;t++){
		for (w : a){
			a.insert(w+q[t]);
		}
	}
	vector<int> i;
	set_intersection(l.begin(),l.end(),a.begin(),a.end(),back_inserter(i));
	if (i.size()==0){
		cout<<'Impossible'<<endl;
		return 0;
	}
	int v=i[0];
	int **g=knt(n,v,p,p);
	int **h=knt(m,v-s,q,q);
	
}