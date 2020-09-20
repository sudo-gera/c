#include <bits/stdc++.h>
using namespace std;
//функция сложения векторов
vector sum(vector a, vector b){
    vector c;
    a.push_back(0);
    b.push_back(0);
    //сделали векторы одной длины, добиваем их нулями
    while(a.size() < b.size()){
        a.push_back(0);
    }
    while(b.size() < a.size()){
        b.push_back(0);
    }        
    //значение переноса
    p = 0
    for (int i = 1; i <= a.size(); i++){
        d = a[i] + b[i] + p;
        c.push_back(d%10);
        p = d/10;
    }
    c = norm(c);
    return c;
}
//сравнение векторов -1, если 1й вектор меньше, 0 - если равны, 1 - если первый вектор больше
int sr(vector a, vector b){
    if (a.size() > b.size())
        return 1;
    if(a.size() < b.size())
        return -1;
    for(int i = a.size() - 1; i >= ; i--){
        if (a[i] > b{i})
            return 1;
        else if (a[i] < b[i])
            return -1;
    }
    return 0;
    }
//функция вычитания 
vector minus(vector a, vector b){
    vector c;
    //сделали векторы одной длины, добиы=в их нулями
    while(a.size() < b.size()){
        a.push_back(0);
    }
    while(b.size() < a.size()){
        b.push_back(0);
    }
            
    //значение переноса
    p = 0
    for (int i = 1; i <= a.size(); i++){
        d = a[i] - b[i] + p;
        if (d >= 0){
            c.push_back(d);
            p = 0;
        }
        else{
            c.push_back(d+10);
            p = -1;
        }
    }
    c = norm(c);
    return c;
}
//a.insert(a.begin, 0)
//функция умножения
vector long_pov(vector a, vector b){
    vector c;
    //проходя по циклам, умножаем каждую циру на каждую и переводим их в массивы. Затем используем уже написанную функцию сложения массивов и все работает.
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < b.size(); j++){
            int y = a[i] * b[j];
            vector r;
            for (int k = 0; k < i + j; k++){
                r.push_back(0);
            }
            r.push_back(y%10);
            r.push_back(y/10);
            c = sum(c, r);
        }
    }
    c = norm(c);
    return c;
}
// вектор, чистящий ведущие нули
vector norm(vector c){
    while(c.size() > 0 and c[c.size() - 1] == 0){
        c.pop_back();
    }
    return c;
}
//класс по работе с длинными числами
class longlong{
    // заводим стороку с цифрами
    string digits;
    //функция вывода
        //создаём оператор << 
    std::ostream& operator<< (std::ostream &st, longlong &l){
        //выполныем функцию
            //разворачиваем число, выводим в st  
        reverse(l.digits.begin(), l.digits.end())
        st<        reverse(l.digits.begin(), l.digits.end())
        //возвращаем cout
        return st;
    }
    //функция ввода
    std::istream& operator>> (std::istream &st, longlong &l){
        //нет смысла разворачивать то, что выкидываем
        //reverse(l.digits.begin(), l.digits.end())
        
        //выполнение функии
            //считываем строку цифр и разворачиваем
        st>>l.digits;
        reverse(l.digits.begin(), l.digits.end())
        //возвращаем cin
        return st;
    }
    //оператор сложения
    longlong operator+ (longlong oth){
        //с векторами работать проще, потому создадим векторы
        std::vector one;
        std::vector two;
        std::vector thr;
        //переменные для знаков(принимают значения 1 и -1)
        int one_sign=1;
        int two_sign=1;
        int thr_sign=1;
        //перегон из строки в вектор
        for (auto &a : digits){
            if (a=='-'){
                one_sign=-1;
            }else{
                one.push_back(a-'0')
            }
        }
        one = norm(one);
        //перегон 2го числа
        for (auto &a : oth.digits){
            if (a=='-'){
                two_sign=-1;
            }else{
                two.push_back(a-'0')
            }
        }
        two = norm(two);
        //код сложения. Если числа одного знака, то складываем их и присваиваем результату знак одного из них, иначе просто вычитаем их
        if(one_sign == two_sign){
            thr_sign = one_sign;
            thr = sum(one, two);
        }
        else{
            int sravn = sr(one, two);
            //определение знака
            if(sravn == 1){
                thr_sign = one_sign;
                thr = minus(one, two);
            }
            else{
                thr_sign = two_sign;
                thr = minus(two, one);
            }
        }
        //создаём переменную, в которую записываем результат
        longlong result
        //перегоняем назад в строку
        for (auto &a : thr){
            result.digits.push_back(a+'0')
        }
        if (thr_sign==-1){
            result.digits.push_back('-')
        }
        //возвращаем число
        return result
    }
    //оператор умножения
    longlong operator* (longlong oth){
        //вводим векторы
        std::vector one;
        std::vector two;
        std::vector thr;
        //чиселки, обозначающие знак:)
        int one_sign=1;
        int two_sign=1;
        int thr_sign=1;
        //перегон из строки в вектор
        for (auto &a : digits){
            if (a=='-'){
                one_sign=-1;
            }else{
                one.push_back(a-'0')
            }
        }
        for (auto &a : oth.digits){
            if (a=='-'){
                two_sign=-1;
            }else{
                two.push_back(a-'0')
            }
        }
        //код умножения. получаем знак умножения, перемножив значения знаков множителей и потом просто перемножаем сами векторы между сбой
        thr_sign = one_sign * two_sign;
        thr = long_pov(one, two);
        /*magic*/
        longlong result
        //перегон вектора в строку
        for (auto &a : thr){
            result.digits.push_back(a+'0')
        }
        if (thr_sign==-1){
            result.digits.push_back('-')
        }
        //возвращаем чиселку
        return result
    }
    //функция присваивания для knglong
    longlong operator= (longlong oth){
        digits=oth.digits;
        return oth;
    }
    //функция присваивания int
    longlong operator= (int oth){
        //превращает в строку и разварачивает
        digits=to_string(oth);
        reverse(digits.begin(),digits.end())
        return oth;
    }
}

int main(){}