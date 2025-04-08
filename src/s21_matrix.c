#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (rows < 1 || columns < 1 || result == NULL) {
    res = MATERROR;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      free(result->matrix);
      res = MATERROR;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          for (int j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          res = MATERROR;
        }
      }
    }
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  unsigned int res = SUCCESS;
  if (is_materror(A) || is_materror(B) || is_calcerror(A, B)) {
    res = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (s21_fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          res = FAILURE;
          break;
        }
      }
      if (res == FAILURE) break;
    }
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (is_materror(A) || is_materror(B) || result == NULL) {
    res = MATERROR;
  } else if (is_calcerror(A, B)) {
    res = CALCERROR;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    res = MATERROR;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (is_materror(A) || is_materror(B) || result == NULL) {
    res = MATERROR;
  } else if (is_calcerror(A, B)) {
    res = CALCERROR;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    res = MATERROR;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (is_materror(A) || result == NULL) {
    res = MATERROR;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    res = MATERROR;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = number * A->matrix[i][j];
      }
    }
  }
  return res;
}

/*
C(1,1) = A(1,1) × B(1,1) + A(1,2) × B(2,1) = 1 × 1 + 4 × 2 = 1 + 8 = 9
C(1,2) = A(1,1) × B(1,2) + A(1,2) × B(2,2) = 1 × (-1) + 4 × 3 = (-1) + 12 = 11
C(1,3) = A(1,1) × B(1,3) + A(1,2) × B(2,3) = 1 × 1 + 4 × 4 = 1 + 16 = 17
C(2,1) = A(2,1) × B(1,1) + A(2,2) × B(2,1) = 2 × 1 + 5 × 2 = 2 + 10 = 12
C(2,2) = A(2,1) × B(1,2) + A(2,2) × B(2,2) = 2 × (-1) + 5 × 3 = (-2) + 15 = 13
C(2,3) = A(2,1) × B(1,3) + A(2,2) × B(2,3) = 2 × 1 + 5 × 4 = 2 + 20 = 22
C(3,1) = A(3,1) × B(1,1) + A(3,2) × B(2,1) = 3 × 1 + 6 × 2 = 3 + 12 = 15
C(3,2) = A(3,1) × B(1,2) + A(3,2) × B(2,2) = 3 × (-1) + 6 × 3 = (-3) + 18 = 15
C(3,3) = A(3,1) × B(1,3) + A(3,2) × B(2,3) = 3 × 1 + 6 × 4 = 3 + 24 = 27
*/
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (is_materror(A) || is_materror(B) || result == NULL) {
    res = MATERROR;
  } else if (A->columns != B->rows) {
    res = CALCERROR;
  } else if (s21_create_matrix(A->rows, B->columns, result) != OK) {
    res = MATERROR;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (is_materror(A) || result == NULL) {
    res = MATERROR;
  } else if (s21_create_matrix(A->columns, A->rows, result) != OK) {
    res = MATERROR;
  } else {
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (is_materror(A) || result == NULL) {
    res = MATERROR;
  } else if (A->columns != A->rows) {
    res = CALCERROR;
  } else {
    res = determinant(A, result);
  }
  return res;
}

int determinant(matrix_t *A, double *result) {
  int res = OK;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else if (A->rows == 3) {
    res = sarrus(A, result);
  } else {
    res = gauss(A, result);
  }
  return res;
}

int sarrus(matrix_t *A, double *result) {
  int res = OK;
  matrix_t temp_matrix;
  if (s21_create_matrix(A->rows, (A->columns) * 2 - 1, &temp_matrix) != OK) {
    res = MATERROR;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        temp_matrix.matrix[i][j] = A->matrix[i][j];
      }
    }
    for (int i = 0; i < A->rows; i++) {
      for (int j = A->columns, k = 0; j < temp_matrix.columns; j++, k++) {
        temp_matrix.matrix[i][j] = A->matrix[i][k];
      }
    }
    double diag_mul = 1;
    *result = 0;
    for (int k = 0; k < A->rows; k++) {
      for (int i = 0, j = 0 + k; i < A->rows; i++, j++) {
        diag_mul *= temp_matrix.matrix[i][j];
      }
      *result += diag_mul;
      diag_mul = 1;
    }
    diag_mul = 1;
    for (int k = 0; k < A->rows; k++) {
      for (int i = A->rows - 1, j = 0 + k; i >= 0; i--, j++) {
        diag_mul *= temp_matrix.matrix[i][j];
      }
      *result -= diag_mul;
      diag_mul = 1;
    }
  }
  s21_remove_matrix(&temp_matrix);
  return res;
}

