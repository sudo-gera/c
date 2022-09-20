template<typename q,typename w,typename e,typename r,typename t=int>
void diff_of_arrays(q&a,w&s,e&d,r f,t g=0){
    auto z=f;
    for (z=0;z<f;++z){
        d[z]=a[z]-s[z]+g;
    }
}