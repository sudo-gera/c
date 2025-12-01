#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <set>

template<typename T, typename C>
void sort_(T begin, T end, C c){
    std::sort(begin, end, c);
}

auto vec_prod(auto lx, auto ly, auto rx, auto ry){
    return lx * ry - ly * rx;
}

auto sca_prod(auto lx, auto ly, auto rx, auto ry){
    return lx * rx + ly * ry;
}

std::vector<
    std::pair<
        ssize_t,
        ssize_t
    >
> dots;

int main(){
    size_t n;
    std::cin>>n;
    for (size_t i = 0; i < n; ++i){
        dots.emplace_back();
        std::cin>>dots.back().first>>dots.back().second;
    }
    sort_(dots.begin(), dots.end(), [&](auto& left, auto& right){return left < right;});
    if (n == 0){
        return 0;
    }
    auto main_dot = dots[0];
    sort_(dots.begin()+1, dots.end(), [&](auto left, auto right){
        left.first -= main_dot.first;
        left.second -= main_dot.second;
        right.first -= main_dot.first;
        right.second -= main_dot.second;
        auto vec = vec_prod(left.first, left.second, right.first, right.second);
        if (vec){
            return vec < 0;
        }
        return left < right;
    });
    for (auto& dot: dots){
        std:: cout << dot.first << " " << dot.second << "\n";
    }
}
