#pragma once
// Файл bn.h
struct bn_s;
typedef struct bn_s bn;
// enum bn_codes {
// BN_OK, BN_NULL_OBJECT, BN_NO_MEMORY, BN_DIVIDE_BY_ZERO
// };
bn *bn_new(); // Со(дат+ новое BN
bn *bn_init(bn const *orig); // Со(дат+ копи1 существу1щего BN
// Инициали(ироват+ (начение BN дес:тичным представлением строки
int bn_init_string(bn *t, const char *init_string);
// Инициали(ироват+ (начение BN представлением строки
// в системе счислени: radix
int bn_init_string_radix(bn *t, const char *init_string, int radix);
// Инициали(ироват+ (начение BN (аданным целым числом
int bn_init_int(bn *t, int init_int);
// Уничто>ит+ BN (освободит+ пам:т+)
int bn_delete(bn *t);
// Операции, аналогичные +=, -=, *=, /=, %=
int bn_add_to(bn *t, bn const *right);
int bn_sub_to(bn *t, bn const *right);
int bn_mul_to(bn *t, bn const *right);
int bn_div_to(bn *t, bn const *right);
int bn_mod_to(bn *t, bn const *right);
// Во(вести число в степен+ degree
int bn_pow_to(bn *t, int degree);
// И(влеч+ корен+ степени reciprocal и( BN
int bn_root_to(bn *t, int reciprocal);
// Аналоги операций x = l+r (l-r, l*r, l/r, l%r)
bn* bn_add(bn const *left, bn const *right);
bn* bn_sub(bn const *left, bn const *right);
bn* bn_mul(bn const *left, bn const *right);
bn* bn_div(bn const *left, bn const *right);
bn* bn_mod(bn const *left, bn const *right);
// Выдат+ представление BN в системе счислени: radix в виде строки
// Строку после испол+(овани: потребуетс: удалит+.
const char *bn_to_string(bn const *t, int radix);
// Если левое мен+ше, вернут+ <0; если равны, вернут+ 0; иначе >0
int bn_cmp(bn const *left, bn const *right);
int bn_neg(bn *t); // И(менит+ (нак на противополо>ный
int bn_abs(bn *t); // В(:т+ модул+
int bn_sign(bn const *t); //-1 если t<0; 0 если t = 0, 1 если t>0
