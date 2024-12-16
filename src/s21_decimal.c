#include "s21_decimal.h"

#define MAX_SCALE 28

// Инициализация децимала
void s21_init_decimal(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}

// Получение знака числа
int s21_get_sign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }

// Установка знака числа
void s21_set_sign(s21_decimal *value, int bit) {
  if (bit) {
    value->bits[3] |= (1u << 31);
  } else {
    value->bits[3] &= ~(1u << 31);
  }
}

// Получение значения бита
int s21_get_bit(s21_decimal value, int bit) {
  return (value.bits[bit / 32] & (1u << (bit % 32))) != 0;
}

void s21_set_bit(s21_decimal *value, int posision, int bit) {
  if (posision / 32 < 4) {
    if (bit)
      value->bits[posision / 32] |= (1u << (posision % 32));
    else
      value->bits[posision / 32] &= ~(1u << (posision % 32));
  }
}

// Получение экспоненты
int s21_get_scale(s21_decimal value) { return (value.bits[3] >> 16) & 255; }

// Установка экспоненты
void s21_set_scale(s21_decimal *value, int scale) {
  value->bits[3] &= ~(255 << 16);
  value->bits[3] |= (scale & 255) << 16;
}

// Проверка на ноль
int s21_dec_is_zero(s21_decimal number) {
  return number.bits[0] == 0 && number.bits[1] == 0 && number.bits[2] == 0;
}

// Сравнение битов
int s21_compare_decimal_bits(s21_decimal value1, s21_decimal value2) {
  // 0 - числа равны, 1 - первое число больше, -1 - второе число больше
  int res = 0;
  for (int i = 95; i >= 0; i--) {
    int bit1 = s21_get_bit(value1, i), bit2 = s21_get_bit(value2, i);

    if (bit1 != bit2) {
      res = (bit1 > bit2) ? 1 : -1;
      break;
    }
  }
  return res;
}

int s21_last_bit(s21_decimal number) {
  int s21_last_bit = 95;
  while (s21_last_bit >= 0 && s21_get_bit(number, s21_last_bit) == 0) {
    s21_last_bit--;
  }
  return s21_last_bit;
}

int s21_shift_left(s21_decimal *value, int offset) {
  int res = OK;
  int lastbit = s21_last_bit(*value);
  if (lastbit + offset > 95) {
    res = INF;
  } else {
    for (int i = 0; i < offset; i++) {
      int bit31 = s21_get_bit(*value, 31);
      int bit63 = s21_get_bit(*value, 63);
      value->bits[0] <<= 1;
      value->bits[1] <<= 1;
      value->bits[2] <<= 1;
      if (bit31) s21_set_bit(value, 32, 1);
      if (bit63) s21_set_bit(value, 64, 1);
    }
  }
  return res;
}

// Выравнивание степеней
void s21_alignment_scale(s21_decimal *value_1, s21_decimal *value_2) {
  int sign1 = s21_get_sign(*value_1);
  int sign2 = s21_get_sign(*value_2);
  s21_decimal ten = {{10u, 0, 0, 0}};
  int scale1 = s21_get_scale(*value_1);
  int scale2 = s21_get_scale(*value_2);

  if (scale1 < scale2) {
    int difference = scale2 - scale1;
    for (int i = 0; i < difference; i++) {
      if (s21_last_bit(*value_1) + 1 <= 95) {
        s21_bit_mul(*value_1, ten, value_1);
      } else {
        s21_decrease_scale(value_2);
      }
    }
    s21_set_scale(value_1, scale2);
  } else if (scale1 > scale2) {
    int difference = scale1 - scale2;
    for (int i = 0; i < difference; i++) {
      if (s21_last_bit(*value_2) + 1 <= 95) {
        s21_bit_mul(*value_2, ten, value_2);
      } else {
        s21_decrease_scale(value_1);
      }
    }
    s21_set_scale(value_2, scale1);
  }
  s21_set_sign(value_1, sign1);
  s21_set_sign(value_2, sign2);
}

