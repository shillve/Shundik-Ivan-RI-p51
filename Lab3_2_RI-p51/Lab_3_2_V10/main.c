
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "header.h"

double func(double x) {
    return 0.25 * pow(x, 3) - 25.0 * pow(x, 2) + x + 1.0;
}

double derivative(double x) {
    return 0.75 * pow(x, 2) - 50.0 * x + 1.0;
}

int main()
{
    double a, b, eps;
    int max_iter, method, debug;
    int iter_done, unlimited;

    printf("=== Solving nonlinear equation f(x)=0 (Variant 10) ===\n");
    printf("Function: f(x)=0.25*x^3 - 25*x^2 + x + 1\n\n");

    printf("Enter interval a b: ");
    scanf("%lf %lf", &a, &b);

    printf("Enter epsilon: ");
    scanf("%lf", &eps);

    printf("Enter max iterations: ");
    scanf("%d", &max_iter);

    printf("Debug mode? (1=yes, 0=no): ");
    scanf("%d", &debug);

    printf("\nChoose method:\n");
    printf("1 - Bisection\n");
    printf("2 - Chord Method\n");
    printf("> ");
    scanf("%d", &method);

    double root = 0;
    clock_t start = clock();

    if (method == 1) {
        root = bisection(a, b, eps, max_iter, debug, &iter_done, &unlimited);
    } else {
        root = chord(a, b, eps, max_iter, debug, &iter_done, &unlimited);
    }

    clock_t end = clock();
    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n================ RESULT ================\n");
    printf("Root ≈ %.10lf\n", root);
    printf("f(root) = %.10lf\n", func(root));
    printf("Iterations used = %d\n", iter_done);
    printf("Exceeded max iterations? %s\n", unlimited ? "YES" : "NO");
    printf("Time = %.6lf seconds\n", time_sec);

    printf("========================================\n");

    return 0;
}
