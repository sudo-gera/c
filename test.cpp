#include <bits/stdc++.h>
using namespace std;
<<<<<<< HEAD
void run(int*q){
	
=======

<<<<<<< HEAD
// #define int int64_t

// #define pline_ std::cout<<"\x1b[32m"<<__LINE__<<"\x1b[0m";
// #define pline pline_ std::cout<<std::endl;

// #define print(...) pline_;cout<<": ";print_f(__VA_ARGS__);cout<<endl;
// template<typename t>
// int print_ff(vector<t> a){
// 	cout<<"[";
// 	int c=0;
// 	for(auto w:a){
// 		if(c){
// 			cout<<", "<<w;
// 		}else{
// 			cout<<w;
// 			c=1;
// 		}
// 	}
// 	cout<<"] ";
// 	return 1;
// }
// template <typename t>
// int print_ff(t a){cout<<a<<' ';return 1;}
// template <typename...t>
// void print_f(t...a){int s[]={1,print_ff(a)...};}
// #define len(...) (__VA_ARGS__).size()
// #define elif else if


// // template <typename...t>
// // auto add(t...a){
// // 	vector tmp={a...};
// // 	auto res=tmp[0];
// // 	res.clear();
// // 	for (auto w:tmp){
// // 		res.insert(res.end(),w.begin(),w.end());
// // 	}
// // 	return res;
// // }

// // template <typename t>
// // auto vect(t q,t w){
// // 	vector<typename remove_reference<decltype(*q)>::type> res(q,w);
// // 	return res;
// // }

// #define elif else if

// template <typename t>
// struct el{
// 	t v;
// 	int w;
// 	el* _z=nullptr;
// 	el* _x=nullptr;
// 	int s=1;
// 	int d=1;
// 	el(t _v){
// 		v=_v;
// 		w=rand();
// 	}

// 	// inline el* z(){
// 	// 	return _z;
// 	// }
// 	template<typename y>
// 	void z(y q){
// 		_z=q;
// 		// update(this);
// 		auto t=this;
// 		if (!(t->_z) and !(t->_x)){
// 			t->s=1;
// 			t->d=1;
// 		}
// 		elif (!(t->_z)){
// 			t->s=t->_x->s+1;
// 			t->d=t->_x->d+1;
// 		}
// 		elif (!(t->_x)){
// 			t->s=t->_z->s+1;
// 			t->d=t->_z->d+1;
// 		}else{
// 			t->s=t->_z->s+t->_x->s+1;
// 			t->d=(t->_z->d>t->_x->d?t->_z->d:t->_x->d)+1;
// 		}
// 	}

// 	// inline el* x(){
// 	// 	return _x;
// 	// }
// 	template<typename y>
// 	void x(y q){
// 		_x=q;
// 		// update(this);
// 		auto t=this;
// 		if (!(t->_z) and !(t->_x)){
// 			t->s=1;
// 			t->d=1;
// 		}
// 		elif (!(t->_z)){
// 			t->s=t->_x->s+1;
// 			t->d=t->_x->d+1;
// 		}
// 		elif (!(t->_x)){
// 			t->s=t->_z->s+1;
// 			t->d=t->_z->d+1;
// 		}else{
// 			t->s=t->_z->s+t->_x->s+1;
// 			t->d=(t->_z->d>t->_x->d?t->_z->d:t->_x->d)+1;
// 		}
// 	}
// };

// template<typename T>
// el<T>* get_by_index(el<T>* s,int n){
// 	if (!s){
// 		cout<<__LINE__<<" ValueError"<<endl;
// 		return (el<T>*)(0);
// 	}
// 	if (!(s->_z)){
// 		if (n==0){
// 			return s;
// 		}
// 		else{
// 			return get_by_index(s->_x,n-1);
// 		}
// 	}
// 	else{
// 		if (n==s->_z->s){
// 			return s;
// 		}
// 		if (n<s->_z->s){
// 			return get_by_index(s->_z,n);
// 		}
// 		if (n>s->_z->s){
// 			return get_by_index(s->_x,n-s->_z->s-1);
// 		}
// 	}
// 	cout<<__LINE__<<" unexpected exit"<<endl;
// 	return (el<T>*)(0);
// }


// // def init(l,b,e,f,w=1):
// // 	if b==e:
// // 		return None
// // 	else:
// // 		c=(b+e)//2
// // 		from random import random
// // 		r=el(l[c],w=(1000-w)/(1000)+random()/1000,f=f[:])
// // 		r.z=init(l,b,c,f,w+1)
// // 		r.x=init(l,c+1,e,f,w+1)
// // 		return r

// // def to_list(s):
// // 	if s==None:
// // 		return []
// // 	a=to_list(s.z)
// // 	a.append(s.v)
// // 	a+=to_list(s.x)
// // 	return a

// template <typename T>
// void update(el<T>*t){
// 	if (!(t->_z) and !(t->_x)){
// 		t->s=1;
// 		t->d=1;
// 	}
// 	elif (!(t->_z)){
// 		t->s=t->_x->s+1;
// 		t->d=t->_x->d+1;
// 	}
// 	elif (!(t->_x)){
// 		t->s=t->_z->s+1;
// 		t->d=t->_z->d+1;
// 	}else{
// 		t->s=t->_z->s+t->_x->s+1;
// 		t->d=(t->_z->d>t->_x->d?t->_z->d:t->_x->d)+1;
// 	}
// }

// // template<typename T>
// // vector<T> to_list(el<T>* q){
// // 	if (!q){
// // 		return vector<T>();
// // 	}
// // 	auto r=to_list(q->_z);
// // 	auto t=vector({q->v});
// // 	r.insert(r.end(),t.begin(),t.end());
// // 	t=to_list(q->_x);
// // 	r.insert(r.end(),t.begin(),t.end());
// // 	return r;
// // }

// // template<typename T>
// // void print(el<T>* q){
// // 	auto w=to_list(q);
// // 	for (auto w:w){
// // 		cout<<w<<" ";
// // 	}
// // 	cout<<endl;
// // }

// template<typename T>
// el<T>* merge(el<T>* t1,el<T>* t2){

// 	if (!t1){
// 		return t2;
// 	}
// 	if (!t2){
// 		return t1;
// 	}
// 	if (t1->w<t2->w){
// 		t2->z(merge(t1,t2->_z));
// 		return t2;
// 	}else{
// 		t1->x(merge(t1->_x,t2));
// 		return t1;
// 	}
// }

// template <typename T>
// pair<el<T>*,el<T>*> split(el<T>* t,int n){
// 	if (!t){
// 		return {(el<T>*)(0),(el<T>*)(0)};
// 	}
// 	elif (!(t->_z)){
// 		if (n<1){
// 			return {(el<T>*)(0),t};
// 		}
// 		else{
// 			auto tmp=split(t->_x,n-1);
// 			t->x(tmp.first);
// 			auto t2=tmp.second;
// 			return {t,t2};
// 		}
// 	}elif (t->_z->s==n){
// 		auto t1=t->_z;
// 		t->z((el<T>*)(0));
// 		return {t1,t};
// 	}elif (t->_z->s+1==n){
// 		auto t2=t->_x;
// 		t->x((el<T>*)(0));
// 		return {t,t2};
// 	}elif (t->_z->s+1<n){
// 		auto tmp=split(t->_x,n-t->_z->s-1);
// 		t->x(tmp.first);
// 		auto t2=tmp.second;
// 		return {t,t2};
// 	}elif (t->_z->s>n){
// 		auto tmp=split(t->_z,n);
// 		auto t1=tmp.first;
// 		t->z(tmp.second);
// 		return {t1,t};
// 	}
// 	cout<<__LINE__<<" unexpected exit"<<endl;
// 	return {(el<T>*)(0),(el<T>*)(0)};
// }


// template <typename T>
// struct treap{
// 	el<T>* e=nullptr;
// 	// template <typename y=vector<T>>
// 	// treap(y l=vector<T>()){
// 	// 	for (auto w:l){
// 	// 		e=merge(e,new el(w));
// 	// 	}
// 	// }
// 	treap(int l){
// 		for (int w=0;w<l;++w){
// 			e=merge(e,new el(T()));
// 		}
// 	}
// 	// treap(const treap&l){
// 	// 	for (int w=0;w<l.size();++w){
// 	// 		e=merge(e,new el(l[w]));
// 	// 	}
// 	// }
// 	// void operator=(const treap&l){
// 	// 	e=l.e;
// 	// }
// 	// def __init__(s,l=[],f=[]):
// 	// 	if isinstance(l,el):
// 	// 		s.e=l
// 	// 	elif l==None:
// 	// 		s.e=l
// 	// 	else:
// 	// 		s.f=dict([[w,None] for w in f])
// 	// 		l=list(l)
// 	// 		s.e=init(l,0,len(l),f[:])
// 	// 		# s.e=balance(l,ff=f[:])

// 	// int size()const{
// 	// 	return e?e->s:0;
// 	// }

// 	T&operator[](int n){
// 		if (n<0){
// 			n+=this->size();
// 		}
// 		return get_by_index(e,n)->v;
// 	}

// 	T&operator[](int n)const{
// 		if (n<0){
// 			n+=this->size();
// 		}
// 		return get_by_index(e,n)->v;
// 	}

// 	// friend int __cmp__(treap s,treap d){
// 	// 	int min_len=s.size()>d.size()?d.size():s.size();
// 	// 	for (int w=0;w<min_len;++w){
// 	// 		if (s[w]<d[w]){
// 	// 			return -1;
// 	// 		}
// 	// 		if (s[w]>d[w]){
// 	// 			return -1;
// 	// 		}
// 	// 	}
// 	// 	if (s.size()>d.size()){
// 	// 		return 1;
// 	// 	}
// 	// 	if (s.size()<d.size()){
// 	// 		return -1;
// 	// 	}
// 	// 	return 0;
// 	// }

// 	// bool operator<(const treap o)const{
// 	// 	return __cmp__(*this,o)<0;
// 	// }

// 	// bool operator==(const treap o)const{
// 	// 	return __cmp__(*this,o)==0;
// 	// }

// 	// void operator+=(treap o){
// 	// 	e=merge(e,o.e);
// 	// }

// 	// void clear(){
// 	// 	e->clear();
// 	// }

// 	// void push_back(T a){
// 	// 	e=merge(e,new el(a));
// 	// }


// 	// treap<T> cut(int n){
// 	// 	if(n<0 or n>this->size()){
// 	// 		print("overflowerror",n,this->size())
// 	// 	}
// 	// 	auto tmp=split(this->e,n);
// 	// 	e=tmp.second;
// 	// 	treap<T> res;
// 	// 	res.e=tmp.first;
// 	// 	return res;
// 	// }

// 	// friend ostream&operator<<(ostream&q,treap w){
// 	// 	auto r=to_list(w.e);
// 	// 	q<<'[';
// 	// 	int c=0;
// 	// 	for (auto w:r){
// 	// 		if (c){
// 	// 			q<<", "<<w;
// 	// 		}else{
// 	// 			q<<w;
// 	// 			c=1;
// 	// 		}
// 	// 	}
// 	// 	q<<']';
// 	// 	return q;
// 	// }
// };


// decltype(0) main(){
// 	int n;
// 	cin>>n;
// 	vector<int> a(n);
// 	for(int w=0;w<n;++w){
// 		cin>>a[w];
// 	}
// 	// vector<vector<int>> s(n);
// 	// for(int w=0;w<n;++w){
// 	// 	s[w]={w,a[w]};
// 	// }
// 	treap<int> d(n);
// 	for(int w=0;w<n;++w){
// 		d[w]=w;
// 	}
// 	// decltype(d) f(n);
// 	// for(int w=0;w<n;++w){
// 	// 	f[w]=w;
// 	// }
// 	// f=add(vect(f.begin()+1,f.end()-a[f[0]]),vect(f.begin(),f.begin()+1),vect(f.end()-a[f[0]],f.end()));
// 	// set<decltype(d)> ss;
// 	set<int> gp;
// 	// while (!ss.count(d)){
// 	int _c=500000;
// 	// while (_c or !(d==f)){
// 	while (_c-->0){
// 		// _c=0;
// 		// ss.insert(d);
// 		gp.insert(d[0]);
// 		// {
// 		// 	auto z=d.cut(1);
// 		// 	auto x=d.cut(n-s[0][1]-1);
// 		// 	x+=z;
// 		// 	x+=d;
// 		// 	d=x;
// 		// }
// 		// {
// 		// 	auto z=s.cut(1);
// 		// 	auto x=s.cut(n-s[0][1]-1);
// 		// 	x+=z;
// 		// 	x+=s;
// 		// 	s=x;
// 		// }
// 		// d=add(vect(d.begin()+1,d.end()-s[0][1]),vect(d.begin(),d.begin()+1),vect(d.end()-s[0][1],d.end()));
// 		// s=add(vect(s.begin()+1,s.end()-s[0][1]),vect(s.begin(),s.begin()+1),vect(s.end()-s[0][1],s.end()));

// 		{
// 			auto q=split(d.e,(d.e?d.e->s:0)-a[d[0]]);
// 			auto w=split(q.first,1);
// 			d.e=merge(merge(w.second,w.first),q.second);
// 		}

// 		// {
// 		// 	auto z=f.cut(1);
// 		// 	auto x=f.cut(n-a[f[0]]-1);
// 		// 	x+=z;
// 		// 	x+=f;
// 		// 	f=x;
// 		// }

// 		// {
// 		// 	auto z=f.cut(1);
// 		// 	auto x=f.cut(n-a[f[0]]-1);
// 		// 	x+=z;
// 		// 	x+=f;
// 		// 	f=x;
// 		// }

// 		// print(d)



// 		// d=add(vect(d.begin()+1,d.end()-a[d[0]]),vect(d.begin(),d.begin()+1),vect(d.end()-a[d[0]],d.end()));
// 		// f=add(vect(f.begin()+1,f.end()-a[f[0]]),vect(f.begin(),f.begin()+1),vect(f.end()-a[f[0]],f.end()));
// 		// f=add(vect(f.begin()+1,f.end()-a[f[0]]),vect(f.begin(),f.begin()+1),vect(f.end()-a[f[0]],f.end()));
// 	}
// 	gp.insert(d[0]);
// 	cout<<n-gp.size()<<endl;
// }



signed main(){
	// string q;
	// cout<<(q.length());

	// int64_t n;
	// cin>>n;

	// int64_t q=(1ULL<<63)-1;
	// cout<<q<<' '<<q+1<<endl;


	// for (int64_t n=-5'000'000'000;n<5'000'000'001;++n){
	// 	// int64_t q=(n<0?-n:n);
	// 	int64_t q=(-(-n)*(n>>(sizeof(n)*8-1))-(n)*~(n>>(sizeof(n)*8-1)));
	// 	// int64_t q=(n<0?-n:n)==(-(-n)*(n>>(sizeof(n)*8-1))-(n)*~(n>>(sizeof(n)*8-1)));
	// 	// if (!q){
	// 	// 	cout<<n<<endl;
	// 	// }
	// 	// int q=w<0?w:-w;
	// }


	printf("--\n" );
	int a[rand()*0+1'000'000'000'0];
	printf("--\n" );

	// for (int64_t n:vector<int64_t>({q,-q,-q-1})){
	// for (int64_t n=-13;n<14;++n){
	// 	cout<<n<<' '<<(

	// 		-(~n+1)*(n>>(sizeof(n)*8-1))-(n)*~(n>>(sizeof(n)*8-1))

	// 	)<<endl;
	// 	// if (n==127){
	// 	// 	break;
	// 	// }
	// }

}
=======
#define pline_ std::cout<<"\x1b[32m"<<__LINE__<<"\x1b[0m";
#define pline pline_ std::cout<<std::endl;

#define print(...) pline_;cout<<": ";print_f(__VA_ARGS__);cout<<endl;
template <typename t>
int print_ff(t a){cout<<a<<' ';return 1;}
template <typename...t>
void print_f(t...a){int s[]={1,print_ff(a)...};}


template <typename t>
class pq{
public:
	map<int,int> pi;
	set<pair<vector<int>,t>> c;
	void put(t o,int p){
		if(!pi.count(p)){
			pi[p]=0;
		}else{
			pi[p]+=1;
		}
		c.insert({{-p,pi[p]},o});
	}
	t get(){
		auto q=c.begin();
		c.erase(q);
		return q->second;
	}
	int size(){
		return c.size();
	}
};


int main(){
	auto q=pq<int>();
	q.put(1,1);
	q.put(2,3);
	q.put(3,1);
	q.put(4,2);
	q.put(1,1);
	while(q.size()){
		print(q.get());
	}
}
>>>>>>> dbfc9160821fd2ebd800f5b61ea2a0a0093b9ec9
>>>>>>> dd444a0caf3da673639609e1d5e1d8742ad7d464
