#include <iostream>

auto get_product(int stack_pos,int* stack,int arg_count,int**arrays,int*args){
	int64_t res=0;
	if (stack_pos==arg_count){
		res=1;
		for (int w=0;w<stack_pos;++w){
			res*=arrays[w][stack[w]];
		}
		return res;
	}
	for (int w=0;w<args[stack_pos];++w){
		int breaked=0;
		for (int e=0;e<stack_pos;++e){
			if (stack[e]==w){
				breaked=1;
				break;
			}
		}
		if (breaked){
			continue;
		}
		stack[stack_pos]=w;
		res+=get_product(stack_pos+1,stack,arg_count,arrays,args);
	}
	return res;
}


int main(int arg_count,char**args_strings){
	auto args=new int[arg_count-1];
	--args;
	for (int w=1;w<arg_count;++w){
		args[w]=0;
		while(args_strings[w][0]){
			args[w]=args[w]*10+args_strings[w][0]-'0';
			args_strings[w]++;
		}
	}
	++args;
	--arg_count;
	auto arrays=new int*[arg_count];
	for (int w=0;w<arg_count;++w){
		arrays[w]=new int[args[w]];
		for (int e=0;e<args[w];++e){
			std::cin>>arrays[w][e];
		}
	}
	auto stack=new int[arg_count];
	auto res=get_product(0,stack,arg_count,arrays,args);
	std::cout<<res<<std::endl;
	delete[] args;
	delete[] stack;
	for (int w=0;w<arg_count;++w){
		delete[] arrays[w];
	}
	delete[] arrays;
}

