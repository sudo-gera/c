#include "header.hpp"



struct q{
	char a[0];
};

struct w{
};


int main(){
	std::cout<<"sizeof char[0] (q) "<<sizeof(q)<<std::endl;
	std::cout<<"sizeof empty   (w) "<<sizeof(w)<<std::endl;
}

