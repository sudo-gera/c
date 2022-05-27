#include <iostream>
 
int fermat() {
	const int MAX = 10;
	int a=1,b=1,c=1;
	// Endless loop with no side effects is UB
	while (1) {
		a+=2;
		if (a==4){
			return 1;
		}
		// if (((a*a*a) == ((b*b*b)+(c*c*c)))) return 1;
		// a++;
		// if (a>MAX) { a=1; b++; }
		// if (b>MAX) { b=1; c++; }
		// if (c>MAX) { c=1;}
	}
	return 0;
}
 
int main() {
	if (fermat())
		std::cout << "Fermat's Last Theorem has been disproved.\n";
	else
		std::cout << "Fermat's Last Theorem has not been disproved.\n";
}
// int main(){
// 	for (int w=0;w<10;++w){
// 		std::cout<<1234567890*w<<std::endl;
// 	}
// }
