#include "/Users/gera/pony/pony.hpp"
using namespace std;
pony_run{
	let a=str("qweйцу");
	let d=vect(a[0],a[1],a[2],a[3],a[4],a[5]);
	let f=vect(ord(a[0]),ord(a[1]),ord(a[2]),ord(a[3]),ord(a[4]),ord(a[5]));
	print(d);
	print(f);
}