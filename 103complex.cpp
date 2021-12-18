#include <iostream>
#include <math.h>

struct C{
	double re=0,im=0;
	C(){}
	C(double r){
		re=r;
	}
	C(double r,double i){
		re=r;
		im=i;
	}
	C(const C& o){
		im=o.im;
		re=o.re;
	}
	friend auto operator+(const C&q,const C&w){
		return C(q.re+w.re,q.im+w.im);
	}
	friend auto operator-(const C&q,const C&w){
		return C(q.re-w.re,q.im-w.im);
	}
	friend auto operator*(const C&q,const C&w){
		return C(q.re*w.re-q.im*w.im,q.re*w.im+q.im*w.re);
	}
	friend auto operator/(const C&q,const C&w){
		return C((q.re*w.re+q.im*w.im)/(w.re*w.re+w.im*w.im),(-q.re*w.im+q.im*w.re)/(w.re*w.re+w.im*w.im));
	}
	friend auto operator==(const C&q,const C&w){
		return q.re==w.re and q.im==w.im;
	}
	friend auto operator!=(const C&q,const C&w){
		return q.re!=w.re or q.im!=w.im;
	}
	friend auto& operator<<( std::ostream &c,const C& q){
		c<<q.re<<' '<<q.im;
		return c;
	}
	double abs(){
		return sqrt(re*re+im*im);
	}
};

#if __has_include("h")
#include "h"

int main(){

	auto q=C(1,2);
	auto w=C(3,4);
	print(q/w);
}

#endif