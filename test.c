#include <stdio.h>

struct{}__cpp__;
const int is_cpp=sizeof(__cpp__);


int main(){
	if (is_cpp){
		printf("it is c++\n");
	}else{
		printf("it is c\n");
	}
}