int gauss(matrix_t *A, double *result) {
  int res = CALCERROR;
  *result = 1;
  matrix_t copyA = {0};
  if (s21_create_matrix(A->rows, A->columns, &copyA) != OK) {
    res = MATERROR;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        copyA.matrix[i][j] = A->matrix[i][j];
      }
    }
    for (int k = 0; k < copyA.rows; k++) {
      if (copyA.matrix[k][k] == 0) {
        res = change_row(&copyA, k, result);
      } else {
        res = OK;
      }
      if (res == OK) {
        double denom =
            copyA.matrix[k][k];  // знаменатель, каждую строку
                                 // делим на k-ый диагональный элемент
        for (int i = k + 1; i < A->rows; i++) {  // номер  изменяемой строки
          double numer = copyA.matrix[i][k];  // числитель, каждую строку
                                              // домножаем на элемент (i,k)
          for (int j = k; j < A->rows; j++) {
            copyA.matrix[i][j] =
                copyA.matrix[i][j] - copyA.matrix[k][j] / denom * numer;
          }
        }
      } else if (res == CALCERROR) {
        *result = 0;
        res = OK;
        break;
      }
    }
    if (*result != 0) {
      for (int i = 0; i < A->rows; i++) {
        *result *= copyA.matrix[i][i];
      }
    }
    s21_remove_matrix(&copyA);
  }
  return res;
}

int change_row(matrix_t *B, int x, double *result) {
  int res = CALCERROR;
  for (int l = x; l < B->rows; l++) {
    if (B->matrix[l][x] != 0) {
      double *temp = B->matrix[x];
      B->matrix[x] = B->matrix[l];
      B->matrix[l] = temp;
      *result *= -1;
      res = OK;
      break;
    }
  }
  return res;
}

void minor_matrix(matrix_t *A, int row, int col, matrix_t *minor) {
  for (int i = 0, k = 0; i < A->rows; ++i) {
    if (row != i) {
      for (int j = 0, l = 0; j < A->columns; ++j) {
        if (col != j) {
          minor->matrix[k][l] = A->matrix[i][j];
          l++;
        }
      }
      k++;
    }
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (is_materror(A) || result == NULL) {
    res = MATERROR;
  } else if (A->rows != A->columns) {
    res = CALCERROR;
  } else {
    matrix_t temp_matrix = {0};
    double sign = 1;
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
      res = MATERROR;
    } else {
      if (A->rows == 1) {
        result->matrix[0][0] = A->matrix[0][0];
      } else {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            if (s21_create_matrix(A->rows - 1, A->columns - 1, &temp_matrix) ==
                OK) {
              minor_matrix(A, i, j, &temp_matrix);
              res = s21_determinant(&temp_matrix, &result->matrix[i][j]);
              s21_remove_matrix(&temp_matrix);
              sign = (i + j) % 2 == 1 ? -1 : 1;
              result->matrix[i][j] = sign * result->matrix[i][j];
              if ((s21_fabs(result->matrix[i][j])) < 1e-7)
                result->matrix[i][j] = 0;

            } else {
              res = MATERROR;
              break;
            }
          }
          if (res == MATERROR) break;
        }
      }
    }
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (is_materror(A) || result == NULL) {
    res = MATERROR;
  } else if (A->rows != A->columns) {
    res = CALCERROR;
  } else {
    double determin;
    s21_determinant(A, &determin);
    if (determin == 0) {
      res = CALCERROR;
    } else {
      matrix_t alg_dop;
      if ((res = s21_create_matrix(A->rows, A->columns, &alg_dop)) == OK) {
        if ((res = s21_calc_complements(A, &alg_dop)) == OK) {
          res = s21_transpose(&alg_dop, result);
          s21_remove_matrix(&alg_dop);

          for (int i = 0; i < A->rows; i++)
            for (int j = 0; j < A->rows; j++) result->matrix[i][j] /= determin;
          // s21_remove_matrix(&alg_dop);
        }
        // s21_remove_matrix(&alg_dop);
      }
    }
  }
  return res;
}

int is_materror(matrix_t *X) {
  int materror = 0;
  if (X == NULL || X->matrix == NULL || X->columns <= 0 || X->rows <= 0)
    materror = 1;
  return materror;
}

int is_calcerror(matrix_t *X, matrix_t *Y) {
  int calcerror = 0;
  if (X->rows != Y->rows || X->columns != Y->columns) calcerror = 2;
  return calcerror;
}

long double s21_fabs(double x) {
  x = x >= 0 ? x : -x;
  return (long double)x;
}

void fill(matrix_t *A, double *mat) {
  for (int i = 0, k = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++, k++) A->matrix[i][j] = mat[k];
}

/*
void print_matrix(matrix_t *P) {
  for (int i = 0; i < P->rows; ++i) {
    for (int j = 0; j < P->columns; ++j) {
      printf("%-9f", (*P).matrix[i][j]);
      if (j == P->columns - 1) printf("\n");
    }
  }
  printf("\n");
}
*/