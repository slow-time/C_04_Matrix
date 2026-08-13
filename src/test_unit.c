#include <check.h>

#include "s21_matrix.h"

START_TEST(test_create_and_remove) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(3, 4, &A), 0);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 4);
  s21_remove_matrix(&A);
  ck_assert_ptr_eq(A.matrix, NULL);
}
END_TEST

START_TEST(test_remove_1) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(3, 4, &A), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&A);
  ck_assert_ptr_eq(A.matrix, NULL);
}
END_TEST

START_TEST(test_remove_2) {
  matrix_t *A = NULL;
  s21_remove_matrix(A);
  ck_assert_ptr_eq(A, NULL);
}
END_TEST

START_TEST(test_create_error_1) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(3, 0, &A), 1);
}
END_TEST

START_TEST(test_create_error_2) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(-2, 8, &A), 1);
}
END_TEST

START_TEST(test_remove_null) {
  matrix_t A;
  A.matrix = NULL;
  s21_remove_matrix(&A);
  ck_assert_ptr_eq(A.matrix, NULL);
}
END_TEST

START_TEST(test_eq_1) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(1, 4, &A);
  s21_create_matrix(1, 4, &B);
  double in_A[] = {1.123456, 112345678, 1.123456789, 1.123456};
  double in_B[] = {1.123456, 112345678, 1.123456789, 1.12345677777777};
  initializing_matrix(&A, in_A);
  initializing_matrix(&B, in_B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(1, 4, &A);
  s21_create_matrix(1, 4, &B);
  double in_A[] = {1.123456, 112345678, 1.123456789, 123.123456};
  double in_B[] = {1.123456, 112345678, 1.123456789, 123.123457};
  initializing_matrix(&A, in_A);
  initializing_matrix(&B, in_B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 4, &B);
  double in_A[] = {1.123456, 112345678, 1.123456789, 123.12345};
  double in_B[] = {1.123456, 112345678, 1.123456789, 123.12345};
  initializing_matrix(&A, in_A);
  initializing_matrix(&B, in_B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_4) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 1, &B);
  double in_A[] = {1.123456, 112345678, 1.123456789, 123.12345};
  double in_B[] = {1.123456, 112345678};
  initializing_matrix(&A, in_A);
  initializing_matrix(&B, in_B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_add_1) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(3, 4, &B);
  double for_matrix_A[] = {1.85, 256.78, -543533.0, 985435534.864536,
                           1.85, 256.78, -543533.0, 985435534.864536,
                           1.85, 256.78, -543533.0, 985435534.864536};
  double for_matrix_B[] = {432423.4, 0,   434.0,    4.0, 432423.4, 0,
                           434.0,    4.0, 432423.4, 0,   434.0,    4.0};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), CORRECT_CALCULATION);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (j == 0) ck_assert_double_eq(result.matrix[i][j], 432425.25);
      if (j == 1) ck_assert_double_eq(result.matrix[i][j], 256.78);
      if (j == 2) ck_assert_double_eq(result.matrix[i][j], -543099);
      if (j == 3) ck_assert_double_eq(result.matrix[i][j], 985435538.864536);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_add_2) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  double for_matrix_A[] = {1, 2, 3, DBL_MAX};
  double for_matrix_B[] = {1, 2, 3, DBL_MAX};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), COMPUTATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_add_3) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(1, 2, &B);
  double for_matrix_A[] = {1, 2, 3, 4, 5, 6};
  double for_matrix_B[] = {1, 2};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), COMPUTATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_add_4) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);
  double for_matrix_A[] = {1, 2, 3, 4, 5, 6};
  double for_matrix_B[] = {1, 2, 3, 4};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), COMPUTATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_add_5) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_add_6) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_remove_matrix(&A);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INVALID_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_add_7) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_remove_matrix(&B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INVALID_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_add_8) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  A.rows = 0;
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INVALID_MATRIX);
  A.rows = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_add_9) {
  matrix_t *A = NULL;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sum_matrix(A, &B, &result), INVALID_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_add_10) {
  matrix_t A;
  matrix_t *B = NULL;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_sum_matrix(&A, B, &result), INVALID_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_add_11) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.columns = 0;
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INVALID_MATRIX);
  A.columns = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_add_12) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  B.columns = 0;
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INVALID_MATRIX);
  B.columns = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_add_13) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  B.rows = 0;
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INVALID_MATRIX);
  B.rows = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_add_14) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(2, 2, &B);
  double for_matrix_A[] = {1, 2};
  double for_matrix_B[] = {1, 2, 3, 4};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), COMPUTATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_1) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  double for_matrix_A[] = {1, 2, 3, -DBL_MAX};
  double for_matrix_B[] = {1, 2, 3, DBL_MAX};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), COMPUTATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_2) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(1, 2, &B);
  double for_matrix_A[] = {1, 2, 3, 4, 5, 6};
  double for_matrix_B[] = {1, 2};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), COMPUTATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_3) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 2, &B);
  double for_matrix_A[] = {1, 2, 3, 4};
  double for_matrix_B[] = {1, 2};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), COMPUTATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_4) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_sub_5) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(3, 4, &B);
  double for_matrix_A[] = {1, 256.78, -543533.0, 985435534.864536,
                           1, 256.78, -543533.0, 985435534.864536,
                           1, 256.78, -543533.0, 985435534.864536};
  double for_matrix_B[] = {432423.4, 0,   434.0,    4.0, 432423.4, 0,
                           434.0,    4.0, 432423.4, 0,   434.0,    4.0};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CORRECT_CALCULATION);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (j == 0) ck_assert_double_eq(result.matrix[i][j], -432422.4);
      if (j == 1) ck_assert_double_eq(result.matrix[i][j], 256.78);
      if (j == 2) ck_assert_double_eq(result.matrix[i][j], -543967);
      if (j == 3) ck_assert_double_eq(result.matrix[i][j], 985435530.864536);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_6) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  A.rows = 0;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), INVALID_MATRIX);
  A.rows = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_7) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  A.columns = 0;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), INVALID_MATRIX);
  A.columns = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_8) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  B.columns = 0;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), INVALID_MATRIX);
  B.columns = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_9) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  B.rows = 0;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), INVALID_MATRIX);
  B.rows = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_10) {
  matrix_t *A = NULL;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sub_matrix(A, &B, &result), INVALID_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_11) {
  matrix_t A;
  matrix_t *B = NULL;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_sub_matrix(&A, B, &result), INVALID_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_sub_12) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_remove_matrix(&A);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), INVALID_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_13) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_remove_matrix(&B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), INVALID_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_sub_14) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 1, &B);
  double for_matrix_A[] = {1, 2, 3, 4};
  double for_matrix_B[] = {1, 2};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), COMPUTATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_numb_1) {
  matrix_t A;
  matrix_t result;
  double number = 100000;
  s21_create_matrix(2, 2, &A);
  double for_matrix_A[] = {1, 2, DBL_MAX, 4};
  initializing_matrix(&A, for_matrix_A);
  ck_assert_int_eq(s21_mult_number(&A, number, &result), COMPUTATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_numb_2) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 4, &A);
  double number = 2;
  double for_matrix_A[] = {1, 256.78, -543533,   34.863,
                           1, 256.78, -543533.0, 34.863,
                           1, 256.78, -543533.0, 34.863};
  initializing_matrix(&A, for_matrix_A);
  ck_assert_int_eq(s21_mult_number(&A, number, &result), CORRECT_CALCULATION);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (j == 0) ck_assert_double_eq(result.matrix[i][j], 2);
      if (j == 1) ck_assert_double_eq(result.matrix[i][j], 513.56);
      if (j == 2) ck_assert_double_eq(result.matrix[i][j], -1087066.0);
      if (j == 3) ck_assert_double_eq(result.matrix[i][j], 69.726);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_numb_3) {
  matrix_t A;
  matrix_t result;
  double number = 2;
  s21_create_matrix(2, 3, &A);
  A.rows = 0;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), INVALID_MATRIX);
  A.rows = 2;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_numb_4) {
  matrix_t A;
  matrix_t result;
  double number = 2;
  s21_create_matrix(2, 3, &A);
  A.columns = 0;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), INVALID_MATRIX);
  A.columns = 2;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_numb_5) {
  matrix_t *A = NULL;
  double number = 2;
  matrix_t result;
  ck_assert_int_eq(s21_mult_number(A, number, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_mult_numb_6) {
  matrix_t A;
  double number = 2;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(s21_mult_number(&A, number, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_mult_matrix_1) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  double for_matrix_A[] = {1, 2, -DBL_MAX, 4};
  double for_matrix_B[] = {1, 2, DBL_MAX, 4};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), COMPUTATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(1, 2, &B);
  double for_matrix_A[] = {1, 2, 3, 4, 5, 6};
  double for_matrix_B[] = {1, 2};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INVALID_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_3) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_remove_matrix(&A);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INVALID_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_4) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(2, 3, &B);
  double for_matrix_A[] = {3, 256};
  double for_matrix_B[] = {43.4, 0, 434.0, 4.0, 35.4, 0};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&B, for_matrix_B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), CORRECT_CALCULATION);
  ck_assert_double_eq(result.matrix[0][0], 1154.2);
  ck_assert_double_eq(result.matrix[0][1], 9062.4);
  ck_assert_double_eq(result.matrix[0][2], 1302);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_5) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  A.rows = 0;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INVALID_MATRIX);
  A.rows = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_6) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  A.columns = 0;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INVALID_MATRIX);
  A.columns = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_7) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  B.columns = 0;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INVALID_MATRIX);
  B.columns = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_8) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  B.rows = 0;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INVALID_MATRIX);
  B.rows = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_9) {
  matrix_t *A = NULL;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_mult_matrix(A, &B, &result), INVALID_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_10) {
  matrix_t A;
  matrix_t *B = NULL;
  matrix_t result;
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_mult_matrix(&A, B, &result), INVALID_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_matrix_11) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_remove_matrix(&B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INVALID_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_transp_1) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  A.rows = 0;
  ck_assert_int_eq(s21_transpose(&A, &result), INVALID_MATRIX);
  A.rows = 2;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_transp_2) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  A.columns = 0;
  ck_assert_int_eq(s21_transpose(&A, &result), INVALID_MATRIX);
  A.columns = 2;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_transp_3) {
  matrix_t *A = NULL;
  matrix_t result;
  ck_assert_int_eq(s21_transpose(A, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_transp_4) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(s21_transpose(&A, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_transp_5) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  double for_matrix_A[] = {4, 2, 0, 3, 4, 5};
  initializing_matrix(&A, for_matrix_A);
  ck_assert_int_eq(s21_transpose(&A, &result), CORRECT_CALCULATION);
  ck_assert_double_eq(result.matrix[0][0], A.matrix[0][0]);
  ck_assert_double_eq(result.matrix[1][0], A.matrix[0][1]);
  ck_assert_double_eq(result.matrix[2][0], A.matrix[0][2]);
  ck_assert_double_eq(result.matrix[0][1], A.matrix[1][0]);
  ck_assert_double_eq(result.matrix[1][1], A.matrix[1][1]);
  ck_assert_double_eq(result.matrix[2][1], A.matrix[1][2]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_determinant_1) {
  matrix_t A;
  double result;
  double ten = 10;
  s21_create_matrix(4, 4, &A);
  double for_matrix_A[] = {5, 1, 2, 7, 3, 0, 0, 2, 1, 3, 4, 5, 2, 0, 0, 3};
  initializing_matrix(&A, for_matrix_A);
  ck_assert_int_eq(s21_determinant(&A, &result), CORRECT_CALCULATION);
  ck_assert_double_eq_tol(result, ten, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2) {
  matrix_t *A = NULL;
  double result;
  ck_assert_int_eq(s21_determinant(A, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_determinant_3) {
  matrix_t A;
  A.matrix = NULL;
  double result;
  ck_assert_int_eq(s21_determinant(&A, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_determinant_4) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), INVALID_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_5) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);
  A.rows = 0;
  ck_assert_int_eq(s21_determinant(&A, &result), INVALID_MATRIX);
  A.rows = 3;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_6) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);
  A.columns = 0;
  ck_assert_int_eq(s21_determinant(&A, &result), INVALID_MATRIX);
  A.columns = 3;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_7) {
  matrix_t A;
  double result;
  double t = 0;
  s21_create_matrix(4, 4, &A);
  double for_matrix_A[] = {1, 2, 3, 4, 2, 4, 6, 8, 3, 6, 9, 12, 4, 8, 12, 16};
  initializing_matrix(&A, for_matrix_A);
  ck_assert_int_eq(s21_determinant(&A, &result), CORRECT_CALCULATION);
  ck_assert_double_eq_tol(result, t, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_8) {
  matrix_t A;
  double result;
  double t = 0;
  s21_create_matrix(4, 4, &A);
  double for_matrix_A[] = {1, 2, 3, 4, 2, 4, 6, 8, 1, 11, 2, 2, 0, 1, 1, 1};
  initializing_matrix(&A, for_matrix_A);
  ck_assert_int_eq(s21_determinant(&A, &result), CORRECT_CALCULATION);
  ck_assert_double_eq_tol(result, t, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_comp_1) {
  matrix_t A;
  matrix_t result;
  matrix_t true_result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &true_result);
  double for_matrix_A[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double for_matrix_true_result[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&true_result, for_matrix_true_result);
  ck_assert_int_eq(s21_calc_complements(&A, &result), CORRECT_CALCULATION);
  ck_assert_double_eq(result.matrix[0][0], true_result.matrix[0][0]);
  ck_assert_double_eq(result.matrix[0][1], true_result.matrix[0][1]);
  ck_assert_double_eq(result.matrix[0][2], true_result.matrix[0][2]);
  ck_assert_double_eq(result.matrix[1][0], true_result.matrix[1][0]);
  ck_assert_double_eq(result.matrix[1][1], true_result.matrix[1][1]);
  ck_assert_double_eq(result.matrix[1][2], true_result.matrix[1][2]);
  ck_assert_double_eq(result.matrix[2][0], true_result.matrix[2][0]);
  ck_assert_double_eq(result.matrix[2][1], true_result.matrix[2][1]);
  ck_assert_double_eq(result.matrix[2][2], true_result.matrix[2][2]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(test_calc_comp_2) {
  matrix_t *A = NULL;
  matrix_t result;
  ck_assert_int_eq(s21_calc_complements(A, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_calc_comp_3) {
  matrix_t A;
  matrix_t result;
  A.matrix = NULL;
  ck_assert_int_eq(s21_calc_complements(&A, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_calc_comp_4) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  A.rows = 0;
  ck_assert_int_eq(s21_calc_complements(&A, &result), INVALID_MATRIX);
  A.rows = 3;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_comp_5) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  A.columns = 0;
  ck_assert_int_eq(s21_calc_complements(&A, &result), INVALID_MATRIX);
  A.columns = 3;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_comp_6) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), INVALID_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_1) {
  matrix_t *A = NULL;
  matrix_t result;
  ck_assert_int_eq(s21_inverse_matrix(A, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_inverse_2) {
  matrix_t A;
  A.matrix = NULL;
  matrix_t result;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INVALID_MATRIX);
}
END_TEST

START_TEST(test_inverse_3) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INVALID_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_4) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  A.rows = 0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INVALID_MATRIX);
  A.rows = 3;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_5) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  A.columns = 0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INVALID_MATRIX);
  A.columns = 3;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_6) {
  matrix_t A;
  matrix_t result;
  matrix_t true_result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &true_result);
  double for_matrix_A[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double for_matrix_true_result[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  initializing_matrix(&A, for_matrix_A);
  initializing_matrix(&true_result, for_matrix_true_result);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CORRECT_CALCULATION);
  ck_assert_double_eq(result.matrix[0][0], true_result.matrix[0][0]);
  ck_assert_double_eq(result.matrix[0][1], true_result.matrix[0][1]);
  ck_assert_double_eq(result.matrix[0][2], true_result.matrix[0][2]);
  ck_assert_double_eq(result.matrix[1][0], true_result.matrix[1][0]);
  ck_assert_double_eq(result.matrix[1][1], true_result.matrix[1][1]);
  ck_assert_double_eq(result.matrix[1][2], true_result.matrix[1][2]);
  ck_assert_double_eq(result.matrix[2][0], true_result.matrix[2][0]);
  ck_assert_double_eq(result.matrix[2][1], true_result.matrix[2][1]);
  ck_assert_double_eq(result.matrix[2][2], true_result.matrix[2][2]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

int main(void) {
  Suite *s = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *sr = srunner_create(s);
  int nf;
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_create_and_remove);
  tcase_add_test(tc, test_remove_1);
  tcase_add_test(tc, test_remove_2);
  tcase_add_test(tc, test_create_error_1);
  tcase_add_test(tc, test_create_error_2);
  tcase_add_test(tc, test_remove_null);
  tcase_add_test(tc, test_eq_1);
  tcase_add_test(tc, test_eq_2);
  tcase_add_test(tc, test_eq_3);
  tcase_add_test(tc, test_eq_4);
  tcase_add_test(tc, test_add_1);
  tcase_add_test(tc, test_add_2);
  tcase_add_test(tc, test_add_3);
  tcase_add_test(tc, test_add_4);
  tcase_add_test(tc, test_add_5);
  tcase_add_test(tc, test_add_6);
  tcase_add_test(tc, test_add_7);
  tcase_add_test(tc, test_add_8);
  tcase_add_test(tc, test_add_9);
  tcase_add_test(tc, test_add_10);
  tcase_add_test(tc, test_add_11);
  tcase_add_test(tc, test_add_12);
  tcase_add_test(tc, test_add_13);
  tcase_add_test(tc, test_add_14);
  tcase_add_test(tc, test_sub_1);
  tcase_add_test(tc, test_sub_2);
  tcase_add_test(tc, test_sub_3);
  tcase_add_test(tc, test_sub_4);
  tcase_add_test(tc, test_sub_5);
  tcase_add_test(tc, test_sub_6);
  tcase_add_test(tc, test_sub_7);
  tcase_add_test(tc, test_sub_8);
  tcase_add_test(tc, test_sub_9);
  tcase_add_test(tc, test_sub_10);
  tcase_add_test(tc, test_sub_11);
  tcase_add_test(tc, test_sub_12);
  tcase_add_test(tc, test_sub_13);
  tcase_add_test(tc, test_sub_14);
  tcase_add_test(tc, test_mult_numb_1);
  tcase_add_test(tc, test_mult_numb_2);
  tcase_add_test(tc, test_mult_numb_3);
  tcase_add_test(tc, test_mult_numb_4);
  tcase_add_test(tc, test_mult_numb_5);
  tcase_add_test(tc, test_mult_numb_6);
  tcase_add_test(tc, test_mult_matrix_1);
  tcase_add_test(tc, test_mult_matrix_2);
  tcase_add_test(tc, test_mult_matrix_3);
  tcase_add_test(tc, test_mult_matrix_4);
  tcase_add_test(tc, test_mult_matrix_5);
  tcase_add_test(tc, test_mult_matrix_6);
  tcase_add_test(tc, test_mult_matrix_7);
  tcase_add_test(tc, test_mult_matrix_8);
  tcase_add_test(tc, test_mult_matrix_9);
  tcase_add_test(tc, test_mult_matrix_10);
  tcase_add_test(tc, test_mult_matrix_11);
  tcase_add_test(tc, test_transp_1);
  tcase_add_test(tc, test_transp_2);
  tcase_add_test(tc, test_transp_3);
  tcase_add_test(tc, test_transp_4);
  tcase_add_test(tc, test_transp_5);
  tcase_add_test(tc, test_determinant_1);
  tcase_add_test(tc, test_determinant_2);
  tcase_add_test(tc, test_determinant_3);
  tcase_add_test(tc, test_determinant_4);
  tcase_add_test(tc, test_determinant_5);
  tcase_add_test(tc, test_determinant_6);
  tcase_add_test(tc, test_determinant_7);
  tcase_add_test(tc, test_determinant_8);
  tcase_add_test(tc, test_calc_comp_1);
  tcase_add_test(tc, test_calc_comp_2);
  tcase_add_test(tc, test_calc_comp_3);
  tcase_add_test(tc, test_calc_comp_4);
  tcase_add_test(tc, test_calc_comp_5);
  tcase_add_test(tc, test_calc_comp_6);
  tcase_add_test(tc, test_inverse_1);
  tcase_add_test(tc, test_inverse_2);
  tcase_add_test(tc, test_inverse_3);
  tcase_add_test(tc, test_inverse_4);
  tcase_add_test(tc, test_inverse_5);
  tcase_add_test(tc, test_inverse_6);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
