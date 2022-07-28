#include <bits/stdc++.h>
using namespace std;

struct el {
  long x = 0;
  long y = 0;
  el *left = nullptr;
  el *right = nullptr;
  long size = 1;
  long sum = 0;
  el(long _v) : x(_v), y(rand()), sum(_v) {}
};

void update(el *t) {
  auto t_left = t ? t->left : 0;
  auto t_right = t ? t->right : 0;
  auto t_left_size = t_left ? t_left->size : 0;
  auto t_right_size = t_right ? t_right->size : 0;
  auto t_left_sum = t_left ? t_left->sum : 0;
  auto t_right_sum = t_right ? t_right->sum : 0;
  t->size = t_left_size + t_right_size + 1;
  t->sum = t_left_sum + t_right_sum + t->x;
}

void del(const el *t) {
  if (!t) {
    return;
  }
  del(t->left);
  del(t->right);
  delete t;
}

el *merge(el *t1, el *t2) {
  if (!t1) {
    return t2;
  }
  if (!t2) {
    return t1;
  }
  if (t1->y < t2->y) {
    t2->left = merge(t1, t2->left);
    update(t2);
    return t2;
  } else {
    t1->right = merge(t1->right, t2);
    update(t1);
    return t1;
  }
}

pair<el *, el *> split(el *t, long val) {
  if (!t) {
    return {nullptr, nullptr};
  }
  if (t->x < val) {
    auto tmp = split(t->right, val);
    t->right = tmp.first;
    update(t);
    return {t, tmp.second};
  } else {
    auto tmp = split(t->left, val);
    t->left = tmp.second;
    update(t);
    return {tmp.first, t};
  }
}

int main() {
  el *a = nullptr;
  long n;
  cin >> n;
  for (size_t w = 0; w < n; ++w) {
    string s;
    cin >> s;
    if (s[0] == '+') {
      long x;
      cin >> x;
      auto [s, d] = split(a, x);
      auto [f, g] = split(d, x + 1);
      if (!f) {
        f = new el(x);
      }
      d = merge(f, g);
      a = merge(s, d);
    }
    if (s[0] == '?') {
      long x, y;
      cin >> x >> y;
      if (x > y) {
        cout << 0 << endl;
      } else {
        auto [s, d] = split(a, x);
        auto [f, g] = split(d, y + 1);
        cout << (f ? f->sum : 0) << endl;
        d = merge(f, g);
        a = merge(s, d);
      }
    }
  }
  del(a);
}
