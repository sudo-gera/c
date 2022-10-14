#include <bits/stdc++.h>
using namespace std;

void run(int*y){
	if (rand()%8<2){
		run(y);
	}
	if (rand()%8<2){
		run(y);
	}
	cout<<y[20];
}


int main(){
	int*y=new int[20];
	run(y);
}








