
#include <stdio.h>
#include <math.h>
#include "header.h"

static double last_value = 0;

extern double func(double x);

double bisection(double a, double b, double eps, int max_iter, int debug,
                 int *iter_done, int *unlimited)
{
    double c;
    int i = 0;

    if (func(a) * func(b) > 0) {
        printf("Error: f(a) and f(b) must have opposite signs!\n");
        return NAN;
    }

    for (i = 1; i <= max_iter; i++) {
        c = (a + b) / 2.0;
        last_value = c;

        double fc = func(c);

        if (debug)
            printf("Iter %d: a = %.10lf, b = %.10lf, c = %.10lf, f(c) = %.10lf\n",
                   i, a, b, c, fc);

        if (fabs(fc) < eps || fabs(b - a) < eps) {
            *iter_done = i;
            *unlimited = 0;
            return c;
        }

        if (func(a) * fc < 0)
            b = c;
        else
            a = c;
    }

    *iter_done = max_iter;
    *unlimited = 1;
    return last_value;
}

double chord(double a, double b, double eps, int max_iter, int debug,
             int *iter_done, int *unlimited)
{
    double x0 = a;
    double x1 = b;
    double x2;
    int i;

    if (func(a) * func(b) > 0) {
        printf("Error: f(a) and f(b) must have opposite signs!\n");
        return NAN;
    }

    for (i = 1; i <= max_iter; i++) {
        x2 = x1 - func(x1) * (x1 - x0) / (func(x1) - func(x0));
        last_value = x2;

        if (debug)
            printf("Iter %d: x0 = %.10lf, x1 = %.10lf, x2 = %.10lf, f(x2)=%.10lf\n",
                   i, x0, x1, x2, func(x2));

        if (fabs(func(x2)) < eps) {
            *iter_done = i;
            *unlimited = 0;
            return x2;
        }

        x0 = x1;
        x1 = x2;
    }

    *iter_done = max_iter;
    *unlimited = 1;
    return last_value;
}

double last_approx(void)
{
    return last_value;
}
