#include <algorithm>
#include <iostream>

struct Node {
  int64_t value = 0;
  int64_t priority = 0;
  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;
  int64_t size = 1;
  int64_t rev = 0;
  int64_t first = 0;
  int64_t last = 0;
  int64_t sum = 0;
  int64_t to_add = 0;
  int64_t to_mul = 1;
  int64_t is_ascending = 1;
  int64_t is_descending = 1;
};

void Update(Node *root) {
  if (root->left) {
    (root->left->parent) = root;
    if (root->left->rev) {
      root->first = root->left->last * root->left->to_mul + root->left->to_add;
    } else {
      root->first = root->left->first * root->left->to_mul + root->left->to_add;
    }
  } else {
    root->first = root->value;
  }
  if (root->right) {
    (root->right->parent) = root;
    if (root->right->rev) {
      root->last =
          root->right->first * root->right->to_mul + root->right->to_add;
    } else {
      root->last =
          root->right->last * root->right->to_mul + root->right->to_add;
    }
  } else {
    root->last = root->value;
  }
  if (root->left and root->right) {
    int64_t left_ascending = (root->left->to_mul == 0 or
                              (root->left->rev ? root->left->is_descending
                                               : root->left->is_ascending));
    int64_t left_descending = (root->left->to_mul == 0 or
                               (root->left->rev ? root->left->is_ascending
                                                : root->left->is_descending));
    int64_t right_ascending = (root->right->to_mul == 0 or
                               (root->right->rev ? root->right->is_descending
                                                 : root->right->is_ascending));
    int64_t right_descending =
        (root->right->to_mul == 0 or
         (root->right->rev ? root->right->is_ascending
                           : root->right->is_descending));
    int64_t right_first =
        (root->right->rev ? root->right->last : root->right->first) *
            root->right->to_mul +
        root->right->to_add;
    int64_t left_last =
        (root->left->rev ? root->left->first : root->left->last) *
            root->left->to_mul +
        root->left->to_add;
    root->size = root->left->size + root->right->size + 1;
    root->sum = root->value + root->left->sum * root->left->to_mul +
                root->left->to_add * root->left->size +
                root->right->sum * root->right->to_mul +
                root->right->to_add * root->right->size;
    root->is_ascending =
        (left_ascending and right_ascending and left_last <= root->value and
         right_first >= root->value);
    root->is_descending =
        (left_descending and right_descending and left_last >= root->value and
         right_first <= root->value);
  } else if (root->left) {
    int64_t left_ascending = (root->left->to_mul == 0 or
                              (root->left->rev ? root->left->is_descending
                                               : root->left->is_ascending));
    int64_t left_descending = (root->left->to_mul == 0 or
                               (root->left->rev ? root->left->is_ascending
                                                : root->left->is_descending));
    int64_t left_last =
        (root->left->rev ? root->left->first : root->left->last) *
            root->left->to_mul +
        root->left->to_add;
    root->size = root->left->size + 1;
    root->sum = root->value + root->left->sum * root->left->to_mul +
                root->left->to_add * root->left->size;
    root->is_ascending = (left_ascending and left_last <= root->value);
    root->is_descending = (left_descending and left_last >= root->value);
  } else if (root->right) {
    int64_t right_ascending = (root->right->to_mul == 0 or
                               (root->right->rev ? root->right->is_descending
                                                 : root->right->is_ascending));
    int64_t right_descending =
        (root->right->to_mul == 0 or
         (root->right->rev ? root->right->is_ascending
                           : root->right->is_descending));
    int64_t right_first =
        (root->right->rev ? root->right->last : root->right->first) *
            root->right->to_mul +
        root->right->to_add;
    root->size = root->right->size + 1;
    root->sum = root->value + root->right->sum * root->right->to_mul +
                root->right->to_add * root->right->size;
    root->is_ascending = (right_ascending and right_first >= root->value);
    root->is_descending = (right_descending and right_first <= root->value);
  } else {
    root->size = 1;
    root->sum = root->value;
    root->is_ascending = 1;
    root->is_descending = 1;
  }
}

