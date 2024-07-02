#ifndef SPLINES_H
#define SPLINES_H

#include <vector>
#include <stdexcept>

class Spline {
public:
    // Конструктор по умолчанию
    Spline() {}

    // Метод для построения сплайна
    void build(const std::vector<double>& xs, const std::vector<double>& ys) {
        int n = xs.size();
        if (n < 2) throw std::invalid_argument("There must be at least two data points.");

        x = xs;
        a = ys;
        b.resize(n);
        c.resize(n);
        d.resize(n);

        std::vector<double> h(n), alpha(n), l(n), mu(n), z(n);
        for (int i = 1; i < n - 1; ++i) {
            h[i] = x[i + 1] - x[i];
            alpha[i] = (3 / h[i]) * (a[i + 1] - a[i]) - (3 / h[i - 1]) * (a[i] - a[i - 1]);
        }

        l[0] = 1;
        mu[0] = z[0] = 0;
        for (int i = 1; i < n - 1; ++i) {
            l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
            mu[i] = h[i] / l[i];
            z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
        }
        l[n - 1] = 1;
        z[n - 1] = c[n - 1] = 0;

        for (int j = n - 2; j >= 0; --j) {
            c[j] = z[j] - mu[j] * c[j + 1];
            b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
            d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
        }
    }

    // Метод для вычисления значения сплайна в точке
    double evaluate(double xi) const {
        int n = x.size();
        if (xi <= x[0]) return a[0];
        if (xi >= x[n - 1]) return a[n - 1];

        int i = 0, j = n - 1;
        while (i < j - 1) {
            int k = (i + j) / 2;
            if (x[k] <= xi) i = k;
            else j = k;
        }

        double dx = xi - x[i];
        return a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
    }

private:
    std::vector<double> x, a, b, c, d;
};

#endif // SPLINES_H
