// #include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
using namespace std;

struct node {
  int64_t v = 0;
  int64_t w = 0;
  node *left = nullptr;
  node *right = nullptr;
  node *p = nullptr;
  int64_t s = 1;
  int64_t d = 1;
  int64_t rev = 0;
  int64_t first = 0;
  int64_t last = 0;
  int64_t sum = 0;
  int64_t to_add = 0;
  int64_t to_mul = 1;
  int64_t is_forward_sorted = 1;
  int64_t is_backward_sorted = 1;
};

void update(node *t) {
  if (t->left) {
    (t->left->p) = t;
    if (t->left->rev) {
      (t->first) = t->left->last * t->left->to_mul + t->left->to_add;
    } else {
      (t->first) = t->left->first * t->left->to_mul + t->left->to_add;
    }
  } else {
    (t->first) = t->v;
  }
  if (t->right) {
    (t->right->p) = t;
    if (t->right->rev) {
      (t->last) = t->right->first * t->right->to_mul + t->right->to_add;
    } else {
      (t->last) = t->right->last * t->right->to_mul + t->right->to_add;
    }
  } else {
    (t->last) = t->v;
  }
  if (t->left and t->right) {
    int64_t s_z_forward_sorted =
        (t->left->to_mul == 0 or (t->left->rev ? t->left->is_backward_sorted
                                               : t->left->is_forward_sorted));
    int64_t s_z_backward_sorted =
        (t->left->to_mul == 0 or (t->left->rev ? t->left->is_forward_sorted
                                               : t->left->is_backward_sorted));
    int64_t s_x_forward_sorted =
        (t->right->to_mul == 0 or
         (t->right->rev ? t->right->is_backward_sorted
                        : t->right->is_forward_sorted));
    int64_t s_x_backward_sorted =
        (t->right->to_mul == 0 or
         (t->right->rev ? t->right->is_forward_sorted
                        : t->right->is_backward_sorted));
    int64_t s_x_first =
        (t->right->rev ? t->right->last : t->right->first) * t->right->to_mul +
        t->right->to_add;
    int64_t s_z_last =
        (t->left->rev ? t->left->first : t->left->last) * t->left->to_mul +
        t->left->to_add;
    int64_t s_z_s = t->left->s;
    int64_t s_x_s = t->right->s;
    (t->s) = t->left->s + t->right->s + 1;
    (t->d) = 1 + (t->left->d > t->right->d ? t->left->d : t->right->d);
    (t->sum) = t->v + t->left->sum * t->left->to_mul +
               t->left->to_add * t->left->s + t->right->sum * t->right->to_mul +
               t->right->to_add * t->right->s;
    (t->is_forward_sorted) = (s_z_forward_sorted and s_x_forward_sorted and
                              s_z_last <= t->v and s_x_first >= t->v);
    (t->is_backward_sorted) = (s_z_backward_sorted and s_x_backward_sorted and
                               s_z_last >= t->v and s_x_first <= t->v);
  } else if (t->left) {
    int64_t s_x_forward_sorted = 1;
    int64_t s_x_backward_sorted = 1;
    int64_t s_z_forward_sorted =
        (t->left->to_mul == 0 or (t->left->rev ? t->left->is_backward_sorted
                                               : t->left->is_forward_sorted));
    int64_t s_z_backward_sorted =
        (t->left->to_mul == 0 or (t->left->rev ? t->left->is_forward_sorted
                                               : t->left->is_backward_sorted));
    int64_t s_z_last =
        (t->left->rev ? t->left->first : t->left->last) * t->left->to_mul +
        t->left->to_add;
    int64_t s_x_first = 0;
    int64_t s_z_s = t->left->s;
    int64_t s_x_s = 0;
    (t->s) = t->left->s + 1;
    (t->d) = t->left->d + 1;
    (t->sum) =
        t->v + t->left->sum * t->left->to_mul + t->left->to_add * t->left->s;
    (t->is_forward_sorted) = (s_z_forward_sorted and s_z_last <= t->v);
    (t->is_backward_sorted) = (s_z_backward_sorted and s_z_last >= t->v);
  } else if (t->right) {
    int64_t s_z_forward_sorted = 1;
    int64_t s_z_backward_sorted = 1;
    int64_t s_x_forward_sorted =
        (t->right->to_mul == 0 or
         (t->right->rev ? t->right->is_backward_sorted
                        : t->right->is_forward_sorted));
    int64_t s_x_backward_sorted =
        (t->right->to_mul == 0 or
         (t->right->rev ? t->right->is_forward_sorted
                        : t->right->is_backward_sorted));
    int64_t s_x_first =
        (t->right->rev ? t->right->last : t->right->first) * t->right->to_mul +
        t->right->to_add;
    int64_t s_z_last = 0;
    int64_t s_z_s = 0;
    int64_t s_x_s = t->right->s;
    (t->s) = t->right->s + 1;
    (t->d) = t->right->d + 1;
    (t->sum) = t->v + t->right->sum * t->right->to_mul +
               t->right->to_add * t->right->s;
    (t->is_forward_sorted) = (s_x_forward_sorted and s_x_first >= t->v);
    (t->is_backward_sorted) = (s_x_backward_sorted and s_x_first <= t->v);
  } else {
    (t->s) = 1;
    (t->d) = 1;
    (t->sum) = t->v;
    (t->is_forward_sorted) = 1;
    (t->is_backward_sorted) = 1;
  }
}

