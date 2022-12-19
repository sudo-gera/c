py_func(rev)({
    def rev(q):
        return q[::-1]
})

int main(){
    vector<int> a({1,2,3,4,5});
    a=(decltype(a))rev(a);
    ic(a)
    string s("12345");
    s=(decltype(s))rev(s);
    ic(s)
}
