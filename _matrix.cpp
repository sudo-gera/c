#include <bits/stdc++.h>
using namespace std;
struct Matrix
{
    long rows=0;
    long columns=0;
    double*data=nullptr;
    Matrix(int _rows,int _columns){
        if (_rows<0 or _columns<0){
            cout<<"Wrong size of matrix";
            exit(1);
        }
        rows=_rows;
        columns=_columns;
        // data=new double[rows*columns];
        data=(double*)calloc(rows*columns,sizeof(double));
        if (!data){
            cout<<"Wrong size of matrix";
            exit(1);
        }
    }
    Matrix(const Matrix&o){
        memmove(this,&o,sizeof(o));
        data=(double*)calloc(rows*columns,sizeof(double));
        if (!data){
            cout<<"Wrong size of matrix";
            exit(1);
        }
        memmove(data,o.data,sizeof(double)*rows*columns);
    }
    Matrix&operator=(const Matrix&o){
        if (&o==this){
            return*this;
        }
        this->~Matrix();
        memmove(this,&o,sizeof(o));
        data=(double*)calloc(rows*columns,sizeof(double));
        if (!data){
            cout<<"Wrong size of matrix";
            exit(1);
        }
        memmove(data,o.data,sizeof(double)*rows*columns);
    }
    void o(ostream&out)const{
        for (long q=0;q<rows;++q){
            for (long w=0;w<columns;++w){
                out<<data[q*columns+w]<<' ';
            }
            cout<<'\n';
        }
    }
    ~Matrix(){
        if (data){
            free(data);
            data=nullptr;
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