#include <iostream>
using namespace std;
char*a="12345";

void run(int t=0){
	cout<<a[t]<<endl;
	run(t+1);
}

int main(){
	run();
}