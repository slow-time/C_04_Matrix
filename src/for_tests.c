#include "s21_matrix.h"

void initializing_matrix(matrix_t *A, double *values) {
  int index_values = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = values[index_values];
      index_values++;
    }
  }
}