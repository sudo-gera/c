template<typename q,typename w>
void copy_array(q a,w s,size_t d=1){
    for (size_t z=0;z<d;++z){
        s[z]=a[z];
    }
}