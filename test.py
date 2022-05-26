def root(q):
	ans=0
	bit=1<<len(bin(q))
	q_minus_ans_mul_ans=q
	bit_mul_bit=bit**2
	_2_mul_ans_mul_bit=0
	while bit_mul_bit:
		_2_mul_ans_mul_bit_plus_bit_mul_bit=_2_mul_ans_mul_bit+bit_mul_bit
		if _2_mul_ans_mul_bit_plus_bit_mul_bit<=q_minus_ans_mul_ans:
			q_minus_ans_mul_ans-=_2_mul_ans_mul_bit_plus_bit_mul_bit
			_2_mul_ans_mul_bit+=bit_mul_bit
			_2_mul_ans_mul_bit+=bit_mul_bit
			ans+=bit
		bit>>=1
		bit_mul_bit>>=2
		_2_mul_ans_mul_bit>>=1
	return ans


for w in range(9999):
	e=root(w)
	assert e*e<=w<(e+1)**2

