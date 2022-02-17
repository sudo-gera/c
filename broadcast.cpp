#include <bits/stdc++.h>
using namespace std;
int main()
{
    unsigned int q, w, e, r, t, y, u, i, o, p;
    scanf("%i.%i.%i.%i", &q, &w, &e, &r);
    scanf("%i.%i.%i.%i", &t, &y, &u, &i);
    o = (q << 24) + (w << 16) + (e << 8) + (r << 0);
    p = (t << 24) + (y << 16) + (u << 8) + (i << 0);

    o = (o & p) + ~p;
    printf("%i.%i.%i.%i", (o >> 24) & 0b11111111, (o >> 16) & 0b11111111, (o >> 8) & 0b11111111,
        (o >> 0) & 0b11111111);
}
