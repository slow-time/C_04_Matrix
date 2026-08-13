#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int result_code = CORRECT_CALCULATION;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0 ||
      A->columns != A->rows) {
    result_code = INVALID_MATRIX;
  } else {
    *result = determinant(A, &result_code);
  }
  if (result_code != CORRECT_CALCULATION) {
    *result = 0;
  }
  return result_code;
}

double determinant(matrix_t *A, int *result_code) {
  double result = 0;
  if (A->columns == 1) {
    result = A->matrix[0][0];
  } else if (A->columns == 2) {
    result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int j = 0; j < A->columns; j++) {
      double minus_one = -1;
      matrix_t tmp;
      copy_matrix(*A, &tmp);
      create_minor(&tmp, 0, j);
      result += pow(minus_one, j + 2) * A->matrix[0][j] *
                determinant(&tmp, result_code);
      s21_remove_matrix(&tmp);
    }
  }
  if (!isfinite(result)) {
    *result_code = COMPUTATION_ERROR;
  }
  return result;
}
