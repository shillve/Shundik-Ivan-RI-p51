#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "matrix.c"


static void pause_enter(void) {
    printf("\nPress ENTER to continue...");
    int c; while ((c = getchar()) != '\n' && c != EOF) {}
    getchar();
}

int main(void) {
    srand((unsigned)time(NULL));

    int **A = NULL, **B = NULL, **C = NULL;
    int nA = 0, nB = 0, mB = 0, nC = 0, mC = 0;

    while (1) {
        printf("\n=== Lab 4.2 (Part 2) — Matrix Menu ===\n");
        printf("1) Create/resize A (square)\n");
        printf("2) Fill A (1=keyboard, 2=random, 3=formula A[i][j]=i+j)\n");
        printf("3) Create/resize B (rectangular)\n");
        printf("4) Fill B (1=keyboard, 2=random, 3=formula B[i][j]=i-j)\n");
        printf("5) Print A and B\n");
        printf("6) For A: max element; min below main diag; min above main diag\n");
        printf("7) Transpose B\n");
        printf("8) Multiply C = A * B and print C\n");
        printf("9) Free all and exit\n");
        printf("Your choice: ");

        int choice = 0;
        if (scanf("%d", &choice) != 1) { printf("Input error.\n"); return 1; }

        if (choice == 1) {
            printf("Enter size n (A is n x n): ");
            int n; if (scanf("%d", &n) != 1 || n <= 0) { printf("Invalid n.\n"); continue; }
            free2D(A, nA);
            A = alloc2D(n, n);
            if (!A) { printf("Allocation failed for A.\n"); nA = 0; continue; }
            nA = n;
            printf("A created: %dx%d\n", nA, nA);
        }
        else if (choice == 2) {
            if (!A) { printf("Create A first.\n"); continue; }
            int mode; printf("Fill mode (1=keyboard, 2=random, 3=formula): ");
            if (scanf("%d", &mode) != 1) { printf("Input error.\n"); continue; }
            if (mode == 1) fill_keyboard(A, nA, nA, 'A');
            else if (mode == 2) fill_random(A, nA, nA, -9, 9);
            else fill_formula_A(A, nA);
            printf("A filled.\n");
        }
        else if (choice == 3) {
            printf("Enter size nB (rows) and mB (cols) for B: ");
            int nb, mb;
            if (scanf("%d %d", &nb, &mb) != 2 || nb <= 0 || mb <= 0) { printf("Invalid sizes.\n"); continue; }
            free2D(B, nB);
            B = alloc2D(nb, mb);
            if (!B) { printf("Allocation failed for B.\n"); nB = mB = 0; continue; }
            nB = nb; mB = mb;
            printf("B created: %dx%d\n", nB, mB);
        }
        else if (choice == 4) {
            if (!B) { printf("Create B first.\n"); continue; }
            int mode; printf("Fill mode (1=keyboard, 2=random, 3=formula): ");
            if (scanf("%d", &mode) != 1) { printf("Input error.\n"); continue; }
            if (mode == 1) fill_keyboard(B, nB, mB, 'B');
            else if (mode == 2) fill_random(B, nB, mB, -9, 9);
            else fill_formula_B(B, nB, mB);
            printf("B filled.\n");
        }
        else if (choice == 5) {
            if (A) { printf("\nMatrix A (%dx%d):\n", nA, nA); print_matrix(A, nA, nA); } else printf("A not created.\n");
            if (B) { printf("\nMatrix B (%dx%d):\n", nB, mB); print_matrix(B, nB, mB); } else printf("B not created.\n");
        }
        else if (choice == 6) {
            if (!A) { printf("Create and fill A first.\n"); continue; }
            int maxVal, minBelow, minAbove;
            max_min_diag_A(A, nA, &maxVal, &minBelow, &minAbove);
            printf("A: max=%d, min below diag=%d, min above diag=%d\n", maxVal, minBelow, minAbove);
        }
        else if (choice == 7) {
            if (!B) { printf("Create and fill B first.\n"); continue; }
            int newRows = 0, newCols = 0;
            int **BT = transpose_new(B, nB, mB, &newRows, &newCols);
            if (!BT) { printf("Transpose failed.\n"); continue; }
            free2D(B, nB);
            B = BT; nB = newRows; mB = newCols;
            printf("B transposed. New size: %dx%d\n", nB, mB);
        }
        else if (choice == 8) {
            if (!A || !B) { printf("Create and fill A and B first.\n"); continue; }
            if (nA != nB) { printf("Multiply requires A(nA x nA) and B(nA x mB). Current: A(%d x %d), B(%d x %d)\n", nA, nA, nB, mB); continue; }
            free2D(C, nC);
            C = alloc2D(nA, mB);
            if (!C) { printf("Allocation failed for C.\n"); continue; }
            multiply_AB(A, nA, B, nB, mB, C);
            nC = nA; mC = mB;
            printf("\nMatrix C = A * B (%dx%d):\n", nC, mC);
            print_matrix(C, nC, mC);
        }
        else if (choice == 9) {
            free2D(A, nA); free2D(B, nB); free2D(C, nC);
            A = B = C = NULL; nA = nB = mB = nC = mC = 0;
            printf("Freed all. Exiting...\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
