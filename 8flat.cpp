#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <string.h>
#include <ctype.h>

template <typename T>
struct vect{
	T*t=nullptr;
	int s=0;
	int d=1;
	vect(){
		s=0;
		d=1;
		t=(T*)malloc(d*sizeof(T));
	}
	void push(T q){
		if (s==d){
			d*=2;
			t=(T*)realloc(t,sizeof(T)*d);
		}
		t[s++]=q;
	}
	~vect(){
		free(t);
	}
};

struct money{
	int num;
	int val;
	vect<money>*d;
	vect<char>*s;
};

// auto print_one(money q){
// 	stringstream ss;
// 	// ss<<"["<<q.num<<","<<q.val<<","<<q.s->t+q.num<<","<<q.s->t+q.val<<"]";
// 	ss<<"["<<q.s->t+q.num<<","<<q.s->t+q.val<<"]";
// 	return ss.str();
// }

int cmp_money(const void* p1, const void* p2)
{
	struct money d=*(const struct money*)(p1);
	struct money s=*(const struct money*)(p2);
	char*q=d.val+d.s->t;
	char*w=s.val+s.s->t;
	int z=strlen(q);
	int x=strlen(w);
	if (q[0]!=w[0]){
		return w[0]-q[0];
	}
	int c=1,v=1;
	while (c<z and q[c]=='0'){
		++c;
	}
	while (v<x and w[v]=='0'){
		++v;
	}
	if (z-c!=x-v){
		return (z-c)-(x-v);
	}
	while (c<z and x<v){
		if (q[c]!=w[v]){
			return q[c]-w[v];
		}
		++c;
		++v;
	}
	return 0;
}

int main(){
	vect<char> s;
	int c;
	vect<money> d;
	int s1=0,s2=-1;
	while ((c = fgetc(stdin)) != EOF) {
		if (isspace(c)){
			if (s.s and s.t[s.s-1]){
				s.push(0);
				if (s2>-1){
					d.push({s1,s2,&d,&s});
					s1=s.s;
					s2=-1;
				}else{
					s2=s.s;
				}
			}
		}else{
			s.push(c);
		}
	}
	qsort(d.t,d.s,sizeof(d.t[0]),cmp_money);
	for (int w=0;w<d.s;++w){
		printf("%s ",s.t+d.t[d.s-1-w].num);
	}
	printf("\n");
}