void Make(Node *root) {
  if (!root) {
    return;
  }
  if (root->to_mul != 1) {
    root->sum *= root->to_mul;
    root->first *= root->to_mul;
    root->last *= root->to_mul;
    root->value *= root->to_mul;
    if (root->left) {
      (root->left->to_mul) *= root->to_mul;
      (root->left->to_add) *= root->to_mul;
    }
    if (root->right) {
      (root->right->to_mul) *= root->to_mul;
      (root->right->to_add) *= root->to_mul;
    }
    if (root->to_mul == 0) {
      root->is_ascending = 1;
      root->is_descending = 1;
    }
    root->to_mul = 1;
  }

  if (root->to_add != 0) {
    root->sum += root->to_add * root->size;
    root->first += root->to_add;
    root->last += root->to_add;
    root->value += root->to_add;
    if (root->left) {
      (root->left->to_add) += root->to_add;
    }
    if (root->right) {
      (root->right->to_add) += root->to_add;
    }
    root->to_add = 0;
  }

  if (root->rev) {
    Node *te = (root->left);
    root->left = (root->right);
    root->right = te;
    int64_t tl = (root->is_ascending);
    root->is_ascending = (root->is_descending);
    root->is_descending = tl;
    std::swap(root->first, root->last);
    if (root->left) {
      (root->left->rev) ^= 1;
    }
    if (root->right) {
      (root->right->rev) ^= 1;
    }
    root->rev = 0;
  }
}

void LeftPut(Node *root, Node *q) {
  root->left = q;
  Update(root);
}

void RightPut(Node *root, Node *q) {
  root->right = q;
  Update(root);
}

Node *LeftGet(Node *root) {
  Make(root->left);
  return root->left;
}

Node *RightGet(Node *root) {
  Make(root->right);
  return root->right;
}

Node *Create(int64_t value) {
  auto root = new Node;
  root->value = value;
  root->priority = rand();
  Update(root);
  return root;
}

int64_t FindIndex(Node *root) {
  auto w = root->parent;
  auto left = root ? LeftGet(root) : nullptr;
  auto right = root ? RightGet(root) : nullptr;
  auto left_size = left ? left->size : 0;
  auto right_size = right ? right->size : 0;
  if (w == nullptr) {
    return left_size;
  } else if (LeftGet(w) == root) {
    return FindIndex(w) - right_size - 1;
  } else if (RightGet(w) == root) {
    return FindIndex(w) + left_size + 1;
  }
  return 0;
}

Node *Merge(Node *t1, Node *t2) {
  if (!t1) {
    return t2;
  }
  if (!t2) {
    return t1;
  }
  if (t1->priority < t2->priority) {
    LeftPut(t2, Merge(t1, LeftGet(t2)));
    return t2;
  } else {
    RightPut(t1, Merge(RightGet(t1), t2));
    return t1;
  }
}

std::pair<Node *, Node *> Split(Node *root, int64_t n) {
  if (!root) {
    return {nullptr, nullptr};
  }
  if (n == 0) {
    return {nullptr, root};
  }
  if (n == root->size) {
    return {root, nullptr};
  }
  auto left = root ? LeftGet(root) : nullptr;
  auto right = root ? RightGet(root) : nullptr;
  auto left_size = left ? left->size : 0;
  if (left_size < n) {
    auto tmp = Split(right, n - left_size - 1);
    RightPut(root, tmp.first);
    auto t2 = tmp.second;
    if (t2) {
      t2->parent = nullptr;
    }
    return {root, t2};
  } else {
    auto tmp = Split(left, n);
    auto t1 = tmp.first;
    LeftPut(root, tmp.second);
    if (t1) {
      t1->parent = nullptr;
    }
    return {t1, root};
  }
}

