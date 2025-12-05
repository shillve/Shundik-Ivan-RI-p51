#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "windows.h"

double math_function(double x);        // f(x)
double derivative_1_math_funct(double x); // f'(x)

void print_table_by_N(double x1, double x2, int N);
void print_table_by_delta(double x1, double x2, double delta);
void draw_table_header();
void draw_table_row(double x);

int main() {
    int mode;
    double x1, x2, delta;
    int N;

    SetConsoleCP(65001); //UTF-8
    SetConsoleOutputCP(65001); //UTF-8

    for (;;) {
        printf("\n=== Вибір режиму введення даних ===\n");
        printf("1 - X1, X2, N (кількість точок)\n");
        printf("2 - X1, X2, delta (крок)\n");
        printf("0 - Вихід\n");
        printf("Ваш вибір: ");
        scanf("%d", &mode);

        if (mode == 0) break;

        switch (mode) {

            case 1:
                printf("Введіть X1: ");
                scanf("%lf", &x1);
                printf("Введіть X2: ");
                scanf("%lf", &x2);
                printf("Введіть N (кількість точок): ");
                scanf("%d", &N);

                if (x2 <= x1 || N <= 1) {
                    printf("Помилка: X2 > X1 та N > 1\n");
                    break;
                }

                print_table_by_N(x1, x2, N);
                break;

            case 2:
                printf("Введіть X1: ");
                scanf("%lf", &x1);
                printf("Введіть X2: ");
                scanf("%lf", &x2);
                printf("Введіть delta (крок): ");
                scanf("%lf", &delta);

                if (x2 <= x1 || delta <= 0 || (x2 - x1) / delta > 10000) {
                    printf("Помилка: Неправильні значення!\n");
                    break;
                }

                print_table_by_delta(x1, x2, delta);
                break;

            default:
                printf("Невідомий режим!\n");
        }
    }

    return 0;
}



// f(x) = 0.25x^3 - 25x^2 + x + 1
double math_function(double x) {
    return 0.25 * pow(x, 3) - 25 * pow(x, 2) + x + 1;
}

// f'(x) = 0.75x^2 - 50x + 1
double derivative_1_math_funct(double x) {
    return 0.75 * pow(x, 2) - 50 * x + 1;
}


// ====== Формування таблиці ======
void print_table_by_N(double x1, double x2, int N) {
    double step = (x2 - x1) / (N - 1);
    draw_table_header();

    for (int i = 0; i < N; i++) {
        double x = x1 + i * step;
        draw_table_row(x);
    }
}

void print_table_by_delta(double x1, double x2, double delta) {
    draw_table_header();

    for (double x = x1; x <= x2; x += delta) {
        draw_table_row(x);
    }
}

void draw_table_header() {
    printf("\n┌────────────┬───────────────┬───────────────┐\n");
    printf("│     x      │     f(x)      │     f'(x)     │\n");
    printf("├────────────┼───────────────┼───────────────┤\n");
}

void draw_table_row(double x) {
    double fx = math_function(x);
    double dfx = derivative_1_math_funct(x);

    printf("│ %10.4lf │ %13.6lf │ %13.6lf │\n", x, fx, dfx);
}
