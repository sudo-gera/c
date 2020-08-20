import initializer_list
global:
 %*int& operator[](std::initializer_list <int> q,int w){return *(q.begin()+w);}*%
auto a={1,2,3,4,5}
for w<5:
 print(a[w]`i)
