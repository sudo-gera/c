#define to ->
struct trap{
 int pri,pz,ml,mr,pl,pr,mz;
 trap* l,r;
 trap(int t){
  pz=t;
  pri=rand();
  ml=0;
  mr=0;
  pl=0;
  pr=0;
  mz=t;
 }
}

auto upd(auto get){
 if 

auto merge(auto fir,auto sec){
 if (!fir) return sec;
 if (!sec) return fir;
 if (fir to pri > sec to pri){
  fir to r = merge(fir to r,sec);
  upd(fir);
  return fir;}
 if (fir to pri < sec to pri){
  sec to l=merge(fir,sec to r);
  upd(sec);
  return sec;}}
