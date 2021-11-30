#include <stdio.h>

int main(){
	auto a=new char[102400];
	auto s=new char[102400];
	scanf("%s",a);
	size_t w=0;
	for (size_t q=0;a[q];++q){
		switch(a[q]){
			case '<':
				s[w++]='>';
				break;
			case '{':
				s[w++]='}';
				break;
			case '[':
				s[w++]=']';
				break;
			case '(':
				s[w++]=')';
				break;
			case '>':
				if (!w or s[--w]!='>'){
					printf("NO");
					return 0;
				}
				break;
			case '}':
				if (!w or s[--w]!='}'){
					printf("NO");
					return 0;
				}
				break;
			case ']':
				if (!w or s[--w]!=']'){
					printf("NO");
					return 0;
				}
				break;
			case ')':
				if (!w or s[--w]!=')'){
					printf("NO");
					return 0;
				}
				break;
		}
	}
	if (w){
		printf("NO");
	}else{
		printf("YES");
	}
}