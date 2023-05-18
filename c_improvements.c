/**
 * Created by Curtis Barnhart on 2023-05-16.
 */

#include <stdio.h>

#include "c_improvements.h"

DoubleTracker *DoubleTracker_new(GCompareFunc comparator, unsigned int size) {
    DoubleTracker *instance = malloc(sizeof(DoubleTracker));
    instance->tree = g_tree_new(comparator);
    instance->keys = g_array_sized_new(FALSE, FALSE, sizeof(double), size);
    instance->count = g_array_sized_new(FALSE, FALSE, sizeof(int), size);
    instance->size = size;
//    g_array_set_size(instance->keys, size);
//    g_array_set_size(instance->count, size);
    return instance;
}

void DoubleTracker_increment(DoubleTracker *tracker, double key) {
    double local_key = key;
    unsigned int *where = (unsigned int *) g_tree_lookup(tracker->tree, &local_key);  // attempt to get current address of the count
    GTree *tree = tracker->tree;
    GArray *keys = tracker->keys;
    GArray *count = tracker->count;

    if (where == NULL) {  // If key is not contained, make a new one
        // First add to the key and count holders
        // Macro g_array_append_val requires variable to hold address of value
        unsigned int v = 1;
        g_array_append_val(tracker->keys, key);
        g_array_append_val(tracker->count, v);

        // Calculate the address of the key and count element you just added
        unsigned int index = keys->len - 1;
        gpointer key_address = keys->data + (index * sizeof(double));
        gpointer count_address = count->data + (index * sizeof(unsigned int));

        // Make sure the array didn't resize
//        printf("thing added at %u\n", index);  // TODO: debug
        if (index + 1 > tracker->size) {  // TODO: debug
            printf("ARRAY RESIZED at %u\n", index);
            exit(0);
        }

        // Add the key and count into the tree
        g_tree_insert(tree, key_address, count_address);
    } else { // If the key is contained, increment the count by 1
        (*where)++;
    }
}

//void DoubleTracker_decrement(DoubleTracker *, double);

unsigned int DoubleTracker_read(DoubleTracker *tracker, double key) {
    unsigned int *where = g_tree_lookup(tracker->tree, &key);
    if (where == NULL) {
        return 0;
    } else {
        return *where;
    }
}

void DoubleTracker_destroy(DoubleTracker *tracker) {
    g_tree_destroy(tracker->tree);
    g_array_free(tracker->keys, TRUE);
    g_array_free(tracker->count, TRUE);
}
