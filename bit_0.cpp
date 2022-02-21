#include <bits/stdc++.h>
using namespace std;
auto spl(std::string q) {
  auto res = std::vector<std::string>();
  res.emplace_back();
  for (auto &w : q) {
    if (isspace(w)) {
      res.emplace_back();
    } else {
      res.end()[-1] += w;
    }
  }
  auto _res = std::vector<std::string>();
  for (auto &e : res) {
    if (e.size()) {
      _res.push_back(e);
    }
  }
  return _res;
}

int main() {
  // char ss[1024];
  string s;
  getline(cin, s);
  vector<string> h = {};

  auto j = vector<vector<string>>(
      {
      	{
      		"fe", "ma"
      	}
      	, {
      		"du", "cl"
      	}
      	, {
      		"nh", "ha"
      	}
      	, {
      		"sk", "tr"
      	}
      }
      );
  auto k = vector<vector<string>>(
      {
      	{
      		"bn", "rd", "bw", "bk"
      	}
      	, {
      		"bu", "ge", "gy", "da"
      	}
      }
      );

  unsigned r = 0;
  unsigned g = 0;

  auto v = spl(s);
  // ic(v)
  for (auto w : v) {
    g = 0;
    for (auto e : j) {
      // ic(bin(r),w,e)
      if (find(e.begin(), e.end(), w) != e.end()) {
        r |= (find(e.begin(), e.end(), w) - e.begin()) << g;
      }
      // ic(bin(r),w,e)
      g += 1;
    }
    for (auto e : k) {
      // ic(bin(r),w,e)
      if (find(e.begin(), e.end(), w) != e.end()) {
        r |= (find(e.begin(), e.end(), w) - e.begin()) << g;
      }
      // ic(bin(r),w,e)
      g += 2;
    }
  }
  g = 1;
  if (g) {
    printf("%x", r);
  }

  // cout << string ( h.begin ( ) + 6 , h.end ( ) - 9 ) << endl;
}
