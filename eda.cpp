#include <bits/stdc++.h>
using namespace std;

size_t floor_2nd_root(size_t n){
    size_t begin=0;
    size_t end=n+1;
    while (begin+1!=end){
        size_t center=(begin+end)/2;
        if (center*center > n){
            end = center;
        }else{
            begin = center;
        }
    }
    return begin;
}

size_t floor_3rd_root(size_t n){
    size_t begin=0;
    size_t end=floor_2nd_root(n)+1;
    while (begin+1!=end){
        size_t center=(begin+end)/2;
        if (center*center*center > n){
            end = center;
        }else{
            begin = center;
        }
    }
    return begin;
}

int main(){
    size_t t=0;
    cin>>t;
    for (size_t test=0; test<t; ++test){
        size_t n=0;
        cin>>n;
        size_t squares_or_cubes_count=0;
        squares_or_cubes_count += floor_2nd_root(n);
        squares_or_cubes_count += floor_3rd_root(n);
        squares_or_cubes_count -= floor_2nd_root(floor_3rd_root(n));
        cout << squares_or_cubes_count << "\n";
    }
}
