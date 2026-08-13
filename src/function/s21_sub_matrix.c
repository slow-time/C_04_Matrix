#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_code = CORRECT_CALCULATION;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      A->rows <= 0 || B->rows <= 0 || A->columns <= 0 || B->columns <= 0) {
    result_code = INVALID_MATRIX;
  } else {
    if (A->rows != B->rows || A->columns != B->columns) {
      result_code = COMPUTATION_ERROR;
    } else {
      result_code = sub_calculate_matrix(A, B, result);
    }
  }
  return result_code;
}

int sub_calculate_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_code = CORRECT_CALCULATION;
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      if (!isfinite(result->matrix[i][j])) {
        result_code = COMPUTATION_ERROR;
      }
    }
  }
  if (result_code != CORRECT_CALCULATION) s21_remove_matrix(result);
  return result_code;
}