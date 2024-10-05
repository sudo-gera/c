#include <tuple>
#include <array>
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char**argv){
    vector<string> args(argv, argv+argc);
    for (auto& arg: args){
        cout << ">" << arg << ">" << endl;
    }
}
