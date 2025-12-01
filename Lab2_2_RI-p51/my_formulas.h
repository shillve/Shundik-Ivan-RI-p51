#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef MY_FORMULAS_H_
#define MY_FORMULAS_H_

// Варіант 10
// f(x) = 0.25*x^3 - 25*x^2 + (x + 25)/100 + 1
double integrand_expression(double x) {
    return 0.25 * pow(x, 3)
         - 25.0 * pow(x, 2)
         + (x + 25.0) / 100.0
         + 1.0;
}

// Метод лівих прямокутників
double integral_left(double a, double b, unsigned int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (unsigned int i = 0; i < n; i++) {
        double x = a + i * h;
        sum += integrand_expression(x);
    }
    return sum * h;
}

// Метод правих прямокутників
double integral_right(double a, double b, unsigned int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (unsigned int i = 1; i <= n; i++) {
        double x = a + i * h;
        sum += integrand_expression(x);
    }
    return sum * h;
}

// Метод трапецій
double integral_trapezoid(double a, double b, unsigned int n) {
    double h = (b - a) / n;
    double sum = (integrand_expression(a) + integrand_expression(b)) / 2.0;
    for (unsigned int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += integrand_expression(x);
    }
    return sum * h;
}

// Метод Сімпсона
double integral_simpson(double a, double b, unsigned int n) {
    if (n % 2 != 0) n++; 
    double h = (b - a) / n;
    double sum = integrand_expression(a) + integrand_expression(b);

    for (unsigned int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0)
            sum += 2 * integrand_expression(x);
        else
            sum += 4 * integrand_expression(x);
    }
    return sum * h / 3.0;
}

#endif

