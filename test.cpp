int main(){
	// auto q=clock();
	auto e=perf();
	let a=vector<int>();
	for (auto w:range(9999999)){
		a.push_back(w);
	}
	sort(a.begin(),a.end());
	// auto w=clock();
	// ic((w-q)/1.0/CLOCKS_PER_SEC)
	ic(e)
}
