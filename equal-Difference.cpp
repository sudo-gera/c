template<typename q,typename e>
bool arrays_are_equal(q a,e s,size_t d=0){
    for (size_t w=0;w<d;++w){
        if (a[w]!=s[w]){
            return false;
        }
    }
    return true;
}