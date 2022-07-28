#include <bits/stdc++.h>
using namespace std;
int main() {
  string q;
  cin >> q;
  if (q == "float") {
    float q = 1;
    size_t b = 0;
    while (q * 2 != q * 2 + 1) {
      q *= 2;
      b += 1;
    }
    cout << b;
    // cout << 23;
  }
  if (q == "double") {
    double q = 1;
    size_t b = 0;
    while (q * 2 != q * 2 + 1) {
      q *= 2;
      b += 1;
    }
    cout << b;
    // cout << 53;
  }
  if (q == "long") {
    long double q = 1;
    size_t b = 0;
    while (q * 2 != q * 2 + 1) {
      q *= 2;
      b += 1;
    }
    cout << b;
    // cout << 65;
  }
}
