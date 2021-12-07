#include "radixsort.cpp"


ima{
	_rand;
	for (size_t w=0;w<1;++w){
		vector<__int128_t> q;
		for (size_t w=0;w<999999;++w){
			// q.push_back((rand()%2*2-1)*(__uint128_t(rand())^(__uint128_t(rand())<<32)^(__uint128_t(rand())<<64)^(__uint128_t(rand())<<96)));
			q.push_back((rand()%2*2-1)*(__uint128_t(rand())*1.0/(__uint128_t(rand()))));
		}
		auto d=q;
		auto e=new remove_reference_t<decltype(q[0])>[q.size()];
		memcpy(e,q.data(),q.size()*sizeof(q[0]));
		let z=q;
		auto c=new remove_reference_t<decltype(q[0])>[q.size()];
		memcpy(c,q.data(),q.size()*sizeof(q[0]));

		auto r=perf();
		// sort(q.begin(),q.end());
		sort(e,e+q.size());
		auto rr=double(r);
		auto v=perf();
		// radixsort(z.begin(),z.size());
		radixsort(c,z.size());
		auto vv=double(r);
		print(rr,vv)
		print(memcmp(e,c,q.size()))
		print(memcmp(q.data(),z.data(),q.size()))
		if (q.size()<12){
			print(d)
			print(itervect(e,e+q.size()))
			print(itervect(c,c+q.size()))
		}
	}


}
