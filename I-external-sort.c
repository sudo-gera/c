#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>
/*
 * array
 *
 * interface: len(a), append(a,n), pop(a), resize(a,l), a[i]
 */
#define OFFSET 2
#define _arr_meta(q) (( (uint64_t*)*(q) )- OFFSET)
uint64_t len(void*a){if (!a){return 0;}return _arr_meta(&a)[1];}
void*resize_f(void**a,uint64_t s,uint64_t y){
	void*p=0;
	if (!a){                  // resize_f(0,12);
		a=&p;
	}
	if (!*a){                 // int*a=0; resize(a,12);
		*a=OFFSET+(uint64_t*)calloc(1,s*(y+1)+OFFSET*sizeof(uint64_t));
		_arr_meta(a)[0]=y+1;
	}else
	if (_arr_meta(a)[0] < y+1 and y+1 <= 2*_arr_meta(a)[0]){
		*a=OFFSET+(uint64_t*)realloc(_arr_meta(a),s*_arr_meta(a)[0]*2+OFFSET*sizeof(uint64_t));
		memset(((char*)(*a))+s*_arr_meta(a)[0],0,s*_arr_meta(a)[0]);
		_arr_meta(a)[0]*=2;
	}else
	if (_arr_meta(a)[0] < y+1){
		*a=OFFSET+(uint64_t*)realloc(_arr_meta(a),s*(y+1)+OFFSET*sizeof(uint64_t));
		memset(((char*)(*a))+s*_arr_meta(a)[0],0,(y+1-_arr_meta(a)[0])*s);
		_arr_meta(a)[0]=y+1;
	}else
	if (_arr_meta(a)[0] > (y+1)*4){
		*a=OFFSET+(uint64_t*)realloc(_arr_meta(a),s*(y+1)+OFFSET*sizeof(uint64_t));
		_arr_meta(a)[0]=y+1;
	}
	_arr_meta(a)[1]=y;
	return *a;
}
#define resize(a,...) resize_f((void**)(&(a)),sizeof(*(a)),__VA_ARGS__)
void del(void*a){if (!a){return;}free(_arr_meta(&a));}
#define append(a,...) (resize((a),len(a)+1),(a)[len(a)-1]=(__VA_ARGS__))
#define pop(a,...) (resize((a),len(a)-1),(a)[len(a)])
#define array(type,name,...) type* name=(type*)resize_f(0,sizeof(type),__VA_ARGS__-0);

FILE*input;
FILE*output;

int cmp(const void*qqq,const void*eee){
	unsigned q=*(const unsigned*)(qqq);
	unsigned e=*(const unsigned*)(eee);
	int c;
	array(char,qq);
	fseek(input,q,SEEK_SET);
	while ((c=fgetc(input))!=EOF and c!='\n'){
		append(qq,c);
	}
	array(char,ee);
	fseek(input,e,SEEK_SET);
	while ((c=fgetc(input))!=EOF and c!='\n'){
		append(ee,c);
	}
	int r=strcmp(qq,ee);
	del(qq);
	del(ee);
	return r;
}


int main(){
	input=fopen("input.txt","r+");
	output=fopen("output.txt","w+");


	// fseek(input,0,SEEK_END);
	// size_t size=ftell(input);
	// fseek(input,0,SEEK_SET);
	// int c;
	// size_t line_count=0;
	// fseek(input,0,SEEK_END);
	// fprintf(input,"%15i",0);
	// fputc('\n',input);
	// fseek(input,0,SEEK_SET);
	// for (size_t w=0;w<size;++w){
	// 	c=fgetc(input);
	// 	if (c=='\n'){
	// 		fseek(input,0,SEEK_END);
	// 		fprintf(input,"%15zu",w+1);
	// 		fputc('\n',input);
	// 		fseek(input,w+1,SEEK_SET);
	// 		line_count++;
	// 	}
	// 	fputc(c,output);
	// }
	// fseek(input,0,SEEK_END);
	// fprintf(input,"%15zu",size+1);
	// fputc('\n',input);
	// fseek(input,0,SEEK_SET);

	int c;
	size_t size=0;
	size_t lines=0;
	array(unsigned,strindex,1)
	while ((c=fgetc(input))!=EOF){
		size++;
		if (c=='\n'){
			append(strindex,size);
			lines++;
		}
		// fputc(c,output);
	}
	// fclose(input);

	qsort(strindex,len(strindex),sizeof(strindex[0]),cmp);

	for (size_t w=0;w<len(strindex);++w){
		fseek(input,strindex[w],SEEK_SET);
		int c;
		while ((c=fgetc(input))!=EOF and c!='\n'){
			fputc(c,output);
		}
		fputc('\n',output);
	}

	// for (size_t x=0;x<lines;++x){
	// 	fseek(output,0,SEEK_SET);
	// 	char*first=0;
	// 	char*second=0;
	// 	size_t to_write=0;
	// 	while ((c=fgetc(output))!=EOF and c!='\n'){
	// 		append(first,c);
	// 	}
	// 	size_t to_read=ftell(output);
	// 	for (size_t z=0;z<lines;++z){
	// 		fseek(output,to_read,SEEK_SET);
	// 		resize(second,len(second));
	// 		while ((c=fgetc(output))!=EOF and c!='\n'){
	// 			append(second,c);
	// 		}
	// 		to_read=ftell(output);
	// 		fseek(output,to_write,SEEK_SET);
	// 		if (strcmp(first,second)>0){
	// 			fprintf(output,"%s\n",second);
	// 			del(second);
	// 			second=0;
	// 		}else{
	// 			fprintf(output,"%s\n",first);
	// 			del(first);
	// 			first=second;
	// 			second=0;
	// 		}
	// 		to_write=ftell(output);
	// 	}
	// 	fprintf(output,"%s\n",first);
	// 	del(first);
	// }

	// fclose(output);
}
