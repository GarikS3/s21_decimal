#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int errCode = 0;
  if (result == NULL)
    errCode = 1;
  else {
    *result = value;
    int scale = s21_get_scale(value);

    // eсли есть дробная часть
    if (scale > 0) {
      unsigned int remainder;
      while (scale > 0) {
        remainder = s21_divide_by_10(result);
        scale--;
      }

      s21_truncate(value, result);

      // округляем
      if (remainder >= 5) {
        if (s21_get_sign(value)) {
          result->bits[0] -= 1;
        } else {
          result->bits[0] += 1;
        }
      }
    } else {
      *result = value;
    }
    s21_set_scale(result, 0);
  }
  return errCode;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int errCode = 0;
  if (result == NULL)
    errCode = 1;
  else {
    *result = value;
    int scale = s21_get_scale(value);

    while (scale > 0) {
      s21_divide_by_10(result);  // делим на 10
      scale--;                   // уменьшаем масштаб
    }

    s21_set_scale(result, 0);
  }
  return errCode;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int errCode = 0;
  if (result == NULL)
    errCode = 1;
  else {
    int sign = s21_get_sign(value);
    *result = value;
    if (sign == 1)
      s21_set_bit(result, 127, 0);
    else
      s21_set_bit(result, 127, 1);
  }
  return errCode;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int errCode = 0;
  if (result == NULL)
    errCode = 1;
  else {
    s21_truncate(value, result);
    // если число отрицательное и не было целым, уменьшаем на 1
    if (s21_get_sign(value)) {
      if (s21_get_scale(value) != 0) result->bits[0] += 1;
    }
  }
  return errCode;
}