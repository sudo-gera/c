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

#define _fmt_split__fmt_split_fix_args (),
#define _fmt_split__nothing
#define _fmt_split_fix_args(...) _nothing(__VA_ARGS__),
#define _fmt_split_concat(x) concat(_fmt_split_, _fmt_split_fix_args x)
#define _fmt_split_parse(f, x) f(x)
#define _fmt_split_call_on_parsed(f, x) _fmt_split_parse(f, _fmt_split_concat(x))

#define _fmt_get_fstr(args, fstr) fstr ""
#define _fmt_args_drop_pars(...) __VA_OPT__(, ) __VA_ARGS__
#define _fmt_get_args(args, fstr) _fmt_args_drop_pars args
#define _fmt_get(part, x) _fmt_split_call_on_parsed(_fmt_get_##part, x)

#define fmt_arg_to_printf_fstr_args(x) _fmt_get(fstr, x) _fmt_get(args, x)

///////////////////////////////////////////////////////////////////////////////////////

#define _fmt_arg_into_snprintf(x)                                                      \
    _fmt_last = snprintf(_fmt_pos, (size_t)_fmt_left, fmt_arg_to_printf_fstr_args(x)); \
    if (_fmt_last < 0) {                                                               \
        fputs("fmt format error\n", stderr);                                           \
        _fmt_used = _fmt_last;                                                         \
        break;                                                                         \
    }                                                                                  \
    if (_fmt_last >= _fmt_left) {                                                      \
        fputs("fmt overflow\n", stderr);                                               \
        _fmt_used = -1;                                                                \
        break;                                                                         \
    }                                                                                  \
    _fmt_pos += _fmt_last;                                                             \
    _fmt_used += _fmt_last;                                                            \
    _fmt_left -= _fmt_last;

#define _fmt_arg_into_fprintf(x)                                    \
    _fmt_last = fprintf(_fmt_file, fmt_arg_to_printf_fstr_args(x)); \
    if (_fmt_last < 0) {                                            \
        fputs("fmt format error\n", stderr);                        \
        _fmt_used = _fmt_last;                                      \
        break;                                                      \
    }                                                               \
    _fmt_used += _fmt_last;

///////////////////////////////////////////////////////////////////////////////////////

#define snfmt(buffer, size, ...)                                         \
    ({                                                                   \
        char* _fmt_buf = (buffer);                                       \
        char* _fmt_pos = _fmt_buf;                                       \
        int _fmt_left = (int)(size);                                     \
        int _fmt_last = 0;                                               \
        int _fmt_used = 0;                                               \
        do {                                                             \
            macro_map(_fmt_arg_into_snprintf __VA_OPT__(, ) __VA_ARGS__) \
        } while (0);                                                     \
        _fmt_used;                                                       \
    })

#define ffmt(file, ...)                                                  \
    ({                                                                   \
        FILE* _fmt_file = file;                                          \
        int _fmt_last = 0;                                               \
        int _fmt_used = 0;                                               \
        do {                                                             \
            macro_map(_fmt_arg_into_fprintf __VA_OPT__(, ) __VA_ARGS__); \
        } while (0);                                                     \
        _fmt_used;                                                       \
    })

#define fmt(...) tmpbuf(snfmt(tmpbuf, sizeof(tmpbuf) __VA_OPT__(, ) __VA_ARGS__);)
#define outfmt(...) ffmt(stdout __VA_OPT__(, ) __VA_ARGS__)
#define errfmt(...) ffmt(stderr __VA_OPT__(, ) __VA_ARGS__)
#define outfmtln(...) outfmt(__VA_ARGS__ __VA_OPT__(, ) "\n")
#define errfmtln(...) errfmt(__VA_ARGS__ __VA_OPT__(, ) "\n")

///////////////////////////////////////////////////////////////////////////////////////

#if __INCLUDE_LEVEL__ == 0

#define M "="
int main() {
    size_t val1 = -1;
    ssize_t val2 = -1;
    uint64_t val3 = 1;
    outfmtln("val1-1 = ", (--val1) "%zu; val2-1 = ", (--val2) "%zd; val3-1 = ", (8, --val3) "%0*" PRIu64 ";");
    outfmtln("val1-2 ", (M) "%s ", (--val1) "%zu; val2-2 = ", (--val2) "%zd; val3-2 = ", (--val3) "%" PRIu64 ";");
    puts(fmt("val1-3 = ", (--val1) "%zu; val2-3 = ", (--val2) "%zd; val3-3 = ", (--val3) "%" PRIu64 ";", ()));
    char* buffers[16];
    buffers[0] = fmt((65536, 0) "%0*d");
    buffers[1] = fmt((65536, 1) "%0*d");
    buffers[2] = fmt((65536, 2) "%0*d");
    buffers[3] = fmt((65536, 3) "%0*d");
    buffers[4] = fmt((65536, 4) "%0*d");
    buffers[5] = fmt((65536, 5) "%0*d");
    buffers[6] = fmt((65536, 6) "%0*d");
    buffers[7] = fmt((65536, 7) "%0*d");
    buffers[8] = fmt((65536, 8) "%0*d");
    buffers[9] = fmt((65536, 9) "%0*d");
    buffers[10] = fmt((65536, 10) "%0*d");
    buffers[11] = fmt((65536, 11) "%0*d");
    buffers[12] = fmt((65536, 12) "%0*d");
    buffers[13] = fmt((65536, 13) "%0*d");
    buffers[14] = fmt((65536, 14) "%0*d");
    buffers[15] = fmt((65536, 15) "%0*d");
    for (size_t i = 0; i < sizeof(buffers) / sizeof(buffers[0]); ++i) {
        if (strcmp(buffers[i], fmt((65536, i) "%0*zu"))) {
            outfmtln("Error: buffers[", (i) "%zu] is lost.");
        }
    }
}

#endif
