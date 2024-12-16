#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdlib.h>

#define OK 0
#define INF 1
#define NEG_INF 2
#define DIV_BY_ZERO 3

#define COMPARSION_FALSE 0
#define COMPARSION_TRUE 1

#define CONVERT_OK 0
#define CONVERT_ERROR 1

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef union {
  int ui;
  float fl;
} float_bits;

// arithmetic functions
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// compare functions
int s21_is_less(s21_decimal value1, s21_decimal value2);
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_equal(s21_decimal value1, s21_decimal value2);
int s21_is_not_equal(s21_decimal value1, s21_decimal value2s);

// convert functions
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// other functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

void s21_init_decimal(s21_decimal *value);
int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int bit);
int s21_get_bit(s21_decimal value, int bit);
void s21_set_bit(s21_decimal *value, int posision, int bit);
int s21_get_scale(s21_decimal value);
void s21_set_scale(s21_decimal *value, int scale);
int s21_dec_is_zero(s21_decimal number);
int s21_compare_decimal_bits(s21_decimal value1, s21_decimal value2);
void s21_alignment_scale(s21_decimal *value1, s21_decimal *value2);
// void s21_increase_scale(s21_decimal *value);
void s21_decrease_scale(s21_decimal *value);
int s21_last_bit(s21_decimal number);
int s21_shift_left(s21_decimal *value, int offset);
int s21_bit_add(s21_decimal value1, s21_decimal value2, s21_decimal *res);
int s21_bit_sub(s21_decimal number_1, s21_decimal number_2,
                s21_decimal *result);
void s21_bit_mul(s21_decimal val1, s21_decimal ten, s21_decimal *result);
void s21_bit_div(s21_decimal number1, s21_decimal number2,
                 s21_decimal *remainder, s21_decimal *res);
// void print_decimal(s21_decimal value);
void s21_copy_bits(s21_decimal src, s21_decimal *dest);
int s21_get_float_sign(float *src);
int s21_get_float_scale(float *src);
unsigned int s21_divide_by_10(s21_decimal *value);

#endif  // S21_DECIMAL_H