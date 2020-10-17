#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class longlong{
	string digits;
    std::ostream& operator<< (std::ostream &st){
    	reverse(digits.begin(), digits.end())
    	st<<digits;
    	reverse(digits.begin(), digits.end())
    	return st;
    }
    std::istream& operator>> (std::istream &st){
    	//reverse(digits.begin(), digits.end())
    	st>>digits;
    	reverse(digits.begin(), digits.end())
    	return st;
    }
    longlong operator+ (longlong oth){
    	std::vector<int> one;
    	std::vector<int> two;
    	std::vector<int> thr;
    	int one_sign=1;
    	int two_sign=1;
    	int thr_sign=1;
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
    	/*magic*/
    	longlong result
    	for (auto &a : thr){
    		result.digits.push_back(a+'0')
    	}
    	if (thr_sign==-1){
    		result.digits.push_back('-')
    	}
    	return result
    }
    longlong operator* (longlong oth){
    	std::vector<int> one;
    	std::vector<int> two;
    	std::vector<int> thr;
    	int one_sign=1;
    	int two_sign=1;
    	int thr_sign=1;
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
    	/*magic*/
    	longlong result
    	for (auto &a : thr){
    		result.digits.push_back(a+'0')
    	}
    	if (thr_sign==-1){
    		result.digits.push_back('-')
    	}
    	return result
    }
    longlong operator= (longlong oth){
    	digits=oth.digits;
    	return digits;
    }
}