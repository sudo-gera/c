
uint64_t st;
#include "flagsort.cpp"
int main(){
	vector<__uint64_t> a(12345);
	for (auto&w:a){
		for (size_t e=0;e<sizeof(w);++e){
			w+=__uint128_t(rand())<<e*8;
		}
		w*=rand()%2*2-1;
	}
	auto q=a;
	// for (auto w:q){
	// 	write(arr(w/256,w%256));
	// }
	// printf("\n");
	auto s=new remove_reference_t<decltype(a[0])>[a.size()];
	memcpy(s,a.data(),sizeof(a[0])*a.size());
	auto d=a;
	auto f=new remove_reference_t<decltype(d[0])>[d.size()];
	memcpy(f,d.data(),sizeof(a[0])*d.size());
	perf zz;
	// flagsort(a.begin(),a.end());
	double z=zz;
	perf xx;
	st=0;
	// st=uint64_t(s);
	flagsort(s,s+a.size());
	ic(st)
	double x=xx;
	perf cc;
	// sort(d.begin(),d.end());
	double c=cc;
	perf vv;
	sort(f,f+d.size());
	double v=vv;
	if (a!=d or memcmp(s,f,a.size())){
		ic("error")
		if (a.size()<12){
			print(q);
			print(a);
			print(itervect(s,s+a.size()));
			print(d);
			print(itervect(f,f+d.size()));
		}
	}
	ic(z,x,c,v);
}
