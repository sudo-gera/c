#include <bits/stdc++.h>
using namespace std;

#ifdef assert_m
#define assert assert_m
#endif

struct el {
  int64_t v = 0;
  int64_t w = 0;
  el const *const z = nullptr;
  el const *const x = nullptr;
  el const *const p = nullptr;
  int64_t const s = 1;
  int64_t const d = 1;
  int64_t const rev = 0;
  int64_t const first = 0;
  int64_t const last = 0;
  int64_t const sum = 0;
  int64_t const to_add = 0;
  int64_t const to_mul = 1;
  int64_t const is_forward_sorted = 1;
  int64_t const is_backward_sorted = 1;
};

void update(const el *t) {
  if (t->z) {
    const_cast<const el *&>(t->z->p) = t;
    if (t->z->rev) {
      const_cast<int64_t &>(t->first) =
          t->z->last * t->z->to_mul + t->z->to_add;
    } else {
      const_cast<int64_t &>(t->first) =
          t->z->first * t->z->to_mul + t->z->to_add;
    }
  } else {
    const_cast<int64_t &>(t->first) = t->v;
  }
  if (t->x) {
    const_cast<const el *&>(t->x->p) = t;
    if (t->x->rev) {
      const_cast<int64_t &>(t->last) =
          t->x->first * t->x->to_mul + t->x->to_add;
    } else {
      const_cast<int64_t &>(t->last) = t->x->last * t->x->to_mul + t->x->to_add;
    }
  } else {
    const_cast<int64_t &>(t->last) = t->v;
  }
  if (t->z and t->x) {
    int64_t s_z_forward_sorted =
        (t->z->to_mul == 0 or
         (t->z->rev ? t->z->is_backward_sorted : t->z->is_forward_sorted));
    int64_t s_z_backward_sorted =
        (t->z->to_mul == 0 or
         (t->z->rev ? t->z->is_forward_sorted : t->z->is_backward_sorted));
    int64_t s_x_forward_sorted =
        (t->x->to_mul == 0 or
         (t->x->rev ? t->x->is_backward_sorted : t->x->is_forward_sorted));
    int64_t s_x_backward_sorted =
        (t->x->to_mul == 0 or
         (t->x->rev ? t->x->is_forward_sorted : t->x->is_backward_sorted));
    int64_t s_x_first =
        (t->x->rev ? t->x->last : t->x->first) * t->x->to_mul + t->x->to_add;
    int64_t s_z_last =
        (t->z->rev ? t->z->first : t->z->last) * t->z->to_mul + t->z->to_add;
    int64_t s_z_s = t->z->s;
    int64_t s_x_s = t->x->s;
    const_cast<int64_t &>(t->s) = t->z->s + t->x->s + 1;
    const_cast<int64_t &>(t->d) = 1 + (t->z->d > t->x->d ? t->z->d : t->x->d);
    const_cast<int64_t &>(t->sum) =
        t->v + t->z->sum * t->z->to_mul + t->z->to_add * t->z->s +
        t->x->sum * t->x->to_mul + t->x->to_add * t->x->s;
    const_cast<int64_t &>(t->is_forward_sorted) =
        (s_z_forward_sorted and s_x_forward_sorted and s_z_last <= t->v and
         s_x_first >= t->v);
    const_cast<int64_t &>(t->is_backward_sorted) =
        (s_z_backward_sorted and s_x_backward_sorted and s_z_last >= t->v and
         s_x_first <= t->v);
  } else if (t->z) {
    int64_t s_x_forward_sorted = 1;
    int64_t s_x_backward_sorted = 1;
    int64_t s_z_forward_sorted =
        (t->z->to_mul == 0 or
         (t->z->rev ? t->z->is_backward_sorted : t->z->is_forward_sorted));
    int64_t s_z_backward_sorted =
        (t->z->to_mul == 0 or
         (t->z->rev ? t->z->is_forward_sorted : t->z->is_backward_sorted));
    int64_t s_z_last =
        (t->z->rev ? t->z->first : t->z->last) * t->z->to_mul + t->z->to_add;
    int64_t s_x_first = 0;
    int64_t s_z_s = t->z->s;
    int64_t s_x_s = 0;
    const_cast<int64_t &>(t->s) = t->z->s + 1;
    const_cast<int64_t &>(t->d) = t->z->d + 1;
    const_cast<int64_t &>(t->sum) =
        t->v + t->z->sum * t->z->to_mul + t->z->to_add * t->z->s;
    const_cast<int64_t &>(t->is_forward_sorted) =
        (s_z_forward_sorted and s_z_last <= t->v);
    const_cast<int64_t &>(t->is_backward_sorted) =
        (s_z_backward_sorted and s_z_last >= t->v);
  } else if (t->x) {
    int64_t s_z_forward_sorted = 1;
    int64_t s_z_backward_sorted = 1;
    int64_t s_x_forward_sorted =
        (t->x->to_mul == 0 or
         (t->x->rev ? t->x->is_backward_sorted : t->x->is_forward_sorted));
    int64_t s_x_backward_sorted =
        (t->x->to_mul == 0 or
         (t->x->rev ? t->x->is_forward_sorted : t->x->is_backward_sorted));
    int64_t s_x_first =
        (t->x->rev ? t->x->last : t->x->first) * t->x->to_mul + t->x->to_add;
    int64_t s_z_last = 0;
    int64_t s_z_s = 0;
    int64_t s_x_s = t->x->s;
    const_cast<int64_t &>(t->s) = t->x->s + 1;
    const_cast<int64_t &>(t->d) = t->x->d + 1;
    const_cast<int64_t &>(t->sum) =
        t->v + t->x->sum * t->x->to_mul + t->x->to_add * t->x->s;
    const_cast<int64_t &>(t->is_forward_sorted) =
        (s_x_forward_sorted and s_x_first >= t->v);
    const_cast<int64_t &>(t->is_backward_sorted) =
        (s_x_backward_sorted and s_x_first <= t->v);
  } else {
    const_cast<int64_t &>(t->s) = 1;
    const_cast<int64_t &>(t->d) = 1;
    const_cast<int64_t &>(t->sum) = t->v;
    const_cast<int64_t &>(t->is_forward_sorted) = 1;
    const_cast<int64_t &>(t->is_backward_sorted) = 1;
  }
}

