/**
 * Curtis Barnhart
 * 2023-05-12
 *
 *
 */

#include <string.h>
#include <stdio.h>
#include <glib.h>
#include <math.h>

#include "main.h"
#include "poly/polynomial.h"
#include "util/double_tracker.h"
#include "util/my_math.h"

/**
 * degree_mins finds all polynomials of degree 'degree' whose minimum modulus on the unit circle is greater than 1.
 * It attempts to group polynomials by their minimum modulus, and counts up how many polynomials have each minimum
 * modulus as their minimum modulus.
 * It then prints each unique minimum modulus as well as how many polynomials had that as their minimum modulus.
 *
 * @param degree degree of polynomials to evaluate
 * @param grain grain to use when searching for minimum modulus of polynomial (multiple minimums within grain of each
 *        other may be counted as one)
 * @param iter iterations to use on minimum finding function when precisely calculating the a local minimum modulus of
 *        a polynomial
 */
void degree_mins(int degree, double grain, int iter) {
    unsigned char signs[((degree + 1) / 8) + 1];
    poly polyData;
    poly *poly1 = &polyData;
    poly1->degree = degree;
    poly1->signs = signs;

    double func_min;
    unsigned long max = 1UL << (degree + 1);

    for (unsigned long i = 0; i < max; i++) {
        set_sign(poly1, i);

        func_min = global_min(poly1, grain, iter);
        if (func_min > 1) {
            poly_print(poly1);
            printf("%.10lf\n", func_min);
        }
    }
}

int compare(gconstpointer a, gconstpointer b) {
    double aDouble = *((double *) a);
    double bDouble = *((double *) b);

    if (fabs(aDouble - bDouble) < 0.0000001) {
        return 0;
    } else {
        return aDouble < bDouble ? -1 : 1;
    }
}

gboolean tree_val_printer(gpointer key, gpointer value, gpointer data) {
    printf("%.10lf : %u\n", *((double *) key), *((unsigned int *) value));
    return FALSE;
}

gboolean tree_val_file_printer(gpointer key, gpointer value, gpointer data) {
    fprintf(data, "%.10lf : %u\n", *((double *) key), *((unsigned int *) value));
    return FALSE;
}

void degree_mins_verbose(int degree, double grain, int iter, unsigned int buckets, FILE *f) {
    DoubleTracker *tracker = DoubleTracker_new(&compare, buckets);

    unsigned char signs[((degree + 1) / 8) + 1];
    poly polyData;
    poly *poly1 = &polyData;
    poly1->degree = degree;
    poly1->signs = signs;

    double func_min;
    unsigned long max = 1UL << (degree + 1);

    for (unsigned long i = 0; i < max; i++) {
        set_sign(poly1, i);

        func_min = global_min(poly1, grain, iter);
        if (func_min > 1.0000001) {
            DoubleTracker_increment(tracker, func_min);
        }
    }

    g_tree_foreach(tracker->tree, &tree_val_file_printer, f);
    DoubleTracker_destroy(tracker);
}

/**
 *
 * @return
 */
int main(int argc, char **argv) {
    if (argc > 1) {
        return testing();
    }

    for (int i = 0; i < 25; ++i) {
        char filename[12];
        sprintf(filename, "polyfile%d", i);
        FILE *f = fopen(filename, "w");
        degree_mins_verbose(i, 0.02, 16, 5000000, f);
        fclose(f);
        printf("file %s written\n", filename);
    }
}

/**
 * Just a place to run test code.
 * If any command line arguments are passed to the program, it will run the testing function instead of main.
 *
 * @return
 */
int testing() {
    printf("%ld\n", ipow(7, 12));

    int error = 0;
    printf("%ld\n", ipow_safe(7, 12, &error));
    printf("%d\n", error);

    error = 0;
    printf("%ld\n", ipow_safe(7, 120, &error));
    printf("%d\n", error);

    return 1;
}
