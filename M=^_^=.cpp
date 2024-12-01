#include <numeric>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


// source: https://github.com/maksim1744/programming-library/blob/master/SuffixArray.cpp

/// @brief for holding buf
/// @tparam T value type of str
template <typename T>
struct SuffixArrayBuf {

    std::vector<T> buf1, buf2, buf3;

    /// @brief create suffix array
    /// @param str - array to create
    /// @param max_value - all elements of str must be less than max_value
    /// @details all elements of str must be greater than 0
    /// @return suffix array
    std::vector<T> SuffixArray(std::vector<T> str, T max_value) {
        if (str.size() <= 4) {
            std::vector<T> res(str.size());
            iota(res.begin(), res.end(), 0);
            sort(res.begin(), res.end(), [&](T i1, T i2) {
                if (i1 == i2) {
                    return false;
                }
                while (i1 < static_cast<T>(str.size()) && i2 < static_cast<T>(str.size()) && str[i1] == str[i2]) {
                    ++i1;
                    ++i2;
                }
                if (i1 == static_cast<T>(str.size()) || i2 == static_cast<T>(str.size())) {
                    return i1 > i2;
                }
                return str[i1] < str[i2];
            });
            return res;
        }
        T init_size = static_cast<T>(str.size());
        str.resize(str.size() + 3, 0);

        std::vector<T> triple_inds;
        for (T i = 0; i + 3 <= static_cast<T>(str.size()); ++i) {
            if (i % 3 != 0) {
                triple_inds.push_back(i);
            }
        }

        // sort triples
        for (T it = 2; it >= 0; --it) {
            buf1.assign(max_value + 1, 0);
            for (T i : triple_inds) {
                buf1[str[i + it]]++;
            }
            for (T i = 1; i < static_cast<T>(buf1.size()); ++i) {
                buf1[i] += buf1[i - 1];
            }
            buf2.resize(triple_inds.size());
            for (T i = static_cast<T>(triple_inds.size()) - 1; i >= 0; --i) {
                buf2[--buf1[str[triple_inds[i] + it]]] = triple_inds[i];
            }
            swap(triple_inds, buf2);
        }

        // assign equivalency classes to triples
        buf2.resize(triple_inds.size());
        buf2[0] = 1;
        for (T i = 1; i < static_cast<T>(triple_inds.size()); ++i) {
            if (str[triple_inds[i]] == str[triple_inds[i - 1]] &&
                str[triple_inds[i] + 1] == str[triple_inds[i - 1] + 1] &&
                str[triple_inds[i] + 2] == str[triple_inds[i - 1] + 2]) {
                buf2[i] = buf2[i - 1];
            } else {
                buf2[i] = buf2[i - 1] + 1;
            }
        }

        // recursively sort triples if there are equal
        if (buf2.back() != static_cast<T>(buf2.size())) {
            T last = buf2.back();
            buf1.resize(str.size());
            for (T i = 0; i < static_cast<T>(triple_inds.size()); ++i) {
                buf1[triple_inds[i]] = buf2[i];
            }
            buf2.clear();
            for (T i = 1; i + 3 <= static_cast<T>(str.size()); i += 3) {
                buf2.push_back(buf1[i]);
            }
            T n1 = static_cast<T>(buf2.size());
            for (T i = 2; i + 3 <= static_cast<T>(str.size()); i += 3) {
                buf2.push_back(buf1[i]);
            }
            triple_inds = SuffixArray(buf2, last);
            for (T &i : triple_inds) {
                {
                    if (i * 3 + 1 + 3 <= static_cast<T>(str.size())) {
                        i = i * 3 + 1;
                    } else {
                        i = (i - n1) * 3 + 2;
                    }
                }
            }
        }

        buf2.clear();
        if (str.size() % 3 == 0) {
            buf2.push_back(static_cast<T>(str.size()) - 3);
        }
        for (T i : triple_inds) {
            if (i % 3 == 1) {
                buf2.push_back(i - 1);
            }
        }

        // sort suffixes with i % 3 = 0
        {
            buf1.assign(max_value + 1, 0);
            for (T i : buf2) {
                buf1[str[i]]++;
            }
            for (T i = 1; i < static_cast<T>(buf1.size()); ++i) {
                buf1[i] += buf1[i - 1];
            }

            buf3.resize(buf2.size());
            for (T i = static_cast<T>(buf2.size()) - 1; i >= 0; --i) {
                buf3[--buf1[str[buf2[i]]]] = buf2[i];
            }

            swap(buf2, buf3);
        }

        buf1.assign(str.size(), 0);
        for (T i = 0; i < static_cast<T>(triple_inds.size()); ++i) {
            buf1[triple_inds[i]] = i + 1;
        }

        // compare suffixes with i1 % 3 != 0 and i2 % 3 == 0
        auto cmp = [&](T i1, T i2) {
            if (str[i1] != str[i2]) {
                return str[i1] < str[i2];
            }
            ++i1;
            ++i2;
            if (i1 % 3 != 0) {
                return buf1[i1] < buf1[i2];
            }
            if (str[i1] != str[i2]) {
                return str[i1] < str[i2];
            }
            ++i1;
            ++i2;
            return buf1[i1] < buf1[i2];
        };

        // merge suf12 and suf0
        buf3.clear();
        auto &res = buf3;
        res.reserve(str.size());
        T i1 = 0;
        T i2 = 0;
        while (i1 < static_cast<T>(triple_inds.size()) || i2 < static_cast<T>(buf2.size())) {
            bool choose1 = false;
            if (i1 == static_cast<T>(triple_inds.size())) {
                choose1 = false;
            } else if (i2 == static_cast<T>(buf2.size())) {
                choose1 = true;
            } else if (cmp(triple_inds[i1], buf2[i2])) {
                choose1 = true;
            } else {
                choose1 = false;
            }

            if (choose1) {
                if (triple_inds[i1] < init_size) {
                    res.push_back(triple_inds[i1]);
                }
                ++i1;
            } else {
                if (buf2[i2] < init_size) {
                    res.push_back(buf2[i2]);
                }
                ++i2;
            }
        }

        return res;
    }
};

int main() {
    std::string s;
    getline(std::cin, s);
    std::vector<int> a(s.begin(), s.end());
    auto d = SuffixArrayBuf<int>().SuffixArray(a, 128);
    for (auto &q : d) {
        q += 1;
        std::cout << q << " ";
    }
    std::cout << std::endl;
}