void s21_decrease_scale(s21_decimal *a) {
  s21_decimal ten = {{10u, 0, 0, 0}};
  if (s21_last_bit(*a) < 32 && a->bits[0] < 10) a->bits[0] = 0;
  s21_decimal remainder;
  s21_bit_div(*a, ten, &remainder, a);
}

int s21_bit_add(s21_decimal value1, s21_decimal value2, s21_decimal *res) {
  int res_code = OK;
  s21_init_decimal(res);
  int carry = 0;

  for (int i = 0; i < 96; i++) {
    int bit1 = s21_get_bit(value1, i);
    int bit2 = s21_get_bit(value2, i);

    int sum = bit1 + bit2 + carry;
    carry = (sum > 1);  // Если сумма больше 1, то будет перенос

    s21_set_bit(res, i,
                sum % 2);  // Устанавливаем бит, равный сумме по модулю 2

    if (i == 95 && carry)
      res_code = INF;  // Если есть перенос на последнем бите, устанавливаем
                       // флаг переполнения
  }

  return res_code;
}

int s21_bit_sub(s21_decimal num_1, s21_decimal num_2, s21_decimal *result) {
  int res_code = OK;
  s21_init_decimal(result);
  int borrow = 0;
  int lastbit_num1 = s21_last_bit(num_1);

  for (int i = 0; i <= lastbit_num1; i++) {
    int bit1 = s21_get_bit(num_1, i);
    int bit2 = s21_get_bit(num_2, i);
    int bit_diff = bit1 - bit2 - borrow;

    if (bit_diff < 0) {
      bit_diff += 2;
      borrow = 1;
    } else {
      borrow = 0;
    }
    s21_set_bit(result, i, bit_diff);
  }
  if (borrow)
    res_code = INF;  // Если был заимствование после последнего бита, это
                     // признак переполнения

  return res_code;
}

void s21_bit_mul(s21_decimal val1, s21_decimal ten, s21_decimal *result) {
  s21_init_decimal(result);
  s21_decimal tmp;
  int lastbit = s21_last_bit(val1);

  for (int i = 0; i <= lastbit; i++) {
    s21_init_decimal(&tmp);
    int val_bit = s21_get_bit(val1, i);
    if (val_bit) {
      tmp = ten;
      s21_shift_left(&tmp, i);
      s21_bit_add(*result, tmp, result);
    }
  }
}

void s21_bit_div(s21_decimal number1, s21_decimal number2,
                 s21_decimal *remainder, s21_decimal *result) {
  s21_init_decimal(remainder);
  s21_init_decimal(result);

  for (int i = s21_last_bit(number1); i >= 0; i--) {
    if (s21_get_bit(number1, i)) s21_set_bit(remainder, 0, 1);
    if (s21_is_greater_or_equal(*remainder, number2)) {
      s21_bit_sub(*remainder, number2, remainder);
      if (i != 0) s21_shift_left(remainder, 1);
      if (s21_get_bit(number1, i - 1)) s21_set_bit(remainder, 0, 1);
      s21_shift_left(result, 1);
      s21_set_bit(result, 0, 1);
    } else {
      s21_shift_left(result, 1);
      if (i != 0) s21_shift_left(remainder, 1);
      if ((i - 1) >= 0 && s21_get_bit(number1, i - 1))
        s21_set_bit(remainder, 0, 1);
    }
  }
}

void s21_copy_bits(s21_decimal src, s21_decimal *dest) {
  dest->bits[0] = src.bits[0];
  dest->bits[1] = src.bits[1];
  dest->bits[2] = src.bits[2];
  dest->bits[3] = src.bits[3];
}

int s21_get_float_sign(float *src) { return *(int *)src >> 31; }

int s21_get_float_scale(float *src) {
  return ((*(int *)src & ~0x80000000) >> 23) - 127;
}

unsigned int s21_divide_by_10(s21_decimal *value) {
  unsigned long long remainder = 0;

  for (int i = 2; i >= 0; i--) {
    unsigned long long temp =
        (remainder << 32) | (unsigned int)(value->bits[i]);
    value->bits[i] = (temp / 10);
    remainder = temp % 10;
  }

  return (unsigned int)remainder;
}