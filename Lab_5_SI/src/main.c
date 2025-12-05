#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "fileio.h"
#include "table.h"

/* Lab 5 (final): exact input format (6 lines) and fixed function:
   f(x) = x^3/30 - 4x^2 + 50
   Files:
     - Input.txt  (read)
     - Output.txt (write table + group + name)
     - table.bin  (binary: N, then pairs x,y as doubles)
*/

static void print_menu(void) {
    printf("\n=== Lab 5: File I/O (Final) ===\n");
    printf("1) Load Input.txt\n");
    printf("2) Build table and write Output.txt + table.bin\n");
    printf("3) Read table.bin and display (allocate 2N doubles)\n");
    printf("4) Exit\n");
    printf("Your choice: ");
}

int main(void) {
    Config cfg = { .x0 = 0, .x1 = 0, .n = 0, .step = 0 };
    cfg.group[0] = '\\0'; cfg.fullname[0] = '\\0';
    Table tbl = {0};
    int running = 1;

    while (running) {
        print_menu();
        int ch = 0;
        if (scanf("%d", &ch) != 1) { fprintf(stderr, "Input error.\n"); return 1; }

        if (ch == 1) {
            if (read_config_text("Input.txt", &cfg) == 0) {
                printf("Loaded Input.txt:\n  x0=%.6lf\n  x1=%.6lf\n  n=%d\n  step=%.6lf\n  group=%s\n  name=%s\n",
                       cfg.x0, cfg.x1, cfg.n, cfg.step, cfg.group, cfg.fullname);
            } else {
                printf("Failed to read Input.txt. Check 6-line format.\n");
            }
        } else if (ch == 2) {
            if (cfg.n < 2 || cfg.step == 0.0) {
                printf("Load Input.txt first (option 1).\n");
                continue;
            }
            free_table(&tbl);
            clock_t t0 = clock();
            int rc = build_table(cfg, &tbl);
            clock_t t1 = clock();
            if (rc != 0) {
                printf("Build failed (ensure xi stay within [x0,x1] with given step and n).\n");
                continue;
            }
            printf("Built %d rows in %.6lf s\n", tbl.rows, (double)(t1-t0)/CLOCKS_PER_SEC);
            if (write_table_text("Output.txt", &tbl, cfg.group, cfg.fullname) == 0) printf("Wrote Output.txt\n");
            else printf("Failed to write Output.txt\n");
            if (write_table_bin("table.bin", &tbl) == 0) printf("Wrote table.bin\n");
            else printf("Failed to write table.bin\n");
        } else if (ch == 3) {
            int N = 0;
            double *pairs = NULL;
            if (read_pairs_from_bin("table.bin", &N, &pairs) == 0) {
                printf("\nRead %d rows from table.bin\n", N);
                printf("%-8s %-18s %-18s\n", "Index", "x", "f(x)");
                for (int i = 0; i < N; ++i) {
                    double x = pairs[2*i], y = pairs[2*i+1];
                    printf("%-8d %-18.10lf %-18.10lf\n", i+1, x, y);
                }
                free(pairs);
            } else {
                printf("Failed to read table.bin\n");
            }
        } else if (ch == 4) {
            running = 0;
        } else {
            printf("Invalid choice.\n");
        }
    }
    free_table(&tbl);
    return 0;
}
