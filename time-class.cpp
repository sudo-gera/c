#include <bits/stdc++.h>
using namespace std;
struct Time
{
    unsigned h=0;
    unsigned m=0;
    Time(unsigned hours, unsigned minutes){
        if (hours<13 and minutes<60){
            h=hours;
            m=minutes;
        }
    }
    void o(ostream&out){
        char t[1024];
        sprintf(t,"%u.%02u",h,m);
        out<<t;
    }
};

Time operator+(Time q,Time w){
    auto h=q.h+w.h;
    auto m=q.m+w.m;
    h+=m/60;
    m%=60;
    if (h!=12){
        h%=12;
    }
    return Time(h,m);
}

bool operator==(Time q,Time w){
    return q.h==w.h and q.m==w.m;
}

ostream&operator<<(ostream&out,Time f){
    f.o(out);
    return out;
}

#if __has_include("d")

int main(){
    Time r(1,0);
    cout<<r<<endl;
}



#endif