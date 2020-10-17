#include <bits/stdc++.h>

struct dot{
	long double x,y;
	dot(){
		x=0;
		y=0;
	}
	dot(long double _x,long double _y){
		x=_x;
		y=_y;
	}
	~dot(){
		//pass
	}
	long double d(dot s){
		return sqrt((x-s.x)*(x-s.x)+(y-s.y)*(y-s.y));
	}
};

int main(){
	dot a;
	dot b(1,1);
	std::cout<<(a.d(b));
}