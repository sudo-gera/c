#define stl(a) a.begin(),a.end()
template <typename ___g>
auto frag(___g a,int_least64_t s=0,int_least64_t d=0){
	auto f=a.size();
	if (a>f){
		a=f;
	}
	if (a<0){
		a+=f;
	}
	if (a<0){
		a=0;
	}
	if (s<-f){
		s=-f;
	}
	if (s>0){
		s-=f;
	}
	if (s>0){
		s=0;
	}
	return decltype(a)(a.begin()+s,a.end()-s);
}