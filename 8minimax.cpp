#include <stdio.h>
#include <stdint.h>

int main()
{
    ssize_t n, m, l;
    scanf("%zi%zi%zi", &n, &m, &l);
    auto a = new int64_t*[n];
    for (ssize_t w = 0; w < n; ++w) {
        a[w] = new int64_t[l];
        for (ssize_t e = 0; e < l; ++e) {
            scanf("%li", a[w] + e);
            a[w][e] *= 10000;
            a[w][e] += e;
        }
    }
    auto b = new int64_t*[m];
    for (ssize_t w = 0; w < m; ++w) {
        b[w] = new int64_t[l];
        for (ssize_t e = 0; e < l; ++e) {
            scanf("%li", b[w] + e);
            b[w][e] *= 10000;
            b[w][e] += 999 - e;
        }
    }
    ssize_t q;
    scanf("%zi", &q);
    for (ssize_t w = 0; w < q; ++w) {
        int i, j;
        scanf("%i%i", &i, &j);
        ssize_t z = 0, x, c, v = l - 1;
        // ic(itervect(a[i-1],a[i-1]+l))
        // ic(itervect(b[j-1],b[j-1]+l))
        while (v - z > 2) {
            x = (z + z + v) / 3;
            c = (z + v + v) / 3;
            auto _b = a[i - 1][x] > b[j - 1][x] ? a[i - 1][x] : b[j - 1][x];
            auto _n = a[i - 1][c] > b[j - 1][c] ? a[i - 1][c] : b[j - 1][c];
            // ic(z,x,c,v,_b,_n)
            if (_b < _n) {
                v = c;
            }
            if (_b > _n) {
                z = x;
            }
            if (_b == _n) {
                z = x;
                v = c;
            }
        }
        ssize_t m = 1000000000000000;
        ssize_t k = 0;
        for (ssize_t e = z; e < v + 1; ++e) {
            auto z = a[i - 1][e] > b[j - 1][e] ? a[i - 1][e] : b[j - 1][e];
            if (z < m) {
                k = e + 1;
                m = z;
            }
        }
        printf("%zu\n", k);
    }
    for (ssize_t w = 0; w < n; ++w) {
        delete[] a[w];
    }
    delete[] a;
    for (ssize_t w = 0; w < m; ++w) {
        delete[] b[w];
    }
    delete[] b;
}
