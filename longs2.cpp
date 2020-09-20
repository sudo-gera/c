#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
// вектор, чистящий ведущие нули
vector <int> norm(vector <int> c){
	while(c.size() > 0 and c[c.size() - 1] == 0){
		c.pop_back();
	}
	return c;
}
//функция сложения векторов
vector <int> sum(vector <int> a, vector <int> b){
	vector <int> c;
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
	int p = 0;
	for (size_t i = 1; i <= a.size(); i++){
		int d = a[i] + b[i] + p;
		c.push_back(d%10);
		p = d/10;
	}
	c = norm(c);
	return c;
}
//сравнение векторов -1, если 1й вектор меньше, 0 - если равны, 1 - если первый вектор больше
int sr(vector <int> a, vector <int> b){
	if (a.size() > b.size())
		return 1;
	if(a.size() < b.size())
		return -1;
	for(int i = a.size() - 1; i >= 0; i--){
		if (a[i] > b[i])
			return 1;
		else if (a[i] < b[i])
			return -1;
	}
	return 0;
	}
//функция вычитания 
vector <int> sub(vector <int> a, vector <int> b){
	vector <int> c;
	//сделали векторы одной длины, добиы=в их нулями
	while(a.size() < b.size()){
		a.push_back(0);
	}
	while(b.size() < a.size()){
		b.push_back(0);
	}
			
	//значение переноса
	int p = 0;
	for (size_t i = 1; i <= a.size(); i++){
		int d = a[i] - b[i] + p;
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
vector <int> long_pov(vector <int> a, vector <int> b){
	vector <int> c;
	//проходя по циклам, умножаем каждую циру на каждую и переводим их в массивы. Затем используем уже написанную функцию сложения массивов и все работает.
	for (size_t i = 0; i < a.size(); i++){
		for (size_t j = 0; j < b.size(); j++){
			int y = a[i] * b[j];
			vector <int> r;
			for (size_t k = 0; k < i + j; k++){
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
//класс по работе с длинными числами
struct longlong{
	// заводим стороку с цифрами
	string digits;
	//оператор сложения
	longlong operator+ (longlong oth){
		//с векторами работать проще, потому создадим векторы
		std::vector<int> one;
		std::vector<int> two;
		std::vector<int> thr;
		//переменные для знаков(принимают значения 1 и -1)
		int one_sign=1;
		int two_sign=1;
		int thr_sign=1;
		//перегон из строки в вектор
		for (auto &a : digits){
			if (a=='-'){
				one_sign=-1;
			}else{
				one.push_back(a-'0');
			}
		}
		one = norm(one);
		//перегон 2го числа
		for (auto &a : oth.digits){
			if (a=='-'){
				two_sign=-1;
			}else{
				two.push_back(a-'0');
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
				thr = sub(one, two);
			}
			else{
				thr_sign = two_sign;
				thr = sub(two, one);
			}
		}
		//создаём переменную, в которую записываем результат
		longlong result;
		//перегоняем назад в строку
		for (auto &a : thr){
			result.digits.push_back(a+'0');
		}
		if (thr_sign==-1){
			result.digits.push_back('-');
		}
		//возвращаем число
		return result;
	}
	//оператор умножения
	longlong operator* (longlong oth){
		//вводим векторы
		std::vector<int> one;
		std::vector<int> two;
		std::vector<int> thr;
		//чиселки, обозначающие знак:)
		int one_sign=1;
		int two_sign=1;
		int thr_sign=1;
		//перегон из строки в вектор
		for (auto &a : digits){
			if (a=='-'){
				one_sign=-1;
			}else{
				one.push_back(a-'0');
			}
		}
		for (auto &a : oth.digits){
			if (a=='-'){
				two_sign=-1;
			}else{
				two.push_back(a-'0');
			}
		}
		//код умножения. получаем знак умножения, перемножив значения знаков множителей и потом просто перемножаем сами векторы между сбой
		thr_sign = one_sign * two_sign;
		thr = long_pov(one, two);
		/*magic*/
		longlong result;
		//перегон вектора в строку
		for (auto &a : thr){
			result.digits.push_back(a+'0');
		}
		if (thr_sign==-1){
			result.digits.push_back('-');
		}
		//возвращаем чиселку
		return result;
	}
	//функция присваивания для knglong
/*    longlong operator= (longlong oth){
		digits=oth.digits;
		return oth;
	}*/
	//функция присваивания int
	void operator= (int oth){
		//превращает в строку и разварачивает
		digits=to_string(oth);
		reverse(digits.begin(),digits.end());
	}
};
//функция вывода
	//создаём оператор << 
std::ostream& operator<< (std::ostream &st,longlong l){
	//выполныем функцию
		//разворачиваем число, выводим в st  
	reverse(l.digits.begin(), l.digits.end());
	st<<l.digits;
	//reverse(l.digits.begin(), l.digits.end());
	//возвращаем cout
	return st;
}
//функция ввода
std::istream& operator>> (std::istream &st,longlong &l){
	//нет смысла разворачивать то, что выкидываем
	//reverse(l.digits.begin(), l.digits.end())
	
	//выполнение функии
		//считываем строку цифр и разворачиваем
	st>>l.digits;
	reverse(l.digits.begin(), l.digits.end());
	//возвращаем cin
	return st;
}

int main(){
	std::vector<int> v;
	v={1,2,3,4,5};
	std::vector<int> e;
	e={1,2,3,4,5};
	auto d=sum(e,v);
	for (auto s:d){
		cout<<s<<' ';
	}
cout<<endl;
}