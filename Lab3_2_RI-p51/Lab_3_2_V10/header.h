
#ifndef METHODS_HEADER_H
#define METHODS_HEADER_H

double bisection(double a, double b, double eps, int max_iter, int debug, int *iter_done, int *unlimited);
double chord(double a, double b, double eps, int max_iter, int debug, int *iter_done, int *unlimited);
double last_approx(void);

#endif
