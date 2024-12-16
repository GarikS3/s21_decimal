#include "s21_decimal.h"

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  int is_equal = COMPARSION_FALSE;

  if (s21_dec_is_zero(value1) &&
      s21_dec_is_zero(value2)) {  /// если оба числа равны 0, то они равны между
    /// собой (на случай +-0)
    is_equal = COMPARSION_TRUE;
  } else {
    if (s21_get_sign(value1) ==
        s21_get_sign(value2)) {  // числа равны только с одинаковыми знаками

      s21_alignment_scale(&value1, &value2);
      is_equal = (s21_compare_decimal_bits(value1, value2) == 0)
                     ? COMPARSION_TRUE
                     : COMPARSION_FALSE;  // сравниваем биты чисел
    }
  }
  return is_equal;
}

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  int is_greater = COMPARSION_FALSE;

  int sign1 = s21_get_sign(value1);
  int sign2 = s21_get_sign(value2);

  if (s21_dec_is_zero(value1) &&
      s21_dec_is_zero(value2)) {  // если оба числа равны 0, то результат false
    is_greater = COMPARSION_FALSE;

  } else if (s21_dec_is_zero(value1) &&
             !s21_dec_is_zero(
                 value2)) {  // если первое число 0, а у второго знак
                             // -, то результат false
    is_greater = (sign2 == 1) ? COMPARSION_TRUE : COMPARSION_FALSE;

  } else if (sign1 != sign2 && sign1 == 0) {  // если знаки не равны, а у value1
                                              // знак +, то первое число больше
    is_greater = COMPARSION_TRUE;

  } else if (sign1 != sign2 && sign1 == 1) {  // если знаки не равны, а у value1
                                              // знак -, то первое число меньше
    is_greater = COMPARSION_FALSE;

  } else {
    s21_alignment_scale(&value1, &value2);

    if (s21_compare_decimal_bits(value1, value2) ==
        1) {  // если в первом числе бит больше и знак +, то value1 > value2

      is_greater = (sign1 == 0) ? COMPARSION_TRUE : COMPARSION_FALSE;
    } else if (s21_compare_decimal_bits(value1, value2) ==
               -1) {  // если во втором числе бит больше и знак +, то value1 <
                      // value2
      is_greater = (sign1 == 0) ? COMPARSION_FALSE : COMPARSION_TRUE;
    } else {  // в остальных случая числа равны
      is_greater = COMPARSION_FALSE;
    }
  }
  return is_greater;
}

int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2) {
  return s21_is_greater(value1, value2) || s21_is_equal(value1, value2);
}

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  return !s21_is_greater(value1, value2) && !s21_is_equal(value1, value2);
}

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  return s21_is_less(value1, value2) || s21_is_equal(value1, value2);
}

int s21_is_not_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_equal(value1, value2);
}