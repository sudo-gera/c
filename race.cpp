#include <bits/stdc++.h>
using namespace std;

size_t a0=0,b0=0;
size_t a1=0,b1=0;
// size_t a2=0,b2=0;

void f1(){
    a0=1;
    b0=1;
}

void f2(){
    b1=b0;
    a1=a0;
}

// void f3(){
//     a1=a0;
//     b1=b0;
// }

// void f4(){
//     b2=b0;
//     a2=a0;
// }

int main(){
    size_t l=10000;
    for (size_t q=0;;++q){
        a0=a1=b0=b1=0;
        thread t1(f1);
        thread t2(f2);
        // thread t3(f3);
        // thread t4(f4);
        t1.join();
        t2.join();
        // t3.join();
        // t4.join();
        assert(not(
                b1==1
            and a1==0
        ));
        if (q%l==0){
            cout<<"made "<<q<<" iterations"<<endl;
        }
    }
}
