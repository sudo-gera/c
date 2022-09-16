#if __has_include("d")
class Lin{
  public:
   int cm; // сантиметры
   int mm; // миллиметры
};

#endif

#include <iostream>

void printLin(Lin a){
    std::cout<<a.cm<<' '<<a.mm<<'\n';
}

Lin convertToLin(int kletki){
    return Lin({kletki/2,kletki%2*5});
}

#if __has_include("d")
int main(){
    long k;
    std::cin>>k;
    auto s=convertToLin(k);
    printLin(s);
}




#endif
