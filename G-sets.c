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


/*
 * type casts and i/o
 */

#define uns unsigned
typedef char*    cstr;

#define make_to_string(type,name,str_,acc,size) \
	cstr to_string_##name(const type q){\
		array(char,res,size);\
		sprintf(res,str_,acc);\
		resize(res,strlen(res));\
		return res;\
	}


make_to_string(long long int,      int,   "%lli", q,      128                 )
make_to_string(long long unsigned, uns,   "%llu", q,      128                 )
make_to_string(long double,        float, "%Lf",  q,      128                 )
make_to_string(cstr,               str,   "%s",   q?q:"", q?128+strlen(q):128 )
make_to_string(char,               char,  "%c",   q,      128                 )
#undef make_to_string
#define func_name_generator(func)\
	const char:func##_char,const char*const:func##_str,const char*:func##_str,\
	const long long int:func##_int,const long int:func##_int,const int:func##_int,\
	const long long uns:func##_uns,const long uns:func##_uns,const uns:func##_uns,\
	const long double:func##_float,const double:func##_float,const float:func##_float,\
	char:func##_char,char*const:func##_str,char*:func##_str,\
	long long int:func##_int,long int:func##_int,int:func##_int,\
	long long uns:func##_uns,long uns:func##_uns,uns:func##_uns,\
	long double:func##_float,double:func##_float,float:func##_float,\
	int8_t:func##_int,const int8_t:func##_int,\
	uint8_t:func##_uns,const uint8_t:func##_uns,\
	int16_t:func##_int,const int16_t:func##_int,\
	uint16_t:func##_uns,const uint16_t:func##_uns

#define generic_generator(q,f) _Generic((q),func_name_generator(f))

#define to_str(q) generic_generator(q,to_string)(q)

#define mkinput(type,name,str,acc) type input_##name(){type q=0;scanf(str,acc);return q;}
mkinput(long long int,int,"%lli",&q)
mkinput(long long uns,uns,"%llu",&q)
mkinput(long double,float,"%Lf", &q)
mkinput(char,char,"%c",&q)
#undef mkinput
cstr input_str(){static char t[1048576];scanf("%s",t);return to_str(t);}

#ifdef print
#undef print
#endif

#define read(type,name) type name = generic_generator(name,input)();
#define write(q) {cstr __t=to_str(q);printf("%s " ,__t);del(__t);}
#define print(q) {cstr __t=to_str(q);printf("%s\n",__t);del(__t);}
#define put(q)   {cstr __t=to_str(q);printf("%s"  ,__t);del(__t);}

#define bit_get(a,s)   (((a)[(s)/8/sizeof((a)[0])]>>(s)%(8*sizeof((a)[0])))&1)
#define bit_set(a,s,d) {(a)[(s)/8/sizeof((a)[0])]&=~(1<<(s)%(8*sizeof((a)[0])));(a)[(s)/8/sizeof((a)[0])]+=(d)<<(s)%(8*sizeof((a)[0]));}

#define RP_0(x) TO_REPEAT(x)
#define RP_1(x) RP_0(x##0) RP_0(x##1)
#define RP_2(x) RP_1(x##0) RP_1(x##1)
#define RP_3(x) RP_2(x##0) RP_2(x##1)
#define RP_4(x) RP_3(x##0) RP_3(x##1)
#define RP_5(x) RP_4(x##0) RP_4(x##1)
#define RP_6(x) RP_5(x##0) RP_5(x##1)
#define RP_7(x) RP_6(x##0) RP_6(x##1)
#define RP_8(x) RP_7(x##0) RP_7(x##1)
#define RP_9(x) RP_8(x##0) RP_8(x##1)
#define REPEAT(x) RP_##x(0b0)

/*
 *
 * TO_REPEAT(x) - what to repeat
 *
 * REPEAT(n) - repeats TO_REPEAT 2**n times with x = 0, 1, 2, ..., 2**n-1
 *
 */


void set_print(size_t*i){
	// в данном подмножестве символ x встречается i[x] раз
	for (size_t x=0;x<128;++x){
		for (size_t w=0;w<i[x];++w){
			putchar_unlocked(x);
		}
	}
	putchar('\n');
}

void set_create(size_t*count){
	array(size_t,i,len(count));
	#define TO_REPEAT(x) for (i[x]=0;i[x]<=count[x];++i[x]){
	REPEAT(7)
	#undef TO_REPEAT
	set_print(i);
	#define TO_REPEAT(x) }
	REPEAT(7)
	#undef	TO_REPEAT
}


int main(){
	array(size_t,count,128);
	char s;
	while (!isspace(s=getchar_unlocked())){
		count[(uns)(s)]++;
	}
	set_create(count);
}
