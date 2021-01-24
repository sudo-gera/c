#include <bits/stdc++.h>
using namespace std;
struct f{
 int g[444];};
int main(){
 f h;
 h.g[4]=5;
 f v=h;
 cout<<v.g[4];
 v.g[4]=2;
 cout<<h.g[4];}
