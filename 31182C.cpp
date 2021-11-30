#define CPP_R
#include "d"
#include "biginteger.h"
// std::string print_one(BigInteger&q){
// 	char b[99999];
// 	b[0]=0;
// 	sprintf(b+strlen(b),"\x1b[92m%s\x1b[0m",1==q.sign?"+":-1==q.sign?"-":1<q.sign?"++":-1>q.sign?"--":"0");
// 	int c=0;
// 	for (int t=q.size-1;t>-1;--t){
// 		if (c%2){
// 			sprintf(b+strlen(b),"\x1b[92m");
// 		}
// 		sprintf(b+strlen(b),"%0*x",8,q.vect[t]);
// 		if (c%2){
// 			sprintf(b+strlen(b),"\x1b[0m");
// 		}
// 		++c;
// 	}
// 	return std::string(b);
// }

// std::string print_one(const BigInteger&q){
// 	return print_one(const_cast<BigInteger&>(q));
// }

auto output_time(double r){
	return to_string(r);
}


using b=BigInteger;
using r=Rational;

int main(){
// #include "stdout.cpp"
	// print(BigInteger("11111111111111111111",10)/BigInteger("9",10))

auto q=BigInteger("ffffffffffffffff",16);
print(q.toString(16));
q+=q;
print(q.toString(16));
}