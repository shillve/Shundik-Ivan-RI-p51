#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "header.h"
#include "header.c"

/* Problem function and its derivative
   VARIANT 10:
   f(x) = 0.25x^3 - 25x^2 + x + 1
*/
double func(double x) {
    return 0.25 * pow(x, 3) - 25.0 * pow(x, 2) + x + 1.0;
}

double derivative(double x) {
    return 0.75 * pow(x, 2) - 50.0 * x + 1.0;
}

/* Check that derivative does not change sign on [a,b]
   (discrete sampling heuristic) => likely a unique root
*/
int check_unique_root(double a, double b) {
    int sign = 0;
    int samples = 100;
    for (int i = 0; i <= samples; i++) {
        double x = a + (b - a) * i / (double)samples;
        double d = derivative(x);
        if (d > 0 && sign == 0) sign = 1;
        if (d < 0 && sign == 0) sign = -1;
        if ((d > 0 && sign == -1) || (d < 0 && sign == 1)) return 0; // changes sign
    }
    return 1; // does not change sign
}

int main() {
    double a, b, eps;
    int max_iter, debug;
    int choice;

    printf("=== Solving a Nonlinear Equation ===\n");
    printf("Example (variant): f(x) = cos(x) - x\n\n");

    printf("Enter the left interval boundary a: ");
    if (scanf("%lf", &a) != 1) return 1;
    printf("Enter the right interval boundary b: ");
    if (scanf("%lf", &b) != 1) return 1;
    if (a >= b) { printf("Error: a must be < b\n"); return 1; }

    printf("Enter tolerance epsilon: ");
    if (scanf("%lf", &eps) != 1) return 1;
    printf("Enter maximum number of iterations: ");
    if (scanf("%d", &max_iter) != 1) return 1;
    printf("Enable debug mode (1 - yes, 0 - no)? ");
    if (scanf("%d", &debug) != 1) return 1;

    if (func(a) * func(b) >= 0) {
        printf("\n(!) On the interval [%.6lf, %.6lf] there is no sign change or there are multiple!\n", a, b);
        printf("f(a)=%.12lf, f(b)=%.12lf\n", func(a), func(b));
        return 1;
    }

    if (check_unique_root(a, b))
        printf("Derivative check: derivative does not change sign => likely a unique root on the interval.\n");
    else
        printf("Derivative check: derivative changes sign => there may be multiple roots or complex behavior.\n");

    printf("\nChoose method:\n1 - Bisection method\n2 - Chord (Secant) method\nYour choice: ");
    if (scanf("%d", &choice) != 1) return 1;
    if (choice != 1 && choice != 2) { printf("Invalid choice!\n"); return 1; }

    clock_t start = clock();
    double root = NAN;
    int iter_done = 0;
    int unlimited = 0; // if 1 - ignore iteration limit and run until convergence
    int current_max = max_iter;

    while (1) {
        if (choice == 1) {
            root = bisection(a, b, eps, current_max, debug, &iter_done, &unlimited);
        } else {
            root = chord(a, b, eps, current_max, debug, &iter_done, &unlimited);
        }

        if (!isnan(root)) {
            // successfully found
            break;
        } else {
            printf("\n--- Iteration limit reached (%d) ---\n", current_max);
            printf("Choose action:\n");
            printf("1 - continue with the same number of additional iterations (%d more)\n", max_iter);
            printf("2 - run until convergence (ignore limit)\n");
            printf("3 - exit and print the intermediate result\n");
            printf("Your choice: ");
            int opt;
            if (scanf("%d", &opt) != 1) opt = 3;
            if (opt == 1) {
                current_max += max_iter; // add another chunk of iterations
                continue;
            } else if (opt == 2) {
                unlimited = 1;
                continue;
            } else {
                printf("\nIntermediate result: x ≈ %.10lf, f(x)=%.12lf, iterations=%d\n",
                       last_approx(), func(last_approx()), iter_done);
                return 0;
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nExecution time: %.6lf seconds\n", time_spent);
    printf("Root value: x ≈ %.12lf\n", root);
    printf("Function value at root: f(x)=%.12lf\n", func(root));
    printf("Iterations completed: %d\n", iter_done);

    return 0;
}
