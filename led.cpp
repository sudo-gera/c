#include <iostream>

<<<<<<< HEAD
struct Str {
  const char* data;
  size_t size;
};

size_t get_power(size_t q) {
  assert(q);
  size_t l = 1;
  while (q % 10 == 0) {
    l *= 10;
    q /= 10;
  }
  return l;
=======
#if __has_include("d")
#include "d"
#endif

struct str_ {
    const char* data;
    size_t size;
};

using namespace std;
bool check_all(str_ q, str_ e)
{
    for (size_t _w = 0; _w < q.size; ++_w) {
        char w = q.data[_w];
        bool b = 0;
        for (size_t _r = 0; _r < e.size; ++_r) {
            char r = e.data[_r];
            if (w == r) {
                b = 1;
                break;
            }
        }
        if (!b) {
            return 0;
        }
    }
    return 1;
>>>>>>> 400128ebf054c37eb8e91090086c0e7f41e46730
}

bool checkAll(Str q, Str e) {
  for (size_t _w = 0; _w < q.size; ++_w) {
    char w = q.data[_w];
    bool b = false;
    for (size_t _r = 0; _r < e.size; ++_r) {
      char r = e.data[_r];
      if (w == r) {
        b = true;
        break;
      }
    }
    if (!b) {
      return false;
    }
  }
  return true;
}

size_t _pow(size_t q, size_t e) {
  size_t res = 1;
  while (e != 0) {
    if (e % 2 != 0) {
      res *= q;
    }
    e /= 2;
    q *= q;
  }
  return res;
}

bool check_rev_v(Str q) {
  for (size_t w = 0; w < q.size; ++w) {
    if (q.data[w] == '2') {
      if (q.data[q.size - 1 - w] != '5') {
        return false;
      }
    } else if (q.data[w] == '5') {
      if (q.data[q.size - 1 - w] != '2') {
        return false;
      }
    } else if (q.data[w] == '0') {
      if (q.data[q.size - 1 - w] != '0') {
        return false;
      }
    } else if (q.data[w] == '8') {
      if (q.data[q.size - 1 - w] != '8') {
        return false;
      }
    } else {
      return false;
    }
  }
  return true;
}

<<<<<<< HEAD
Str slice_(Str q, size_t e) {
  if (e > q.size) {
    e = q.size;
  }
  return {q.data + e, q.size - e};
}

size_t count_with_zero(Str pref, size_t count) {
  ssize_t res = 0;
  if (checkAll(pref, {"1380", 4})) {
    res += _pow(4, count);
  }
  if (check_rev_v(slice_(pref, count)) && checkAll(pref, {"5208", 4})) {
    if (count > pref.size) {
      if ((count - pref.size) % 2 != 0) {
        res += _pow(4, ((count - pref.size) / 2)) * 2;
      } else {
        res += _pow(4, ((count - pref.size) / 2));
      }
    } else {
      res += 1;
    }
  }
  if (checkAll(pref, {"1380", 4}) && check_rev_v(slice_(pref, count)) &&
      checkAll(pref, {"5208", 4})) {
    ssize_t tmp = (pref.size + count + 1) / 2 - pref.size;
    res -= _pow(2, tmp > 0 ? tmp : 0);
  }
  return res;
=======
#if __has_include("d")
auto check=pyfunc(pref,count)=
"  def check_rev_h(q):\n"
"    for w in range(len(q)):\n"
"      if q[w] in '1380':\n"
"        pass\n"
"      else:\n"
"        return 0\n"
"    return 1\n"
"\n"
"  def check_rev_v(q):\n"
"    for w in range(len(q)):\n"
"      if q[w]=='2':\n"
"        if q[-1-w]!='5':\n"
"          return 0\n"
"      elif q[w]=='5':\n"
"        if q[-1-w]!='2':\n"
"          return 0\n"
"      elif q[w]=='0':\n"
"        if q[-1-w]!='0':\n"
"          return 0\n"
"      elif q[w]=='8':\n"
"        if q[-1-w]!='8':\n"
"          return 0\n"
"      else:\n"
"        return 0\n"
"    return 1;\n"
"\n"
"  def check_rev(q):\n"
"    return check_rev_h(q) or check_rev_v(q)\n"
"\n"
"  c=0\n"
"  for w in range(int(pref+'0'*count),int(pref+'9'*count)+1):\n"
"    c+=bool(check_rev(str(w)))\n"
"    c%=10**9+7\n"
"  return (c)\n";
#endif


size_t count_with_zero(str_ pref, size_t count)
{
    // ic(pref.data,pref.size,count)
#if __has_include("d")
    assert(pref.size);
    // int64_t res_=check(pref.data,int64_t(count));
#endif
    ssize_t res = 0;
    if (check_all(pref, { "1380", 4 })) {
        res += _pow(4, count);
        res %= 1000000007;
    }
    // ic(res)
    if (check_rev_v(slice_(pref, count)) and check_all(pref, { "5208", 4 })) {
        if (count > pref.size) {
            if ((count - pref.size) % 2) {
                res += _pow(4, ((count - pref.size) / 2)) * 2;
                res %= 1000000007;
            }
            else {
                res += _pow(4, ((count - pref.size) / 2));
                res %= 1000000007;
            }
        }
        else {
            res += 1;
            res %= 1000000007;
        }
    }
    // ic(res)
    if (check_all(pref, { "1380", 4 }) and check_rev_v(slice_(pref, count)) and check_all(pref, { "5208", 4 })) {
        ssize_t tmp = (pref.size + count + 1) / 2 - pref.size;
        res -= _pow(2, tmp > 0 ? tmp : 0);
        res %= 1000000007;
        res += 1000000007;
        res %= 1000000007;
    }
    // ic(res)
    res %= 1000000007;
    res += 1000000007;
    res %= 1000000007;
    // ic(res)
    // ic(res_)
#if __has_include("d")
    // assert(res==res_);
#endif
    return res;
>>>>>>> 400128ebf054c37eb8e91090086c0e7f41e46730
}

size_t count_from_zero(size_t end);

<<<<<<< HEAD
size_t count_one_dig(size_t b, size_t e) {
  if (b == 0) {
    assert(e == get_power(e));
    if (e < 2) {
      return e;
=======
size_t count_one_dig(size_t b, size_t e)
{
    // ic(b,e)
    if (b == 0) {
        if (e < 2) {
            return e;
        }
        return count_from_zero(e - 1);
    }
    e -= 1;
    size_t l = 0;
    while (e != b) {
#if __has_include("d")
        assert(b % 10 == 0 and e % 10 == 9);
#endif
        ++l;
        b /= 10;
        e /= 10;
>>>>>>> 400128ebf054c37eb8e91090086c0e7f41e46730
    }
    return count_from_zero(e - 1);
  }
  assert(e);
  assert(b / get_power(e) + 1 == e / get_power(e));
  e -= 1;
  size_t l = 0;
  while (e != b) {
    ++l;
    b /= 10;
    e /= 10;
  }
  char* data = new char[20];

  size_t _b = b;
  size_t _s = 0;
  while (_b != 0) {
    data[_s++] = '0' + _b % 10;
    _b /= 10;
  }
  for (size_t w = 0; w + w < _s; ++w) {
    char tmp = data[w];
    data[w] = data[_s - 1 - w];
    data[_s - 1 - w] = tmp;
  }
  data[_s] = 0;
  size_t res = count_with_zero({data, _s}, l);
  delete[] data;
  return res;
}

size_t count_mul_dig(size_t b, size_t e) {
  assert(0 <= e - b);
  assert(e - b <= 9 * get_power(e));
  assert(b == 0 or b / get_power(b) == e / get_power(b));
  size_t _b = b;
  size_t l = 1;
  while (b % 10 == 0 && e % 10 == 0) {
    l *= 10;
    b /= 10;
    e /= 10;
  }
  size_t res = 0;
  for (size_t w = b % 10; w < e - b + b % 10; ++w) {
    res += count_one_dig(_b + w * l, _b + l + w * l);
  }
  return res;
}

size_t count_from_zero(size_t end) {
  size_t b = end;
  size_t e = end;
  size_t lb = 1;
  size_t le = 1;
  lb *= 10;
  b /= 10;
  size_t res = 0;
  while (e != 0) {
    res += count_mul_dig(b * lb, e * le);
    lb *= 10;
    b /= 10;
    le *= 10;
    e /= 10;
  }
  return res;
}

int main() {
  size_t q, e;
  std::cin >> q >> e;
  size_t res = count_from_zero(e + 1) - count_from_zero(q);
  res %= 1000000007;
  std::cout << res << std::endl;
  std::cerr << q << " " << e << " " << res << std::endl;
}
