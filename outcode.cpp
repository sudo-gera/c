////6c3d313030300a696e7420615b6c5d0a615b305d3d390a615b315d3d310a615b325d3d350a615b335d3d310a615b345d3d310a615b355d3d310a615b365d3d310a615b375d3d310a615b385d3d310a615b395d3d350a615b31305d3d310a615b31315d3d31380a666f722031323d773c6c3a0a09615b775d3d615b772d31315d0a656e3d615b6c2d315d0a65643d310a793d300a666f72206c2d323d793e2d313a0a096e3d65642b615b795d2a656e0a09643d656e0a0965643d640a09656e3d6e0a64656620696e742067636428612c73293a0a0972657475726e20733f67636428732c612573293a610a673d6763642865642c656e290a65642f3d670a656e2f3d670a7072696e7428290a7072696e74662822254c692f254c695c6e222c656e2c656429
#pragma GCC optimize("Ofast")
#include <stdio.h>
long long int gcd(auto a,auto s){
 return s ? gcd ( s , a % s ) : a;}
int main(){
 long long int l = 1000;
 long long int a [ l ];
 a [ 0 ] = 9;
 a [ 1 ] = 1;
 a [ 2 ] = 5;
 a [ 3 ] = 1;
 a [ 4 ] = 1;
 a [ 5 ] = 1;
 a [ 6 ] = 1;
 a [ 7 ] = 1;
 a [ 8 ] = 1;
 a [ 9 ] = 5;
 a [ 10 ] = 1;
 a [ 11 ] = 18;
 long long int  w =12 ;
 for(; w < l; w ++){
  a [ w ] = a [ w - 11 ];}
 long long int en = a [ l - 1 ];
 long long int ed = 1;
 long long int y = 0;
  y =l - 2 ;
 for(; y > - 1; y --){
  long long int n = ed + a [ y ] * en;
  long long int d = en;
  ed = d;
  en = n;}
 long long int g = gcd ( ed , en );
 ed /= g;
 en /= g;
 printf("\n");
 printf ( "%Li/%Li\n" , en , ed );
 }
