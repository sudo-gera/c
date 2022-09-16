#include <math.h>
struct C{
    double re=0,im=0;
    double abs(){
        return sqrt(re*re+im*im);
    }
    C(double q=0,double w=0){
        re=q;
        im=w;
    }
};

C operator+(C a,C s){
    return C(a.re+s.re,a.im+s.im);
}

C operator-(C a,C s){
    return C(a.re-s.re,a.im-s.im);
}

C operator*(C a,C s){
    return C(a.re*s.re-a.im*s.im,a.re*s.im+a.im*s.re);
}

C operator/(C a,C s){
    auto e=s;
    e.im*=-1;
    auto d=a*e;
    auto f=s*e;
    d.re/=f.re;
    d.im/=f.re;
    return d;
}

bool operator==(C a,C s){
    return a.re==s.re and a.im==s.im;
}

bool operator!=(C a,C s){
    return !(a==s);
}

#include <iostream>
using namespace std;

ostream&operator<<(ostream&out,C f){
    out<<f.re<<' '<<f.im;
    return out;
}

#if __has_include("d")

int main(){
    C a(1,2);
    auto s=a;
    cout<<a/s<<endl;
}




#endif
