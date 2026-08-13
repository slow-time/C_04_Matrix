#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_code = CORRECT_CALCULATION;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      A->rows <= 0 || B->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
      A->columns != B->rows) {
    result_code = INVALID_MATRIX;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          if (result_code == CORRECT_CALCULATION) {
            double tmp = A->matrix[i][k] * B->matrix[k][j];
            if (!isfinite(tmp)) {
              result_code = COMPUTATION_ERROR;
            }
            result->matrix[i][j] += tmp;
            if (!isfinite(result->matrix[i][j])) {
              result_code = COMPUTATION_ERROR;
            }
          }
        }
      }
    }
    if (result_code != CORRECT_CALCULATION) s21_remove_matrix(result);
  }
  return result_code;
}
