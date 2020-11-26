#ifndef other_int
#define other_int int
#endif
struct range{
	struct range_iterator{
		other_int val, step;
		inline range_iterator(other_int v,other_int s){
			val=v;
			step=s;
		}
		inline bool operator!=(range_iterator o){
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
		inline void operator++(){
			val+=step;
		}
		inline other_int operator*(){
			return val;
		}
	};
	other_int start, stop, step;
	inline range(other_int a,other_int o,other_int e=1){
		start=a;
		stop=o;
		step=e;
	}
	inline range(other_int o){
		start=0;
		stop=o;
		step=1;
	}
	friend inline range range(other_int a,other_int o,other_int e=1){
		range r(a,o,e);
		return r;
	}
	friend inline range range(other_int o){
		range r(0,o,1);
		return r;
	}
	inline range_iterator begin(){
		range_iterator r(start,step);
		return r;
	}
	inline range_iterator end(){
		range_iterator r(stop,step);
		return r;
	}
};