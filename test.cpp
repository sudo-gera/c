uint64_t dohash(str a){
	// ic(vector<uint8_t>(a.begin(), a.end()))
	uint64_t r=0;
	for (auto w:a){
		r*=4294967291;
		r%=9223372036854775783;
		r+=uint8_t(w);
		r%=9223372036854775783;
	}
	// ic(r)
	return r;
}

str antihash(uint64_t dohash){
	// ic(dohash)
	str r;
	while(dohash){
		r+=uint8_t(dohash%4294967291)%256;
		dohash+=9223372036854775783-uint8_t(r.back());
		dohash%=9223372036854775783;
		dohash*=1106804644594371786;
	}
	// ic(vector<uint8_t>(r.begin(), r.end()))
	reverse(r.begin(),r.end());
	return r;
}


int main(){
	long sr=0;
	sr=time(0);
	printf("seed == %li\n",sr);
	srand(sr);
	str t;
	while(antihash(dohash(t))==t){
		ic(len(t));
		t+=rand()%256;
	}
}
