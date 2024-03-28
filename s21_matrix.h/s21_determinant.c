#include <math.h>

#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int row_size = A->rows;
  int column_size = A->columns;
  int return_code = OK;

  if (!A || A->rows == 0 || A->columns == 0)
    return MATERROR;

  else if (row_size != column_size) {
    return CALCERROR;
  }

  else if (row_size == 1)
    *result = A->matrix[0][0];

  else if (row_size == 2)
    *result =
        (A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1]);

  else {
    matrix_t minor;
    s21_create_matrix(row_size - 1, column_size - 1, &minor);
    if (minor.matrix == NULL) {
      return MATERROR;
    }
    for (int k = 0; k < row_size; k++) {
      for (int row = 1; row < row_size; row++) {
        int column_ptr = 0;
        for (int column = 0; column < column_size; column++) {
          if (column != k) {
            minor.matrix[row - 1][column_ptr++] = A->matrix[row][column];
          }
        }
      }
      double minor_determinant = 0;
      return_code = s21_determinant(&minor, &minor_determinant);
      if (return_code != OK) {
        return return_code;
      }
      *result += pow(-1, k) * A->matrix[0][k] * minor_determinant;
    }
    s21_remove_matrix(&minor);
  }
  return return_code;
}