int64_t LowerBound(Node *root, int64_t d) {
  int64_t ret = -1;
  if (!root) {
    ret = 0;
  } else if (d <= root->first) {
    ret = 0;
  } else if (d > root->last) {
    ret = (root ? root->size : 0);
  } else {
    auto w = root;
    w = nullptr;
    while (root) {
      if (root->value >= d) {
        w = root;
        root = LeftGet(root);
      } else {
        root = RightGet(root);
      }
    }
    ret = FindIndex(w);
  }
  return ret;
}

int64_t UpperBound(Node *root, int64_t d) {
  int64_t ret = -1;
  if (!root) {
    ret = 0;
  } else if (d < root->first) {
    ret = 0;
  } else if (d >= root->last) {
    ret = (root ? root->size : 0);
  } else {
    auto w = root;
    w = nullptr;
    while (root) {
      if (root->value > d) {
        w = root;
        root = LeftGet(root);
      } else {
        root = RightGet(root);
      }
    }
    ret = FindIndex(w);
  }
  return ret;
}

int64_t AscendingPrefix(Node *root) {
  int64_t ret = -1;
  auto w = root;
  w = nullptr;
  if (!root or root->is_ascending) {
    ret = (root ? root->size : 0);
  } else {
    while (root) {
      auto left = root ? LeftGet(root) : nullptr;
      auto right = root ? RightGet(root) : nullptr;
      if (!left or left->is_ascending) {
        if (!left or root->value >= left->last) {
          if (!w or w->value <= root->first) {
            w = root;
          } else {
            ret = FindIndex(w) + 1;
            break;
          }
          root = right;
        } else {
          if (!w or w->value <= root->first) {
            w = root;
            ret = FindIndex(w);
            break;
          }
          ret = FindIndex(w) + 1;
          break;
        }
      } else {
        root = left;
      }
    }
    if (ret == -1) {
      ret = FindIndex(w) + 1;
    }
  }
  return ret;
}

int64_t DescendingPrefix(Node *root) {
  int64_t ret = -1;
  auto w = root;
  w = nullptr;
  if (!root or root->is_descending) {
    ret = (root ? root->size : 0);
  } else {
    while (root) {
      auto left = root ? LeftGet(root) : nullptr;
      auto right = root ? RightGet(root) : nullptr;
      if (!left or left->is_descending) {
        if (!left or root->value <= left->last) {
          if (!w or w->value >= root->first) {
            w = root;
          } else {
            ret = FindIndex(w) + 1;
            break;
          }
          root = right;
        } else {
          if (!w or w->value >= root->first) {
            w = root;
            ret = FindIndex(w);
            break;
          } else {
            ret = FindIndex(w) + 1;
            break;
          }
        }
      } else {
        root = left;
      }
    }
    if (ret == -1) {
      ret = FindIndex(w) + 1;
    }
  }
  return ret;
}

Node *NextPermutation(Node *root) {
  if (!root) {
    return root;
  }
  root->rev ^= 1;
  Make(root);
  auto s = AscendingPrefix(root);
  root->rev ^= 1;
  Make(root);
  s = (root ? root->size : 0) - s;
  auto tmp = Split(root, s);
  auto t = tmp.first;
  root = tmp.second;
  if (t) {
    tmp = Split(t, t->size - 1);
    t = tmp.first;
    auto h = tmp.second;
    auto r = h->value;
    root->rev ^= 1;
    Make(root);
    auto p = UpperBound(root, r);
    tmp = Split(root, p);
    auto z = tmp.first;
    root = tmp.second;
    tmp = Split(root, 1);
    auto x = tmp.first;
    root = tmp.second;
    std::swap(x->value, r);
    Update(x);
    root = Merge(x, root);
    x = nullptr;
    root = Merge(z, root);
    z = nullptr;
    auto c = h;
    c->value = r;
    Update(c);
    t = Merge(t, c);
    c = nullptr;
    root = Merge(t, root);
    t = nullptr;
    return root;
  }
  root->rev ^= 1;
  Make(root);
  return root;
}

