#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Варіант 10
int main()
{
    double x, y;

    printf("Enter x: ");
    scanf("%lf", &x);

    if (x < -7)
        // (x^2 - 4) / (x^2 + 1)
        y = (x*x - 4.0) / (x*x + 1.0);

    else if (x >= -7 && x < 4)
        // 7x - 3
        y = 7.0 * x - 3.0;

    else if (x >= 4 && x < 25)
        // sqrt(x) + x/10
        y = sqrt(x) + x / 10.0;

    else
        // x^3 - 5x
        y = pow(x, 3.0) - 5.0 * x;

    printf("x = %.6lf", x);
    printf("\ny = %.6lf", y);

    printf("\n");
    system("pause");
    return 0;
}

