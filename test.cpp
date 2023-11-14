#include <bits/stdc++.h>
using namespace std;

struct base{
    private:
    int r = 0;
};

struct derived:virtual protected base{
    void run(){
        r += 1;
    }
};

int main(){
}


