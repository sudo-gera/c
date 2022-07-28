#include <vector>
#include <exception>
#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <array>
#include <type_traits>
#include <cassert>
template <size_t M,size_t N,typename Field>
class Matrix{
public:
	Matrix(){}
	std::array<std::array<Field,N>,M> data;
	Matrix(std::initializer_list<std::vector<Field>>list){
		auto vect=std::vector<std::vector<Field>>(list.begin(),list.end());
		for (size_t w=0;w<vect.size();++w){
			for (size_t e=0;e<vect[w].size();++e){
				data[w][e]=vect[w][e];
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
	auto&operator*=(const Field&e){
		for (size_t w=0;w<M;++w){
			for (size_t q=0;q<N;++q){
				data[w][q]*=e;
			}
		}
		return *this;
	}
	template<typename T>
	Matrix<M,N,Field>&operator*=(const Matrix<N,N,T>&e){
		*this=*this*e;
		return *this;
	}
	auto transposed()const{
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
	std::vector<Field> getRow(unsigned q)const{
		std::vector<Field> res;
		for (size_t w=0;w<M;++w){
			res.push_back(data[q][w]);
		}
		return res;
	}
	std::vector<Field> getColumn(unsigned q)const{
		std::vector<Field> res;
		for (size_t w=0;w<M;++w){
			res.push_back(data[w][q]);
		}
		return res;
	}
	auto& out(std::ostream&cout)const{
		size_t v=0;
		cout<<"[";
		for (size_t w=0;w<data.size();++w){
			cout<<(v++?",\n ":"");
			cout<<'[';
			size_t c=0;
			for (size_t e=0;e<data[w].size();++e){
				cout<<(c++?",\t":"");
				cout<<data[w][e];
			}
			cout<<"]";
		}
		cout<<"]\n";
		return cout;
	}
	friend auto&operator<<(std::ostream&q,const Matrix&e){
		return e.out(q);
	}
};

template <int N,typename Field>
using SquareMatrix=Matrix<N,N,Field>;


template <size_t _M,size_t _N,typename _Field1,typename _Field2>
auto operator==(const Matrix<_M,_N,_Field1>&q,const Matrix<_M,_N,_Field2>&e){
	for (size_t w=0;w<_M;++w){
		for (size_t r=0;r<_N;++r){
			if (q.data[w][r]!=e.data[w][r]){
				return 0;
			}
		}
	}
	return 1;

}
template <size_t _M,size_t _N,typename _Field1,typename _Field2>
auto operator!=(const Matrix<_M,_N,_Field1>&q,const Matrix<_M,_N,_Field2>&e){
	return !(q==e);
}
template <size_t _M,size_t _N,typename _Field1,typename _Field2>
auto operator+(const Matrix<_M,_N,_Field1>&q,const Matrix<_M,_N,_Field2>&e){
	auto tmp=q;
	tmp+=e;
	return tmp;
}
template <size_t _M,size_t _N,typename _Field1,typename _Field2>
auto operator-(const Matrix<_M,_N,_Field1>&q,const Matrix<_M,_N,_Field2>&e){
	auto tmp=q;
	tmp-=e;
	return tmp;
}
template <size_t _M,size_t _K,size_t _N,typename _Field1,typename _Field2>
auto operator*(const Matrix<_M,_K,_Field1>&q,const Matrix<_K,_N,_Field2>&e){
	using dt=decltype(q[0][0]*e[0][0]);
	auto res=Matrix<_M,_N,dt>();
	for (size_t w=0;w<_M;++w){
		for (size_t r=0;r<_N;++r){
			dt t_=0;
			for (size_t t=0;t<_K;++t){
				t_+=q[w][t]*e[t][r];
			}
			res[w][r]=t_;
		}
	}
	return res;
}

template <size_t _M,size_t _K,typename _Field1,typename _Field2>
auto operator*(const Matrix<_M,_K,_Field1>&q,const _Field2&e){
	auto tmp=q;
	tmp*=e;
	return tmp;
}

template <size_t _K,size_t _N,typename _Field1,typename _Field2>
auto operator*(const _Field1&q,const Matrix<_K,_N,_Field2>&e){
	auto tmp=e;
	tmp*=q;
	return tmp;
}

long gcd(long q,long e){
	while (q and e){
		q%=e;
		if (q and e){
			e%=q;
		}
	}
	if (q){
		return q;
	}
	return e;
}


class Rational{
public:
	long numerator=0;
	long denominator=1;
private:
	void norm(){
		auto g=gcd(numerator,denominator);
		assert(denominator);
		numerator/=g;
		denominator/=g;
		if (denominator<0){
			numerator*=-1;
			denominator*=-1;
		}
	}
public:
	Rational(int q=0,int w=1):numerator(q),denominator(w){}
	Rational(long q, long w=1):numerator(q),denominator(w){}


	Rational(const std::string&orig){
		auto slash_index=orig.find('/');
		if (slash_index==orig.npos){
			numerator=stol(orig);
		}else{
			numerator=stol(std::string(orig.begin(),orig.begin()+slash_index));
			denominator=stol(std::string(orig.begin()+slash_index+1,orig.end()));
			norm();
		}
	}
	Rational(const char*a){
		*this=Rational(std::string(a));
	}
	auto&operator+=(const Rational&e){
		numerator*=e.denominator;
		numerator+=e.numerator*denominator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	auto&operator-=(const Rational&e){
		numerator*=e.denominator;
		numerator-=e.numerator*denominator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	auto&operator/=(const Rational&e){
		numerator*=e.denominator;
		denominator*=e.numerator;
		norm();
		return *this;
	}
	auto&operator*=(const Rational&e){
		numerator*=e.numerator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	auto operator-()const{
		return Rational(-numerator)/=denominator;
	}
	operator std::string()const{
		auto res=std::to_string(numerator);
		if (denominator!=1){
			res+="/"+std::to_string(denominator);
		}
		return res;
	}
};


auto operator+(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp+=e;
	return tmp;
}
auto operator-(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp-=e;
	return tmp;
}
auto operator*(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp*=e;
	return tmp;
}
auto operator/(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp/=e;
	return tmp;
}
bool operator<(const Rational&q,const Rational&e){
	return q.numerator*e.denominator<q.denominator*e.numerator;
}
bool operator>(const Rational&q,const Rational&e){
	return q.numerator*e.denominator>q.denominator*e.numerator;
}
bool operator==(const Rational&q,const Rational&e){
	return q.numerator*e.denominator==q.denominator*e.numerator;
}
bool operator<=(const Rational&q,const Rational&e){
	return q.numerator*e.denominator<=q.denominator*e.numerator;
}
bool operator!=(const Rational&q,const Rational&e){
	return q.numerator*e.denominator!=q.denominator*e.numerator;
}
bool operator>=(const Rational&q,const Rational&e){
	return q.numerator*e.denominator>=q.denominator*e.numerator;
}
std::ostream&operator<<(std::ostream&q,const Rational&w){
	q<<std::string(w);
	return q;
}
std::istream&operator>>(std::istream&q,Rational&w){
	std::string a;
	q>>a;
	w=Rational(a);
	return q;
}


int main(){
	const Matrix<4,5,long> a = {{384109,	447757,	-342414,	-48560,	-10078},
								{195533,	435169,	-470612,	-13175,	-132425},
								{-335782,	213500,	4467,	168967,	505711},
								{70521,	272514,	-519301,	-387030,	-469733}};
  	const Matrix<5,4,long> b = {{94215,	263003,	-210046,	323207},
								{371653,	514860,	-335316,	-421284},
								{266394,	-197304,	371181,	239343},
								{-45147,	66399,	-404932,	-360647},
								{396606,	358296,	21470,	488839}};
	const SquareMatrix<4, long> ab = {{109577369692,	392278397675,	-338471092900,	-133854037549},
									{2860054999,	320008352362,	-359180471344,	-292752770931},
									{241841860085,	213143047975,	-56964764575,	-11128263813},
									{-199239571725,	67312097169,	-152309958421,	-306346567949}};

	const auto a_b = SquareMatrix<4,long>(a*b);
	assert (a_b == ab);

	const auto aminusb = a - b.transposed();
	const Matrix<4,5,long> diff = {{289894,	76104,	-608808,	-3413,	-406684},
									{-67470,	-79691,	-273308,	-79574,	-490721},
									{-125736,	548816,	-366714,	573899,	484241},
									{-252686,	693798,	-758644,	-26383,	-958572}};
	assert (aminusb == diff);

	auto newMatrix = 2 * aminusb * b;
	newMatrix[2][2] = 1;

	Matrix<4,4,long> small_one;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			small_one[i][j] = long(i == j);
		}
	}

	assert (small_one*small_one==small_one);

    std::string in_s(
"1/12,  43/17,  13/20 "
"71/6,  86/7,   199/68 "
"10/33, 4/77,   5/34 "

"-245480/599499,       50174/599499,           28853/199833 "
"1139425/5395491,      493255/10790982,        -13258861/7193988 "
"4150040/5395491,      -1017620/5395491,       12865600/1798497 "
);


    std::stringstream in;
    in<<in_s;
    SquareMatrix<3,Rational> bigMatrix;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            in >> bigMatrix[i][j];
        }
    }
    SquareMatrix<3,Rational> ratMatrix;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            in >> ratMatrix[i][j];
        }
    }
    SquareMatrix<3,Rational> one;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            one[i][j]=(i==j);
        }
    }
    assert (bigMatrix*ratMatrix==one);


}
