#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int return_code = OK;
  if (A == NULL || result == NULL || (A->columns <= 0) || (A->rows <= 0))
    return_code = MATERROR;
  else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int row = 0; row < A->columns; row++) {
      for (int column = 0; column < A->rows; column++) {
        result->matrix[row][column] = A->matrix[column][row];
      }
    }
  }
  return return_code;
}