void make(node *t) {
  if (!t) {
    return;
  }
  if (t->to_mul != 1) {
    (t->sum) *= t->to_mul;
    (t->first) *= t->to_mul;
    (t->last) *= t->to_mul;
    (t->v) *= t->to_mul;
    if (t->left) {
      (t->left->to_mul) *= t->to_mul;
      (t->left->to_add) *= t->to_mul;
    }
    if (t->right) {
      (t->right->to_mul) *= t->to_mul;
      (t->right->to_add) *= t->to_mul;
    }
    if (t->to_mul == 0) {
      (t->is_forward_sorted) = 1;
      (t->is_backward_sorted) = 1;
    }
    (t->to_mul) = 1;
  }

  if (t->to_add != 0) {
    (t->sum) += t->to_add * t->s;
    (t->first) += t->to_add;
    (t->last) += t->to_add;
    (t->v) += t->to_add;
    if (t->left) {
      (t->left->to_add) += t->to_add;
    }
    if (t->right) {
      (t->right->to_add) += t->to_add;
    }
    (t->to_add) = 0;
  }

  if (t->rev) {
    node *te = (t->left);
    (t->left) = (t->right);
    (t->right) = te;
    int64_t tl = (t->is_forward_sorted);
    (t->is_forward_sorted) = (t->is_backward_sorted);
    (t->is_backward_sorted) = tl;
    tl = (t->first);
    (t->first) = (t->last);
    (t->last) = tl;
    if (t->left) {
      (t->left->rev) ^= 1;
    }
    if (t->right) {
      (t->right->rev) ^= 1;
    }
    (t->rev) = 0;
  }
}

void left_put(node *t, node *q) {
  (t->left) = q;
  update(t);
}

void right_put(node *t, node *q) {
  (t->right) = q;
  update(t);
}

node *left_get(node *t) {
  make(t->left);
  return t->left;
}

node *right_get(node *t) {
  make(t->right);
  return t->right;
}

node *create(int64_t v) {
  auto t = new node;
  t->v = v;
  t->w = rand();
  update(t);
  return t;
}

int64_t find_index(node *q) {
  auto w = q->p;
  auto q_z = q ? left_get(q) : 0;
  auto q_x = q ? right_get(q) : 0;
  auto q_z_s = q_z ? q_z->s : 0;
  auto q_x_s = q_x ? q_x->s : 0;
  if (w == nullptr) {
    return q_z_s;
  } else if (left_get(w) == q) {
    return find_index(w) - q_x_s - 1;
  } else if (right_get(w) == q) {
    return find_index(w) + q_z_s + 1;
  }
  assert(0);
  return 0;
}

node * begin(node *q) {
  if (!q) {
    return q;
  }
  node *b = q;
  while (left_get(b)) {
    b = b->left;
  }
  return b;
}

node * end(node *q) {
  if (!q) {
    return q;
  }
  node *e = q;
  while (right_get(e)) {
    e = e->right;
  }
  return e;
}

node *merge(node *t1, node *t2) {
  if (!t1) {
    return t2;
  }
  if (!t2) {
    return t1;
  }
  if (t1->w < t2->w) {
    left_put(t2, merge(t1, left_get(t2)));
    return t2;
  } else {
    right_put(t1, merge(right_get(t1), t2));
    return t1;
  }
}

