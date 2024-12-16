#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error_code = OK;
  if (dst) {
    s21_init_decimal(dst);
    if (src < 0) {
      s21_set_sign(dst, 1);
      src *= -1;
    }
    dst->bits[0] = src;
  } else {
    error_code = CONVERT_ERROR;
  }
  return error_code;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_init_decimal(dst);
  int error_code = CONVERT_OK;
  if (isinf(src) || isnan(src)) {
    error_code = CONVERT_ERROR;
  } else {
    if (src != 0) {
      int sign = s21_get_float_sign(&src);
      int exp = s21_get_float_scale(&src);
      double temp = (double)fabs(src);
      int off = 0;
      for (; off < 28 && (int)temp / (int)pow(2, 21) == 0; temp *= 10, off++) {
      }
      temp = round(temp);
      if (off <= 28 && (exp > -94 && exp < 96)) {
        float_bits mant;
        temp = (float)temp;
        for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {
        }
        mant.fl = temp;
        exp = s21_get_float_scale(&mant.fl);
        dst->bits[exp / 32] |= 1 << exp % 32;
        for (int i = exp - 1, j = 22; j >= 0; i--, j--)
          if ((mant.ui & (1 << j)) != 0) dst->bits[i / 32] |= 1 << i % 32;
        dst->bits[3] = (sign << 31) | (off << 16);
      } else
        error_code = CONVERT_ERROR;
    }
  }
  return error_code;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error_code = CONVERT_OK;
  *dst = 0;
  int scale = s21_get_scale(src);
  if (scale <= 28) {
    if (scale) s21_truncate(src, &src);
    *dst = src.bits[0];
    if (s21_get_sign(src)) *dst *= -1;
  } else {
    error_code = CONVERT_ERROR;
  }
  return error_code;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error_code = CONVERT_OK;
  *dst = 0;
  int scale = s21_get_scale(src);
  if (scale > 28) {
    error_code = CONVERT_ERROR;
  } else {
    *dst = 0.0;
    double tmp = *dst;
    for (int i = 0; i < 96; i++) {
      if (s21_get_bit(src, i)) {
        tmp += pow(2, i);
      }
    }
    while (scale > 0) {
      tmp /= 10;
      scale--;
    }
    *dst = tmp;
    if (s21_get_sign(src)) *dst *= -1;
  }
  return error_code;
}