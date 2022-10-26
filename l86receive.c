int syscall(int q,...);

int main(int argc,char**argv){
	







	FILE* a=fopen("/mnt/input.txt","w"), *s=NULL;
	int len=atoi(argv[1]);
	for (int w=0;w<len;++w){
		fputc(0,a);
	}
	fclose(a);
	a=fopen("/mnt/input.txt","r");
	s=fopen(argv[2],"w");
	for (int w=0;w<len;++w){
		fputc(fgetc(a),s);
	}
	fclose(a);
	fclose(s);
	return 0;
}
