#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my_formulas.h"

int main() {
    double a, b, eps;
    unsigned int fixed_n[] = {10, 100, 1000, 10000};
    unsigned int N = 2;
    int choice;
    double I1, I2, delta;

    // Введення меж інтегрування
    printf("Enter left boundary a: ");
    scanf("%lf", &a);
    printf("Enter right boundary b: ");
    scanf("%lf", &b);

    // Введення epsilon
    do {
        printf("Enter accuracy epsilon (0.00001 <= eps <= 0.001): ");
        scanf("%lf", &eps);
        if (eps < 0.00001 || eps > 0.001)
            printf("Error: epsilon must be in range [0.00001, 0.001]\n");
    } while (eps < 0.00001 || eps > 0.001);

    // Вибір методу
    do {
        printf("\nChoose method of calculation:\n");
        printf("  1. Left rectangles\n");
        printf("  2. Right rectangles\n");
        printf("  3. Trapezoid\n");
        printf("  4. Parabola (Simpson)\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 4)
            printf("Invalid choice. Try again.\n");
    } while (choice < 1 || choice > 4);

    // ===============================
    // Завдання 1: Розрахунок при фіксованих n
    // ===============================
    printf("\n%-25s", "Method");
    for (int i = 0; i < 4; i++) {
        printf("| n=%-8u", fixed_n[i]);
    }
    printf("\n");

    switch (choice) {
        case 1:
            printf("%-25s", "Left rectangles");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf", integral_left(a, b, fixed_n[i]));
            printf("\n");
            break;

        case 2:
            printf("%-25s", "Right rectangles");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf", integral_right(a, b, fixed_n[i]));
            printf("\n");
            break;

        case 3:
            printf("%-25s", "Trapezoid");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf", integral_trapezoid(a, b, fixed_n[i]));
            printf("\n");
            break;

        case 4:
            printf("%-25s", "Parabola (Simpson)");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf", integral_simpson(a, b, fixed_n[i]));
            printf("\n");
            break;
    }

    // ===============================
    // Завдання 2: Пошук мінімального N для заданої точності
    // ===============================
    printf("\n=== Accuracy analysis ===\n");

    do {
        switch (choice) {
            case 1:
                I1 = integral_left(a, b, N);
                I2 = integral_left(a, b, N + 2);
                break;
            case 2:
                I1 = integral_right(a, b, N);
                I2 = integral_right(a, b, N + 2);
                break;
            case 3:
                I1 = integral_trapezoid(a, b, N);
                I2 = integral_trapezoid(a, b, N + 2);
                break;
            case 4:
                I1 = integral_simpson(a, b, N);
                I2 = integral_simpson(a, b, N + 2);
                break;
        }

        delta = fabs(I1 - I2);
        printf("N = %-5u | I1 = %-10.6lf | I2 = %-10.6lf | Delta = %.8lf\n",
               N, I1, I2, delta);
        N += 2;
    } while (delta > eps);

    // Остаточний результат
    N -= 2;
    printf("\nMinimum N found: %u (Delta ≤ %.8lf)\n", N, eps);

    // Обчислюємо остаточне значення інтегралу при цьому N
    double final_result;
    switch (choice) {
        case 1: final_result = integral_left(a, b, N); break;
        case 2: final_result = integral_right(a, b, N); break;
        case 3: final_result = integral_trapezoid(a, b, N); break;
        case 4: final_result = integral_simpson(a, b, N); break;
    }
    printf("Final integral value at N=%u: %.10lf\n", N, final_result);

    printf("\n");
    system("pause");
    return 0;
}
