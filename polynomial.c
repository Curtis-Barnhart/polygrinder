/**
 * Curtis Barnhart
 * 2023-05-12
 */

#include "polynomial.h"

/**
 *
 * @param p
 * @param value
 * @return
 */
double eval(poly *p, complex double value) {
	double complex result = 0;
    if (GET_SIGN(p, 0)) {
        result += 1;
    } else {
        result -= 1;
    }
	for (int i = 1; i <= p->degree; i++) {
		if (GET_SIGN(p, i)) {
			result += cpow(value, i);
		} else {
			result -= cpow(value, i);
		}
	}
	return cabs(result);
}

/**
 *
 * @param p
 * @param start
 * @param grain
 * @return
 */
double scan(poly *p, double start, double grain) {
	double TAU = (M_PI + grain) * 2;
	double delta_last, delta_current, input_next;
    input_next = start + grain;
	delta_current = eval(p, TTOC(input_next)) - eval(p, TTOC(start));

	while (start < TAU) {
        start = input_next;
        input_next += grain;
		delta_last = delta_current;
		delta_current = eval(p, TTOC(input_next)) - eval(p, TTOC(start));

		if (delta_last < 0) {
			if (delta_current > 0) {
				return start;
			}
		}
	}
	return -1;
}

/**
 *
 * @param p
 * @param start
 * @return
 */
double local_min_newton(poly *p, double start) {
    for (int i = 0; i < 4; i++) {
        double x1 = start;
        double x2 = x1 + EPS;
        double x3 = x2 + EPS;
        double y1 = eval(p, TTOC(x1));
        double y2 = eval(p, TTOC(x2));
        double y3 = eval(p, TTOC(x3));

        double x21 = x1 + (EPS / 2);
        double y21 = (y2 - y1) / EPS;
        double y22 = (y3 - y2) / EPS;

        double slope = (y22 - y21) / EPS;
        double root = -y21 / slope + x21;

        start = root;
    }

    return eval(p, TTOC(start));
}

/**
 *
 * @param p
 * @param start
 * @param grain
 * @param depth
 * @return
 */
double local_min_custom(poly *p, double start, double grain, int depth) {
    double x_vals[5];
    double y_vals[5];
    int smallest = 0;
    for (int i = 0; i < 5; ++i) {
        x_vals[i] = start + (i * grain / 4);
        y_vals[i] = eval(p, TTOC(x_vals[i]));
        if (y_vals[i] < y_vals[smallest]) {
            smallest = i;
        }
    }

    if (depth == 0) {
        return y_vals[smallest];
    }

    switch (smallest) {
        case 0:
            return local_min_custom(p, x_vals[0], grain / 4, depth - 1);
        case 4:
            return local_min_custom(p, x_vals[3], grain / 4, depth - 1);
        default:
            return local_min_custom(p, x_vals[smallest - 1], grain / 2, depth - 1);
    }
}

/**
 *
 * @param p
 * @param grain
 * @param iter
 * @return
 */
double global_min(poly *p, double grain, int iter) {
    double current_min = INFINITY;
    double next_min;
    double current_x = 0;
    while ((current_x = scan(p, current_x, grain)) > -1) {
        next_min = local_min_custom(p, current_x - grain, grain * 2, iter);
        current_min = current_min < next_min ? current_min : next_min;
    }
    return current_min;
}

/**
 *
 * @param p
 */
void poly_print(poly *p) {
    for (int i = p->degree; i > -1; i--) {
        printf("%c z^%d ", GET_SIGN(p, i) ? '+' : '-', i);
    }
    printf("\n");
}

//char *poly_str(poly *p) {
//
//
//    int accounted_terms = 0;
//    int str_len = 0;
//    int digits = 1;
//
//    while (accounted_terms < p->degree) {
//        long double max = powl(10, digits);
//
//    }
//
//
//    int degree_copy = p->degree;
//    int term_len = 5;
//    int expo_len = 1;
//    while (terms < p->degree) {
//
//    }
//    char str_builder[p->degree]
//}

/**
 *
 * @param p
 * @param signs
 */
void set_sign(poly *p, unsigned long signs) {
    int signBytes = (p->degree / 8) + 1;
    signs = signs << ((sizeof(unsigned long) * 8) - (p->degree) + 1);
    for (int i = 0; i < signBytes; i++) {
        p->signs[i] = (signs >> ((sizeof(unsigned long) - (i + 1)) * 8)) & 0xFF;  // TODO: maybe make i * 8 another sizeof?
    }
}
