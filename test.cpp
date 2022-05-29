#include <iostream>
 
py_func(f,{
def f(s):
	return s[::-1]
})


int main(){
	vector<long> a({1,2,3});
	a=vector<long>(f(a));
	ic(a)
}
