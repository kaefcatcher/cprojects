#include "s21_matrix.h"

#define OK 0
#define MATERROR 1
#define CALCERROR 2

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    return MATERROR;
  }
  s21_create_matrix(A->rows, A->columns, result);
  matrix_t minor;
  int minor_rows = A->rows - 1;
  int minor_columns = A->columns - 1;
  if (s21_create_matrix(minor_rows, minor_columns, &minor) != OK) {
    return MATERROR;
  }

  for (int k = 0; k < A->rows; k++) {
    for (int j = 0; j < A->columns; j++) {
      int minor_row = 0;
      for (int row = 0; row < A->rows; row++) {
        if (row != k) {
          int minor_column = 0;
          for (int column = 0; column < A->columns; column++) {
            if (column != j) {
              minor.matrix[minor_row][minor_column++] = A->matrix[row][column];
            }
          }
          minor_row++;
        }
      }

      double minor_determinant = 0;
      int determinant_status = s21_determinant(&minor, &minor_determinant);
      if (determinant_status != OK) {
        s21_remove_matrix(&minor);
        return CALCERROR;
      }

      result->matrix[k][j] = pow(-1, k + j) * minor_determinant;
    }
  }

  s21_remove_matrix(&minor);
  return OK;
}
