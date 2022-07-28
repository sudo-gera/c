#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <ctype.h>
struct num{
	char*b=nullptr;
	char*e=nullptr;
	num(){}
	num(char*d){
		e=d;
		--d;
		while(*d!='\n'){
			--d;
		}
		++d;
		b=d;
	}
};

bool operator<(num q,num e){
	auto z=q,x=e;
	while (q.b!=q.e and e.e!=e.b){
		if (q.b[0]!=e.b[0]){
			return q.b[0]<e.b[0];
		}
		q.b+=1;
		e.b+=1;
	}
	if (q.b==q.e and e.b==e.e){
		return false;
	}else
	if (q.b==q.e){
		q=x;
		q.e=q.b+(e.e-e.b);
		return q<e;
	}else
	if (e.b==e.e){
		e=z;
		e.e=e.b+(q.e-q.b);
		return q<e;
	}
	return false;
}


int main(){
	int c;
	auto data=new char[12345];
	auto ds=0;
	data[ds++]='\n';
	auto nums=new num[12345];
	auto ns=0;
	while ((c = fgetc(stdin)) != EOF) {
		data[ds++]=c;
		if (isspace(data[ds-1])){
			data[ds-1]='\n';
			if (data[ds-2]!='\n'){
				nums[ns++]=num(data+ds-1);
			}
		}
	}
	std::sort(nums,nums+ns);
	for (int w=0;w<ns;++w){
		for (auto e=nums[ns-1-w].b;e<nums[ns-1-w].e;++e){
			printf("%c",*e);
		}
	}
	printf("\n");
	delete[] data;
	delete[] nums;
}