void make(const el *t) {
  if (!t) {
    return;
  }
  if (t->to_mul != 1) {
    const_cast<int64_t &>(t->sum) *= t->to_mul;
    const_cast<int64_t &>(t->first) *= t->to_mul;
    const_cast<int64_t &>(t->last) *= t->to_mul;
    const_cast<int64_t &>(t->v) *= t->to_mul;
    if (t->z) {
      const_cast<int64_t &>(t->z->to_mul) *= t->to_mul;
      const_cast<int64_t &>(t->z->to_add) *= t->to_mul;
    }
    if (t->x) {
      const_cast<int64_t &>(t->x->to_mul) *= t->to_mul;
      const_cast<int64_t &>(t->x->to_add) *= t->to_mul;
    }
    if (t->to_mul == 0) {
      const_cast<int64_t &>(t->is_forward_sorted) = 1;
      const_cast<int64_t &>(t->is_backward_sorted) = 1;
    }
    const_cast<int64_t &>(t->to_mul) = 1;
  }

  if (t->to_add != 0) {
    const_cast<int64_t &>(t->sum) += t->to_add * t->s;
    const_cast<int64_t &>(t->first) += t->to_add;
    const_cast<int64_t &>(t->last) += t->to_add;
    const_cast<int64_t &>(t->v) += t->to_add;
    if (t->z) {
      const_cast<int64_t &>(t->z->to_add) += t->to_add;
    }
    if (t->x) {
      const_cast<int64_t &>(t->x->to_add) += t->to_add;
    }
    const_cast<int64_t &>(t->to_add) = 0;
  }

  if (t->rev) {
    const el *te = const_cast<const el *&>(t->z);
    const_cast<const el *&>(t->z) = const_cast<const el *&>(t->x);
    const_cast<const el *&>(t->x) = te;
    int64_t tl = const_cast<int64_t &>(t->is_forward_sorted);
    const_cast<int64_t &>(t->is_forward_sorted) =
        const_cast<int64_t &>(t->is_backward_sorted);
    const_cast<int64_t &>(t->is_backward_sorted) = tl;
    tl = const_cast<int64_t &>(t->first);
    const_cast<int64_t &>(t->first) = const_cast<int64_t &>(t->last);
    const_cast<int64_t &>(t->last) = tl;
    if (t->z) {
      const_cast<int64_t &>(t->z->rev) ^= 1;
    }
    if (t->x) {
      const_cast<int64_t &>(t->x->rev) ^= 1;
    }
    const_cast<int64_t &>(t->rev) = 0;
  }
}

