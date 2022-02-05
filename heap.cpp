template<typename T,typename F>
struct heap{
	T*data=nullptr;
	T&top;
	size_t size=0;
	heap(T*d):data(d),top(*data){}
	void insert(T q){
		data[size++]=q;
		data--;
		size_t c=size;
		while (c>1 and F{}(data[c],data[c/2])){
			T t=data[c];
			data[c]=data[c/2];
			data[c/2]=t;
			c=c/2;
		}
		data++;
	}
	void erase(T* q=nullptr){
		assert(size);
		data[0]=data[size-1];
		data--;
		size_t c=1;
		while( 2*c+1<size and ( F{}(data[2*c],data[c]) or F{}(data[2*c+1],data[c]) ) ){
			if (F{}(data[2*c],data[2*c+1])){
				T t=data[c];
				data[c]=data[c*2];
				data[c*2]=t;
				c=c*2;
			}else{
				T t=data[c];
				data[c]=data[c*2+1];
				data[c*2+1]=t;
				c=c*2+1;
			}
		}
		if( 2*c<size and F{}(data[2*c],data[c]) ){
			T t=data[c];
			data[c]=data[c*2];
			data[c*2]=t;
			c=c*2;
		}
		data++;
		size--;
	}
	T* begin(){
		return data;
	}
	T* end(){
		return data+size;
	}
};
