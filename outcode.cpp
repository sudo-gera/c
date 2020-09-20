<<<<<<< HEAD
////6c3d313030300a696e7420615b6c5d0a615b305d3d390a615b315d3d310a615b325d3d350a615b335d3d310a615b345d3d310a615b355d3d310a615b365d3d310a615b375d3d310a615b385d3d310a615b395d3d350a615b31305d3d310a615b31315d3d31380a666f722031323d773c6c3a0a09615b775d3d615b772d31315d0a656e3d615b6c2d315d0a65643d310a793d300a666f72206c2d323d793e2d313a0a096e3d65642b615b795d2a656e0a09643d656e0a0965643d640a09656e3d6e0a64656620696e742067636428612c73293a0a0972657475726e20733f67636428732c612573293a610a673d6763642865642c656e290a65642f3d670a656e2f3d670a7072696e7428290a7072696e74662822254c692f254c695c6e222c656e2c656429
#pragma GCC optimize("Ofast")
=======
<<<<<<< HEAD
////6c696d706f72742072616e67650a666f72207720696e2072616e676528312c31322c32293a0a207072696e742877290a
#pragma GCC optimize("Ofast")
#include <stdio.h>


struct range_class{
  long long int start,stop,step,val;
  auto begin(){
    range_class t;
    t.val=start;
    t.step=step;
    return t;
  }
  auto end(){
    range_class t;
    t.val=stop;
    t.step=step;
    return t;
  }
  auto operator++(){
    val+=step;
  }
  auto operator++(int){
    val+=step;
  }
  auto operator!=(range_class o){
    return o.val!=val;
  }
  auto operator*(){
    return val;
  }
};

