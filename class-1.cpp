/*
  В начале программы директивы препроцессора
*/
// Начало мантры

#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;
// Конец директив и выбора пространства имён

class Time{
  public:
   int hour;
   int min;
};

  Time add(Time a, int min){
// Здесь нужно написать код

    a.min+=min;
    a.hour+=a.min/60;
    a.min%=60;
    a.hour%=24;
    return a;

}


int main() {
    Time a,newtime;
    int min;
    
    // Получить a  из консоли 


    cin>>a.hour>>a.min;
   // Получить min  из консоли 

    cin>>min;
    newtime = add(a,min);
    cout << newtime.hour << ":" << newtime.min << endl;
}