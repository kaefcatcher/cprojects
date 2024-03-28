#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int return_code = OK;
  if (A == NULL || result == NULL || (A->columns <= 0) || (A->rows <= 0))
    return_code = MATERROR;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row < A->rows; row++) {
      for (int column = 0; column < A->columns; column++) {
        result->matrix[row][column] = A->matrix[row][column] * number;
      }
    }
  }
  return return_code;
}
