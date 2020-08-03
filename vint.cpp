#include <vector>
#include <iostream>
class pint{
 public:
  std::vector <unsigned int> data;
  unsigned int operator=(unsigned int b){
   data.clear();
   data.push_back(b);
   return b;}
  void operator+=(pint b){
   long unsigned int tmp=0,tpr;
   int l=b.data.size();
   int k=data.size();
   int w;
   if (k>=l){
    for (w=0;w<l;w++){
     tmp+=data[w];
     tmp+=b.data[w];
     data[w]=tmp%(1L<<32);
     tmp>>=32;}
    for (;w<l;w++){
     tmp+=b.data[w];
     data.push_back(tmp%(1L<<32));
     tmp>>=32;}
    if (tmp){
     data.push_back(tmp);}
    }
   else{
    for (w=0;w<k;w++){
     tmp+=data[w];
     tmp+=b.data[w];
     data[w]=tmp%(1L<<32);
     tmp>>=32;}
    for (;w<k && tmp;w++){
     tmp+=data[w];
     data[w]=tmp%(1L<<32);
     tmp>>=32;}
    if (tmp){
     data.push_back(tmp);}}}
  void get(){
   for (int w:data){
    std::cout<<w<<'\n';}}

};
int main(){
 pint a,b;
 a=1L<<62;
 b=1L<<62;
 a+=b;
 a.get();
 }
