#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#define M_PI 3.1415926535

// Factorial function
double factor(int N) {
    double c = 1;
    for (int j = 1; j <= N; j++) {
        c *= j;  // Multiply directly
    }
    return c;
}

// Function f1(x)
double fa(double x) {
    if (x <= 3) {
        return pow(x, 2) - 3 * x + 9;
    }
    else {
        return 1 / (pow(x, 3) + 3);
    }
}

// Function f2(x)
double fb(double x) {
    return x * exp(sin(pow(x, 2)));
}

// Sine approximation using series
double sinus_n(double x, int N) {
    double sin_val = 0.;
    for (int k = 1; k <= N; k++) {
        int c = 2 * k - 1;
        sin_val += pow(-1, k - 1) * (pow(x, c) / factor(c));  // Accumulate terms
    }
    return sin_val;
}

// Sine approximation with given error margin
double epssin(double x, double eps) {
    double s = 0;
    double x2 = x;  // Initial approximation
    int k = 1, d = 1;
    while (fabs(x2) > eps) {
        s += d * x2;  // Accumulate the terms
        int c = 2 * k - 1;
        x2 = (pow(-1, k - 1) * (pow(x, c) / factor(c)));
        d = -d;
        k++;
    }
    return s;
}

// Function to print a pentagon
void print_pentagon(int radius, char symbol) {
    // Printing the upper part of the pentagon
    for (int i = 0; i < radius; i++) {
        for (int j = 0; j < radius - i - 1; j++) {
            printf(" ");
        }
        for (int j = 0; j < 2 * i + 1; j++) {
            printf("%c", symbol);
        }
        printf("\n");
    }

    // Printing the lower part of the pentagon
    for (int i = 0; i < radius; i++) {
        for (int j = 0; j < 2 * radius - 1; j++) {
            if (j == 0 || j == 2 * radius - 2) {
                printf("%c", symbol);
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// Function to calculate the area of a pentagon
float area_pentagon(int R) {
    float S;
    S = (5.0 * R * R) / (4.0 * tan(M_PI / 5));
    return S;
}

// Function to print the figure name
void name(int an) {
    if (an == 1) printf("Это линия\n");
    if (an == 2) printf("Это угол\n");
    if (an == 3) printf("Это треугольник\n");
    if (an == 5) printf("Это пентагон\n");
}

// Main function
int main() {
    setlocale(LC_CTYPE, "RUS");

    int R, an = 0;
    printf("\nВведите радиус: ");
    scanf("%d", &R);
    printf("\nВведите число сторон: ");
    scanf("%d", &an);

    while (1) {
        double x, eps;
        int N;
        char a;
        printf("\nВведите x: ");
        scanf("%lf", &x);
        printf("Введите eps (Пример: 0.001): ");
        scanf("%lf", &eps);
        printf("Введите N: ");
        scanf("%d", &N);

        // Output f1(x) and f2(x)
        printf("f1(x) = %lf\t f2(x) = %lf", fa(x), fb(x));
        printf("\nПроизведение = %lf\t Сложение = %lf\t Вычитание = %lf", fa(x) * fb(x), fa(x) + fb(x), fa(x) - fb(x));
        printf("\n");

        // Output sine approximation results
        printf("Номер  Результат  Отклонение\n");
        for (int i = 1; i <= N; i++) {
            double res = sinus_n(x, i);
            printf("%4.d | \t%lf | %e \n", i, res, sin(x) - res);
        }

        // Menu for geometric operations
        int l;
        do {
            printf("\nВыберите операцию над фигурой: \n\t1) Расчитать площадь\n\t2) Вывести определение фигуры\n\t3) Нарисовать фигуру\n");
            scanf("%d", &l);
switch (l) {
case 1:
    printf("Выбран расчет площади\n");
    printf("Площадь = %lf\n", area_pentagon(R));
    break;
case 2:
    printf("Выбран вывод определения фигуры\n");
    name(5);
    break;
case 3:
{
    char symvol;
    printf("Выбрана операция нарисовать фигуру\n");
    printf("\nВведите символ для построения фигуры: ");
    scanf(" %c", &symvol);
    print_pentagon(R, symvol);
    break;
}
default:
    printf("Не верно введен номер\n");
}
        } while (l != 0);

        printf("\nПродолжить ? (Да-y / Нет-n): ");
        scanf(" %c", &a);
        if (a == 'n') break;

    }

}