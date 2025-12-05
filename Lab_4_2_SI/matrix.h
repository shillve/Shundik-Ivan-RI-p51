#ifndef MATRIX_FUNCS_H
#define MATRIX_FUNCS_H

int **alloc2D(int rows, int cols);
void free2D(int **m, int rows);

void print_matrix(int **m, int rows, int cols);

void fill_keyboard(int **m, int rows, int cols, char nameHint); /* read ints from stdin */
void fill_random(int **m, int rows, int cols, int lo, int hi);  /* uniform ints in [lo,hi] */
void fill_formula_A(int **A, int n);                            /* A[i][j] = i + j */
void fill_formula_B(int **B, int rows, int cols);               /* B[i][j] = i - j */

void max_min_diag_A(int **A, int n, int *maxVal, int *minBelow, int *minAbove);

int **transpose_new(int **B, int rows, int cols, int *outRows, int *outCols);

void multiply_AB(int **A, int nA, int **B, int nB, int mB, int **C); /* C = A(nA x nA) * B(nA x mB) */

#endif
