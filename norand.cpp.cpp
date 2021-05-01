#include "/Users/gera/pony/pony.hpp"
using namespace std;
def2(random,a,b){
	return rand()%(b-a)+a;
}
def2(random1,a,b){
	return int(rand()*1.0*(b-a)/2147483648);
}


pony_run{
	srand(time(0));
	let m=int(2147483648);
	let c=m/3;
	let gc=0;
	let lc=0;
	for w in range(1000000) do{
		let s=random1(0,c*2);
		if s<c do{
			lc++;
		}else{
			gc++;
		}
	}
	let r=int(1);
	for w in range(18) do{
		r*=10;
	}
	for w in range(1) do{
		print(int(1.0*r*lc*1.0/gc))
		print(int(r))
		r*=10;
	}
}