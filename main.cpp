#include <math.h>
#include <stdio.h>
#include "splines.h"
#include "quanc8.h"

// Пример функции f(x)
double f(double x) {
    return sin(x); // Здесь можно подставить любую другую функцию
}

// Основная программа
int main() {
    const double h = 0.1;
    const int n = 10; // Количество точек y_k
    double y[n];
    double fy[n];
    double sy[n];

    // Вычисляем точки y_k и значения функции f(x) в этих точках с использованием QUANC8
    for (int k = 0; k < n; k++) {
        y[k] = 0.05 + 0.1 * (k + 1);
        fy[k] = quanc8(f, y[k] - h, y[k] + h, 1e-6);
    }

    // Строим сплайн-функцию по точкам
    spline s;
    s.build(y, fy, n);

    // Вычисляем значения сплайн-функции S(x) в точках y_k
    for (int k = 0; k < n; k++) {
        sy[k] = s.evaluate(y[k]);
    }

    // Вычисляем погрешность и выводим результаты
    printf("k\ty_k\tf(y_k)\tS(y_k)\tError\n");
    for (int k = 0; k < n; k++) {
        double error = fabs(fy[k] - sy[k]);
        printf("%d\t%.2f\t%.6f\t%.6f\t%.6f\n", k + 1, y[k], fy[k], sy[k], error);
    }

    return 0;
}
