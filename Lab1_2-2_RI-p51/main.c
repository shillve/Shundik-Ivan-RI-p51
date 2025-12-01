#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
    return 0.25*x*x*x - 25.0/(x*x + 1) + (x + 25)/100.0;
}

int main() {
    unsigned int variant;
    double X1, X2, delta;
    int N;

    // вибір методу
    do {
        printf("Enter variant (1 - using N, 2 - using delta): ");
        if (scanf("%u", &variant) != 1) {
            while (getchar() != '\n');
            variant = 0;
        }
    } while (variant < 1 || variant > 2);

    // X1
    printf("Enter X1: ");
    while (scanf("%lf", &X1) != 1) {
        printf("Incorrect X1!\n");
        while (getchar() != '\n');
        printf("Enter X1: ");
    }

    // X2
    printf("Enter X2: ");
    while (scanf("%lf", &X2) != 1 || X2 <= X1) {
        printf("Incorrect X2! Must be > X1.\n");
        while (getchar() != '\n');
        printf("Enter X2: ");
    }

    // залежно від варіанту
    if (variant == 1) {
        printf("Enter N: ");
        while (scanf("%d", &N) != 1 || N < 2) {
            printf("Incorrect N >= 2\n");
            while (getchar() != '\n');
            printf("Enter N: ");
        }
        delta = (X2 - X1) / (N - 1);
    } else {
        printf("Enter delta: ");
        while (scanf("%lf", &delta) != 1 || delta <= 0 || delta > (X2 - X1)) {
            printf("Incorrect delta!\n");
            while (getchar() != '\n');
            printf("Enter delta: ");
        }
        N = (int)((X2 - X1) / delta) + 1;
    }

    printf("\nInitial data:\n");
    printf("X1 = %.3f\n", X1);
    printf("X2 = %.3f\n", X2);
    printf("delta = %.3f\n", delta);
    printf("N = %d\n\n", N);

    printf("+--------+-----------------------+-----------------------+\n");
    printf("| Point  |         X             |        f(X)           |\n");
    printf("+--------+-----------------------+-----------------------+\n");

    double prev = f(X1);
    for (int i = 0; i < N; i++) {
        double x = X1 + i*delta;
        if (x > X2) x = X2;
        double y = f(x);

        printf("|%8d|%23.6f|%23.6f", i+1, x, y);

        if (i > 0 && prev * y < 0)
            printf("   <-- sign change");

        printf("\n");
        prev = y;
    }

    printf("+--------+-----------------------+-----------------------+\n");
    return 0;
}
