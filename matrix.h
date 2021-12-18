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
const size_t root=root_s<N,0>::value;

template <size_t N>
const bool is_prime=tree<N,2,root<N>+1>::value;

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
	enable_if_t<is_prime<N>,Residue&> operator/=(const Residue&e){
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
	friend enable_if_t<is_prime<N>,Residue> operator/(const Residue&q,const Residue&e){
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
	std::array<std::array<Field,N>,M> data;
public:
	Matrix(const std::vector<std::vector<Field>> q){
		for (size_t w=0;w<M;++w){
			for (size_t e=0;e<N;++e){
				data[w][e]=q[w][e];
			}
		}
	}
	template<typename T>
	auto&operator+=(const Matrix<M,N,T>&e){
		for (size_t w=0;w<M;++w){
			for (size_t q=0;q<N;++q){
				data[w][q]+=e.data[w][q];
			}
		}
		return *this;
	}
	template<typename T>
	auto&operator-=(const Matrix<M,N,T>&e){
		for (size_t w=0;w<M;++w){
			for (size_t q=0;q<N;++q){
				data[w][q]-=e.data[w][q];
			}
		}
		return *this;
	}
	template <size_t _M,size_t _N,typename _Field1,typename _Field2>
	friend auto operator+(const Matrix<_M,_N,_Field1>&q,const Matrix<_M,_N,_Field2>&e){
		auto w=q;
		w+=e;
		return w;
	}
	template <size_t _M,size_t _N,typename _Field1,typename _Field2>
	friend auto operator-(const Matrix<_M,_N,_Field1>&q,const Matrix<_M,_N,_Field2>&e){
		auto w=q;
		w-=e;
		return w;
	}
	template <size_t _M,size_t _K,size_t _N,typename _Field1,typename _Field2>
	friend auto operator*(const Matrix<_M,_K,_Field1>&q,const Matrix<_K,_N,_Field2>&e){
		using dt=decltype(q.data[0][0]*e.data[0][0]);
		auto res=Matrix<_M,_N,dt>();
		for (size_t w=0;w<_M;++w){
			for (size_t r=0;r<_N;++r){
				dt t=0;
				for (size_t t=0;t<_K;++t){
					t+=q[w][t]*e[t][r];
				}
				res[w][r]=t;
			}
		}
		return res;
	}
private:
	enable_if_t<M==N,Field> change_and_det(){
		for (size_t q=0;q<M;++q){
			size_t zero=1;
			size_t w=q+1;
			for (;w<M;++w){
				if (data[w][q]!=0){
					zero=0;
					break;
				}
			}
			if (zero){
				continue;
			}
			if (data[q][q]==0){
				for (size_t e=0;e<M;++e){
					data[q][e]+=data[w][e];
				}
			}
			for (size_t w=q+1;w<M;++w){
				auto h=data[w][q]/data[q][q];
				for (size_t e=0;e<M;++e){
					data[w][e]-=data[q][e]*h;
				}
			}
		}
		Field res=1;
		for (size_t q=0;q<M;++q){
			res*=data[q][q];
		}
		return res;
	}
public:
	enable_if_t<M==N,Field> det(){
		auto h=*this;
		return h.change_and_det();
	}
	auto transposed(){
		Matrix<N,M,Field> res;
		for (size_t q=0;q<M;++q){
			for (size_t w=0;w<N;++w){
				res.data[w][q]=data[q][w];
			}
		}
		return res;
	}
	auto&operator[](size_t q){
		return data[q];
	}
	const auto&operator[](size_t q)const{
		return data[q];
	}
	#if __has_include("d")
	operator vector<vector<Field>>(){
		vector<vector<Field>> res(M,vector<Field>(N));
		for (size_t w=0;w<M;++w){
			for (size_t e=0;e<N;++e){
				res[w][e]=data[w][e];
			}
		}
		return res;
	}
	auto to_string()const{
		str res="\n";
		for (size_t w=0;w<M;++w){
			res+=dumps(itervect(data[w].begin(),data[w].end()))+"\n";
		}
		return res;
	}
	template<typename T>
	friend auto&operator<<(ostream&q,const T&w){
		q<<w.to_string();
		return q;
	}
	#endif
};




ima{
	Matrix<3,3> a=vector<vector<Rational>>({
		{0,1,0},
		{3,4,5},
		{2,1,0}
	});
	print(a)
	print(a.det())
}