void z_put(const el *t, const el *q) {
  const_cast<const el *&>(t->z) = q;
  update(t);
}

void x_put(const el *t, const el *q) {
  const_cast<const el *&>(t->x) = q;
  update(t);
}

const el *z_get(const el *t) {
  make(t->z);
  return t->z;
}

const el *x_get(const el *t) {
  make(t->x);
  return t->x;
}

const el* create(int64_t v){
  auto t=new el;
  t->v=v;
  t->w=rand();
  update(t);
  return t;
}

int64_t nz_find_index(const el *q) {
  auto w = q->p;
  auto q_z = q ? z_get(q) : 0;auto q_x = q ? x_get(q) : 0;auto q_z_s = q_z ? q_z->s : 0;auto q_x_s = q_x ? q_x->s : 0;;
  if (w == nullptr) {
    return q_z_s;
  } else if (z_get(w) == q) {
    return nz_find_index(w) - q_x_s - 1;
  } else if (x_get(w) == q) {
    return nz_find_index(w) + q_z_s + 1;
  }
  assert(0);
  return 0;
}

const el *get_by_index(const el *s, int64_t n) {
  if (!s) {
    return nullptr;
  }
  auto s_z = s ? z_get(s) : 0;auto s_x = s ? x_get(s) : 0;auto s_z_s = s_z ? s_z->s : 0;auto s_x_s = s_x ? s_x->s : 0;;
  if (s_z == nullptr) {
    if (n == 0) {
      return s;
    } else {
      return get_by_index(s_x, n - 1);
    }
  } else {
    if (n == s_z_s) {
      return s;
    }
    if (n < s_z_s) {
      return get_by_index(s_z, n);
    }
    if (n > s_z_s) {
      return get_by_index(s_x, n - s_z_s - 1);
    }
  }
  assert(0);
  return (el *)(nullptr);
}

std::pair<const el *, int64_t> add(std::pair<const el *, int64_t> qn,int64_t o=0) {
  auto[q,n]=qn;
  n+=o;
  if (!q){
    return qn;
  }
  o = 0;
  auto q_z = q ? z_get(q) : 0;auto q_x = q ? x_get(q) : 0;auto q_z_s = q_z ? q_z->s : 0;auto q_x_s = q_x ? q_x->s : 0;;
  while (n) {
    auto w = q->p;
    auto w_z = w ? z_get(w) : 0;auto w_x = w ? x_get(w) : 0;auto w_z_s = w_z ? w_z->s : 0;auto w_x_s = w_x ? w_x->s : 0;;
    if (n > 0) {
      if (q_x_s >= n) {
        n = n - 1;
        q = get_by_index(q_x, n);
        break;
      } else {
        if (w == nullptr) {
          o += n - q_x_s;
          n = q_x_s;
          continue;
        } else if (w_z == q) {
          n = -q_x_s - 1 + n;
          q = w;
          q_x = w_x;
          q_z = w_z;
          continue;
        } else if (w_x == q) {
          n = q_z_s + 1 + n;
          q = w;
          q_x = w_x;
          q_z = w_z;
          continue;
        }
        assert(0);
      }
    } else if (n < 0) {
      if (-q_z_s <= n) {
        n = q_z_s + n;
        q = get_by_index(q_z, n);
        break;
      } else {
        if (w == nullptr) {
          o += n + q_z_s;
          n = -q_z_s;
          continue;
        } else if (w_z == q) {
          n = -q_x_s - 1 + n;
          q = w;
          q_x = w_x;
          q_z = w_z;
          continue;
        } else if (w_x == q) {
          n = q_z_s + 1 + n;
          q = w;
          q_x = w_x;
          q_z = w_z;
          continue;
        }
        assert(0);
      }
    }
  }
  return {q, o};
}

int64_t find_index(pair<const el*,int64_t> t){
  return nz_find_index(t.first) + t.second;
}

