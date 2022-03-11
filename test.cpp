#include <iostream>
#include <iterator>
#include <vector>
#include <assert.h>
#include <algorithm>
using namespace std;
template <typename T>
class iter {
public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::output_iterator_tag;
    T*a;
    iter(T*s):a(s){}
    reference operator*(){
    	return *a;
    }
    auto&operator--(){
    	--a;
    	return *this;
    }
    auto&operator++(){
    	++a;
    	return *this;
    }
    auto&operator+=(int w){
    	a+=w;
    	return *this;
    }
};

template<typename T>
ptrdiff_t operator-(iter<T> q,iter<T> w){
	return q.a-w.a;
}

template<typename T>
auto operator+(iter<T> q,int w){
	return iter(q.a+w);
}

template<typename T>
auto operator-(iter<T> q,int w){
	return iter(q.a-w);
}

template<typename T>
bool operator==(iter<T> q,iter<T> w){
	return q.a==w.a;
}

template<typename T>
bool operator>=(iter<T> q,iter<T> w){
	return q.a>=w.a;
}

template<typename T>
bool operator<=(iter<T> q,iter<T> w){
	return q.a<=w.a;
}

template<typename T>
bool operator<(iter<T> q,iter<T> w){
	return q.a<w.a;
}

template<typename T>
bool operator>(iter<T> q,iter<T> w){
	return q.a>w.a;
}

template<typename T>
bool operator!=(iter<T> q,iter<T> w){
	return q.a!=w.a;
}

template<typename T>
void check(T q,T e){
	vector<T> a;
	for (auto w=q;w!=e;++w){
		a.push_back(w);
	}
	a.push_back(e);
	for (size_t w=0;w<a.size();++w){
		for (size_t e=0;e<a.size();++e){
			assert(a[w]-a[e]==w-e);
			assert(w>=e or  a[w]<a[e]);
			assert(w<=e or  a[w]>a[e]);
			assert(w==e or a[w]!=a[e]);
			assert(w>e  or a[w]<=a[e]);
			assert(w<e  or a[w]>=a[e]);
			assert(w!=e or a[w]==a[e]);
			assert(a[w]+(e-w)==a[e]);
			assert(a[w]-(w-e)==a[e]);
		}
	}
	auto s=a;
	s.clear();
	for (auto w=e;w!=q;--w){
		s.push_back(w);
	}
	s.push_back(q);
	reverse(s.begin(),s.end());
	assert(a==s);
}


int main(){
	auto a=vector<int>({4,3,2,1});
	iter q=&a[0];
	auto w=q+4;
	sort(q,w);
	for (auto w:a){
		cout<<w<<' ';
	}
	cout<<'\n';
	check(a.begin(),a.end());
	check(q,w);
}
