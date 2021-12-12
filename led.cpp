#include <iostream>

// #include "d"

struct str_ {
    const char* data;
    size_t size;
};

using namespace std;
// using str_=str_ing;
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
}

size_t _pow(size_t q, size_t e)
{
    size_t res = 1;
    while (e) {
        if (e % 2) {
            res *= q;
        }
        e /= 2;
        q *= q;
    }
    return res;
}

bool check_rev_v(str_ q)
{
    for (size_t w = 0; w < q.size; ++w) {
        if (q.data[w] == '2') {
            if (q.data[q.size - 1 - w] != '5') {
                return 0;
            }
        }
        else if (q.data[w] == '5') {
            if (q.data[q.size - 1 - w] != '2') {
                return 0;
            }
        }
        else if (q.data[w] == '0') {
            if (q.data[q.size - 1 - w] != '0') {
                return 0;
            }
        }
        else if (q.data[w] == '8') {
            if (q.data[q.size - 1 - w] != '8') {
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    return 1;
}

str_ slice_(str_ q, size_t e)
{
    if (e > q.size) {
        e = q.size;
    }
    return { q.data + e, q.size - e };
}

// auto check=pyfunc(pref,count)=
// "  def check_rev_h(q):\n"
// "    for w in range(len(q)):\n"
// "      if q[w] in '1380':\n"
// "        pass\n"
// "      else:\n"
// "        return 0\n"
// "    return 1\n"
// "\n"
// "  def check_rev_v(q):\n"
// "    for w in range(len(q)):\n"
// "      if q[w]=='2':\n"
// "        if q[-1-w]!='5':\n"
// "          return 0\n"
// "      elif q[w]=='5':\n"
// "        if q[-1-w]!='2':\n"
// "          return 0\n"
// "      elif q[w]=='0':\n"
// "        if q[-1-w]!='0':\n"
// "          return 0\n"
// "      elif q[w]=='8':\n"
// "        if q[-1-w]!='8':\n"
// "          return 0\n"
// "      else:\n"
// "        return 0\n"
// "    return 1;\n"
// "\n"
// "  def check_rev(q):\n"
// "    return check_rev_h(q) or check_rev_v(q)\n"
// "\n"
// "  c=0\n"
// "  for w in range(int(pref+'0'*count),int(pref+'9'*count)+1):\n"
// "    c+=bool(check_rev(str(w)))\n"
// "    c%=10**9+7\n"
// "  return (c)\n";

size_t count_with_zero(str_ pref, size_t count)
{
    assert(pref.size);
    // ic(pref.data,pref.size,count)
    // int64_t res_=check(pref.data,int64_t(count));
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
    // assert(res==res_);
    return res;
}

size_t count_from_zero(size_t end);

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
        assert(b % 10 == 0 and e % 10 == 9);
        ++l;
        b /= 10;
        e /= 10;
    }
    char* data = new char[20];

    size_t _b = b;
    size_t _s = 0;
    while (_b) {
        data[_s++] = '0' + _b % 10;
        _b /= 10;
    }
    for (size_t w = 0; w + w < _s; ++w) {
        char tmp = data[w];
        data[w] = data[_s - 1 - w];
        data[_s - 1 - w] = tmp;
    }
    data[_s] = 0;
    size_t res = count_with_zero({ data, _s }, l);
    delete[] data;
    return res;
}

size_t count_mul_dig(size_t b, size_t e)
{
    // ic("--",b,e)
    size_t _b = b, _e = e;
    size_t l = 1;
    while (b % 10 == 0 and e % 10 == 0) {
        l *= 10;
        b /= 10;
        e /= 10;
    }
    size_t res = 0;
    for (size_t w = b % 10; w < e - b + b % 10; ++w) {
        res += count_one_dig(_b + w * l, _b + l + w * l);
        res %= 1000000007;
    }
    return res;
}

size_t count_from_zero(size_t end)
{
    // ic(end)
    size_t b = end;
    size_t e = end;
    size_t lb = 1;
    size_t le = 1;
    lb *= 10;
    b /= 10;
    size_t res = 0;
    while (e) {
        // ic(b,lb,e,le)
        res += count_mul_dig(b * lb, e * le);
        res %= 1000000007;
        lb *= 10;
        b /= 10;
        le *= 10;
        e /= 10;
    }
    // ic(end,res)
    return res;
}

int main()
{
    size_t q, e;
    std::cin >> q >> e;
    size_t res = count_from_zero(e + 1) - count_from_zero(q);
    res %= 1000000007;
    cout << res << endl;
}
