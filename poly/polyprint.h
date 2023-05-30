/**
 * Created by Curtis Barnhart on 2023-05-28
 */

#ifndef POLYGRINDER_POLYPRINT_H
#define POLYGRINDER_POLYPRINT_H

#include "polynomial.h"

typedef enum {
    NORMAL,
    EULER
} poly_str_mode;

static int str_size(poly *, poly_str_mode);

char *poly_str(poly *);

char *poly_str_real(poly *);

#endif //POLYGRINDER_POLYPRINT_H
