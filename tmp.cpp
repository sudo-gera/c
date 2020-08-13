#include "stdio.h"
struct range_iterator{
	long long int val,step;
	auto operator++(){
		val+=step;
	}
	auto operator++(int){
		val+=step;
	}
	auto operator!=(auto o){
		return o.val!=val;
	}
	auto operator*(){
		return val;
	}
};

struct range_class{
	long long int start,stop,step;
	auto begin(){
		range_iterator t;
		t.val=start;
		t.step=step;
		return t;
	}
	auto end(){
		range_iterator t;
		t.val=stop;
		t.step=step;
		return t;
	}
};

range_class range(long int start,long int stop,long int step){
	range_class t;
	t.start=start;
	t.stop=stop;
	t.step=step;
	return t;
}
range_class range(long int start,long int stop){
	range_class t;
	t.start=start;
	t.stop=stop;
	t.step=1;
	return t;
}
range_class range(long int stop){
	range_class t;
	t.start=0;
	t.stop=stop;
	t.step=1;
	return t;
}
int main(){
	for (auto w: range(10)){
		printf("%Li",w);
	}
}