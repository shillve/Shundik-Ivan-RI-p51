#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "table.h"

static double fx(double x) {
    return (x*x*x)/30.0 - 4.0*x*x + 50.0;
}

int build_table(Config cfg, Table *out) {
    if (cfg.n < 2 || cfg.step == 0.0) return -1;
    Pair *arr = (Pair*)malloc(sizeof(Pair) * cfg.n);
    if (!arr) return -1;
    for (int i = 0; i < cfg.n; ++i) {
        double x = cfg.x0 + i * cfg.step;
        if ((cfg.step > 0 and x > cfg.x1 + 1e-12) || (cfg.step < 0 and x < cfg.x1 - 1e-12)) {
            free(arr);
            return -1;
        }
        arr[i].x = x;
        arr[i].y = fx(x);
    }
    out->data = arr;
    out->rows = cfg.n;
    return 0;
}

void print_table(const Table *t) {
    if (!t || !t->data) { printf("(empty)\n"); return; }
    printf("\n%-8s %-18s %-18s\n", "Index", "x", "f(x)");
    for (int i = 0; i < t->rows; ++i) {
        printf("%-8d %-18.10lf %-18.10lf\n", i+1, t->data[i].x, t->data[i].y);
    }
}

int write_table_text(const char *path, const Table *t, const char *group, const char *name) {
    FILE *fp = fopen(path, "w");
    if (!fp) return -1;
    fprintf(fp, "%-8s %-18s %-18s\n", "Index", "x", "f(x)");
    for (int i = 0; i < t->rows; ++i) {
        fprintf(fp, "%-8d %-18.12lf %-18.12lf\n", i+1, t->data[i].x, t->data[i].y);
    }
    fprintf(fp, "%s\n%s\n", group ? group : "", name ? name : "");
    fclose(fp);
    return 0;
}

int write_table_bin(const char *path, const Table *t) {
    FILE *fp = fopen(path, "wb");
    if (!fp) return -1;
    int rows = t->rows;
    fwrite(&rows, sizeof(int), 1, fp);
    for (int i = 0; i < rows; ++i) {
        fwrite(&t->data[i].x, sizeof(double), 1, fp);
        fwrite(&t->data[i].y, sizeof(double), 1, fp);
    }
    fclose(fp);
    return 0;
}

int read_pairs_from_bin(const char *path, int *outN, double **outPairs) {
    FILE *fp = fopen(path, "rb");
    if (!fp) return -1;
    int rows = 0;
    if (fread(&rows, sizeof(int), 1, fp) != 1 || rows <= 0) { fclose(fp); return -1; }
    double *arr = (double*)malloc(sizeof(double) * (2 * rows));
    if (!arr) { fclose(fp); return -1; }
    for (int i = 0; i < rows; ++i) {
        if (fread(&arr[2*i], sizeof(double), 1, fp) != 1) { free(arr); fclose(fp); return -1; }
        if (fread(&arr[2*i+1], sizeof(double), 1, fp) != 1) { free(arr); fclose(fp); return -1; }
    }
    fclose(fp);
    *outN = rows;
    *outPairs = arr;
    return 0;
}

void free_table(Table *t) {
    if (!t) return;
    free(t->data);
    t->data = NULL;
    t->rows = 0;
}
