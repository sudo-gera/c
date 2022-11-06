#include <unistd.h>
#include <fcntl.h>

char* getchar_p=0;

static inline int getint() {
	int sign = 1;
	int c;
	unsigned res = 0;
	c = (getchar_p++[0]);
	if (c == '-') {
		sign = -1;
	} else {
		res = c - '0';
	}
	while (c = (getchar_p++[0]), ('0'<=c && c<='9')) {
		res *= 10;
		res += c - '0';
	}
	return (int)(res)*sign;
}

char data[4096];

int main(int argc,char**argv){
    int f1=open(argv[1],O_RDWR|O_TRUNC);
    int f2=open(argv[2],O_RDWR|O_TRUNC);
	getchar_p=argv[3];
	int len=getint();
	// int len=atoi(argv[3]);
	int w=0;
	for (w=0;w<=len;w+=sizeof(data)){
		write(f1,data,sizeof(data));
	}
	lseek(f1,0,SEEK_SET);
	for (w=0;w+sizeof(data)<=len;w+=sizeof(data)){
		read(f1,data,sizeof(data));
		write(f2,data,sizeof(data));
	}
	if (w<len){
		read(f1,data,len-w);
		write(f2,data,len-w);
	}







	// FILE* a=fopen("/mnt/input.txt","w"), *s=NULL;
	// int len=atoi(argv[1]);
	// for (int w=0;w<len;++w){
	// 	fputc(0,a);
	// }
	// fclose(a);
	// a=fopen("/mnt/input.txt","r");
	// s=fopen(argv[2],"w");
	// for (int w=0;w<len;++w){
	// 	fputc(fgetc(a),s);
	// }
	// fclose(a);
	// fclose(s);
	// return 0;
}
