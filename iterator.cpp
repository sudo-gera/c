#include <iostream>
#include <iterator>
#include <vector>
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

int main(){
	auto a=vector<int>({4,3,2,1});
	iter q=&a[0];
	auto w=q+4;
	sort(q,w);
	for (auto w:a){
		cout<<w<<' ';
	}
	cout<<'\n';
}
