#include <tuple>
#include <array>
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
using namespace std;

std::unique_ptr<int> test(){
    std::unique_ptr<int> q;
    return q;
}

int main(int argc, char**argv){
    auto tmp = test();
}
