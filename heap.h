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
	begin--;
	if (1 < n) {
		T t = end[-1];
		end[-1] = begin[1];
		begin[1] = t;
		--n;
		int left, right, c = 1;
		while (i < c) {
			i = c;
			left = 2 * i;
			right = 2 * i + 1;
			if (left - 1 < n and begin[i] < begin[left]) {
				c = left;
			}
			if (right - 1 < n and begin[c] < begin[right]) {
				c = right;
			}
			T t = begin[i];
			begin[i] = begin[c];
			begin[c] = t;
		}
	}
}
template <typename T>
void heapsort(T*begin,T*end){
	for (T *w = begin; w != end; ++w){
		PushHeap(begin, w + 1);
	}
	for (T *w = end; w != begin; --w){
		PopHeap(begin, w);
	}
}

void hs(int*a,int n){
	heapsort(a,a+n);
}
