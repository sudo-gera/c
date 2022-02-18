#include "d"
#define bit_get(a,s)   (((a)[(s)/8/sizeof((a)[0])]>>(s)%(8*sizeof((a)[0])))&1)
#define bit_set(a,s,d) {(a)[(s)/8/sizeof((a)[0])]&=~(1<<(s)%(8*sizeof((a)[0])));(a)[(s)/8/sizeof((a)[0])]+=(d)<<(s)%(8*sizeof((a)[0]));}


ima{
	auto q=new uint8_t[4]();
	size_t w=1;
	cin>>w;
	while (w){
		if (w==1){
			size_t e,r;
			cin>>e>>r;
			bit_set(q,e,r);
		}else{
			size_t e;
			cin>>e;
			print(bit_get(q,e))
		}
		// for (size_t w=0;w<4;++w){
		// 	write(bin_repr(q[w]));
		// }
		// print()
		cin>>w;
	}
}
