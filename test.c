#define cat(x, ...) cat_impl(x, __VA_ARGS__)
#define cat_impl(x, ...) x ## __VA_ARGS__

#define _fff_fff_1 0,
#define fff_1(...) _w_ (__VA_ARGS__) ,
#define fff_get(x) fff_2(cat(_fff_, fff_1 x))
#define fff_2(...) fff_3(__VA_ARGS__)
#define fff_3(a, s) _z_ a _x_ s _c_

#define M "-"

int main() {
    fff_get(M);
    fff_get((x) M);
}