range_class range(long long int start,long long int stop,long long int step){
  range_class t;
  t.start=start;
  t.stop=stop;
  t.step=step;
  return t;
}
range_class range(long long int start,long long int stop){
  range_class t;
  t.start=start;
  t.stop=stop;
  t.step=1;
  return t;
}
range_class range(long long int stop){
  range_class t;
  t.start=0;
  t.stop=stop;
  t.step=1;
  return t;
}
int main(){
 
 for(long long int w:range ( 1 , 12 , 2 )){
  printf("%Li\n",w);}
=======
////696d706f727420616c676f726974686d0a6e616d65207374640a7363616e28696e74206e2c696e74206b290a696e7420615b3230303030305d0a666f7220773c6e2b6b3a0a207363616e28696e742074290a20615b775d3d740a73747275637420646f743a0a20696e7420782c792c670a646f7420795b3230303030305d0a753d300a666f7220723c6b2b313a0a20666f7220743c6b2b313a0a2020646f7420690a2020692e783d6e2b6b2d312d720a2020692e793d740a2020692e673d300a2020795b752b2b5d3d690a706173730a20696e7420645b3230303030305d0a20666f7220773c6e2b6b2d313a0a2020645b775d3d615b772b315d2d615b775d0a20736f727428642c642b6e2b6b2d31290a20645b6e2b6b2d315d3d2d310a20733d300a206d3d2d310a20763d2d310a20666f7220773c6e2b6b2d313a0a2020696620645b772b315d2d645b775d3a0a202020696620772b312d733e6d3a0a202020206d3d772b312d730a20202020763d645b775d0a202020733d772b310a20666f7220773c753a0a2020696620615b795b775d2e782b315d2d615b795b775d2e785d3d3d7620616e6420615b795b775d2e792b315d2d615b795b775d2e795d3d3d76206f7220615b795b775d2e782d315d2d615b795b775d2e785d3d3d2d7620616e6420615b795b775d2e792d315d2d615b795b775d2e795d3d3d2d763a0a202020795b775d2e673d310a736f727428792c792b752c5b5d28646f7420612c646f742062297b72657475726e20612e673b7d290a706173730a20696e7420655b3230303030305d0a20666f7220773c3230303030303a0a2020655b775d3d2d320a20666f72206a3c753a0a2020643d795b6a5d0a202064783d302b642e780a202064793d302b642e790a20207072696e742864782c6479290a20207072696e742864290a2020723d6e2b6b2d312d795b6a5d2e780a2020743d302b795b6a5d2e790a2020733d615b745d2b615b6e2b6b2d312d725d0a2020696e7420783d6e2b6b2d312d720a2020696e7420793d740a20206c3d300a20207768696c65206c3c6e20616e6420783e7420616e6420793c6e2b6b2d312d723a0a202020696620615b785d2b615b795d3d3d733a0a20202020655b6c2b2b5d3d782d2d0a20202020655b6c2b2b5d3d792b2b0a202020656c696620615b785d2b615b795d3c733a0a20202020792b2b0a202020656c696620615b785d2b615b795d3e733a0a20202020782d2d0a20206966206c3e3d6e2f323a0a202020736f727428652c652b6e290a202020666f7220773c6e3a0a20202020703d615b655b775d5d0a202020207072696e7428702c656e643d272027290a2020207072696e7428290a20202072657475726e20300a
#include <algorithm>
>>>>>>> 14e3b2af47f4f757aca22d7f2014a965be29e2de
#include <stdio.h>
long long int gcd(auto a,auto s){
 return s ? gcd ( s , a % s ) : a;}
int main(){
<<<<<<< HEAD
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
=======
 
 
 long long int n;
long long int k;
scanf("%Li%Li",&(n),&(k));
 long long int a [ 200000 ];
 long long int w ;
 for(w =0;w < n + k;w ++){
  long long int t;
scanf("%Li",&(t));
  a [ w ] = t;}
 dot y [ 200000 ];
 long long int u = 0;
 long long int r ;
 for(r =0;r < k + 1;r ++){
  long long int t ;
  for(t =0;t < k + 1;t ++){
   dot i;
   i . x = n + k - 1 - r;
   i . y = t;
   i . g = 0;
   y [ u ++ ] = i;}}
 {
  long long int d [ 200000 ];
  for(w =0;w < n + k - 1;w ++){
   d [ w ] = a [ w + 1 ] - a [ w ];}
  sort ( d , d + n + k - 1 );
  d [ n + k - 1 ] = - 1;
  long long int s = 0;
  long long int m = - 1;
  long long int v = - 1;
  for(w =0;w < n + k - 1;w ++){
   if(d [ w + 1 ] - d [ w ] ){
    if(w + 1 - s > m ){
     m = w + 1 - s;
     v = d [ w ];}
    s = w + 1;}}
  for(w =0;w < u;w ++){
   if(a [ y [ w ] . x + 1 ] - a [ y [ w ] . x ] == v && a [ y [ w ] . y + 1 ] - a [ y [ w ] . y ] == v || a [ y [ w ] . x - 1 ] - a [ y [ w ] . x ] == - v && a [ y [ w ] . y - 1 ] - a [ y [ w ] . y ] == - v ){
    y [ w ] . g = 1;}}}
 sort ( y , y + u , [ ] ( dot a , dot b ) { return a . g;
 } );
 {
  long long int e [ 200000 ];
  for(w =0;w < 200000;w ++){
   e [ w ] = - 2;}
  long long int j ;
  for(j =0;j < u;j ++){
   dot d = y [ j ];
   long long int dx = 0 + d . x;
   long long int dy = 0 + d . y;
   auto dx;
auto dy;
printf("%Li %Li\n",dx,dy);
   char* _yExJgJ8uoLN8kVm_m3CeZCzohR6GUi9z=d.__print__();
printf("%Li\n",_yExJgJ8uoLN8kVm_m3CeZCzohR6GUi9z);free(_yExJgJ8uoLN8kVm_m3CeZCzohR6GUi9z);

   r = n + k - 1 - y [ j ] . x;
   long long int t = 0 + y [ j ] . y;
   long long int s = a [ t ] + a [ n + k - 1 - r ];
   long long int x = n + k - 1 - r;
   long long int y = t;
   long long int l = 0;
   while(l < n && x > t && y < n + k - 1 - r ){
    if(a [ x ] + a [ y ] == s ){
     e [ l ++ ] = x --;
     e [ l ++ ] = y ++;}
    else if(a [ x ] + a [ y ] < s ){
     y ++;}
    else if(a [ x ] + a [ y ] > s ){
     x --;}}
   if(l >= n / 2 ){
    sort ( e , e + n );
    for(w =0;w < n;w ++){
     long long int p = a [ e [ w ] ];
     printf("%Li ",p);}
    printf("\n");
    return 0;}}}
>>>>>>> 38ad0c3891e4ca1331981ce6bbd869ac96221531
>>>>>>> 14e3b2af47f4f757aca22d7f2014a965be29e2de
 }
