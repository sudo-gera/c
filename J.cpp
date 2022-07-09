#include <iostream>
using namespace std;

struct Tree {
  Tree *left = 0;
  Tree *right = 0;
  long data = 0;
  Tree *prev = 0;
  long has_value = 0;
  long len = 0;
  long depth = 0;
};

struct Iter {
  Tree *p = 0;
  long l = 0;
};

void Del(Tree &s) {
  if (s.left) {
    Del(s.left[0]);
    delete s.left;
  }
  if (s.right) {
    Del(s.right[0]);
    delete s.right;
  }
}

void Update(Tree &s, uint64_t c = 1) {
  if (c == 0) {
    return;
  }
  s.len = s.has_value;
  if (s.left && s.right) {
    Update(s.left[0], c - 1);
    Update(s.right[0], c - 1);
    s.depth = std::max(s.left->depth, s.right->depth) + 1;
    s.len += s.left->len;
    s.left->prev = &s;
    s.len += s.right->len;
    s.right->prev = &s;
  } else if (s.left) {
    Update(s.left[0], c - 1);
    s.depth = s.left->depth + 1;
    s.len += s.left->len;
    s.left->prev = &s;
  } else if (s.right) {
    Update(s.right[0], c - 1);
    s.depth = s.right->depth + 1;
    s.len += s.right->len;
    s.right->prev = &s;
  } else {
    s.depth = 1;
  }
}

void Add(Iter &s, long n) {
  while (n != 0 || ((0 > s.l || s.l >= s.p->has_value) && s.p->prev)) {
    if (0 <= s.l && s.l < s.p->has_value) {
      if (n > 0) {
        if ((s.p->right ? s.p->right->len : 0) < n) {
          n -= (s.p->right ? s.p->right->len : 0) + 1;
          s.l++;
        } else {
          s.p = s.p->right;
          s.l = 0;
          n -= s.p->left ? s.p->left->len : 0;
          n -= 1;
        }
      } else {
        if ((s.p->left ? s.p->left->len : 0) < -n) {
          n += (s.p->left ? s.p->left->len : 0) + 1;
          s.l--;
        } else {
          s.p = s.p->left;
          s.l = s.p->has_value - 1;
          n += s.p->right ? s.p->right->len : 0;
          n += 1;
        }
      }
    } else {
      if (s.p->prev) {
        long w = 0;
        if (s.p->prev->left != s.p) {
          ++w;
        }
        s.p = s.p->prev;
        if (s.l < 0) {
          s.l = w - 1;
        } else {
          s.l = w;
        }
      } else {
        if (s.l < -1) {
          n += s.l + 1;
          s.l = -1;
        } else if (s.l > s.p->has_value) {
          n += s.l - s.p->has_value;
          s.l = s.p->has_value;
        } else if (s.l == -1) {
          if (n > 0) {
            n -= s.p->left ? s.p->left->len : 0;
            n--;
            s.l = 0;
          } else {
            s.l += n;
            n = 0;
          }
        } else if (s.l == s.p->has_value) {
          if (n < 0) {
            if (s.p->has_value) {
              n += s.p->right ? s.p->right->len : 0;
            } else {
              n += s.p->left ? s.p->left->len : 0;
            }
            n++;
            s.l = s.p->has_value - 1;
          } else {
            s.l += n;
            n = 0;
          }
        }
      }
    }
  }
}

long Get(Iter s, long q) {
  auto t = s;
  Add(t, q);
  return t.p->data;
}

bool IsBegin(Iter s) {
  auto t = s;
  Add(t, -1);
  return t.l == -1;
}

bool IsEnd(Iter s) { return s.l == s.p->has_value; }

auto Begin(Tree &s) {
  Iter t;
  t.p = &s;
  t.l = -1;
  Add(t, 1);
  return t;
}
auto End(Tree &s) {
  Iter t;
  t.p = &s;
  t.l = s.has_value;
  return t;
}

long Size(Tree &s) { return s.len; }

auto LowerBound(Tree &s, const long &val) {
  if (!s.has_value) {
    return Begin(s);
  }
  if (s.data < val) {
    if (s.right) {
      return LowerBound(s.right[0], val);
    } else {
      Iter p;
      p.p = &s;
      p.l = 0;
      Add(p, 1);
      return p;
    }
  } else if (val < s.data) {
    if (s.left) {
      return LowerBound(s.left[0], val);
    } else {
      Iter p;
      p.p = &s;
      p.l = 0;
      return p;
    }
  }
  Iter p;
  p.p = &s;
  p.l = 0;
  return p;
}

auto UpperBound(Tree &s, const long &val) {
  auto p = LowerBound(s, val);
  if (!IsEnd(p) && Get(p, 0) == val) {
    Add(p, 1);
  }
  return p;
}

