#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>
//////// FastRandom stuff ////////////////
typedef struct FastRandom_s {
    unsigned long long rnd;
} FastRandom;

FastRandom *FastRandom_create(unsigned long long seed) {
  FastRandom *t = (FastRandom *)malloc(sizeof (FastRandom));
  t->rnd = seed;
  return t;
}

unsigned long long 
FastRandom_rand(FastRandom *t) {
  t->rnd ^= t->rnd << 21;
  t->rnd ^= t->rnd >> 35;
  t->rnd ^= t->rnd << 4;
  return t->rnd;                                                                                      
}

void FastRandom_delete(FastRandom *r) {
  free(r);
}

int main(){
  size_t q;
  cin>>q;
  FastRandom* a=FastRandom_create(q);
  FastRandom* s=FastRandom_create(q);
  size_t c=0;
  while (1){
    FastRandom_rand(a);
    size_t f=FastRandom_rand(s);
    print(bin_repr(f))
    if (FastRandom_rand(a)==f){
      break;
    }
  }
  print(c)
}
