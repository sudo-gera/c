#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>
#include <stdint.h>
#define OFFSET 3
#define arr_meta(q) (((int64_t*)(q))- OFFSET)
#define arr_data(t,q) ((t*)(q))
int64_t len(void*a){if (!a){return 0;}return arr_meta(a)[1];}
void setlen_f(void**a,int64_t y){if (!*a){return;}arr_meta(*a)[1]=y;arr_data(char,*a)[arr_meta(*a)[1]*arr_meta(*a)[0]]=0;}
// #define setlen(q,w) setlen_f((void**)(&q),w)
void del(void*a){if (!a){return;}return free(arr_meta(a));}
#define mk4(q) \
mk(1)mk(2)mk(3)mk(4)mk(5)mk(6)mk(7)mk(8)mk(9)mk(10)mk(11)mk(12)mk(13)mk(14)mk(15)mk(16)\
mk(17)mk(18)mk(19)mk(20)mk(21)mk(22)mk(23)mk(24)mk(25)mk(26)mk(27)mk(28)mk(29)mk(30)mk(31)mk(32)\
mk(33)mk(34)mk(35)mk(36)mk(37)mk(38)mk(39)mk(40)mk(41)mk(42)mk(43)mk(44)mk(45)mk(46)mk(47)mk(48)\
mk(49)mk(50)mk(51)mk(52)mk(53)mk(54)mk(55)mk(56)mk(57)mk(58)mk(59)mk(60)mk(61)mk(62)mk(63)mk(64)\
mk(65)mk(66)mk(67)mk(68)mk(69)mk(70)mk(71)mk(72)mk(73)mk(74)mk(75)mk(76)mk(77)mk(78)mk(79)mk(80)\
mk(81)mk(82)mk(83)mk(84)mk(85)mk(86)mk(87)mk(88)mk(89)mk(90)mk(91)mk(92)mk(93)mk(94)mk(95)mk(96)\
mk(97)mk(98)mk(99)mk(100)mk(101)mk(102)mk(103)mk(104)mk(105)mk(106)mk(107)mk(108)mk(109)mk(110)mk(111)mk(112)\
mk(113)mk(114)mk(115)mk(116)mk(117)mk(118)mk(119)mk(120)mk(121)mk(122)mk(123)mk(124)mk(125)mk(126)mk(127)mk(128)
#define mk(q) typedef struct{char a[q];} _s##q;
mk4(1)
#undef mk
void append_f(void**a,uint64_t s,...){
	va_list vl;
	va_start(vl,s);
	void*t;
	if (!*a){
		*a=OFFSET+(int64_t*)calloc(1,s+OFFSET*sizeof(int64_t)+1);
		arr_meta(*a)[2]=1;
		arr_meta(*a)[0]=s;
	}else{
		if (arr_meta(*a)[2]==arr_meta(*a)[1]){
			*a=OFFSET+(int64_t*)realloc(arr_meta(*a),arr_meta(*a)[2]*s*2+OFFSET*sizeof(int64_t)+1);
			arr_meta(*a)[2]<<=1;
		}
	}
	switch(s){
		#define mk(q) case q:arr_data(_s##q,*a)[arr_meta(*a)[1]++]=va_arg(vl,_s##q);arr_data(char,*a)[arr_meta(*a)[1]*arr_meta(*a)[0]]=0;break;
		mk4(1)
		#undef mk
	}
}
#define append(arr,data) append_f((void**)(&(arr)),sizeof(data),data);
#define array() 0LL
typedef char* str;
char*mkstr(const char*a){char*s=array();while (*a){append(s,*a);++a;}return s;}
#define mkto_string(type,name,str,acc,size) char*to_string_##name(const type q){char*buff=(char*)malloc(size);sprintf(buff,str,acc);char*t=mkstr(buff);append(t,(char)(0));setlen(t,len(t)-1);free(buff);return t;}
mkto_string(long long int,int,"%lli",q,128);
mkto_string(long double,float,"%Lf",q,128);
mkto_string(char*,str,"%s",q?q:"",q?128+strlen(q):128);
mkto_string(char,char,"%c",q,128);
#define to_str(q) _Generic((q),\
	const long long int:to_string_int,const long int:to_string_int,const int:to_string_int,\
	const unsigned long long int:to_string_int,const unsigned long int:to_string_int,const unsigned int:to_string_int,\
	const long double:to_string_float,const double:to_string_float,const float:to_string_float,\
	const char:to_string_int,const char*const:to_string_str,const char*:to_string_str,\
	long long int:to_string_int,long int:to_string_int,int:to_string_int,\
	unsigned long long int:to_string_int,unsigned long int:to_string_int,unsigned int:to_string_int,\
	long double:to_string_float,double:to_string_float,float:to_string_float,\
	char:to_string_int,char*const:to_string_str,char*:to_string_str\
	)(q)
#define mkinput(type,name,str,acc) type input_##name(){type q=0;scanf(str,acc);return q;}
mkinput(long long int,int,"%lli",&q);
mkinput(long double,float,"%Lf",&q);
char* input_str(){static char t[1073741824];scanf("%s",t);return to_str(t);}
#define write(q) {char *__t=to_str(q);printf("%s ",__t);del(__t);}
#define print(q) {char *__t=to_str(q);printf("%s\n",__t);del(__t);}
#define put(q) {char *__t=to_str(q);printf("%s",__t);del(__t);}
// #define mappend(q,...) {___t          mappend_f((void**)(&q),sizeof(q[0]),__VA_ARGS__);
// void mappend_f(void**a,uint64_t s,...){
// 	va_list vl;
// 	va_start(vl,q);

// }
// #define add(q,w) add_f((void**)(&q),w);
// void add_f(void**a,void*s){
// 	for (int64_t w=0;w<len(s);++w){
// 		append(*a,arr_data()
// 	}
// }


int main(){
	int** a=array();
	append(a,array())
	append(a[0],11)
	append(a[0],12)
	append(a[0],13)
	append(a,array())
	append(a[1],21)
	append(a[1],22)
	append(a[1],23)
	append(a,array())
	append(a[2],31)
	append(a[2],32)
	append(a[2],33)
	size_t w,e;
	for (w=0;w<len(a);++w){
		for (e=0;e<len(a[w]);++e){
			write(a[w][e]);
		}
		put("\n")
	}
	int64_t*s=array();
	int64_t w_;
	for (w_=0;w_<1e+7;++w_){
		append(s,w_);
	}
	print(len(s));
	print(s[0]);
	print(s[1]);
	print(s[2]);
	print(s[len(s)-1]);
	print(s[len(s)-2]);
	print(s[len(s)-3]);
	print(s[len(s)-4]);
	print(s[len(s)-5]);
	print(s[len(s)-6]);
	// str q=input_str();
	// str w=input_str();
	// str e=input_str();
	// write(q);
	// write(w);
	// write(e);

}
