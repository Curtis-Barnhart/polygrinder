/**
 * Created by Curtis Barnhart on 2023-05-16.
 */

#include <glib.h>

#ifndef POLYGRINDER_C_IMPROVEMENTS_H
#define POLYGRINDER_C_IMPROVEMENTS_H

typedef struct {
    GTree *tree;
    GArray *keys;
    GArray *count;
    unsigned int size;
} DoubleTracker;

DoubleTracker *DoubleTracker_new(GCompareFunc, unsigned int);

void DoubleTracker_increment(DoubleTracker *, double);

//void DoubleTracker_decrement(DoubleTracker *, double);

unsigned int DoubleTracker_read(DoubleTracker *, double);

void DoubleTracker_destroy(DoubleTracker *);


#endif //POLYGRINDER_C_IMPROVEMENTS_H