std::pair<node *, node *> split(node *t, int64_t n) {
  if (!t) {
    return {nullptr, nullptr};
  }
  if (n == 0) {
    return {nullptr, t};
  }
  if (n == t->s) {
    return {t, nullptr};
  }
  auto t_z = t ? left_get(t) : 0;
  auto t_x = t ? right_get(t) : 0;
  auto t_z_s = t_z ? t_z->s : 0;
  auto t_x_s = t_x ? t_x->s : 0;
  if (t_z_s < n) {
    auto tmp = split(t_x, n - t_z_s - 1);
    right_put(t, tmp.first);
    auto t2 = tmp.second;
    if (t2) {
      (t2->p) = nullptr;
    }
    return {t, t2};
  } else {
    auto tmp = split(t_z, n);
    auto t1 = tmp.first;
    left_put(t, tmp.second);
    if (t1) {
      (t1->p) = nullptr;
    }
    return {t1, t};
  }
}

int64_t lower_bound(node *q, int64_t d) {
  int64_t t = -1;
  if (!q) {
    t = find_index(begin(q));
  } else if (d <= q->first) {
    t = find_index(begin(q));
  } else if (d > q->last) {
    t = find_index(end(q)) + 1;
  } else {
    assert(q);
    auto w = q;
    w = nullptr;
    while (q) {
      if (q->v >= d) {
        w = q;
        q = left_get(q);
      } else {
        q = right_get(q);
      }
    }
    t = find_index(w);
  }
  return t;
}
int64_t upper_bound(node *q, int64_t d) {
  int64_t t = -1;
  if (!q) {
    t = find_index(begin(q));
  } else if (d < q->first) {
    t = find_index(begin(q));
  } else if (d >= q->last) {
    t = find_index(end(q)) + 1;
  } else {
    assert(q);
    auto w = q;
    w = nullptr;
    while (q) {
      if (q->v > d) {
        w = q;
        q = left_get(q);
      } else {
        q = right_get(q);
      }
    }
    t = find_index(w);
  }
  return t;
}
int64_t forward_sorted_prefix(node *q) {
  int64_t t = -1;
  auto w = q;
  w = nullptr;
  if (!q or q->is_forward_sorted) {
    t = find_index(end(q)) + bool(q);
  } else {
    while (q) {
      auto q_z = q ? left_get(q) : 0;
      auto q_x = q ? right_get(q) : 0;
      auto q_z_s = q_z ? q_z->s : 0;
      auto q_x_s = q_x ? q_x->s : 0;
      if (!q_z or q_z->is_forward_sorted) {
        if (!q_z or q->v >= q_z->last) {
          if (!w or w->v <= q->first) {
            w = q;
          } else {
            t = find_index(w) + 1;
            break;
          }
          q = q_x;
        } else {
          if (!w or w->v <= q->first) {
            w = q;
            t = find_index(w);
            break;
          } else {
            t = find_index(w) + 1;
            break;
          }
        }
      } else {
        q = q_z;
      }
    }
    if (t == -1) {
      t = find_index(w) + 1;
    }
  }
  return t;
}

int64_t backward_sorted_prefix(node *q) {
  int64_t t = -1;
  auto w = q;
  w = nullptr;
  if (!q or q->is_backward_sorted) {
    t = find_index(end(q)) + bool(q);
  } else {
    while (q) {
      auto q_z = q ? left_get(q) : 0;
      auto q_x = q ? right_get(q) : 0;
      auto q_z_s = q_z ? q_z->s : 0;
      auto q_x_s = q_x ? q_x->s : 0;
      if (!q_z or q_z->is_backward_sorted) {
        if (!q_z or q->v <= q_z->last) {
          if (!w or w->v >= q->first) {
            w = q;
          } else {
            t = find_index(w) + 1;
            break;
          }
          q = q_x;
        } else {
          if (!w or w->v >= q->first) {
            w = q;
            t = find_index(w);
            break;
          } else {
            t = find_index(w) + 1;
            break;
          }
        }
      } else {
        q = q_z;
      }
    }
    if (t == -1) {
      t = find_index(w) + 1;
    }
  }
  return t;
}

