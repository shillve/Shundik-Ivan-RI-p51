#ifndef FILEIO_H
#define FILEIO_H

typedef struct {
    double x0, x1;   /* start and end of argument */
    int n;           /* number of points (>=2) */
    double step;     /* argument step */
    char group[64];  /* group code */
    char fullname[128]; /* student's surname and name */
} Config;

int read_config_text(const char *path, Config *cfg);
int write_config_text(const char *path, const Config *cfg);

#endif
