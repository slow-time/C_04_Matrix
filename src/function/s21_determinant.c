#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int result_code = CORRECT_CALCULATION;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0 ||
      A->columns != A->rows) {
    result_code = INVALID_MATRIX;
  } else {
    if (A->columns == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      matrix_t tmp;
      copy_matrix(*A, &tmp);
      *result = determinant(&tmp, &result_code);
      s21_remove_matrix(&tmp);
      if (result_code != CORRECT_CALCULATION) {
        *result = 0;
      }
    }
  }

  return result_code;
}

double determinant(matrix_t *A, int *result_code) {
  double result = 1.0;
  bool det_not_null = true;
  for (int i = 0; i < A->rows; i++) {
    if (fabs(A->matrix[i][i]) < 1e-07) {
      for (int j = i; j < A->rows; j++) {
        swap(A, i, &j, &result);
      }
      if (fabs(A->matrix[i][i]) < 1e-07) {
        det_not_null = false;
        result = 0.0;
      }
    }

    if (det_not_null) {
      gauss_triangle(A, i, result_code);
    }
  }

  if (det_not_null) {
    for (int i = 0; i < A->rows; i++) {
      result *= A->matrix[i][i];
      if (!isfinite(result)) {
        *result_code = COMPUTATION_ERROR;
      }
    }
  }

  return result;
}

void swap(matrix_t *A, int i, int *j, double *result) {
  if (fabs(A->matrix[*j][i]) > 1e-07) {
    for (int k = i + 1; k < A->rows; k++) {
      double temp = A->matrix[i][k];
      A->matrix[i][k] = A->matrix[*j][k];
      A->matrix[*j][k] = temp;
    }
    *result *= -1.0;
    *j = A->rows;
  }
}

void gauss_triangle(matrix_t *A, int i, int *result_code) {
  for (int j = i + 1; j < A->rows; j++) {
    double factor = A->matrix[j][i] / A->matrix[i][i];
    for (int k = i; k < A->rows; k++) {
      double tmp = factor * A->matrix[i][k];
      A->matrix[j][k] -= tmp;

      if (!(isfinite(tmp) && isfinite(A->matrix[j][k]))) {
        *result_code = COMPUTATION_ERROR;
      }
    }
  }
}
