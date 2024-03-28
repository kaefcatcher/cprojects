#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = OK;
  if (A == NULL || B == NULL || result == NULL || (A->columns <= 0) ||
      (A->rows <= 0) || (B->columns <= 0) || (B->rows <= 0))
    return_code = MATERROR;
  else if ((A->rows != B->rows) || (A->columns != B->columns))
    return_code = CALCERROR;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row < A->rows; row++) {
      for (int column = 0; column < A->columns; column++) {
        result->matrix[row][column] =
            A->matrix[row][column] - B->matrix[row][column];
      }
    }
  }
  return return_code;
}