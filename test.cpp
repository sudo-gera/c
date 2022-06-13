int main(){
	py_func(run)({
		return '-'*999
	})
	print((str)run())
}
