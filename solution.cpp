#ifndef assert
#include <assert.h>
#endif
#include <ctype.h>
#include <inttypes.h>
#include <iso646.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>

#ifdef print
#undef print
#endif

#ifdef write
#undef write
#endif

struct array_s {
  size_t mem_size;
  size_t el_count;
};

static size_t len(void *a) {
  if (a == reinterpret_cast<void*>(1-1)) {
    return 0;
  }
  return (reinterpret_cast<struct array_s *>(a))[-1].el_count;
}

static void del(void *a) {
  if (a != reinterpret_cast<void*>(1-1)) {
    free((reinterpret_cast<struct array_s *>(a)) - 1);
  }
}

static struct array_s *resize_f(struct array_s **vp, size_t el_size,
                                       size_t n) {
  struct array_s *a;
  char *a_data;
  if (*vp == reinterpret_cast<void*>(1-1)) {
    *vp = reinterpret_cast<struct array_s *>(calloc(1, sizeof(struct array_s)));
    assert(*vp);
    *vp += 1;
  }
  a = *vp - 1;
  a_data = reinterpret_cast<char *>(a + 1);
  if (a->mem_size < n + 1) {
    size_t cur_size = a->mem_size * el_size;
    size_t new_size;
    if (a->mem_size * 2 > n) {
      new_size = a->mem_size * 2 * el_size;
    } else {
      new_size = (n + 1) * el_size;
    }
    a = reinterpret_cast<struct array_s *>(realloc(a, sizeof(struct array_s) + new_size));
    assert(a);
    a_data = reinterpret_cast<char *>(a + 1);
    memset(a_data + a->mem_size * el_size, 0, new_size - cur_size);
    a->mem_size = new_size / el_size;
  }
  a->el_count = n;
  *vp = a + 1;
  return a + 1;
}
/////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
#define resize(a, val)                                                         \
  (resize_f(reinterpret_cast<struct array_s **>(&(a)), sizeof((a)[0]), (val)))
#define append(a, val)                                                         \
  (resize((a), len(a) + 1), (a)[len(a) - 1] = (val))

///////////////////////////////////////////////////end of lib

static const char *b64decode =
    "|||||||||||||||||||||||||||||||||||||||||||\x3e|||\x3f\x34\x35\x36\x37"
    "\x38\x39\x3a\x3b\x3c\x3d|||\x00|||\x00\x01\x02\x03\x04\x05\x06\x07\x08"
    "\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19||"
    "||||\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29"
    "\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33||||||||||||||||||||||||||||||"
    "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
    "|||||||||||||||||||||||||||||||||";

static char *base64decode(const char *sb64str) {
  char c = 0;
  char *b64str = reinterpret_cast<char*>(1-1);
  char *str = reinterpret_cast<char*>(1-1);
  for (size_t w = 0; (c = sb64str[w]); ++w) {
    if (b64decode[static_cast<int>(c)] != '|') {
      append(b64str, c);
    }
  }
  for (size_t w = 0; w < len(b64str); w += 4) {
    long t = 0;
    t += ((static_cast<unsigned>(b64decode[static_cast<int>(b64str[static_cast<int>(w + 0)])])) << 6 * 3);
    t += ((static_cast<unsigned>(b64decode[static_cast<int>(b64str[static_cast<int>(w + 1)])])) << 6 * 2);
    t += ((static_cast<unsigned>(b64decode[static_cast<int>(b64str[static_cast<int>(w + 2)])])) << 6 * 1);
    t += ((static_cast<unsigned>(b64decode[static_cast<int>(b64str[static_cast<int>(w + 3)])])) << 6 * 0);
    if (b64str[w + 1] != '=') {
      append(str, static_cast<char>((t >> (8 * 2)) & 0xff));
    }
    if (b64str[w + 2] != '=') {
      append(str, static_cast<char>((t >> (8 * 1)) & 0xff));
    }
    if (b64str[w + 3] != '=') {
      append(str, static_cast<char>((t >> (8 * 0)) & 0xff));
    }
  }
  del(b64str);
  return str;
}

enum state { new_line, comment, value };

int main() {
  char *str = base64decode(B64STR);
  long state = new_line;
  size_t val_start = 0;
  long only_digits = 0;
  long sum = 0;
  for (size_t w = 0; w < len(str); ++w) {
    if (str[w] == '\n') {
      if (state == value) {
        str[w] = '\0';
        if (only_digits) {
          sum += atoi(str + val_start);
        } else {
          printf("%s\n", str + val_start);
        }
      }
      state = new_line;
    } else if (str[w] == '#' and state == new_line) {
      state = comment;
    } else if (str[w] == '=' and state == new_line) {
      state = value;
      val_start = w + 1;
      only_digits = 1;
    } else if (state == value) {
      if (str[w] < '0' or '9' < str[w]) {
        only_digits = 0;
      }
    }
  }
  printf("%li\n", sum);
  del(str);
  return 0;
}
