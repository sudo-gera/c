#include <iostream>
#include <vector>
using namespace std;

int main(){
	int c;
	long maxlen=0;
	long currstart=-1;
	long w=0;
	for(c=cin.get(); 'A'<=c and c<='Z';  ++w,c=cin.get()){
		if (c=='W' and currstart==-1){
			currstart=w;
		}else
		if (c!='W' and currstart!=-1){
			maxlen=max(maxlen,w-currstart);
			currstart=-1;
		}
	}
	if (currstart!=-1){
			maxlen=max(maxlen,w-currstart);
	}
	cout<<maxlen<<endl;
}
