#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res_code = OK;
  s21_init_decimal(result);

  if (s21_get_sign(value_1) !=
      s21_get_sign(value_2)) {  // Если знаки разные, то выполняем вычитание
    if (s21_get_sign(value_1) == 0) {
      s21_set_sign(&value_2, 0);
      res_code = s21_sub(value_1, value_2, result);
    } else {
      s21_set_sign(&value_1, 0);
      res_code = s21_sub(value_2, value_1, result);
    }
  } else {
    if (s21_get_scale(value_1) != s21_get_scale(value_2))
      s21_alignment_scale(&value_1, &value_2);

    res_code = s21_bit_add(value_1, value_2, result);

    if (res_code) {  // Если произошло переполнение
      if (s21_get_sign(value_1) == 0)
        res_code = INF;  // Число слишком велико или равно бесконечности
      else
        res_code = NEG_INF;  // Число слишком мало или равно отрицательной
                             // бесконечности
    }
    s21_set_sign(result, s21_get_sign(value_1));
    s21_set_scale(result, s21_get_scale(value_1));
  }

  return res_code;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res_code = OK;
  s21_init_decimal(result);

  if (s21_get_sign(value_1) !=
      s21_get_sign(value_2)) {  // Если знаки разные, то выполняем сложение
    if (s21_get_sign(value_1) == 0) {
      s21_set_sign(&value_2, 0);
      res_code = s21_add(value_1, value_2, result);
    } else {
      s21_set_sign(&value_2, 1);
      res_code = s21_add(value_1, value_2, result);
    }
  } else if (s21_get_sign(value_1) == s21_get_sign(value_2) &&
             s21_get_sign(value_1) ==
                 1) {  // Если оба числа со знаком -, то выполняем сложение
    s21_set_sign(&value_2, 0);
    res_code =
        s21_add(value_1, value_2, result);  // пример: -10 - (-20) = -10 + 20
  } else {
    if (s21_get_scale(value_1) != s21_get_scale(value_2))
      s21_alignment_scale(&value_1, &value_2);

    int swap = 0;
    if (s21_is_less(value_1, value_2)) {  // Если первое число меньше второго,
                                          // то меняем их местами
      s21_decimal tmp_dec = value_1;
      value_1 = value_2;
      value_2 = tmp_dec;
      swap =
          1;  // Если был обмен, то ставим флаг. Знак результата должен быть -
    }

    res_code = s21_bit_sub(value_1, value_2, result);

    if (res_code == INF &&
        s21_get_sign(value_1) ==
            s21_get_sign(value_2)) {  // Если произошла ошибка переполнения
      res_code = (s21_get_sign(value_1) == 0) ? NEG_INF : INF;
    }

    s21_set_sign(result, swap);  // Устанавливаем знак, в зависимости от того,
                                 // менялись ли числа местами
    s21_set_scale(result, s21_get_scale(value_1));
  }
  return res_code;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res_code = OK;
  s21_init_decimal(result);

  int res_sign = (s21_get_sign(value_1) != s21_get_sign(value_2)) ? 1 : 0;

  int s21_last_bit1 = s21_last_bit(value_1);
  s21_decimal tmp = {{0, 0, 0, 0}};
  int inf_check = OK;

  for (int i = 0; i <= s21_last_bit1; i++) {
    s21_init_decimal(&tmp);
    int cur_bit = s21_get_bit(value_1, i);

    if (cur_bit) {
      tmp = value_2;
      inf_check = s21_shift_left(&tmp, i);
      inf_check = s21_bit_add(*result, tmp, result);
    }
  }
  if (inf_check == INF) {
    if (res_sign)
      res_code = NEG_INF;
    else
      res_code = INF;
    s21_init_decimal(result);
  } else {
    int scale = s21_get_scale(value_1) + s21_get_scale(value_2);
    s21_set_scale(result, scale);
    s21_set_sign(result, res_sign);
  }
  return res_code;
}

int s21_div(s21_decimal divident, s21_decimal divisor, s21_decimal *result) {
  int res_code = OK;
  s21_init_decimal(result);
  s21_decimal zero = {{0, 0, 0, 0}};

  if (s21_is_equal(divisor, zero)) {
    res_code = DIV_BY_ZERO;
    s21_init_decimal(result);
  } else {
    int res_sign = (s21_get_sign(divident) != s21_get_sign(divisor)) ? 1 : 0;
    int beginScale = s21_get_scale(divident) - s21_get_scale(divisor);

    s21_decimal remainder = {0}, tmp = {0};
    s21_set_scale(&divisor, 0);
    s21_set_scale(&divident, 0);
    s21_set_sign(&divisor, 0);
    s21_set_sign(&divident, 0);

    s21_bit_div(divident, divisor, &remainder, &tmp);
    s21_copy_bits(tmp, result);

    s21_decimal border_value = {{4294967295u, 4294967295u, 4294967295u, 0}};
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_set_scale(&border_value, 1);

    int inside_scale = 0;

    for (; inside_scale <= 27 && !s21_is_equal(remainder, zero);) {
      if (!s21_is_less(*result, border_value)) {
        res_code = (res_sign == 0) ? INF : NEG_INF;
        break;
      }
      s21_mul(remainder, ten, &remainder);
      s21_bit_div(remainder, divisor, &remainder, &tmp);
      s21_mul(*result, ten, result);
      s21_bit_add(*result, tmp, result);
      inside_scale++;
    }
    s21_decimal temp;
    int endScale = beginScale + inside_scale;
    for (; endScale > 28;) {
      s21_bit_div(*result, ten, &temp, result);
      endScale--;
    }
    for (; endScale < 0;) {
      s21_mul(*result, ten, result);
      endScale++;
    }
    s21_set_scale(result, endScale);
    s21_set_sign(result, res_sign);
  }

  return res_code;
}