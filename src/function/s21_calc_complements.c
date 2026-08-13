#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int result_code = CORRECT_CALCULATION;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0 ||
      A->columns != A->rows) {
    result_code = INVALID_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    result_code = calc_minor(A, result);

    if (result_code == CORRECT_CALCULATION) {
      cofactor(result, &result_code);
    }
    if (result_code != CORRECT_CALCULATION) {
      s21_remove_matrix(result);
    }
  }
  return result_code;
}

int calc_minor(matrix_t *A, matrix_t *result) {
  int result_code = CORRECT_CALCULATION;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t tmp;
      copy_matrix(*A, &tmp);
      create_minor(&tmp, i, j);
      double determinant_minor = 0;
      result_code = s21_determinant(&tmp, &determinant_minor);
      result->matrix[i][j] = determinant_minor;
      s21_remove_matrix(&tmp);
    }
  }
  return result_code;
}

void create_minor(matrix_t *A, int index_row, int index_column) {
  for (int i = 0, counter_i = 0; i < A->rows - 1; i++, counter_i++) {
    if (i == index_row) {
      counter_i++;
    }
    for (int j = 0, counter_j = 0; j < A->columns - 1; j++, counter_j++) {
      if (j == index_column) {
        counter_j++;
      }
      A->matrix[i][j] = A->matrix[counter_i][counter_j];
    }
  }
  for (int i = 0; i < A->columns; i++) {
    A->matrix[i][A->columns - 1] = 0;
  }
  A->columns -= 1;
  A->rows -= 1;
  free(A->matrix[A->rows]);
}

void copy_matrix(matrix_t A, matrix_t *B) {
  s21_create_matrix(A.rows, A.columns, B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      B->matrix[i][j] = A.matrix[i][j];
    }
  }
}

void cofactor(matrix_t *result, int *result_code) {
  double tmp = -1;
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] *= pow(tmp, i + j + 2);
      if (!isfinite(result->matrix[i][j])) {
        *result_code = COMPUTATION_ERROR;
      }
    }
  }
}