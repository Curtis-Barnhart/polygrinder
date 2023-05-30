/**
 * Curtis Barnhart
 * 2023-05-12
 */

#ifndef POLYGRINDER_POLYNOMIAL_H
#define POLYGRINDER_POLYNOMIAL_H

#include <complex.h>

#define GET_SIGN(poly, i) ((((poly->signs)[i >> 3] >> (7 - (i & 7))) & 1))
#define TTOC(c) (cos(c) + I * sin(c))
#define eval_theta(poly, theta, radius) (eval(poly, TTOC(theta) * radius))
#define slope(p, t0, t1, r) ((eval_theta(p, t1, r) - eval_theta(p, t0, r)) / (t1 - t0))

#define EPS (0.000001)
#define TAU (6.28318530717958647692)

typedef struct {
	int degree;
	unsigned char *signs;
} poly;

double eval(poly *, complex double);

double scan_radius(poly *, double, double, double);

double scan(poly *, double, double);

double local_min_newton(poly *p, double start);

double local_min_custom(poly *, double, double, int);

double global_min(poly *, double, int);

void poly_print(poly *p);

void set_sign(poly *, unsigned long);

#endif //POLYGRINDER_POLYNOMIAL_H
