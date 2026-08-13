#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int result_code = CORRECT_CALCULATION;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    result_code = INVALID_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (result_code == CORRECT_CALCULATION) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
        if (!isfinite(result->matrix[i][j])) {
          result_code = COMPUTATION_ERROR;
        }
      }
    }
    if (result_code != CORRECT_CALCULATION) s21_remove_matrix(result);
  }
  return result_code;
}