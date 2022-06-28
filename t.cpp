#include <bits/stdc++.h>
using namespace std;

struct el {
  long x = 0;
  long y = 0;
  el *left = nullptr;
  el *right = nullptr;
  long size = 1;
  el(long _v) : x(_v), y(rand()) {}
};

void update(el *t) {
  auto t_left = t ? t->left : 0;
  auto t_right = t ? t->right : 0;
  auto t_left_size = t_left ? t_left->size : 0;
  auto t_right_size = t_right ? t_right->size : 0;
  t->size = t_left_size + t_right_size + 1;
}

void pr(el *t) {
  if (!t) {
    return;
  }
  pr(t->left);
  cout << t->x << ' ';
  pr(t->right);
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

pair<el *, el *> split(el *t, int64_t n) {
  if (!t) {
    return {nullptr, nullptr};
  }
  if (n == 0) {
    return {nullptr, t};
  }
  if (n == t->size) {
    return {t, nullptr};
  }
  auto t_left = t ? t->left : 0;
  auto t_right = t ? t->right : 0;
  auto t_left_size = t_left ? t_left->size : 0;
  if (t_left_size < n) {
    auto tmp = split(t_right, n - t_left_size - 1);
    t->right = tmp.first;
    update(t);
    return {t, tmp.second};
  } else {
    auto tmp = split(t_left, n);
    t->left = tmp.second;
    update(t);
    return {tmp.first, t};
  }
}

int main() {
  long n, m;
  cin >> n >> m;
  el *q0 = nullptr;
  for (long y = 0; y < n; ++y) {
    q0 = merge(q0, new el(y + 1));
  }
  for (long y = 0; y < m; ++y) {
    long l, r;
    cin >> l >> r;
    auto [q1, q2] = split(q0, r);
    auto [q3, q4] = split(q1, l - 1);
    q3 = merge(q4, q3);
    q0 = merge(q3, q2);
  }
  pr(q0);
  cout << endl;
  del(q0);
}
