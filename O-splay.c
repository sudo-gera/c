int main(){
	uint64_t n=getint();
	// uint64_t n=-1;
	// tree<long> a;
	// treap<long> z;
	vector<long> b;
	long last=0;
	// long sr=0;
	// sr=time(0);
	// printf("seed == %li\n",sr);
	// srand(sr);
	for (uint64_t w=0;w<n;++w){
		char c;
		c=0;
		// c=rand()%2;
		scanf(" %c",&c);
		if (c=='+'){
			long x=getint();
			// long x=rand()%99;
			x+=last;
			// a.insert(x);
			// auto y=z.lower_bound(x);
			// if (y==z.upper_bound(x)){
			// 	z.insert(y,x);
			// }
			auto h=lower_bound(b.begin(),b.end(),x);
			if (h==upper_bound(b.begin(),b.end(),x)){
				b.insert(h,x);
			}
			last=0;
		}else
		if (c=='?'){
			// long x=rand()%99;
			// long y=rand()%99;
			long x=getint(),y=getint();
			if (x<y){
				// auto s=a.cut_less(x);
				// auto d=a.cut_greater(y);
				// auto c=z.cut_left(z.lower_bound(x)-z.begin());
				// auto v=z.cut_right(z.end()-z.upper_bound(y));
				last=0;
				for (auto w=lower_bound(b.begin(),b.end(),x);w!=upper_bound(b.begin(),b.end(),y);++w){
					last+=*w;
				}
				// assert(last==a.sum());
				// assert(last==z.sum());
				// a.add_less(s);
				// a.add_greater(d);
				// z.add_left(c);
				// z.add_right(v);
			}else{
				last=0;
			}
			putint(last);
			putchar('\n');
		}else{
			assert(0);
		}
	}
}
