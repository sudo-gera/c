#include <bits/stdc++.h>
using namespace std;


int table[4] = {1, 23, 456, 7890};

bool exists_in_table(int v){
    for (int i = 0; i <= 4; i++) {
        if (table[i] == v) return true;
    }
    return false;
}


int main(){
    int t;
    cin >> t;
    cout << exists_in_table(t) << endl;
}


