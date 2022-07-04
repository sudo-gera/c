template<typename T>
auto _run(const T&f){
	auto [q,w,e,r]=f;
	return q;
}


template<typename T>
auto run(const T&g)->decltype(auto[q,w,e,r]=g){
	return 0;
}

struct a{
	int a,s,d,f;
};


int main(){
	run(a());

}
