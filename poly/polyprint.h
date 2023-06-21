/**
 * Created by Curtis Barnhart on 2023-05-28
 */

#ifndef POLYGRINDER_POLYPRINT_H
#define POLYGRINDER_POLYPRINT_H

#include "polynomial.h"

static int str_size(poly *);

char *poly_str_cp(poly *, char *);

char *poly_str(poly *);

#endif //POLYGRINDER_POLYPRINT_H
