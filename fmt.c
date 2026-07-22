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

#define fmt_one_cat(x, ...) fmt_one_cat_impl(x, __VA_ARGS__)
#define fmt_one_cat_impl(x, ...) x ## __VA_ARGS__
#define fmt_one_remove(...)

#define fmt_one_nothing_fmt_one_replace
#define fmt_one_replace(...) fmt_one_replace
#define fmt_one_get_fstr(...) fmt_one_cat(fmt_one_nothing_, fmt_one_replace __VA_ARGS__ "")
#define fmt_one_1(...) _w_ (__VA_ARGS__) ,
#define fmt_one_get_args(x) fmt_one_2(fmt_one_cat(fmt_one_, fmt_one_1 x))
#define fmt_one_fmt_one_1 (),
#define fmt_one_2(...) fmt_one_3(__VA_ARGS__)
#define fmt_one_3(a, s) fmt_one_4 a
#define fmt_one__w_
#define fmt_one_4(...) __VA_OPT__(,) __VA_ARGS__

// clang-format off
#define fmt_one_for_tmpbuf(x)                                                  \
snprintf(                                                                      \
    tmpbuf + strlen(tmpbuf),                                                   \
    sizeof(tmpbuf) - strlen(tmpbuf),                                           \
    fmt_one_get_fstr(x)                                                        \
    fmt_one_get_args(x)                                                        \
);
// clang-format on

#define fmt_00(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_01(__VA_ARGS__))
#define fmt_01(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_02(__VA_ARGS__))
#define fmt_02(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_03(__VA_ARGS__))
#define fmt_03(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_04(__VA_ARGS__))
#define fmt_04(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_05(__VA_ARGS__))
#define fmt_05(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_06(__VA_ARGS__))
#define fmt_06(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_07(__VA_ARGS__))
#define fmt_07(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_08(__VA_ARGS__))
#define fmt_08(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_09(__VA_ARGS__))
#define fmt_09(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_10(__VA_ARGS__))
#define fmt_10(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_11(__VA_ARGS__))
#define fmt_11(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_12(__VA_ARGS__))
#define fmt_12(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_13(__VA_ARGS__))
#define fmt_13(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_14(__VA_ARGS__))
#define fmt_14(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_15(__VA_ARGS__))
#define fmt_15(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_16(__VA_ARGS__))
#define fmt_16(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_17(__VA_ARGS__))
#define fmt_17(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_18(__VA_ARGS__))
#define fmt_18(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_19(__VA_ARGS__))
#define fmt_19(x, ...) fmt_one_for_tmpbuf(x) __VA_OPT__(fmt_20(__VA_ARGS__))
#define fmt_20(x) fmt_one_for_tmpbuf(x)

#define fmt(...) tmpbuf(__VA_OPT__(fmt_00(__VA_ARGS__)))
#define outfmt(...) fputs(fmt(__VA_ARGS__), stdout)
#define errfmt(...) fputs(fmt(__VA_ARGS__), stdout)
#define outfmtln(...) outfmt(__VA_ARGS__ __VA_OPT__(, )() "\n")
#define errfmtln(...) errfmt(__VA_ARGS__ __VA_OPT__(, )() "\n")

#define M "-"

int main() {
    size_t val1 = -1;
    ssize_t val2 = -1;
    uint64_t val3 = 1;
    outfmtln( "val1-1 = ", (--val1) "%zu; val2-1 = ", (--val2) "%zd; val3-1 = ", (--val3) "%" PRIu64 ";");
    outfmtln( "val1-2 = ", (--val1) "%zu; val2-2 = ", (--val2) "%zd; val3-2 = ", (--val3) "%" PRIu64 ";");
    outfmtln( "val1-3 = ", (--val1) "%zu; val2-3 = ", (--val2) "%zd; val3-3 = ", (--val3) "%" PRIu64 ";");
}
