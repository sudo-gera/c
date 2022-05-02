#include <bits/stdc++.h>
using namespace std;

struct digit{
	unsigned a;
	void print(){
		cout<<a<<endl;
	}
	void set(unsigned t){
		a=t;
	}
	void operator+=(unsigned h){
		a+=h%10;
		a%=10;
	}
	void operator-=(unsigned h){
		a+=10;
		a-=h%10;
		a%=10;
	}
	void operator*=(unsigned h){
		a*=h;
		a%=10;
	}
	void operator=(unsigned h){
		a=h;
		a%=10;
	}
	// digit operator+(digit j){
	// 	digit tmp=*this;
	// 	tmp+=j;
	// 	return tmp;
	// }
	// operator int(){
	// 	return a;
	// }
};

// void inc(int&r){
// 	r++;
// }


int main(){
	vector<int> y(9);
	y[0]=2;
	y[1]=3;
	// int*f=&y;

	int*p=&(y[0]);
	// cout<< y <<endl;
	++(p);
	// y++;
	// inc(y);
	cout<< *(p) <<endl;

	// digit g;
	// g=3;
	// g.print();
	// digit h=g+g;
	// g.print();
	// h.print();
}
