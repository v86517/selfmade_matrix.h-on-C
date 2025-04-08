#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define MATERROR 1
#define CALCERROR 2

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int determinant(matrix_t *A, double *result);
void minor_matrix(matrix_t *A, int row, int col, matrix_t *minor);
int sarrus(matrix_t *A, double *result);
int gauss(matrix_t *A, double *result);
int change_row(matrix_t *B, int x, double *result);
int is_materror(matrix_t *X);
int is_calcerror(matrix_t *X, matrix_t *Y);
void fill(matrix_t *A, double *mat);
long double s21_fabs(double x);
