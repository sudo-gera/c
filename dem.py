global:
 %*
struct arman{
 char *a;
 int l;
 arman(char *s,int k){
  a=s;
  l=k;}
 char* begin(){
  return a;}
 char* end(){
  return a+l;}
 char& operator[](int k){
  return a[k];}};
*%
str a[32]
a='12345'
arman s(a,5)
0[a]:='\a'
print(s`s)
