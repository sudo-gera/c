#include <stdio.h>
#include <stdint.h>

int& acess(size_t max, int* mdb, size_t b, size_t e)
{
    return mdb[(max + b) / (e - b)];
}

int init(size_t max, int* mdb, int* a, size_t b, size_t e)
{
    if (e - b == 1) {
        acess(max, mdb, b, e) = a[b];
        return a[b];
    }
    auto z = init(max, mdb, a, b, (b + e) / 2);
    auto x = init(max, mdb, a, (b + e) / 2, e);
    z = acess(max, mdb, b, e) = z < x ? z : x;
    return z;
}

int min(size_t max, int* mdb, size_t ub, size_t ue, size_t b, size_t e)
{
    // ic(ub,ue,b,e)
    auto c = (b + e) / 2;
    if (b == ub and ue == e) {
        return acess(max, mdb, b, e);
    }
    if (b <= ub and ue <= c) {
        return min(max, mdb, ub, ue, b, c);
    }
    if (c <= ub and ue <= e) {
        return min(max, mdb, ub, ue, c, e);
    }
    auto z = min(max, mdb, ub, c, b, c);
    auto x = min(max, mdb, c, ue, c, e);
    return z < x ? z : x;
}

int main()
{
    size_t n;
    scanf("%zu", &n);
    size_t max = 1024;
    auto mdb = new int[max * 2];
    auto a = new int[max];
    for (size_t w = 0; w < n; ++w) {
        scanf("%i", a + w);
    }
    init(max, mdb, a, 0, max);
    // print(itervect(mdb,mdb+max*2));
    auto res = 0;
    for (size_t w = 0; w < n; ++w) {
        for (size_t e = 0; e <= w; ++e) {
            auto z = (w + 1 - e) * min(max, mdb, e, w + 1, 0, max);
            // ic(e,w+1,z,res)
            res = res > z ? res : z;
        }
    }
    delete[] mdb;
    delete[] a;
    printf("%i\n", res);
}
	
