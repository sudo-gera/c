class fraction{
	int numerator,denominator;
	inline norm{
		while (numerator*denominator){
			numerator=numerator%denominator;
			denominator=denominator%numerator;
		}
		return numerator+denominator;
	}
	inline fraction(n=0,d=1){
		numerator=n;
		denominator=d;
		this->norm();
	}
	inline fraction(long double d){
		
	}
}