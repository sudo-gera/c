#define MERGE_(a,b)  a##b
#define LABEL_(a) MERGE_(unique_name_,a)
#define PRINT_LINE struct{int a=printf("%i\n",__LINE__);} LABEL_(__COUNTER__);

PRINT_LINE
auto run(){
	PRINT_LINE
}

	PRINT_LINE
int main(){
	PRINT_LINE
	PRINT_LINE
}

