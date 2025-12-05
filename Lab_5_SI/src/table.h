#ifndef TABLE_H
#define TABLE_H

#include "fileio.h"

typedef struct {
    double x;
    double y;
} Pair;

typedef struct {
    Pair *data;
    int rows;
} Table;

int build_table(Config cfg, Table *out);
void print_table(const Table *t);
int write_table_text(const char *path, const Table *t, const char *group, const char *name);
int write_table_bin(const char *path, const Table *t);
int read_pairs_from_bin(const char *path, int *outN, double **outPairs);
void free_table(Table *t);

#endif
