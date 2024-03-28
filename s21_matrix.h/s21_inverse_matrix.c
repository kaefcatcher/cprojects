#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int return_code = 0;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0 &&
      result != NULL) {
    if (A->rows == A->columns) {
      double determinant = 0;
      s21_determinant(A, &determinant);
      if (determinant != 0) {
        matrix_t matrix_calc = {NULL, 0, 0};
        matrix_t matrix_transpose = {NULL, 0, 0};
        s21_calc_complements(A, &matrix_calc);
        s21_transpose(&matrix_calc, &matrix_transpose);
        s21_mult_number(&matrix_transpose, 1 / determinant, result);
        s21_remove_matrix(&matrix_calc);
        s21_remove_matrix(&matrix_transpose);
      } else {
        return_code = 2;
      }
    } else {
      return_code = 2;
    }
  } else {
    return_code = 1;
  }
  return return_code;
}