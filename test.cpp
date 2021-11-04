#include "h"
µ{
	try{
		let a=vector<int>(2000000000);
		for (let w:range(100)){
			a.resize(a.size()+400000000);
			write(a.size());
			for (let e:range(w)){
				write("#");
			}
			for (let e:range(100-w)){
				write("-");
			}
			write("\r");
			cout<<flush;
		}
		for (let e:range(104)){
			write(" ");
		}
		write("\n");
		print(a.size())
	}catch(const exception &a){
		print(a.what())
	}
}
