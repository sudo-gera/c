#include <bits/stdc++.h>
using namespace std;

int main() {
  string a, s;
  cin >> a >> s;
  if (a.size() < s.size()) {
    cout << 0 << endl;
    return 0;
  }
  size_t base = 127;
  size_t sh = 0;
  size_t ah = 0;
  size_t mb = 1;
  for (size_t i = 0; i < s.size(); ++i) {
    sh *= base;
    sh += s[i];
    ah *= base;
    ah += a[i];
    mb *= base;
  }
  vector<size_t> ans;
  for (size_t i = 0; i < a.size() - s.size() + 1; ++i) {
    if (ah == sh and memcmp(a.data() + i, s.data(), s.size()) == 0) {
      ans.push_back(i + 1);
    }
    ah *= base;
    ah += a[i + s.size()];
    ah -= mb * a[i];
  }
  cout << ans.size() << endl;
  for (auto i : ans) {
    cout << i << " ";
  }
  cout << endl;
}
