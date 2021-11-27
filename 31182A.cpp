#include <iostream>
// #include "d"

auto get_product(int q,int* s,int argc,int**h,int*args){
	int64_t res=0;
	if (q==argc){
		res=1;
		for (int w=0;w<q;++w){
			res*=h[w][s[w]];
		}
		return res;
	}
	for (int w=0;w<args[q];++w){
		int b=0;
		for (int e=0;e<q;++e){
			if (s[e]==w){
				b=1;
				break;
			}
		}
		if (b){
			continue;
		}
		s[q]=w;
		res+=get_product(q+1,s,argc,h,args);
	}
	return res;
}


int main(int argc,char**argv){
	auto args=new int[argc-1];
	--args;
	for (int w=1;w<argc;++w){
		args[w]=0;
		while(argv[w][0]){
			args[w]=args[w]*10+argv[w][0]-'0';
			argv[w]++;
		}
	}
	++args;
	--argc;
	auto h=new int*[argc];
	for (int w=0;w<argc;++w){
		h[w]=new int[args[w]];
		for (int e=0;e<args[w];++e){
			std::cin>>h[w][e];
		}
	}
	auto s=new int[argc];
	auto f=get_product(0,s,argc,h,args);
	std::cout<<f<<std::endl;
	delete[] args;
	delete[] s;
	for (int w=0;w<argc;++w){
		delete[] h[w];
	}
	delete[] h;
}