void check(const el *s) {
#if !__has_include("d")
  return;
#endif
  if (!s) {
    return;
  }
  check(s->z);
  check(s->x);
  assert(s->rev < 2);
  if (s->z) {
    assert(s->z->p == s);
    assert(s->z->w <= s->w);
    if (s->z->rev) {
      assert(s->first == s->z->last * s->z->to_mul + s->z->to_add);
    } else {
      assert(s->first == s->z->first * s->z->to_mul + s->z->to_add);
    }
  } else {
    assert(s->first == s->v);
  }
  if (s->x) {
    assert(s->x->p == s);
    assert(s->x->w <= s->w);
    if (s->x->rev) {
      assert(s->last == s->x->first * s->x->to_mul + s->x->to_add);
    } else {
      assert(s->last == s->x->last * s->x->to_mul + s->x->to_add);
    }
  } else {
    assert(s->last == s->v);
  }
  if (s->z and s->x) {
    assert(s->z->s + s->x->s + 1 == s->s);
    assert(s->d == 1 + std::max(s->z->d, s->x->d));
    assert(s->sum == s->v + s->z->sum * s->z->to_mul + s->z->to_add * s->z->s +
                         s->x->sum * s->x->to_mul + s->x->to_add * s->x->s);
    assert(
        (s->is_forward_sorted) ==
        ((s->z->to_mul == 0 or
          (s->z->rev ? s->z->is_backward_sorted : s->z->is_forward_sorted)) and
         (s->x->to_mul == 0 or
          (s->x->rev ? s->x->is_backward_sorted : s->x->is_forward_sorted)) and
         (s->z->rev ? s->z->first : s->z->last) * s->z->to_mul + s->z->to_add <=
             s->v and
         (s->x->rev ? s->x->last : s->x->first) * s->x->to_mul + s->x->to_add >=
             s->v));
    assert(
        (s->is_backward_sorted) ==
        ((s->z->to_mul == 0 or
          (s->z->rev ? s->z->is_forward_sorted : s->z->is_backward_sorted)) and
         (s->x->to_mul == 0 or
          (s->x->rev ? s->x->is_forward_sorted : s->x->is_backward_sorted)) and
         (s->z->rev ? s->z->first : s->z->last) * s->z->to_mul + s->z->to_add >=
             s->v and
         (s->x->rev ? s->x->last : s->x->first) * s->x->to_mul + s->x->to_add <=
             s->v));
  } else if (s->z) {
    assert(s->z->s + 1 == s->s);
    assert(s->z->d + 1 == s->d);
    assert(s->sum == s->v + s->z->sum * s->z->to_mul + s->z->to_add * s->z->s);
    assert(
        (s->is_forward_sorted) ==
        ((s->z->to_mul == 0 or
          (s->z->rev ? s->z->is_backward_sorted : s->z->is_forward_sorted)) and
         (s->z->rev ? s->z->first : s->z->last) * s->z->to_mul + s->z->to_add <=
             s->v));
    assert(
        (s->is_backward_sorted) ==
        ((s->z->to_mul == 0 or
          (s->z->rev ? s->z->is_forward_sorted : s->z->is_backward_sorted)) and
         (s->z->rev ? s->z->first : s->z->last) * s->z->to_mul + s->z->to_add >=
             s->v));
  } else if (s->x) {
    assert(s->x->s + 1 == s->s);
    assert(s->x->d + 1 == s->d);
    assert(s->sum == s->v + s->x->sum * s->x->to_mul + s->x->to_add * s->x->s);
    assert(
        (s->is_forward_sorted) ==
        ((s->x->to_mul == 0 or
          (s->x->rev ? s->x->is_backward_sorted : s->x->is_forward_sorted)) and
         (s->x->rev ? s->x->last : s->x->first) * s->x->to_mul + s->x->to_add >=
             s->v));
    assert(
        (s->is_backward_sorted) ==
        ((s->x->to_mul == 0 or
          (s->x->rev ? s->x->is_forward_sorted : s->x->is_backward_sorted)) and
         (s->x->rev ? s->x->last : s->x->first) * s->x->to_mul + s->x->to_add <=
             s->v));
  } else {
    assert(1 == s->s);
    assert(1 == s->d);
    assert(s->sum == s->v);
    assert(s->is_forward_sorted == 1);
    assert(s->is_backward_sorted == 1);
  }
}

pair<const el *, const el *> be(const el *q) {
  if (!q) {
    return {q, q};
  }
  const el *b = q, *e = q;
  while (z_get(b)) {
    b = b->z;
  }
  while (x_get(e)) {
    e = e->x;
  }
  return {b, e};
}

int64_t el_size(const el *s) { return s ? s->s : 0; }

// void del(const el *q) {
//   if (!q) {
//     return;
//   }
//   del(q->z);
//   del(q->x);
//   delete q;
// }

