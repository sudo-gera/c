template<typename T>
struct node{
	shared_ptr<node> k=0,l=0;
	size_t dep=0;
	T data;
	auto insert(const T&q){
		if (q<data){
			auto nd=k->insert(q);
			if (nd>l->)
		}
	}
};
