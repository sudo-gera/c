#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  set<long> d;
  while (cin >> s) {
    long q;
    cin >> q;
    if (s[0] == 'i') {
      d.insert(q);
    } else if (s[0] == 'd') {
      d.erase(q);
    } else if (s[0] == 'e') {
      cout << (d.find(q)!=d.end() ? "true" : "false") << endl;
    } else if (s[0] == 'n') {
      auto t = d.upper_bound(q);
      if (!d.size() or t==d.end()) {
        cout << "none" << endl;
      } else {
        cout << *t << endl;
      }
    } else if (s[0] == 'p') {
      auto t = d.lower_bound(q);
      if (!d.size() or t==d.begin()) {
        cout << "none" << endl;
      } else {
        cout << *prev(t) << endl;
      }
    } else if (s[0] == 'k') {
      if (q < 0 or q >= d.size()) {
        cout << "none" << endl;
      } else {
        cout << *next(d.begin(),q) << endl;
      }
    } else {
      break;
    }
  }
}
