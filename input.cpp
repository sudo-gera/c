int64_t get_int(){
	int64_t res=0;
	int8_t sign=1;
	int c;
	while (c=fgetc(res),isspace(c)){

	}
	if (c=='-'){
		sign*=-1;
	}else{
		res=c-'0';
	}
	while (c=fgetc(res),c!=EOF and !isspace(c)){
		res*=10;
		res+=c-'0';
	}
	return sign*res;
}
