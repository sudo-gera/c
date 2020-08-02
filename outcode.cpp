////636f6d70696c653a0a20672b2b207b7d0a63696d706f7274206d6174680a696e7420793d313032340a626f6f6c20745b795d5b795d0a666c6f617420660a252a663d792f322d302e353b2a250a666f7220773c793a0a20666f7220653c793a0a2020696620737172742828772d66292a28772d66292b28652d66292a28652d6629293c3d663a0a202020745b775d5b655d3d310a2020656c73653a0a202020745b775d5b655d3d300a666f7220773c793a0a20666f7220653c793a0a2020696620745b775d5b655d3a0a2020207072696e7428275f272c656e643d2727290a202020696620652b313c7920616e6420745b775d5b652b315d3a0a202020207072696e7428272d272c656e643d2727290a202020656c73653a0a202020207072696e74282720272c656e643d2727290a2020656c73653a0a2020207072696e7428272020272c656e643d2727290a207072696e7428290a
#pragma GCC optimize("Ofast")
#include <math.h>
#include <stdio.h>
int main(){
 
 long long int y = 1024;
 bool t [ y ] [ y ];
 long double f;
 f=y/2-0.5;
 long long int w ;
 for(w =0;w < y;w ++){
  long long int e ;
  for(e =0;e < y;e ++){
   if(sqrt ( ( w - f ) * ( w - f ) + ( e - f ) * ( e - f ) ) <= f ){
    t [ w ] [ e ] = 1;}
   else{
    t [ w ] [ e ] = 0;}}}
 for(w =0;w < y;w ++){
  long long int e ;
  for(e =0;e < y;e ++){
   if(t [ w ] [ e ] ){
    printf("_");
    if(e + 1 < y && t [ w ] [ e + 1 ] ){
     printf("-");}
    else{
     printf(" ");}}
   else{
    printf("  ");}}
  printf("\n");}
 }
