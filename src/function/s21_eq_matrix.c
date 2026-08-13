#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result_code = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) {
    result_code = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        long double integer_A = A->matrix[i][j] * 1000000;
        long double integer_B = B->matrix[i][j] * 1000000;
        long long integer_remainder_A = integer_A;
        long long integer_remainder_B = integer_B;
        if (integer_remainder_A != integer_remainder_B) {
          result_code = FAILURE;
        }
      }
    }
  }
  return result_code;
}
