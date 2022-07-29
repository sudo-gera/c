py_func(a)({
    def a():
        return '-'*99
})

int main(){
    perf();
    ic(str(a()))
    perf();
}