Node *PrevPermutation(Node *root) {
  if (!root) {
    return root;
  }
  root->rev ^= 1;
  Make(root);
  auto s = DescendingPrefix(root);
  root->rev ^= 1;
  Make(root);
  s = (root ? root->size : 0) - s;
  auto tmp = Split(root, s);
  auto t = tmp.first;
  root = tmp.second;
  if (t) {
    tmp = Split(t, t->size - 1);
    t = tmp.first;
    auto h = tmp.second;
    auto r = h->value;
    auto p = LowerBound(root, r);
    tmp = Split(root, p - 1);
    auto z = tmp.first;
    root = tmp.second;
    tmp = Split(root, 1);
    auto x = tmp.first;
    root = tmp.second;
    std::swap(x->value, r);
    Update(x);
    root = Merge(x, root);
    x = nullptr;
    root = Merge(z, root);
    z = nullptr;
    auto c = h;
    c->value = r;
    Update(c);
    t = Merge(t, c);
    c = nullptr;
    root->rev ^= 1;
    Make(root);
    root = Merge(t, root);
    t = nullptr;
    return root;
  }
  root->rev ^= 1;
  Make(root);
  return root;
}

int64_t GetInt() {
  int64_t l;
  std::cin >> l;
  return l;
}

int main() {
  std::pair<Node *, Node *> tmp;
  int64_t n = GetInt();
  Node *a = nullptr;
  for (int64_t w = 0; w < n; ++w) {
    a = Merge(a, Create(GetInt()));
  }
  int64_t q = GetInt();
  for (int64_t w = 0; w < q; ++w) {
    int64_t t = GetInt();
    if (t == -1) {
      break;
    }
    if (t == 1) {
      int64_t l = GetInt(), r = GetInt() + 1;
      tmp = Split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = Split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      std::cout << (s ? s->sum : 0) << '\n';
      s = Merge(d, s);
      d = nullptr;
      a = Merge(s, a);
      s = nullptr;
    }
    if (t == 2) {
      int64_t f = GetInt();
      int64_t u = GetInt();
      int64_t l = u, r = u;
      tmp = Split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = Split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s = Create(f);
      s = Merge(d, s);
      d = nullptr;
      a = Merge(s, a);
      s = nullptr;
    }
    if (t == 3) {
      int64_t u = GetInt();
      tmp = Split(a, u);
      auto s = tmp.first;
      a = tmp.second;
      tmp = Split(a, 1);
      a = tmp.second;
      delete tmp.first;
      a = Merge(s, a);
      s = nullptr;
    }
    if (t == 4) {
      int64_t f = GetInt();
      int64_t l = GetInt(), r = GetInt() + 1;
      tmp = Split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = Split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s ? (s->to_mul) *= 0 : 0;
      s ? (s->to_add) += f : 0;
      Make(s);
      s = Merge(d, s);
      d = nullptr;
      a = Merge(s, a);
      s = nullptr;
    }
    if (t == 5) {
      int64_t f = GetInt();
      int64_t l = GetInt(), r = GetInt() + 1;
      tmp = Split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = Split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s ? (s->to_add) += f : 0;
      Make(s);
      s = Merge(d, s);
      d = nullptr;
      a = Merge(s, a);
      s = nullptr;
    }
    if (t == 6) {
      int64_t l = GetInt(), r = GetInt() + 1;
      tmp = Split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = Split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s = NextPermutation(s);
      s = Merge(d, s);
      d = nullptr;
      a = Merge(s, a);
      s = nullptr;
    }
    if (t == 7) {
      int64_t l = GetInt(), r = GetInt() + 1;
      tmp = Split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = Split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s = PrevPermutation(s);
      s = Merge(d, s);
      d = nullptr;
      a = Merge(s, a);
      s = nullptr;
    }
  }
  while (a) {
    tmp = Split(a, 1);
    auto s = tmp.first;
    a = tmp.second;
    std::cout << s->value << ' ';
    delete s;
    s = nullptr;
  }
  std::cout << std::endl;
}
