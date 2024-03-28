#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = OK;
  if (A == NULL || B == NULL || result == NULL || (A->columns <= 0) ||
      (A->rows <= 0) || (B->columns <= 0) || (B->rows <= 0))
    return_code = MATERROR;
  else if ((A->columns != B->rows))
    return_code = CALCERROR;
  else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int row = 0; row < A->rows; row++) {
      for (int column = 0; column < B->columns; column++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[row][column] +=
              A->matrix[row][k] * B->matrix[k][column];
        }
      }
    }
  }
  return return_code;
}