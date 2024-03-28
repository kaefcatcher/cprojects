#include <math.h>

#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int return_code = SUCCESS;
  if (((A->columns != B->columns)) || (A->rows != B->rows) || (A == NULL) ||
      (B == NULL))
    return_code = FAILURE;
  else {
    for (int row = 0; row < A->rows; row++) {
      for (int column = 0; column < A->columns; column++) {
        if (fabs(A->matrix[row][column] - B->matrix[row][column]) >= 1e-7)
          return_code = FAILURE;
      }
    }
  }
  return return_code;
}