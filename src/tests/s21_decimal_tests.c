#include <check.h>
#include <limits.h>

#include "../s21_decimal.h"

START_TEST(test_less_1) {
  s21_decimal decimal1 = {{100, 0, 0, 0x00000000}};  // 100
  s21_decimal decimal2 = {{200, 0, 0, 0x00000000}};  // 200
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_less_2) {
  s21_decimal decimal1 = {{123456, 0, 0, 0x00010000}};  // 12.3456
  s21_decimal decimal2 = {{123456, 0, 0, 0x00020000}};  // 1.23456
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_less_3) {
  s21_decimal decimal1 = {{0, 0, 0, 0x80000000}};  // -0
  s21_decimal decimal2 = {{1, 0, 0, 0x00000000}};  // 1
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_less_4) {
  s21_decimal decimal1 = {{500, 0, 0, 0x80000000}};  // -500
  s21_decimal decimal2 = {{500, 0, 0, 0x00000000}};  // 500
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_less_5) {
  s21_decimal decimal1 = {{500, 0, 0, 0x80000000}};  // -500
  s21_decimal decimal2 = {{400, 0, 0, 0x80000000}};  // -400
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_less_or_equal_1) {
  s21_decimal decimal1 = {{500, 0, 0, 0x00000000}};  // 500
  s21_decimal decimal2 = {{500, 0, 0, 0x00000000}};  // 500
  ck_assert_int_eq(s21_is_less_or_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_less_or_equal_2) {
  s21_decimal decimal1 = {{300, 0, 0, 0x00000000}};  // 300
  s21_decimal decimal2 = {{400, 0, 0, 0x00000000}};  // 400
  ck_assert_int_eq(s21_is_less_or_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_less_or_equal_3) {
  s21_decimal decimal1 = {{1000, 0, 0, 0x80000000}};  // -1000
  s21_decimal decimal2 = {{1000, 0, 0, 0x80000000}};  // -1000
  ck_assert_int_eq(s21_is_less_or_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_less_or_equal_4) {
  s21_decimal decimal1 = {{100, 0, 0, 0x80000000}};  // -100
  s21_decimal decimal2 = {{200, 0, 0, 0x80000000}};  // -200
  ck_assert_int_eq(s21_is_less_or_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_less_or_equal_5) {
  s21_decimal decimal1 = {{9999, 0, 0, 0x00000000}};  // 9999
  s21_decimal decimal2 = {{999, 0, 0, 0x00010000}};   // 99.9
  ck_assert_int_eq(s21_is_less_or_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_greater_1) {
  s21_decimal decimal1 = {{1000, 0, 0, 0x00000000}};  // 1000
  s21_decimal decimal2 = {{500, 0, 0, 0x00000000}};   // 500
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_greater_2) {
  s21_decimal decimal1 = {{1000, 0, 0, 0x80000000}};  // -1000
  s21_decimal decimal2 = {{500, 0, 0, 0x80000000}};   // -500
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_greater_3) {
  s21_decimal decimal1 = {{123456, 0, 0, 0x00020000}};  // 1.23456
  s21_decimal decimal2 = {{123456, 0, 0, 0x00010000}};  // 12.3456
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_greater_4) {
  s21_decimal decimal1 = {{0, 0, 0, 0x00000000}};  // 0
  s21_decimal decimal2 = {{0, 0, 0, 0x80000000}};  // -0
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_greater_5) {
  s21_decimal decimal1 = {{100, 0, 0, 0x00010000}};  // 10.0
  s21_decimal decimal2 = {{10, 0, 0, 0x00000000}};   // 10
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_greater_or_equal_1) {
  s21_decimal decimal1 = {{123, 0, 0, 0x00000000}};  // 123
  s21_decimal decimal2 = {{123, 0, 0, 0x00000000}};  // 123
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_greater_or_equal_2) {
  s21_decimal decimal1 = {{9876, 0, 0, 0x00000000}};  // 9876
  s21_decimal decimal2 = {{8765, 0, 0, 0x00000000}};  // 8765
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_greater_or_equal_3) {
  s21_decimal decimal1 = {{12345, 0, 0, 0x80000000}};  // -12345
  s21_decimal decimal2 = {{12345, 0, 0, 0x00000000}};  // 12345
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_greater_or_equal_4) {
  s21_decimal decimal1 = {{1, 0, 0, 0x00010000}};   // 0.1
  s21_decimal decimal2 = {{10, 0, 0, 0x00020000}};  // 0.10
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_greater_or_equal_5) {
  s21_decimal decimal1 = {{1, 0, 0, 0x80000000}};  // -1
  s21_decimal decimal2 = {{1, 0, 0, 0x80000000}};  // -1
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_equal_1) {
  s21_decimal decimal1 = {{100, 0, 0, 0x00000000}};  // 100
  s21_decimal decimal2 = {{100, 0, 0, 0x00000000}};  // 100
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_equal_2) {
  s21_decimal decimal1 = {{0, 0, 0, 0x00000000}};  // 0
  s21_decimal decimal2 = {{0, 0, 0, 0x80000000}};  // -0
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_equal_3) {
  s21_decimal decimal1 = {{9999, 0, 0, 0x00040000}};  // 0.9999
  s21_decimal decimal2 = {{999, 0, 0, 0x00030000}};   // 0.999
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_equal_4) {
  s21_decimal decimal1 = {{123456, 0, 0, 0x00010000}};  // 12.3456
  s21_decimal decimal2 = {{123456, 0, 0, 0x00010000}};  // 12.3456
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_equal_5) {
  s21_decimal decimal1 = {{500, 0, 0, 0x80000000}};  // -500
  s21_decimal decimal2 = {{500, 0, 0, 0x80000000}};  // -500
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_not_equal_1) {
  s21_decimal decimal1 = {{100, 0, 0, 0x00000000}};  // 100
  s21_decimal decimal2 = {{200, 0, 0, 0x00000000}};  // 200
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_not_equal_2) {
  s21_decimal decimal1 = {{1234, 0, 0, 0x80000000}};  // -1234
  s21_decimal decimal2 = {{1234, 0, 0, 0x80000000}};  // -1234
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_not_equal_3) {
  s21_decimal decimal1 = {{9999, 0, 0, 0x00040000}};  // 0.9999
  s21_decimal decimal2 = {{999, 0, 0, 0x00030000}};   // 0.999
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_not_equal_4) {
  s21_decimal decimal1 = {{999, 0, 0, 0x00030000}};   // 0.999
  s21_decimal decimal2 = {{1000, 0, 0, 0x00030000}};  // 1.000
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_not_equal_5) {
  s21_decimal decimal1 = {{0, 0, 0, 0x00000000}};  // 0
  s21_decimal decimal2 = {{1, 0, 0, 0x00000000}};  // 1
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(round_1) {
  s21_decimal val = {{3, 3, 3, ~(0xffffffff / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_2) {
  s21_decimal val = {{3, 3, 3, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_3) {
  s21_decimal val = {{7, 7, 7, ~(0xffffffff / 2)}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_4) {
  s21_decimal val = {{25, 0, 0, ~(0xffffffff / 2)}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_5) {
  s21_decimal val = {{26, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_6) {
  s21_decimal val = {{115, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_7) {
  s21_decimal val = {{118, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_8) {
  s21_decimal val = {{125, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_11) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_12) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

// START_TEST(round_15) {
//   s21_decimal src1 = {0};
//   src1.bits[0] = 0b01010101001110101110101110110001;
//   src1.bits[1] = 0b00001101101101001101101001011111;
//   src1.bits[2] = 0b00000000000000000000000000000000;
//   src1.bits[3] = 0b10000000000100100000000000000000;
//   s21_decimal result = {0};
//   result.bits[0] = 0b00000000000000000000000000000001;
//   result.bits[1] = 0b00000000000000000000000000000000;
//   result.bits[2] = 0b00000000000000000000000000000000;
//   result.bits[3] = 0b10000000000000000000000000000000;
//   s21_decimal res_od = {0};
//   s21_round(src1, &res_od);
//   ck_assert_float_eq(res_od.bits[0], result.bits[0]);
//   ck_assert_float_eq(res_od.bits[1], result.bits[1]);
//   ck_assert_float_eq(res_od.bits[2], result.bits[2]);
//   ck_assert_float_eq(res_od.bits[3], result.bits[3]);
// }
// END_TEST

START_TEST(test_truncate_1) {
  s21_decimal dec1 = {0};
  dec1.bits[0] = 0b00000000000000000000000011010011;  // 21.1
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000010101;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1 = {0};
  s21_truncate(dec1, &res1);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_truncate_2) {
  s21_decimal dec1 = {0};
  dec1.bits[0] = 0b00000000000000000000000010100101;
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000010000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1 = {0};
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_truncate_4) {
  s21_decimal dec1 = {0};

  dec1.bits[3] = 0x000A0000;
  dec1.bits[2] = 0x0;
  dec1.bits[1] = 0xFFFFFFFF;
  dec1.bits[0] = 0xFFFFFFFF;
  s21_decimal result = {0};
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  s21_decimal res1 = {0};
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_truncate_5) {
  s21_decimal dec1 = {0};

  dec1.bits[3] = 0b10000000000011000000000000000000;
  dec1.bits[2] = 0x0;
  dec1.bits[1] = 0xFFFFFFFF;
  dec1.bits[0] = 0xFFFFFFFF;
  s21_decimal result = {0};
  result.bits[3] = 0b10000000000000000000000000000000;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x1197998;
  s21_decimal res1 = {0};
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_truncate_6) {
  s21_decimal dec1 = {0};

  dec1.bits[3] = 0x80000000;
  dec1.bits[2] = 0x0;
  dec1.bits[1] = 0xFFFFFFFF;
  dec1.bits[0] = 0xFFFFFFFF;
  s21_decimal result = {0};
  result.bits[3] = 0x80000000;
  result.bits[2] = 0x0;
  result.bits[1] = 0xFFFFFFFF;
  result.bits[0] = 0xFFFFFFFF;
  s21_decimal res1 = {0};
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_truncate_7) {
  s21_decimal dec1 = {0};

  dec1.bits[0] = 0b00000000000000000000000001101101;
  dec1.bits[1] = 0b00000000000011000110010101011011;
  dec1.bits[2] = 0b00000000000000000011000000111001;
  dec1.bits[3] = 0b00000000000011100000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1 = {0};
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_truncate_8) {
  s21_decimal dec1 = {0};

  dec1.bits[3] = 0x80090000;
  dec1.bits[2] = 0;
  dec1.bits[1] = 0xFFFFEA34;
  dec1.bits[0] = 0xFF837E4F;
  s21_decimal result = {0};
  s21_truncate(dec1, &result);
  s21_decimal res1 = {0};

  res1.bits[3] = 0x80000000;
  res1.bits[2] = 0;
  res1.bits[1] = 0x4;
  res1.bits[0] = 0x4B829C70;
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_truncate_9) {
  s21_decimal dec1 = {0};

  dec1.bits[0] = 0b11010000101000110011000001101101;
  dec1.bits[1] = 0b00011111100110100110101101011000;
  dec1.bits[2] = 0;
  dec1.bits[3] = 0b00000000000010010000000000000000;
  s21_decimal result = {0};
  s21_truncate(dec1, &result);
  s21_decimal result_origin;
  result_origin.bits[3] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b10000111101111000001011000011110;
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_truncate_10) {
  s21_decimal dec1 = {0};

  dec1.bits[0] = 0b01111000101001111011110011000110;
  dec1.bits[1] = 0b10011111111111001111101010000100;
  dec1.bits[2] = 0b00011111111010011010111101101101;
  dec1.bits[3] = 0b00000000000111000000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1 = {0};
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_truncate_11) {
  // 6766
  s21_decimal src1, origin;
  // src1 = 2;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_truncate_12) {
  // 6787
  s21_decimal src1, origin;
  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_truncate_13) {
  // 6808
  s21_decimal src1, origin;
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_truncate_14) {
  // 6829
  s21_decimal src1, origin;
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_truncate_15) {
  // 6850
  s21_decimal src1, origin;
  // src1 = -9878798789;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b01001100110100101000000111000101;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_negate_1) {
  s21_decimal decimal = {{100, 0, 0, 0x00000000}};   // 100
  s21_decimal expected = {{100, 0, 0, 0x80000000}};  // -100
  s21_decimal result;
  s21_negate(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_negate_2) {
  s21_decimal decimal = {{0, 0, 0, 0x00000000}};   // 0
  s21_decimal expected = {{0, 0, 0, 0x80000000}};  // -0
  s21_decimal result;
  s21_negate(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_negate_3) {
  s21_decimal decimal = {{9999, 0, 0, 0x00040000}};   // 0.9999
  s21_decimal expected = {{9999, 0, 0, 0x80040000}};  // -0.9999
  s21_decimal result;
  s21_negate(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_negate_4) {
  s21_decimal decimal = {{123456, 0, 0, 0x00010000}};   // 12.3456
  s21_decimal expected = {{123456, 0, 0, 0x80010000}};  // -12.3456
  s21_decimal result;
  s21_negate(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_negate_5) {
  s21_decimal decimal = {{500, 0, 0, 0x80000000}};   // -500
  s21_decimal expected = {{500, 0, 0, 0x00000000}};  // 500
  s21_decimal result;
  s21_negate(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(floor_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_set_scale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_scale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

START_TEST(floor_5) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_6) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_set_sign(&value_1, 1);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_7) {
  s21_decimal src1;
  src1.bits[0] = 0b00001111111111111111111111111111;
  src1.bits[1] = 0b00111110001001010000001001100001;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal res_od = {0};
  s21_floor(src1, &res_od);
  s21_decimal result = {0};
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_3) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(sub_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_8) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_9) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_14) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_15) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_18) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_19) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_from_decimal_to_intTest1) {
  // 6556
  s21_decimal src1;
  // src1 = 2;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest2) {
  // 6570
  s21_decimal src1;
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest3) {
  // 6584
  s21_decimal src1;
  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 3);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest4) {
  // 6598
  s21_decimal src1;
  // src1 = 4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 4);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest5) {
  // 6612
  s21_decimal src1;
  // src1 = -4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -4);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest11) {
  // 6696
  s21_decimal src1;
  // src1 = 1;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest12) {
  // 6710
  s21_decimal src1;
  // src1 = 1.25;

  src1.bits[0] = 0b00000000000000000000000001111101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000100000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest13) {
  // 6724
  s21_decimal src1;
  // src1 = -1.25;

  src1.bits[0] = 0b00000000000000000000000001111101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest14) {
  // 6738
  s21_decimal src1;
  // src1 = -12.25;

  src1.bits[0] = 0b00000000000000000000010011001001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -12);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest15) {
  // 6752
  s21_decimal src1;
  // src1 = -3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -3);
}
END_TEST

START_TEST(test_mul_1) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_decimal value_2 = {{7, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal excepted_result = {{105, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_mul_2) {
  s21_decimal value_1 = {{125, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal excepted_result = {{1250, 0, 0, 0}};
  s21_set_sign(&excepted_result, 1);
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_mul_3) {
  s21_decimal value_1 = {{1415, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{23, 0, 0, 0}};
  s21_set_sign(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal excepted_result = {{32545, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_mul_4) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  s21_set_scale(&value_1, 3);
  s21_decimal value_2 = {{54321, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal excepted_result = {{670592745, 0, 0, 0}};
  s21_set_scale(&excepted_result, 5);
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_mul_5) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal excepted_result = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &excepted_result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, INF);
}
END_TEST

START_TEST(test_mul_6) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_set_sign(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal excepted_result = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &excepted_result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, NEG_INF);
}
END_TEST

START_TEST(test_mul_7) {
  s21_decimal value_1 = {{17, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result;
  s21_decimal excepted_result = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_div_1) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal excepted_result = {{2469, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_div_2) {
  s21_decimal value_1 = {{256, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal excepted_result = {{128, 0, 0, 0}};
  s21_set_sign(&excepted_result, 1);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_div_3) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal excepted_result = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &excepted_result);
  ck_assert_int_eq(return_value, DIV_BY_ZERO);
}
END_TEST

START_TEST(test_div_4) {
  s21_decimal value_1 = {{100, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_decimal value_2 = {{8, 0, 0, 0}};
  s21_set_scale(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal excepted_result = {{125, 0, 0, 0}};
  s21_set_scale(&excepted_result, 1);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_div_5) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_set_scale(&value_2, 28);
  s21_decimal result = {{0}};
  ck_assert(s21_div(value_1, value_2, &result) == INF);
}
END_TEST

START_TEST(test_div_6) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_set_scale(&value_2, 28);
  s21_set_sign(&value_2, 1);
  s21_decimal result = {{0}};
  ck_assert(s21_div(value_1, value_2, &result) == NEG_INF);
}
END_TEST

START_TEST(test_div_7) {
  s21_decimal divisible = {{1, 0, 0, 0}};
  s21_decimal divider = {{3, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected_result = {{0x05555555, 0x14B700CB, 0xAC544CA, 0}};
  s21_set_scale(&expected_result, 28);
  ck_assert(s21_div(divisible, divider, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result));
}
END_TEST

START_TEST(test_div_8) {
  s21_decimal divisible = {{0, 0, 0, 0}};

  s21_decimal divider = {{3, 0, 0, 0}};
  s21_decimal result = {{0}};

  s21_decimal expected_result = {{0, 0, 0, 0}};
  ck_assert(s21_div(divisible, divider, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result));
}
END_TEST

START_TEST(test_from_int_to_decimal_1) {
  int src = 258456;
  s21_decimal excepted_result = {{258456, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_int_to_decimal_2) {
  int src = -987654;
  s21_decimal excepted_result = {{987654, 0, 0, 0}};
  s21_set_sign(&excepted_result, 1);
  s21_decimal result;
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_int_to_decimal_3) {
  int src = -0;
  s21_decimal excepted_result = {{0, 0, 0, 0}};
  s21_set_sign(&excepted_result, 1);
  s21_decimal result;
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_decimal_to_float_1) {
  s21_decimal value = {{1812, 0, 0, 0}};
  s21_set_sign(&value, 1);
  float result;
  float excepted_result = -1812;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, excepted_result);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_decimal_to_float_2) {
  s21_decimal value = {{12345, 0, 0, 0}};
  s21_set_scale(&value, 4);
  float result;
  float excepted_result = 1.2345;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, excepted_result);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_decimal_to_float_3) {
  s21_decimal value = {{34567, 0, 0, 0}};
  s21_set_scale(&value, 3);
  s21_set_sign(&value, 1);
  float result;
  float excepted_result = -34.567;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, excepted_result);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_decimal_to_float_4) {
  s21_decimal value = {{0xFFFFFF, 0, 0, 0}};
  float result;
  float excepted_result = 16777215;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, excepted_result);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_decimal_to_int_1) {
  s21_decimal value = {{789456, 0, 0, 0}};
  int dst;
  int excepted_result = 789456;
  int return_value = s21_from_decimal_to_int(value, &dst);
  ck_assert_int_eq(dst, excepted_result);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_decimal_to_int_2) {
  s21_decimal value = {{49135648, 0, 0, 0}};
  s21_set_scale(&value, 1);
  int dst;
  int excepted_result = 4913564;
  int return_value = s21_from_decimal_to_int(value, &dst);
  ck_assert_int_eq(dst, excepted_result);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_decimal_to_int_3) {
  s21_decimal value = {{1234567, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_scale(&value, 2);
  int dst;
  int excepted_result = -12345;
  int return_value = s21_from_decimal_to_int(value, &dst);
  ck_assert_int_eq(dst, excepted_result);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_float_to_decimal_1) {
  float f = 0.07;
  s21_decimal result = {{0}};
  s21_decimal excepted_result = {{7, 0, 0, 0}};
  s21_set_scale(&excepted_result, 2);
  int return_value = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, excepted_result), 1);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_float_to_decimal_2) {
  float f = -128.023;
  s21_decimal result;
  s21_decimal check = {{12802299, 0, 0, 0}};
  s21_set_scale(&check, 5);
  s21_set_sign(&check, 1);
  int return_value = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, CONVERT_OK);
}
END_TEST

START_TEST(test_from_float_to_decimal_3) {
  float f = 1.0 / 0.0;
  s21_decimal result;
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, CONVERT_ERROR);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_decimal");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_less_1);
  tcase_add_test(tc_core, test_less_2);
  tcase_add_test(tc_core, test_less_3);
  tcase_add_test(tc_core, test_less_4);
  tcase_add_test(tc_core, test_less_5);

  tcase_add_test(tc_core, test_less_or_equal_1);
  tcase_add_test(tc_core, test_less_or_equal_2);
  tcase_add_test(tc_core, test_less_or_equal_3);
  tcase_add_test(tc_core, test_less_or_equal_4);
  tcase_add_test(tc_core, test_less_or_equal_5);

  tcase_add_test(tc_core, test_greater_1);
  tcase_add_test(tc_core, test_greater_2);
  tcase_add_test(tc_core, test_greater_3);
  tcase_add_test(tc_core, test_greater_4);
  tcase_add_test(tc_core, test_greater_5);

  tcase_add_test(tc_core, test_greater_or_equal_1);
  tcase_add_test(tc_core, test_greater_or_equal_2);
  tcase_add_test(tc_core, test_greater_or_equal_3);
  tcase_add_test(tc_core, test_greater_or_equal_4);
  tcase_add_test(tc_core, test_greater_or_equal_5);

  tcase_add_test(tc_core, test_equal_1);
  tcase_add_test(tc_core, test_equal_2);
  tcase_add_test(tc_core, test_equal_3);
  tcase_add_test(tc_core, test_equal_4);
  tcase_add_test(tc_core, test_equal_5);

  tcase_add_test(tc_core, test_not_equal_1);
  tcase_add_test(tc_core, test_not_equal_2);
  tcase_add_test(tc_core, test_not_equal_3);
  tcase_add_test(tc_core, test_not_equal_4);
  tcase_add_test(tc_core, test_not_equal_5);

  tcase_add_test(tc_core, round_1);
  tcase_add_test(tc_core, round_2);
  tcase_add_test(tc_core, round_3);
  tcase_add_test(tc_core, round_4);
  tcase_add_test(tc_core, round_5);
  tcase_add_test(tc_core, round_6);
  tcase_add_test(tc_core, round_7);
  tcase_add_test(tc_core, round_8);
  tcase_add_test(tc_core, round_11);
  tcase_add_test(tc_core, round_12);
  // tcase_add_test(tc_core, round_15);

  tcase_add_test(tc_core, test_truncate_1);
  tcase_add_test(tc_core, test_truncate_2);
  tcase_add_test(tc_core, test_truncate_4);
  tcase_add_test(tc_core, test_truncate_5);
  tcase_add_test(tc_core, test_truncate_6);
  tcase_add_test(tc_core, test_truncate_7);
  tcase_add_test(tc_core, test_truncate_8);
  tcase_add_test(tc_core, test_truncate_9);
  tcase_add_test(tc_core, test_truncate_10);
  tcase_add_test(tc_core, test_truncate_11);
  tcase_add_test(tc_core, test_truncate_12);
  tcase_add_test(tc_core, test_truncate_13);
  tcase_add_test(tc_core, test_truncate_14);
  tcase_add_test(tc_core, test_truncate_15);

  tcase_add_test(tc_core, test_negate_1);
  tcase_add_test(tc_core, test_negate_2);
  tcase_add_test(tc_core, test_negate_3);
  tcase_add_test(tc_core, test_negate_4);
  tcase_add_test(tc_core, test_negate_5);

  tcase_add_test(tc_core, floor_1);
  tcase_add_test(tc_core, floor_2);
  tcase_add_test(tc_core, floor_3);
  tcase_add_test(tc_core, floor_5);
  tcase_add_test(tc_core, floor_6);
  tcase_add_test(tc_core, floor_7);

  tcase_add_test(tc_core, add_0);  // s21_add
  tcase_add_test(tc_core, add_1);
  tcase_add_test(tc_core, add_2);
  tcase_add_test(tc_core, add_3);
  tcase_add_test(tc_core, add_4);
  tcase_add_test(tc_core, add_5);
  tcase_add_test(tc_core, add_6);
  tcase_add_test(tc_core, add_7);
  tcase_add_test(tc_core, add_8);
  tcase_add_test(tc_core, add_9);
  tcase_add_test(tc_core, add_10);
  tcase_add_test(tc_core, add_11);
  tcase_add_test(tc_core, add_12);
  tcase_add_test(tc_core, add_13);
  tcase_add_test(tc_core, add_14);
  tcase_add_test(tc_core, add_15);
  tcase_add_test(tc_core, add_16);

  tcase_add_test(tc_core, sub_0);  // s21_sub
  tcase_add_test(tc_core, sub_1);
  tcase_add_test(tc_core, sub_2);
  tcase_add_test(tc_core, sub_3);
  tcase_add_test(tc_core, sub_4);
  tcase_add_test(tc_core, sub_5);
  tcase_add_test(tc_core, sub_6);
  tcase_add_test(tc_core, sub_7);
  tcase_add_test(tc_core, sub_8);
  tcase_add_test(tc_core, sub_9);
  tcase_add_test(tc_core, sub_10);
  tcase_add_test(tc_core, sub_11);
  tcase_add_test(tc_core, sub_12);
  tcase_add_test(tc_core, sub_13);
  tcase_add_test(tc_core, sub_14);
  tcase_add_test(tc_core, sub_15);
  tcase_add_test(tc_core, sub_16);
  tcase_add_test(tc_core, sub_17);
  tcase_add_test(tc_core, sub_18);
  tcase_add_test(tc_core, sub_19);

  tcase_add_test(tc_core, s21_from_decimal_to_intTest1);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest2);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest3);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest4);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest5);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest11);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest12);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest13);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest14);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest15);

  tcase_add_test(tc_core, test_mul_1);
  tcase_add_test(tc_core, test_mul_2);
  tcase_add_test(tc_core, test_mul_3);
  tcase_add_test(tc_core, test_mul_4);
  tcase_add_test(tc_core, test_mul_5);
  tcase_add_test(tc_core, test_mul_6);
  tcase_add_test(tc_core, test_mul_7);

  tcase_add_test(tc_core, test_div_1);
  tcase_add_test(tc_core, test_div_2);
  tcase_add_test(tc_core, test_div_3);
  tcase_add_test(tc_core, test_div_4);
  tcase_add_test(tc_core, test_div_5);
  tcase_add_test(tc_core, test_div_6);
  tcase_add_test(tc_core, test_div_7);
  tcase_add_test(tc_core, test_div_8);

  tcase_add_test(tc_core, test_from_int_to_decimal_1);
  tcase_add_test(tc_core, test_from_int_to_decimal_2);
  tcase_add_test(tc_core, test_from_int_to_decimal_3);

  tcase_add_test(tc_core, test_from_float_to_decimal_1);
  tcase_add_test(tc_core, test_from_float_to_decimal_2);
  tcase_add_test(tc_core, test_from_float_to_decimal_3);

  tcase_add_test(tc_core, test_from_decimal_to_int_1);
  tcase_add_test(tc_core, test_from_decimal_to_int_2);
  tcase_add_test(tc_core, test_from_decimal_to_int_3);

  tcase_add_test(tc_core, test_from_decimal_to_float_1);
  tcase_add_test(tc_core, test_from_decimal_to_float_2);
  tcase_add_test(tc_core, test_from_decimal_to_float_3);
  tcase_add_test(tc_core, test_from_decimal_to_float_4);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_decimal_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}