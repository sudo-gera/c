int main(){
	long double q=1;
	size_t c=0;
	while (1!=q+1){
		print(bin_repr(q),bin_repr(q+1))
		q/=2;
		c+=1;
	}
	print(c)
}
