#include "cppbase.cpp"

py_func(parse)({
    def parse(a):
        a=a.splitlines()
        a=[w.split(',') for w in a]
        a=[[float(e) for e in w] for w in a]
        assert len(set([len(w) for w in a]))==1
        return a
})


vector<vector<double>> a;
long n=0;

double _get(long z,long x){
    return a[z][x];
}

void _set(long z,long x,double v){
    a[z][x]=v;
}

long s,d,y;
double f,t;

int main(int argc,char**argv){
    a=decltype(a)({
        {2,1,-1,8},
        {-3,-1,2,-11},
        {-2,1,2,-3},
    });
    n=a.size();
    for (long w=0;w<n;++w){
        t=_get(w,w);
        if (t==0){
            y=w+1;
            for (long e=y;e<n;++e){
                t=_get(e,w);
                if (t!=0){
                    s=w;
                    d=e;
                    f=1;
                    y=n+1;
                    for (long g=0;g<y;++g){
                        t=_get(d,g);
                        t*=f;
                        t+=_get(s,g);
                        _set(s,g,t);
                    }
                    break;
                }
            }
        }
        t=_get(w,w);
        if (t!=0){
            y=w+1;
            for (long e=y;e<n;++e){
                s=e;
                d=w;
                f=_get(e,w);
                f=-f;
                f/=_get(w,w);
                y=n+1;
                for (long g=0;g<y;++g){
                    t=_get(d,g);
                    t*=f;
                    t+=_get(s,g);
                    _set(s,g,t);
                }
            }
        }
    }
    for (long w=0;w<n;++w){
        for (long e=0;e<w;++e){
            s=e;
            d=w;
            f=_get(e,w);
            f=-f;
            f/=_get(w,w);
            y=n+1;
            for (long g=0;g<y;++g){
                t=_get(d,g);
                t*=f;
                t+=_get(s,g);
                _set(s,g,t);
            }
        }
    }
    for (long w=0;w<n;++w){
        ic(_get(w,n)/_get(w,w));
    }

}

