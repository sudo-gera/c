#include <bits/stdc++.h>
using namespace std;
struct Matrix
{
    long rows=0;
    long columns=0;
    double*data=nullptr;
    Matrix(int _rows,int _columns){
        rows=_rows;
        columns=_columns;
        data=new double[rows*columns];
    }
    Matrix(const Matrix&o){
        memmove(this,&o,sizeof(o));
        data=new double[rows*columns];
        memmove(data,o.data,sizeof(double)*rows*columns);
    }
    Matrix&operator=(const Matrix&o){
        memmove(this,&o,sizeof(o));
        data=new double[rows*columns];
        memmove(data,o.data,sizeof(double)*rows*columns);
        return *this;
    }
    void o(ostream&out)const{
        for (long q=0;q<rows;++q){
            for (long w=0;w<columns;++w){
                out<<data[q*columns+w]<<' ';
            }
            cout<<'\n';
        }
    }

};


ostream&operator<<(ostream&out,const Matrix&f){
    f.o(out);
    return out;
}

#if __has_include("d")

int main(){
    Matrix s(2,3);
    vector<double> a({1,2,3,4,5,6});
    memmove(s.data,a.data(),sizeof(double)*a.size());
    cout<<s;
}
#endif