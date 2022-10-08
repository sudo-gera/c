#include <bits/stdc++.h>
using namespace std;

void run1(int&&y){
	int r=y;
}

void run2(int&&y){
	run1(y);
}



int main(){
	int u=0;
	run2(std::move(u));
}








