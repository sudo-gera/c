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

#define _fmt_fstr_nothing__fmt_fstr_self_replace
#define _fmt_fstr_self_replace(...) _fmt_fstr_self_replace
#define fmt_arg_to_printf_fstr(...) concat(_fmt_fstr_nothing_, _fmt_fstr_self_replace __VA_ARGS__ "")

#define _fmt_args__fmt_args_fix_args (),
#define _fmt_args_drop_pars(...) __VA_OPT__(, ) __VA_ARGS__
#define _fmt_args_drop_fstr(args, fstr) _fmt_args_drop_pars args
#define _fmt_args_split(...) _fmt_args_drop_fstr(__VA_ARGS__)
#define _fmt_args_nothing
#define _fmt_args_fix_args(...) nothing(__VA_ARGS__),
#define fmt_arg_to_printf_args(x) _fmt_args_split(concat(_fmt_args_, _fmt_args_fix_args x))

#define fmt_arg_to_printf_fstr_args(x) fmt_arg_to_printf_fstr(x) fmt_arg_to_printf_args(x)

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

//////////////////////////////////////////////////////////////////////////////////////

/*
The task is to figure out how to use the lib above.

First attempt:

*/

int main(){
    char *s = fmt_arg_to_printf_fstr(("%d", x));
}

/*
end of gcc -E -P  test.c | clang-format 

int main() {
    char *s = "";
}
*/