node *next_permutation(node *s) {
  if (!s) {
    return s;
  }
  (s->rev) ^= 1;
  make(s);
  auto q = forward_sorted_prefix(s);
  (s->rev) ^= 1;
  make(s);
  q = (s ? s->s : 0) - q;
  auto tmp = split(s, q);
  auto t = tmp.first;
  s = tmp.second;
  if (t) {
    auto tmp = split(t, t->s - 1);
    t = tmp.first;
    auto h = tmp.second;
    auto r = h->v;
    s->rev ^= 1;
    make(s);
    auto p = upper_bound(s, r);
    tmp = split(s, p);
    auto left = tmp.first;
    s = tmp.second;
    tmp = split(s, 1);
    auto right = tmp.first;
    s = tmp.second;
    auto tr = right->v;
    right->v = r;
    update(right);
    r = tr;
    s = merge(right, s);
    right = nullptr;
    s = merge(left, s);
    left = nullptr;
    auto c = h;
    c->v = r;
    update(c);
    t = merge(t, c);
    c = nullptr;
    s = merge(t, s);
    t = nullptr;
    return s;
  } else {
    (s->rev) ^= 1;
    make(s);
    return s;
  }
}

node *prev_permutation(node *s) {
  if (!s) {
    return s;
  }
  (s->rev) ^= 1;
  make(s);
  auto q = backward_sorted_prefix(s);
  (s->rev) ^= 1;
  make(s);
  q = (s ? s->s : 0) - q;
  auto tmp = split(s, q);
  auto t = tmp.first;
  s = tmp.second;
  if (t) {
    tmp = split(t, t->s - 1);
    t = tmp.first;
    auto h = tmp.second;
    auto r = h->v;
    auto p = lower_bound(s, r);
    tmp = split(s, p - 1);
    auto left = tmp.first;
    s = tmp.second;
    tmp = split(s, 1);
    auto right = tmp.first;
    s = tmp.second;
    auto tr = right->v;
    (right->v) = r;
    update(right);
    r = tr;
    s = merge(right, s);
    right = nullptr;
    s = merge(left, s);
    left = nullptr;
    auto c = h;
    (c->v) = r;
    update(c);
    t = merge(t, c);
    c = nullptr;
    (s->rev) ^= 1;
    make(s);
    s = merge(t, s);
    t = nullptr;
    return s;
  } else {
    (s->rev) ^= 1;
    make(s);
    return s;
  }
}

int64_t getint() {
  int64_t l;
  std::cin >> l;
  return l;
}

int main() {
  pair<node *, node *> tmp;
  int64_t n = getint();
  node *a = nullptr;
  for (int64_t w = 0; w < n; ++w) {
    a = merge(a, create(getint()));
  }
  int64_t qq = getint();
  for (int64_t w = 0; w < qq; ++w) {
    int64_t q = getint();
    if (q == -1) {
      break;
    }
    if (q == 1) {
      int64_t l = getint(), r = getint() + 1;
      tmp = split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      cout << (s ? s->sum : 0) << '\n';
      s = merge(d, s);
      d = nullptr;
      a = merge(s, a);
      s = nullptr;
    }
    if (q == 2) {
      int64_t right = getint();
      int64_t u = getint();
      int64_t l = u, r = u;
      tmp = split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      assert(!s);
      s = create(right);
      s = merge(d, s);
      d = nullptr;
      a = merge(s, a);
      s = nullptr;
    }
    if (q == 3) {
      int64_t u = getint();
      tmp = split(a, u);
      auto left = tmp.first;
      a = tmp.second;
      tmp = split(a, 1);
      a = tmp.second;
      delete tmp.first;
      a = merge(left, a);
      left = nullptr;
    }
    if (q == 4) {
      int64_t right = getint();
      int64_t l = getint(), r = getint() + 1;
      tmp = split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s ? (s->to_mul) *= 0 : 0;
      s ? (s->to_add) += right : 0;
      make(s);
      s = merge(d, s);
      d = nullptr;
      a = merge(s, a);
      s = nullptr;
    }
    if (q == 5) {
      int64_t right = getint();
      int64_t l = getint(), r = getint() + 1;
      tmp = split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s ? (s->to_add) += right : 0;
      make(s);
      s = merge(d, s);
      d = nullptr;
      a = merge(s, a);
      s = nullptr;
    }
    if (q == 6) {
      int64_t l = getint(), r = getint() + 1;
      tmp = split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s = next_permutation(s);
      s = merge(d, s);
      d = nullptr;
      a = merge(s, a);
      s = nullptr;
    }
    if (q == 7) {
      int64_t l = getint(), r = getint() + 1;
      tmp = split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s = prev_permutation(s);
      s = merge(d, s);
      d = nullptr;
      a = merge(s, a);
      s = nullptr;
    }
  }
  while (a) {
    tmp = split(a, 1);
    auto s = tmp.first;
    a = tmp.second;
    cout << s->v << ' ';
    delete s;
    s = nullptr;
  }
  cout << endl;
}
