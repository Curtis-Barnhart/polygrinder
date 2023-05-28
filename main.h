/**
 * Curtis Barnhart
 * 2023-05-12
 */

#ifndef POLYGRINDER_MAIN_H
#define POLYGRINDER_MAIN_H

void degree_mins(int, double, int);

int compare(gconstpointer, gconstpointer);

gboolean tree_val_printer(gpointer, gpointer, gpointer);

gboolean tree_val_file_printer(gpointer, gpointer, gpointer);

void degree_mins_verbose(int, double, int, unsigned int, FILE*);

int main(int argc, char **argv);

int testing();

#endif //POLYGRINDER_MAIN_H
