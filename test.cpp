#include <stdio.h>

template<int q>
struct sized_data{char e[q];};


template<typename T>
char return_char(const T&q){
	return '0';
}

template<typename...T>
auto count_args_as_data(const T&...a){
	char t[]={return_char(a)...};
	sized_data<sizeof(t)> f;
	return f;
}

#define count_args(...) sizeof(count_args_as_data(__VA_ARGS__))

int main(){
	printf("%i\n",count_args(1,2L,3U,"4",'5'));
}

