#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int result_code = CORRECT_CALCULATION;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0 ||
      A->columns != A->rows) {
    result_code = INVALID_MATRIX;
  } else {
    double determinant = 0;
    s21_determinant(A, &determinant);
    if (determinant == 0) {
      result_code = COMPUTATION_ERROR;
    } else {
      s21_create_matrix(A->rows, A->columns, result);
      result_code = calc_minor(A, result);
      cofactor(result);
      matrix_t tmp;
      copy_matrix(*result, &tmp);
      s21_remove_matrix(result);
      s21_transpose(&tmp, result);
      s21_remove_matrix(&tmp);
      if (result_code == CORRECT_CALCULATION) {
        double for_mult = 1 / determinant;
        result_code = s21_mult_number(result, for_mult, &tmp);
        s21_remove_matrix(result);
        copy_matrix(tmp, result);
        s21_remove_matrix(&tmp);
      }
      if (result_code != CORRECT_CALCULATION) {
        s21_remove_matrix(result);
      }
    }
  }
  return result_code;
}
