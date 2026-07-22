#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

///////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////

#define macro_map(f, ...) __VA_OPT__(macro_map_00(f, __VA_ARGS__))
#define macro_map_00(f, x, ...) f(x) __VA_OPT__(macro_map_01(f, __VA_ARGS__))
#define macro_map_01(f, x, ...) f(x) __VA_OPT__(macro_map_02(f, __VA_ARGS__))
#define macro_map_02(f, x, ...) f(x) __VA_OPT__(macro_map_03(f, __VA_ARGS__))
#define macro_map_03(f, x, ...) f(x) __VA_OPT__(macro_map_04(f, __VA_ARGS__))
#define macro_map_04(f, x, ...) f(x) __VA_OPT__(macro_map_05(f, __VA_ARGS__))
#define macro_map_05(f, x, ...) f(x) __VA_OPT__(macro_map_06(f, __VA_ARGS__))
#define macro_map_06(f, x, ...) f(x) __VA_OPT__(macro_map_07(f, __VA_ARGS__))
#define macro_map_07(f, x, ...) f(x) __VA_OPT__(macro_map_08(f, __VA_ARGS__))
#define macro_map_08(f, x, ...) f(x) __VA_OPT__(macro_map_09(f, __VA_ARGS__))
#define macro_map_09(f, x, ...) f(x) __VA_OPT__(macro_map_10(f, __VA_ARGS__))
#define macro_map_10(f, x, ...) f(x) __VA_OPT__(macro_map_11(f, __VA_ARGS__))
#define macro_map_11(f, x, ...) f(x) __VA_OPT__(macro_map_12(f, __VA_ARGS__))
#define macro_map_12(f, x, ...) f(x) __VA_OPT__(macro_map_13(f, __VA_ARGS__))
#define macro_map_13(f, x, ...) f(x) __VA_OPT__(macro_map_14(f, __VA_ARGS__))
#define macro_map_14(f, x, ...) f(x) __VA_OPT__(macro_map_15(f, __VA_ARGS__))
#define macro_map_15(f, x, ...) f(x) __VA_OPT__(macro_map_16(f, __VA_ARGS__))
#define macro_map_16(f, x, ...) f(x) __VA_OPT__(macro_map_17(f, __VA_ARGS__))
#define macro_map_17(f, x, ...) f(x) __VA_OPT__(macro_map_18(f, __VA_ARGS__))
#define macro_map_18(f, x, ...) f(x) __VA_OPT__(macro_map_19(f, __VA_ARGS__))
#define macro_map_19(f, x, ...) f(x) __VA_OPT__(macro_map_20(f, __VA_ARGS__))
#define macro_map_20(f, x) f(x)

///////////////////////////////////////////////////////////////////////////////////////

#define concat(x, ...) concat_impl(x, __VA_ARGS__)
#define concat_impl(x, ...) x##__VA_ARGS__

///////////////////////////////////////////////////////////////////////////////////////

#define fmt_fstr_nothing_fmt_fstr_self_replace
#define fmt_fstr_self_replace(...) fmt_fstr_self_replace
#define fmt_arg_to_printf_fstr(...) concat(fmt_fstr_nothing_, fmt_fstr_self_replace __VA_ARGS__ "")

#define fmt_args_fmt_args_fix_args (),
#define fmt_args_drop_pars(...) __VA_OPT__(, ) __VA_ARGS__
#define fmt_args_drop_fstr(args, fstr) fmt_args_drop_pars args
#define fmt_args_split(...) fmt_args_drop_fstr(__VA_ARGS__)
#define fmt_args_nothing
#define fmt_args_fix_args(...) nothing(__VA_ARGS__),
#define fmt_arg_to_printf_args(x) fmt_args_split(concat(fmt_args_, fmt_args_fix_args x))

#define fmt_arg_to_printf_fstr_args(x) fmt_arg_to_printf_fstr(x) fmt_arg_to_printf_args(x)

#define fmt_arg_into_snprintf_for_tmpbuf(x)                                    \
    _fmt_last = snprintf(_fmt_pos, _fmt_left, fmt_arg_to_printf_fstr_args(x)); \
    if (_fmt_last < 0) {                                                       \
        fputs("fmt format error\n", stderr);                                   \
        tmpbuf[0] = 0;                                                         \
        break;                                                                 \
    }                                                                          \
    if (_fmt_last >= _fmt_left) {                                              \
        fputs("fmt overflow\n", stderr);                                       \
        tmpbuf[0] = 0;                                                         \
        break;                                                                 \
    }                                                                          \
    _fmt_pos += _fmt_last;                                                     \
    _fmt_left -= _fmt_last;

#define fmt_arg_into_fprintf(x)                                     \
    _fmt_last = fprintf(_fmt_file, fmt_arg_to_printf_fstr_args(x)); \
    if (_fmt_last < 0) {                                            \
        fputs("fmt format error\n", stderr);                        \
        _fmt_used = -1;                                             \
        break;                                                      \
    }                                                               \
    _fmt_used += _fmt_last;

#define fmt(...)                                                 \
    tmpbuf(({                                                    \
        char* _fmt_pos = tmpbuf;                                 \
        int _fmt_left = sizeof(tmpbuf);                          \
        int _fmt_last = 0;                                       \
        macro_map(fmt_arg_into_snprintf_for_tmpbuf, __VA_ARGS__) \
    }))

#define fmtf(file, ...)                                   \
    ({                                                    \
        FILE* _fmt_file = file;                           \
        int _fmt_last = 0;                                \
        int _fmt_used = 0;                                \
        do {                                              \
            macro_map(fmt_arg_into_fprintf, __VA_ARGS__); \
        } while (0);                                      \
        _fmt_used;                                        \
    })

#define outfmt(...) fmtf(stdout, __VA_ARGS__)
#define errfmt(...) fmtf(stderr, __VA_ARGS__)
#define outfmtln(...) outfmt(__VA_ARGS__ __VA_OPT__(, ) "\n")
#define errfmtln(...) errfmt(__VA_ARGS__ __VA_OPT__(, ) "\n")

#define M "-"

int main() {
    size_t val1 = -1;
    ssize_t val2 = -1;
    uint64_t val3 = 1;
    outfmtln("val1-1 = ", (--val1) "%zu; val2-1 = ", (--val2) "%zd; val3-1 = ", (--val3) "%" PRIu64 ";");
    outfmtln("val1-2 = ", (--val1) "%zu; val2-2 = ", (--val2) "%zd; val3-2 = ", (--val3) "%" PRIu64 ";");
    outfmtln("val1-3 = ", (--val1) "%zu; val2-3 = ", (--val2) "%zd; val3-3 = ", (--val3) "%" PRIu64 ";");
}
