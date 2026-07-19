#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

#define tmpbuf(...)                         \
    (({                                     \
         char tmpbuf[65537];                \
         memset(tmpbuf, 0, sizeof(tmpbuf)); \
         do {                               \
             __VA_ARGS__                    \
         } while (0);                       \
         struct {                           \
             char d[sizeof(tmpbuf)];        \
         } s;                               \
         memcpy(s.d, tmpbuf, sizeof(s.d));  \
         s;                                 \
     }).d)

// clang-format off
#define fmt_one_get_fstr(...)
#define fmt_one_get_args(...) __VA_OPT__(,) __VA_ARGS__); fmt_one_get_fstr(
#define fmt_one_for_tmpbuf(x)                                                  \
snprintf(                                                                      \
    tmpbuf + strlen(tmpbuf),                                                   \
    sizeof(tmpbuf) - strlen(tmpbuf),                                           \
    fmt_one_get_fstr x ""                                                      \
    fmt_one_get_args x ""                                                      \
);
// clang-format on

#define fmt_00(x) fmt_one_for_tmpbuf(x)

#define fmt(...) fmt_00(__VA_ARGS__)

int main() {
    fmt(()"");
}
