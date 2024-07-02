#ifndef QUANC8_H
#define QUANC8_H

#include <functional>
#include <cmath>

// QUANC8 - численное интегрирование методом QUANC8
double quanc8(std::function<double(double)> f, double a, double b, double tol) {
    const int n = 5;
    const double x[n] = {0.1488743389816312, 0.4333953941292472, 0.6794095682990244, 0.8650633666889845, 0.9739065285171717};
    const double w[n] = {0.2955242247147529, 0.2692667193099963, 0.2190863625159820, 0.1494513491505806, 0.0666713443086881};
    
    double m = (a + b) / 2;
    double h = (b - a) / 2;
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        result += w[i] * (f(m - h * x[i]) + f(m + h * x[i]));
    }

    return h * result;
}

#endif // QUANC8_H
