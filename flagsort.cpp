template <size_t n>struct sized_int{};
template <> struct sized_int <1> {using type=  __uint8_t;};
template <> struct sized_int <2> {using type= __uint16_t;};
template <> struct sized_int <4> {using type= __uint32_t;};
template <> struct sized_int <8> {using type= __uint64_t;};
template <> struct sized_int<16> {using type=__uint128_t;};
template<size_t n>
struct digit_size{
	const static size_t value=
		n == 1 ? 1 :
		n == 2 ? 1 :
		n == 4 ? 1 :
		n == 8 ? 1 :
		n ==16 ? 1 :
	0;
};

template<typename T,size_t _digit>
struct constants{
	using uns=typename sized_int<sizeof(*declval<T>())>::type;
	using dig = typename sized_int<digit_size<sizeof(*declval<T>())>::value>::type;
	const static size_t len=sizeof(uns)/sizeof(dig);
	const static size_t digit=len-_digit-1;
	const static size_t next__d=(_digit+1)%len;
};

template <typename T,size_t _digit=0>
void flagsort(T a,T e){
	// ic(__uint64_t(a)-st,__uint64_t(e)-st,_digit)
	st++;
	if(a==e){
		return;
	}
	using c=constants<T,_digit>;
	size_t n=e-a;
	using uns = typename c::uns;
	using dig = typename c::dig;
	uint32_t offsets[1+(1ULL<<sizeof(dig)*8)];
	uint32_t next_free[1ULL<<sizeof(dig)*8];
	memset(offsets,0,sizeof(offsets));
	memset(next_free,0,sizeof(next_free));
	auto _offsets=offsets+1;
	for (size_t w=0;w<n;++w){
		++_offsets[(reinterpret_cast<dig*>(&(a[w])))[c::digit]];
	}
	for (size_t w=1;w<sizeof(offsets)/sizeof(offsets[0])-1;++w){
		_offsets[w]+=_offsets[w-1];
	}
	memcpy(next_free,offsets,sizeof(next_free));
	size_t cblock=0;
	for (size_t w=0;w<n;++w){
		while (w==offsets[cblock+1]){
			++cblock;
		}
		size_t cdig;
		uns t;
		while ((cdig=(reinterpret_cast<dig*>(&(a[w])))[c::digit])!=cblock){
			t                                         =reinterpret_cast<uns&>(a[w]);
			reinterpret_cast<uns&>(a[w])              =reinterpret_cast<uns&>(a[next_free[cdig]]);
			reinterpret_cast<uns&>(a[next_free[cdig]])=t;
			++next_free[cdig];
		}
	}
	if (c::next__d){
		for (size_t w=0;w<sizeof(next_free)/sizeof(next_free[0]);++w){
			if (offsets[w]!=offsets[w+1]){
				flagsort<T,c::next__d>(a+offsets[w],a+offsets[w+1]);
			}
		}
	}
}
