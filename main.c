/**
 * Curtis Barnhart
 * 2023-05-12
 *
 *
 */

#include <string.h>

#include "main.h"

#include "c_improvements.h"

/**
 *
 * @param degree
 * @param grain
 * @param iter
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
int main() {
    for (int i = 0; i < 25; ++i) {
        char filename[12];
        sprintf(filename, "polyfile%d\n", i);
        FILE *f = fopen(filename, "w");
        degree_mins_verbose(i, 0.02, 16, 5000000, f);
        fclose(f);
        printf("file %s written\n", filename);
    }
}
