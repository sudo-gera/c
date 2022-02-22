int main(){
	long double w=45.56;
	let q=bin_repr(w);
	print(sizeof(w))
	print(str(q.begin(),q.begin()+1),str(q.begin()+1,q.end()-23),str(q.end()-23,q.end()))
	print(inf(q,2).to_string(16))
}
