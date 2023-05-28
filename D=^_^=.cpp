#include <algorithm>
#include <iostream>
#include <vector>


/// @brief prefix function
/// @tparam T string-like type
/// @param str - string of type T
/// @return result[i] = max k<=i | str[:k]==str[i+1-k:i+1]
template <typename T>
auto PrefixFun(T&& str) {
    std::vector<int64_t> pref_fun(str.size());
    for (size_t q = 1; q < str.size(); ++q) {
        int64_t k = pref_fun[q - 1];
        while (k > 0 and str[q] != str[k]) {
            k = pref_fun[k - 1];
        }
        if (str[q] == str[k]) {
            k++;
        }
        pref_fun[q] = k;
    }
    return pref_fun;
}

int main() {
    std::string prefixes;
    std::string text;
    std::cin >> prefixes >> text;
    auto sum = prefixes + " " + text;
    auto pref_fun = PrefixFun(sum);
    pref_fun.push_back(1);
    if (*std::min_element(pref_fun.begin() + static_cast<int64_t>(prefixes.size()) + 1, pref_fun.end() - 1) == 0) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
        for (size_t q = 0; q <= text.size(); ++q) {
            auto z = pref_fun[q + prefixes.size() + 1];
            auto x = pref_fun[q + prefixes.size()] + 1;
            if (x>z){
                std::cout << std::string(prefixes.begin(), prefixes.begin() + x - z)<<" ";
            }
        }
        std::cout << std::endl;
    }
}