const el *merge(const el *t1, const el *t2) {
  if (!t1) {
    return t2;
  }
  if (!t2) {
    return t1;
  }
  if (t1->w < t2->w) {
    z_put(t2, merge(t1, z_get(t2)));
    return t2;
  } else {
    x_put(t1, merge(x_get(t1), t2));
    return t1;
  }
}

std::pair<const el *, const el *> split(const el *t, int64_t n) {
  if (!t) {
    return {nullptr, nullptr};
  }
  if (n == 0) {
    return {nullptr, t};
  }
  if (n == t->s) {
    return {t, nullptr};
  }
  auto t_z = t ? z_get(t) : 0;auto t_x = t ? x_get(t) : 0;auto t_z_s = t_z ? t_z->s : 0;auto t_x_s = t_x ? t_x->s : 0;;
  if (t_z_s < n) {
    auto tmp = split(t_x, n - t_z_s - 1);
    x_put(t, tmp.first);
    auto t2 = tmp.second;
    if (t2) {
      const_cast<const el *&>(t2->p) = nullptr;
    }
    return {t, t2};
  } else {
    auto tmp = split(t_z, n);
    auto t1 = tmp.first;
    z_put(t, tmp.second);
    if (t1) {
      const_cast<const el *&>(t1->p) = nullptr;
    }
    return {t1, t};
  }
}

int64_t lower_bound(const el *q, int64_t d) {
  pair<const el*,int64_t> t, y;
  if (!q) {
    t = {be(q).first, 0};
  } else if (d <= q->first) {
    t = {be(q).first, 0};
  } else if (d > q->last) {
    t = {be(q).second, 1};
  } else {
    assert(q);
    auto w = q;
    w = nullptr;
    while (q) {
      if (q->v >= d) {
        w = q;
        q = z_get(q);
      } else {
        q = x_get(q);
      }
    }
    t = {w, 0};
  }
  return find_index(t);
}
int64_t upper_bound(const el *q, int64_t d) {
  pair<const el*,int64_t> t;
  if (!q) {
    t = {be(q).first, 0};
  } else if (d < q->first) {
    t = {be(q).first, 0};
  } else if (d >= q->last) {
    t = {be(q).second, 1};
  } else {
    assert(q);
    auto w = q;
    w = nullptr;
    while (q) {
      if (q->v > d) {
        w = q;
        q = z_get(q);
      } else {
        q = x_get(q);
      }
    }
    t = pair<const el*,int64_t>{w, 0};
  }
  return find_index(t);
}
int64_t forward_sorted_prefix(const el *q) {
  pair<const el*,int64_t> t;
  auto w = q;
  w = nullptr;
  if (!q or q->is_forward_sorted) {
    t = {be(q).second, bool(q)};
  } else {
    while (q) {
      auto q_z = q ? z_get(q) : 0;auto q_x = q ? x_get(q) : 0;auto q_z_s = q_z ? q_z->s : 0;auto q_x_s = q_x ? q_x->s : 0;;
      if (!q_z or q_z->is_forward_sorted) {
        if (!q_z or q->v >= q_z->last) {
          if (!w or w->v <= q->first) {
            w = q;
          } else {
            t = {w, 0};
            t=add(t,1);
            break;
          }
          q = q_x;
        } else {
          if (!w or w->v <= q->first) {
            w = q;
            t = {w, 0};
            break;
          } else {
            t = {w, 0};
            t=add(t,1);
            break;
          }
        }
      } else {
        q = q_z;
      }
    }
    if (!t.first) {
      t = {w, 0};
      t=add(t,1);
    }
  }
  return find_index(t);
}
int64_t backward_sorted_prefix(const el *q) {
  pair<const el*,int64_t> t;
  auto w = q;
  w = nullptr;
  if (!q or q->is_backward_sorted) {
    t = {be(q).second, bool(q)};
  } else {
    while (q) {
      auto q_z = q ? z_get(q) : 0;auto q_x = q ? x_get(q) : 0;auto q_z_s = q_z ? q_z->s : 0;auto q_x_s = q_x ? q_x->s : 0;;
      if (!q_z or q_z->is_backward_sorted) {
        if (!q_z or q->v <= q_z->last) {
          if (!w or w->v >= q->first) {
            w = q;
          } else {
            t = {w, 0};
            t=add(t,1);
            break;
          }
          q = q_x;
        } else {
          if (!w or w->v >= q->first) {
            w = q;
            t = {w, 0};
            break;
          } else {
            t = {w, 0};
            t=add(t,1);
            break;
          }
        }
      } else {
        q = q_z;
      }
    }
    if (!t.first) {
      t = {w, 0};
      t=add(t,1);
    }
  }
  return find_index(t);
}

