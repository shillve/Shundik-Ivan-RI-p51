#include <stdio.h>
#include <string.h>
#include "fileio.h"

int read_config_text(const char *path, Config *cfg) {
    FILE *fp = fopen(path, "r");
    if (!fp) return -1;
    char line[256];

    if (!fgets(line, sizeof(line), fp)) { fclose(fp); return -1; }
    if (sscanf(line, "%lf", &cfg->x0) != 1) { fclose(fp); return -1; }

    if (!fgets(line, sizeof(line), fp)) { fclose(fp); return -1; }
    if (sscanf(line, "%lf", &cfg->x1) != 1) { fclose(fp); return -1; }

    if (!fgets(line, sizeof(line), fp)) { fclose(fp); return -1; }
    if (sscanf(line, "%d", &cfg->n) != 1) { fclose(fp); return -1; }

    if (!fgets(line, sizeof(line), fp)) { fclose(fp); return -1; }
    if (sscanf(line, "%lf", &cfg->step) != 1) { fclose(fp); return -1; }

    if (!fgets(cfg->group, sizeof(cfg->group), fp)) { fclose(fp); return -1; }
    size_t L = strlen(cfg->group);
    if (L && cfg->group[L-1]=='\n') cfg->group[L-1]=0;

    if (!fgets(cfg->fullname, sizeof(cfg->fullname), fp)) { fclose(fp); return -1; }
    L = strlen(cfg->fullname);
    if (L && cfg->fullname[L-1]=='\n') cfg->fullname[L-1]=0;

    fclose(fp);
    return 0;
}

int write_config_text(const char *path, const Config *cfg) {
    FILE *fp = fopen(path, "w");
    if (!fp) return -1;
    fprintf(fp, "%.10lf\n%.10lf\n%d\n%.10lf\n%s\n%s\n", cfg->x0, cfg->x1, cfg->n, cfg->step, cfg->group, cfg->fullname);
    fclose(fp);
    return 0;
}
