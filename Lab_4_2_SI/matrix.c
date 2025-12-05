#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "matrix.h"
#include <math.h>

// === ФУНКЦІЯ ВАРІАНТА №10 ===
double func10(double x) {
    if (x >= -5.2 && x < 0)
        return exp(-x) + 1.0;

    else if (x >= 0 && x < 8)
        return exp(x) - 1.0;

    else if (x >= 8 && x < 15) {
        if (2*x - 7 < 0 || x*x - 25 <= 0)
            return 0;

        double num = sqrt(2*x - 7);
        double den = sqrt(x*x - 25);
        return (num / den) + 2 * pow(x, exp(1));
    }

    return 0.0;
}

int **alloc2D(int rows, int cols) {
    int **m = (int**)malloc(rows * sizeof(int*));
    if (!m) return NULL;
    for (int i = 0; i < rows; ++i) {
        m[i] = (int*)malloc(cols * sizeof(int));
        if (!m[i]) {
            for (int k = 0; k < i; ++k) free(m[k]);
            free(m);
            return NULL;
        }
    }
    return m;
}

void free2D(int **m, int rows) {
    if (!m) return;
    for (int i = 0; i < rows; ++i) free(m[i]);
    free(m);
}

void print_matrix(int **m, int rows, int cols) {
    if (!m) { printf("(null)\n"); return; }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%5d ", m[i][j]);
        }
        printf("\n");
    }
}

void fill_keyboard(int **m, int rows, int cols, char nameHint) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%c[%d][%d] = ", nameHint, i, j);
            if (scanf("%d", &m[i][j]) != 1) {
                printf("Input error, setting 0.\n");
                m[i][j] = 0;
            }
        }
    }
}

void fill_random(int **m, int rows, int cols, int lo, int hi) {
    if (lo > hi) { int t = lo; lo = hi; hi = t; }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int r = lo + rand() % (hi - lo + 1);
            m[i][j] = r;
        }
    }
}

void fill_formula_A(int **A, int n) {
    for (int i = 0; i < n; ++i) {
        double x = i;   // аргумент x
        double y = func10(x);  // значення за варіантом 10

        for (int j = 0; j < n; ++j)
            A[i][j] = (int)y;  // можна округляти, якщо треба
    }
}
void fill_formula_B(int **B, int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            B[i][j] = i - j;
}

void max_min_diag_A(int **A, int n, int *maxVal, int *minBelow, int *minAbove) {
    int maxv = INT_MIN;
    int minB = INT_MAX;
    int minA = INT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (A[i][j] > maxv) maxv = A[i][j];
            if (i > j && A[i][j] < minB) minB = A[i][j];  /* below main diagonal */
            if (i < j && A[i][j] < minA) minA = A[i][j];  /* above main diagonal */
        }
    }
    if (maxVal) *maxVal = maxv;
    if (minBelow) *minBelow = (minB == INT_MAX ? 0 : minB);
    if (minAbove) *minAbove = (minA == INT_MAX ? 0 : minA);
}

int **transpose_new(int **B, int rows, int cols, int *outRows, int *outCols) {
    int **T = alloc2D(cols, rows);
    if (!T) return NULL;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            T[j][i] = B[i][j];
    if (outRows) *outRows = cols;
    if (outCols) *outCols = rows;
    return T;
}

void multiply_AB(int **A, int nA, int **B, int nB, int mB, int **C) {
    if (nA != nB) { printf("multiply_AB: dimensions mismatch.\n"); return; }
    for (int i = 0; i < nA; ++i) {
        for (int j = 0; j < mB; ++j) {
            long long sum = 0;
            for (int k = 0; k < nA; ++k) sum += (long long)A[i][k] * (long long)B[k][j];
            C[i][j] = (int)sum;
        }
    }
}
