template <typename T>
void PushHeap(T *begin, T *end) {
	size_t i = end - begin;
	begin--;
	size_t j=i/2;
	while (1 < i and begin[j] < begin[i]) {
		T t = begin[i];
		begin[i] = begin[j];
		begin[j] = t;
		i = j;
		j/=2;
	}
}
template <typename T>
void PopHeap(T *begin, T *end) {
	int i = 0, n = end - begin;
	T t = end[-1];
	end[-1] = begin[0];
	begin[0] = t;
	begin--;
	--n;
	int left=1, right=1, c = 1;
	if (n%2){
		for (;;) {
			i = c;
			left = 2 * i;
			right = left + 1;
			if (left>n){
				break;
			}
			if(begin[i] < begin[left]) {
				c = left;
			}
			if (begin[c] < begin[right]) {
				c = right;
			}
			if(i==c){
				break;
			}
			T t = begin[i];
			begin[i] = begin[c];
			begin[c] = t;
		}
	}else{
		for (;;) {
			i = c;
			left = 2 * i;
			right = left + 1;
			if (left>n){
				break;
			}
			if(begin[i] < begin[left]) {
				c = left;
			}
			if (right - 1 < n and begin[c] < begin[right]) {
				c = right;
			}
			if(i==c){
				break;
			}
			T t = begin[i];
			begin[i] = begin[c];
			begin[c] = t;
		}
	}
}
template <typename T>
void heapsort(T*begin,T*end){
	end++;
	for (T *w = begin+1; w != end; ++w){
		PushHeap(begin, w);
	}
	end--;
	for (T *w = end; w != begin; --w){
		PopHeap(begin, w);
	}
}

void hs(int*a,int n){
	heapsort(a,a+n);
}
