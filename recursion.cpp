#include <iostream>
#include <vector>

using ull=unsigned long long;

struct layer{
    ull n,m,ret,jmp;
};

ull ackermann(ull m,ull n){
    std::vector<layer> a;
    a.push_back({.n=n,.m=m,.jmp=0});
    auto s=&a[0];
    auto d=&a[0];
    long es=-1;
    while (1){
        if (es==-1){
            es=-2;
        }
        if (es==-2){
            s=&a.back();
            d=&a.back();
            if (s->m==0){
                s->ret=s->n+1;
                es=-3;
            }
        }
        if (es!=-2 or s->n==0){
            if (es==-2){
                a.push_back({.m=s->m-1,.n=1,.jmp=1});
                es=-1;
            }
            if (es==1){
                es=-2;
            }
            if (es==-2){
                s=-1+&a.back();
                d=&a.back();
                s->ret=d->ret;
                a.pop_back();
                es=-3;
            }
        }
        if (es==-2){
            a.push_back({.m=s->m,.n=s->n-1,.jmp=2});
            es=-1;
        }
        if (es==2){
            es=-2;
        }
        if (es==-2){
            s=-1+&a.back();
            d=&a.back();
            s->n=d->ret;
            d->m=s->m-1;
            d->n=s->n;
            d->jmp=3;
            es=-1;
        }
        if (es==3){
            es=-2;
        }
        if (es==-2){
            s=-1+&a.back();
            d=&a.back();
            s->ret=d->ret;
            a.pop_back();
            es=-3;
        }
        if (es==-3){
            es=-2;
        }
        if (es==-2){
            es=s->jmp;
        }
        if (es==0){
            es=-2;
        }
        if (es==-2){
            return a[0].ret;
        }
    }
}




int main(){
    printf("\x1b[92m%i\x1b[0m\t",0);
    for (ull m=0;m<5;++m){
        printf("\x1b[92m%llu\x1b[0m\t",m);
    }
    printf("\n\n\n");
    for (ull n=0;n<16;++n){
        printf("\x1b[92m%llu\x1b[0m\t",n);
        for (ull m=0;m*m+n<17;++m){
            printf("%llu\t",ackermann(m,n));
            fflush(stdout);
        }
        printf("\n\n\n");
    }
}


