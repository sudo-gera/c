#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

// repeat char and convert to int
// repeat('1',4) is 1111
size_t repeat(char t,size_t w){
	size_t r=0;
	size_t p=1;
	for (size_t e=0;e<w;++e){
		r+=(t-'0')*p;
		p*=10;
	}
	return r;
}



// solve task if n==10**len-1
size_t get_index(char* k,size_t len){
	if (strlen(k)==1){
		// весь набор чисел может быть разделён на блоки из чисел, начинающихся с одинаковой цифры
		// всего чисел 10**len-1, блоков 9, тогда в кажом блоке (10**len-1)/9 чисел.
		// однозначные числа лексикографически меньше любого числа своего блока
		// тогда они стоят в начале блока.
		// Тогда, число 1 имеет место 1, число 2 - (10**len-1)/9+1
		// число n - (10**len-1)/9*(n-1)+1, если n однозначно
		// заметим, что (10**len-1)/9 это repeat('1',len)
		// (10**len-1)/9*(n-1) это repeat('0'+n-1,len)
		// при этом, если исходное число подаётся как строка k,
		// то n это k[0]-'0'
		return repeat(k[0]-1,len)+1;
	}
	// далее идут только те числа, где хотя бы 2 цифры.
	if (k[0]>'1'){
		// рассмотрим все остальные числа.
		// их расположение внутри блока зависит только от
		// всех цифр, кроме первой.
		// Тогда если взять 2 числа из 1 блока, то после замены
		// их первой цифры на какую-либо другую, их относительный порядок не изменится.
		// При этом, если в каком-то блоке есть число, то есть число в другом блоке
		// с другой первой цифрой и остальными такими же.
		// Тогда если взять число и заменить в нём первую цифру,
		// оно перейдёт в другой блок,
		// его позиция относительно начала нового блока будет той же,
		// что и в старом блоке.
		// Тогда чтобы вычислить позицию числа, можно заменить первую цифру на 1
		// вычислить позицию полученного числа
		// прибавить позицию начала блока исходного числа
		// относительно начала первого блока
		// если длина блока это repeat('1',len),
		// то позиция начала блока исходного числа
		// относительно начала первого блока
		// это repeat(n-1+'0',len), где n - первая цифра.
		// Если число представлено строкой k,
		// то его первая цифра равна k[0]-'0'
		char t=k[0];
		k[0] = '1';
		size_t t1=get_index(k,len);
		k[0] = t;
		return t1+repeat(t-1,len);
	}
	// далее идут только те числа, где хотя бы 2 цифры
	// и первая равна 1
	if (k[0]=='1' and k[1]!='0'){
		char* w = k+1;
		return get_index(w,len-1)+repeat('1',(len-1))+1;
	}
	if (k[0]=='1' and k[1]=='0'){
		char t = k[1];
		k[1] = '1';
		size_t t1 = get_index(k,len);
		k[1] = '2';
		size_t t2 = get_index(k,len);
		k[1] = t;
		return t1*2-t2;
	}
	assert(0);
	return 0;
}

size_t get_index1(char* k,char* n){
	size_t l1=strlen(k);
	size_t l2=strlen(n);
	if (memcmp(k,n,l1<l2?l1:l2)>0){
		size_t l=strlen(n);
		char t=n[l-1];
		size_t t1=get_index(k,l-1);
		n[l-1]=0;
		size_t t2=get_index(n,l-1);
		n[l-1]='0';
		size_t t3=get_index(n,l);
		return t1-t2+t3+t-'0';
	}
	else{
		return get_index(k,strlen(n));
	}
}

int main(){
	char k[10];
	char n[10];
	scanf("%s",n);
	scanf("%s",k);
	printf("%li\n",get_index1(k,n));

}

