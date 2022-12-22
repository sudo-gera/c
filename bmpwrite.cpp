#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

struct pixel{
    uint8_t blue,green,red,alpha;
};

void bmp_write(vector<vector<pixel>> &a,string filename){
    int height=a.size();
    int width=a[0].size();
    vector<int> data={
        0x4d420000,
        height * width * 4 + 54,
        0, 54, 40,
        width, height,
        0x200001, 0,
        height * width * 4,
        0, 0, 0, 0
    };
    for (auto&q:a){
        for (auto&w:q){
            data.push_back((int&)w);
        }
    }
    char*bytes=(char*)(data.data());
    ofstream o(filename);
    o<<string(bytes+2,bytes+data.size()*4);
}

int main(){
    vector<vector<pixel>> a;
    for (long w=-1023;w<1024;++w){
        a.emplace_back();
        for (long e=-1023;e<1024;++e){
            a.back().emplace_back();
            a.back().back().red=(uint64_t)sqrt(w*w+e*e)+85*2;
            a.back().back().green=(uint64_t)sqrt(w*w+e*e);
            a.back().back().blue=(uint64_t)sqrt(w*w+e*e)+85;
        }
    }
    bmp_write(a,"test.bmp");
}