const el *next_permutation(const el *s) {
  if (!s) {
    return s;
  }
  const_cast<int64_t &>(s->rev) ^= 1;
  make(s);
  auto q = forward_sorted_prefix(s);
  const_cast<int64_t &>(s->rev) ^= 1;
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
    const_cast<int64_t &>(s->rev) ^= 1;
    make(s);
    auto p = upper_bound(s, r);
    tmp = split(s, p);
    auto z = tmp.first;
    s = tmp.second;
    tmp = split(s, 1);
    auto x = tmp.first;
    s = tmp.second;
    auto tr = x->v;
    const_cast<int64_t &>(x->v) = r;
    update(x);
    r = tr;
    s = merge(x, s);
    x = nullptr;
    s = merge(z, s);
    z = nullptr;
    auto c = h;
    const_cast<int64_t &>(c->v) = r;
    update(c);
    t = merge(t, c);
    c = nullptr;
    s = merge(t, s);
    t = nullptr;
    return s;
  } else {
    const_cast<int64_t &>(s->rev) ^= 1;
    make(s);
    return s;
  }
}

const el *prev_permutation(const el *s) {
  if (!s) {
    return s;
  }
  const_cast<int64_t &>(s->rev) ^= 1;
  make(s);
  auto q = backward_sorted_prefix(s);
  const_cast<int64_t &>(s->rev) ^= 1;
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
    auto z = tmp.first;
    s = tmp.second;
    tmp = split(s, 1);
    auto x = tmp.first;
    s = tmp.second;
    auto tr = x->v;
    const_cast<int64_t &>(x->v) = r;
    update(x);
    r = tr;
    s = merge(x, s);
    x = nullptr;
    s = merge(z, s);
    z = nullptr;
    auto c = h;
    const_cast<int64_t &>(c->v) = r;
    update(c);
    t = merge(t, c);
    c = nullptr;
    const_cast<int64_t &>(s->rev) ^= 1;
    make(s);
    s = merge(t, s);
    t = nullptr;
    return s;
  } else {
    const_cast<int64_t &>(s->rev) ^= 1;
    make(s);
    return s;
  }
}

int64_t getint() {
  int64_t l;
  std::cin >> l;
  return l;
}

///////////////////////////////////////////////////end of lib

int main() {
  pair<const el *, const el *> tmp;
  uint64_t n = getint();
  const el *a = nullptr;
  for (uint64_t w = 0; w < n; ++w) {
    a = merge(a, create(getint()));
  }
  uint64_t qq = getint();
  for (uint64_t w = 0; w < qq; ++w) {
    check(a);
    uint64_t q = getint();
    if (q == -1) {
      break;
    }
    if (q == 1) {
      uint64_t l = getint(), r = getint() + 1;
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
      int64_t x = getint();
      uint64_t u = getint();
      int64_t l = u, r = u;
      tmp = split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      assert(!s);
      s = create(x);
      s = merge(d, s);
      d = nullptr;
      a = merge(s, a);
      s = nullptr;
    }
    if (q == 3) {
      uint64_t u = getint();
      tmp = split(a, u);
      auto z = tmp.first;
      a = tmp.second;
      tmp = split(a, 1);
      a = tmp.second;
      delete tmp.first;
      a = merge(z, a);
      z = nullptr;
    }
    if (q == 4) {
      int64_t x = getint();
      uint64_t l = getint(), r = getint() + 1;
      tmp = split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s ? const_cast<int64_t &>(s->to_mul) *= 0 : 0;
      s ? const_cast<int64_t &>(s->to_add) += x : 0;
      make(s);
      s = merge(d, s);
      d = nullptr;
      a = merge(s, a);
      s = nullptr;
    }
    if (q == 5) {
      int64_t x = getint();
      uint64_t l = getint(), r = getint() + 1;
      tmp = split(a, r);
      auto s = tmp.first;
      a = tmp.second;
      tmp = split(s, l);
      auto d = tmp.first;
      s = tmp.second;
      s ? const_cast<int64_t &>(s->to_add) += x : 0;
      make(s);
      s = merge(d, s);
      d = nullptr;
      a = merge(s, a);
      s = nullptr;
    }
    if (q == 6) {
      uint64_t l = getint(), r = getint() + 1;
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
      uint64_t l = getint(), r = getint() + 1;
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
