struct range_iterator{
	int val, step;
	range_iterator(v,s){
		val=v;
		step=s;
	}
	bool operator!=(range_iterator o){
		if (step>0) and (val>o.val){
			return false;
		}
		if (step<0) and (val<o.val){
			return false;
		}
		if (step==0) and (val==o.val){
			return false;
		}
		return true;
	}
	range_iterator operator++(){
		val+=step;
	}
};
struct range{
	int start, stop, step;
	range(a,o,e){
		start=a;
		stop=o;
		step=e;
	}
	friend range range(a,o,e){
		range r(a,o,e);
		return r;
	}
	friend range range(a,o){
		range r(a,o,1);
		return r;
	}
	friend range range(o){
		range r(0,o,1);
		return r;
	}
	range_iterator begin(){
		range_iterator r(start,step);
		return r;
	}
	range_iterator end(){
		range_iterator r(stop,step);
		return r;
	}
};