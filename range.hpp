struct range{
	struct range_iterator{
		int val, step;
		range_iterator(int v,int s){
			val=v;
			step=s;
		}
		bool operator!=(range_iterator o){
			if (step>0 and val>=o.val){
				return false;
			}
			if (step<0 and val<=o.val){
				return false;
			}
			if (step==0 and val==o.val){
				return false;
			}
			return true;
		}
		void operator++(){
			val+=step;
		}
		int operator*(){
			return val;
		}
	};
	int start, stop, step;
	range(int a,int o,int e=1){
		start=a;
		stop=o;
		step=e;
	}
	range(int o){
		start=0;
		stop=o;
		step=1;
	}
	friend range range(int a,int o,int e=1){
		range r(a,o,e);
		return r;
	}
	friend range range(int o){
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