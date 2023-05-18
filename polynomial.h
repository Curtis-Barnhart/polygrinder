/**
 * Curtis Barnhart
 * 2023-05-12
 */

#include <complex.h>

#ifndef POLYGRINDER_POLYNOMIAL_H
#define POLYGRINDER_POLYNOMIAL_H

#define GET_SIGN(poly, i) ((((poly->signs)[i >> 3] >> (7 - (i & 7))) & 1))
#define TTOC(c) (cos(c) + I * sin(c))
#define EPS (0.000001)

typedef struct {
	int degree;
	unsigned char *signs;
} poly;

double eval(poly *, complex double);

double scan(poly *, double, double);

double local_min_newton(poly *p, double start);

double global_min(poly *, double, int);

void poly_print(poly *p);

void set_sign(poly *, unsigned long);

#endif //POLYGRINDER_POLYNOMIAL_H
