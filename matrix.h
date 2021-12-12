#include "biginteger.h"
template <size_t N,size_t B,size_t C>
struct tree{
	static const bool value=tree<N,B,C/2>::value and tree<N,B+C/2,C-C/2>::value;
};

template <size_t N,size_t B>
struct tree<N,B,1>{
	static const bool value=N%B;
};

template <size_t N,size_t B>
struct root_s{
	static const size_t v1=root_s<N,B+1>::value;
	static const size_t v2=v1+(1ULL<<B);
	static const size_t value=v2*v2>N?v1:v2;
};

template <size_t N>
struct root_s<N,32>{
	static const size_t value=0;
};

template <size_t N>
const size_t root=root_s<N,0>::value+1;

template <size_t N>
const bool is_prime=tree<N,2,root<N>>::value;

size_t pow(size_t q,size_t w,size_t e){
	size_t res=1;
	while (w){
		if (w%2){
			res*=q;
			res%=e;
		}
		q*=q;
		q%=e;
		w/=2;
	}
	return res;
}

template <size_t N>
class Residue{
	int64_t v=0;
public:
	Residue(){}
	explicit Residue(int q){
		v=(q%N+N)%N;
	}
	auto&operator+=(const Residue&e){
		v+=e.v;
		v%=N;
		return *this;
	}
	auto&operator*=(const Residue&e){
		v*=e.v;
		v%=N;
		return *this;
	}
	auto&operator-=(const Residue&e){
		v-=e.v;
		v%=N;
		v+=N;
		v%=N;
		return *this;
	}
	typename enable_if<is_prime<N>,Residue&>::type operator/=(const Residue&e){
		v*=pow(e.v,N-2,N);
		v%=N;
		return *this;
	}
	friend auto operator+(const Residue&q,const Residue&e){
		auto w=q;
		w+=e;
		return w;
	}
	friend auto operator*(const Residue&q,const Residue&e){
		auto w=q;
		w*=e;
		return w;
	}
	friend typename enable_if<is_prime<N>,Residue>::type operator/(const Residue&q,const Residue&e){
		auto w=q;
		w/=e;
		return w;
	}
	explicit operator int(){
		return v;
	}
	friend auto&operator<<(ostream&q,const Residue&e){
		q<<e.v;
		return q;
	}
};

template <size_t M,size_t N,typename Field=Rational>
class Matrix{
	array<
}

ima{
}
