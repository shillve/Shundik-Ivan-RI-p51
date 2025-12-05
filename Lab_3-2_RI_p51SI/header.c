#include <stdio.h>
#include <math.h>
#include "header.h"

/* Keep the last intermediate approximation between calls */
static double g_last_approx = NAN;

double last_approx(void) {
    return g_last_approx;
}

extern double func(double x);

/* Bisection method */
double bisection(double a, double b, double eps, int max_iter, int debug, int *iter_done, int *unlimited) {
    double fa = func(a), fb = func(b);
    if (fa * fb > 0) {
        printf("Error: no sign change on the interval!\n");
        return NAN;
    }
    double c = a;
    int iter = 0;
    while (1) {
        c = (a + b) / 2.0;
        g_last_approx = c;
        double fc = func(c);
        if (debug) printf("Iter %d: a=%.12lf b=%.12lf c=%.12lf f(c)=%.12lf\n", iter+1, a, b, c, fc);
        if (fabs(fc) <= eps || fabs(b - a) <= eps) {
            if (iter_done) *iter_done = iter + 1;
            return c;
        }
        if (fa * fc < 0) {
            b = c; fb = fc;
        } else {
            a = c; fa = fc;
        }
        iter++;
        if (!(*unlimited) && iter >= max_iter) {
            if (iter_done) *iter_done = iter;
            return NAN;
        }
    }
}

/* Chord (Secant) method */
double chord(double a, double b, double eps, int max_iter, int debug, int *iter_done, int *unlimited) {
    double fa = func(a), fb = func(b);
    if (fa * fb > 0) {
        printf("Error: no sign change on the interval!\n");
        return NAN;
    }
    double x0 = a;
    double x1 = b;
    double x2 = x1;
    int iter = 0;
    while (1) {
        double f0 = func(x0);
        double f1 = func(x1);
        if (fabs(f1 - f0) < 1e-16) {
            /* Division by near-zero slope */
            g_last_approx = x1;
            if (iter_done) *iter_done = iter;
            return NAN;
        }
        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        g_last_approx = x2;
        double f2 = func(x2);
        if (debug) printf("Iter %d: x0=%.12lf x1=%.12lf x2=%.12lf f(x2)=%.12lf\n", iter+1, x0, x1, x2, f2);
        if (fabs(f2) <= eps) {
            if (iter_done) *iter_done = iter + 1;
            return x2;
        }
        /* Shift for next secant step */
        x0 = x1;
        x1 = x2;
        iter++;
        if (!(*unlimited) && iter >= max_iter) {
            if (iter_done) *iter_done = iter;
            return NAN;
        }
    }
}
