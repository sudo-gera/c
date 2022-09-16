#include <string>
#include <iostream>
using namespace std;
struct long_object{
  mutable string expr;
  mutable char c=0;
  void norm()const{
    std::string s;
    // ic(("python3 -c 'print("+expr+")'").c_str(),"r");
    auto pipe=popen(("python3 -c 'print("+expr+")'").c_str(),"r");
    int c; // note: int, not char, required to handle EOF
    while ((c = fgetc(pipe)) != EOF) { // standard C I/O file reading loop
      s+=static_cast<char>(c);
    }
    pclose(pipe);
    expr=s;
    expr.pop_back();
  }
  void check(){
    auto c_=count_if(expr.begin(), expr.end(),[&](char g){return isalnum(g);});
    c_=expr.size()-c_;
    if (c_>80){
      norm();
    }
  }
  void prepare(char t)const{
    // ic(c,t)
    if (t=='+'){
      if (c=='+' or c=='-' or c=='*' or c=='/' or c=='%' or c==0){

      }else{
        expr="("+expr+")";
      }
    }
    if (t=='-'){
      // if (c=='+' or c=='-' or c=='*' or c=='/' or c=='%' or c==0){

      // }else{
        expr="("+expr+")";
      // }
    }
    if (t=='*'){
      if (c=='*' or c=='/' or c=='%' or c==0){

      }else{
        expr="("+expr+")";
      }
    }
    if (t=='/'){
      // if (c=='*' or c=='/' or c=='%' or c==0){

      // }else{
        expr="("+expr+")";
      // }
    }
    if (t=='%'){
      // if (c=='*' or c=='/' or c=='%' or c==0){

      // }else{
        expr="("+expr+")";
      // }
    }
    c=t;
  }
  long_object(long d=0){
    expr=to_string(d);
  }
  long_object(string d,long h=0){
    expr=d;
    check();
  }
  auto&operator+=(const long_object&o);
  auto&operator-=(const long_object&o);
  auto&operator*=(const long_object&o);
  auto&operator/=(const long_object&o);
  auto&operator%=(const long_object&o);
  explicit operator string()const{
    // norm();
    auto ret=expr;
    ret+='|';
    auto j=*this;
    j.norm();
    ret+=j.expr;
    return ret;
  }
  explicit operator long()const{
    norm();
    return stol(expr);
  }
  explicit operator bool()const;
  // operator bool()const{
  //   return 0!=*this;
  // }
  auto&out(ostream&q)const{
    return q<<string(*this);
  }
};

auto&operator<<(ostream&q,const long_object&o){
  return o.out(q);
}

bool operator==(const long_object&q,const long_object&e){
  q.norm();
  e.norm();
  return q.expr==e.expr;
}

bool operator!=(const long_object&q,const long_object&e){
  q.norm();
  e.norm();
  return q.expr!=e.expr;
}

bool operator<(const long_object&q,const long_object&e){
  q.norm();
  e.norm();
  return q.expr<e.expr;
}

bool operator>(const long_object&q,const long_object&e){
  q.norm();
  e.norm();
  return q.expr>e.expr;
}

bool operator<=(const long_object&q,const long_object&e){
  q.norm();
  e.norm();
  return q.expr<=e.expr;
}

bool operator>=(const long_object&q,const long_object&e){
  q.norm();
  e.norm();
  return q.expr>e.expr;
}

long_object operator+(const long_object&q,const long_object&e){
  q.prepare('+');
  e.prepare('+');
  long_object f=q.expr+"+"+e.expr;
  f.c=q.c;
  return f;
}

long_object operator-(const long_object&q,const long_object&e){
  q.prepare('-');
  e.prepare('-');
  long_object f=q.expr+"-"+e.expr;
  f.c=q.c;
  return f;
}

long_object operator*(const long_object&q,const long_object&e){
  q.prepare('*');
  e.prepare('*');
  long_object f=q.expr+"*"+e.expr;
  f.c=q.c;
  return f;
}

long_object operator/(const long_object&q,const long_object&e){
  q.prepare('/');
  e.prepare('/');
  long_object f=q.expr+"//"+e.expr;
  f.c=q.c;
  return f;
}

long_object operator%(const long_object&q,const long_object&e){
  q.prepare('%');
  e.prepare('%');
  long_object f=q.expr+"%"+e.expr;
  f.c=q.c;
  return f;
}

auto&long_object::operator+=(const long_object&o){
  return *this=*this+o;
}

auto&long_object::operator-=(const long_object&o){
  return *this=*this-o;
}

auto&long_object::operator*=(const long_object&o){
  return *this=*this*o;
}

auto&long_object::operator/=(const long_object&o){
  return *this=*this/o;
}

auto&long_object::operator%=(const long_object&o){
  return *this=*this%o;
}

long_object::operator bool()const{
  return 0!=*this;
}