auto Find(Tree &s, const long &val) {
  auto p = LowerBound(s, val);
  if (!IsEnd(p) && Get(p, 0) == val) {
    return p;
  }
  return End(s);
}

void Left(Tree &s) {
  std::swap(s.left, s.right->left);
  std::swap(s.left, s.right);
  std::swap(s.right, s.left->right);
  std::swap(s.data, s.left->data);
}
void Right(Tree &s) {
  std::swap(s.right, s.left->right);
  std::swap(s.left, s.right);
  std::swap(s.left, s.right->left);
  std::swap(s.data, s.right->data);
}

void Insert(Tree &s, const long &val) {
  if (!s.has_value) {
    s.has_value = 1;
    s.data = val;
    Update(s);
  } else if (val < s.data) {
    if (s.left) {
      Insert(s.left[0], val);
      if (s.left->depth == (s.right ? s.right->depth : 0) + 2) {
        if ((s.left->left ? s.left->left->depth : 0) <
            (s.left->right ? s.left->right->depth : 0)) {
          Left(s.left[0]);
        }
        Right(s);
        Update(s, 3);
      }
    } else {
      s.left = new Tree();
      s.left->data = val;
      s.left->has_value = 1;
      Update(s.left[0]);
    }
  } else if (s.data < val) {
    if (s.right) {
      Insert(s.right[0], val);
      if (s.right->depth == (s.left ? s.left->depth : 0) + 2) {
        if ((s.right->left ? s.right->left->depth : 0) >
            (s.right->right ? s.right->right->depth : 0)) {
          Right(s.right[0]);
        }
        Left(s);
        Update(s, 3);
      }
    } else {
      s.right = new Tree();
      s.right->data = val;
      s.right->has_value = 1;
      Update(s.right[0]);
    }
  }
  Update(s);
}

void EraseDeep(Tree &s, __uint128_t p) {
  if (s.depth == 1) {
    s.has_value = 0;
  } else if ((p & 2) == 0) {
    EraseDeep(s.left[0], p >> 1);
    if (s.left->has_value == 0) {
      delete s.left;
      s.left = nullptr;
    }
    if ((s.right ? s.right->depth : 0) == (s.left ? s.left->depth : 0) + 2) {
      if ((s.right->left ? s.right->left->depth : 0) >
          (s.right->right ? s.right->right->depth : 0)) {
        Right(s.right[0]);
      }
      Left(s);
      Update(s, 3);
    }
  } else {
    EraseDeep(s.right[0], p >> 1);
    if (s.right->has_value == 0) {
      delete s.right;
      s.right = nullptr;
    }
    if ((s.left ? s.left->depth : 0) == (s.right ? s.right->depth : 0) + 2) {
      if ((s.left->left ? s.left->left->depth : 0) <
          (s.left->right ? s.left->right->depth : 0)) {
        Left(s.left[0]);
      }
      Right(s);
      Update(s, 3);
    }
  }
  Update(s);
}

void Erase(Tree &s, const long &val) {
  auto t = Find(s, val);
  if (!IsEnd(t)) {
    while (t.p->depth > 1) {
      auto p = t;
      Add(t, 1);
      p.p->data = Get(t, 0);
      if (IsEnd(t)) {
        Add(t, -1);
        while (t.p->depth > 1) {
          auto p = t;
          Add(t, -1);
          p.p->data = Get(t, 0);
        }
      }
    }
    __uint128_t p = 0;
    auto y = t.p;
    while (y->prev) {
      p |= y->prev->right == y;
      p <<= 1;
      y = y->prev;
    }
    EraseDeep(s, p);
  }
}

int main() {
  string s;
  Tree d;
  while (cin >> s) {
    long q;
    cin >> q;
    if (s[0] == 'i') {
      Insert(d, q);
    } else if (s[0] == 'd') {
      Erase(d, q);
    } else if (s[0] == 'e') {
      cout << (!IsEnd(Find(d, q)) ? "true" : "false") << endl;
    } else if (s[0] == 'n') {
      auto t = UpperBound(d, q);
      if (!Size(d) || IsEnd(t)) {
        cout << "none" << endl;
      } else {
        cout << Get(t, 0) << endl;
      }
    } else if (s[0] == 'p') {
      auto t = LowerBound(d, q);
      if (!Size(d) || IsBegin(t)) {
        cout << "none" << endl;
      } else {
        cout << Get(t, -1) << endl;
      }
    } else if (s[0] == 'k') {
      if (q < 0 || q >= Size(d)) {
        cout << "none" << endl;
      } else {
        cout << Get(Begin(d), q) << endl;
      }
    } else {
      break;
    }
  }
  Del(d);
}
