#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int result_code = CORRECT_CALCULATION;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    result_code = INVALID_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return result_code;
}