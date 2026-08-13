#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define CORRECT_CALCULATION 0
#define INVALID_MATRIX 1
#define COMPUTATION_ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int sum_calculate_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int sub_calculate_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
double determinant(matrix_t *A, int *result_code);
void swap(matrix_t *A, int i, int *j, double *result);
void gauss_triangle(matrix_t *A, int i, int *result_code);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
void cofactor(matrix_t *result, int *result_code);
int calc_minor(matrix_t *A, matrix_t *result);
void create_minor(matrix_t *A, int index_row, int index_column);
void copy_matrix(matrix_t A, matrix_t *B);
void initializing_matrix(matrix_t *A, double *values);