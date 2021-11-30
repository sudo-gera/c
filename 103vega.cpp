#include <stdio.h>
#include <stdint.h>

int main(){
	auto a=new int[203040];
	auto s=new int[203040];
	int64_t ab=101010,ae=101010,sb=101010,se=101010;
	size_t n;
	scanf("%zu",&n);
	for (size_t w=0;w<n;++w){
		char c;
		int n;
		scanf(" %c",&c);
		switch(c){
			case '+':
				scanf("%i",&n);
				s[se]=n;
				se+=1;
				break;
			case '*':
				scanf("%i",&n);
				while(ae-ab>se-sb){
					sb-=1;
					ae-=1;
					s[sb]=a[ae];
				}
				while(ae-ab<se-sb){
					a[ae]=s[sb];
					sb+=1;
					ae+=1;
				}
				a[ae++]=n;
				break;
			case '-':
				if(ae!=ab){
					printf("%i\n",a[ab]);
					ab+=1;
				}else{
					printf("%i\n",s[sb]);
					sb+=1;
				}
				break;
		}
	}
}