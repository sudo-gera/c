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
 }
