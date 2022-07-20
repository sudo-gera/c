#include <iostream>
#include <vector>
using namespace std;

int main(){
	vector<long> maxnums(5);
	long t;
	cin>>t;
	while(t){
		if (t%21==0){
			if (t>maxnums[3]){
				maxnums[4]=maxnums[3];
				maxnums[3]=t;
			}else{
				maxnums[4]=t;
			}
		}else
		if (t%7==0){
			maxnums[2]=max(maxnums[2],t);
		}else
		if (t%3==0){
			maxnums[1]=max(maxnums[1],t);
		}else{
			maxnums[0]=max(maxnums[0],t);
		}
		cin>>t;
	}
	long maxans=0;
	long ans1=0,ans2=0;
	if (maxnums[0]*maxnums[3]>maxans){
		maxans=maxnums[0]*maxnums[3];
		ans1=maxnums[0];
		ans2=maxnums[3];
	}
	if (maxnums[1]*maxnums[3]>maxans){
		maxans=maxnums[1]*maxnums[3];
		ans1=maxnums[1];
		ans2=maxnums[3];
	}
	if (maxnums[2]*maxnums[3]>maxans){
		maxans=maxnums[2]*maxnums[3];
		ans1=maxnums[3];
		ans2=maxnums[2];
	}
	if (maxnums[1]*maxnums[2]>maxans){
		maxans=maxnums[1]*maxnums[2];
		ans1=maxnums[1];
		ans2=maxnums[2];
	}
	if (maxnums[3]*maxnums[4]>maxans){
		maxans=maxnums[3]*maxnums[4];
		ans1=maxnums[3];
		ans2=maxnums[4];
	}
	cout<<ans1<<' '<<ans2<<endl;
}
