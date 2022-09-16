#if __has_include("d")
/*
Эту часть сдавать НЕ надо. Она будет вставлена ПЕРЕД Вашим кодом.
*/

#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

class Time{
  public:
   int hour;
   int min;
};

#endif

/*
А вот здесь начинается Ваша функция, которую Вы сдаёте:
*/

  int isEqual(Time a, int min){
// Здесь нужно написать код

    return a.hour*60+a.min==min;

}


/*
Здесь Ваша функция кончается. Для удобства отладки приведено то, что будет вставлено ПОСЛЕ  Вашего кода.
*/

#if __has_include("d")

int main() {
    Time a,newtime;
    int min;
    int res;
    
    // Получить a  из консоли 


    cin>>a.hour>>a.min;
   // Получить min  из консоли 

    cin>>min;
    res = isEqual(a,min);
    cout <<res<< endl;
}

#endif
