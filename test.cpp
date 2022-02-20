#include <algorithm>

int main(){
	int*a=new int[9];
	for (int w=0;w<9;++w){
		a[w]=-w;
	}
	std::sort(a,a+9);
}
