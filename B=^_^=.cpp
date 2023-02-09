#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#ifndef assert
#include <cassert>
#endif
#include <tuple>
#include <numeric>
#include <list>
#include <string_view>
#include <cstring>
#include <functional>
#include <type_traits>
using std::back_inserter, std::list, std::hash, std::reverse;
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::copy_if, std::exit, std::enable_if, std::enable_if;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::tuple_element, std::tuple_size, std::is_same;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::unique;

int main() {
    auto getint = []() {
        size_t tmp = 0;
        cin >> tmp;
        return tmp;
    };
    size_t n = getint();
    vector<size_t> p;
    generate_n(back_inserter(p), n, getint);
    string s = "a";
    for (size_t q = 1; q < n; ++q) {
        for (s += "a";; ++s.back()) {
            size_t k = p[q - 1];
            while (k > 0 and s[q] != s[k]) {
                k = p[k - 1];
            }
            if (s[q] == s[k]) {
                k++;
            }
            if (p[q] == k) {
                break;
            }
        }
    }
    cout << s << endl;
}
