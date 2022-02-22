#include <bits/stdc++.h>
using namespace std;
int main() {
  int q;
  cin >> q;
  cout << ((q >> 7) & 1);
  cout << ((q >> 6) & 1);
  cout << ((q >> 5) & 1);
  cout << ((q >> 4) & 1);
  cout << ((q >> 3) & 1);
  cout << ((q >> 2) & 1);
  cout << ((q >> 1) & 1);
  cout << ((q >> 0) & 1);
  cout << endl;
}
