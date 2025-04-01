#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
    return x * x * x + x * x - 2 * x - 2;
}

double dichotomy(double (*func)(double), double a, double b, double e) {
    double c = (a + b) / 2.0;

    if (b - a <= 2 * e) return c;

    if (func(a) * func(c) < 0)
        return dichotomy(func, a, c, e);
    else
        return dichotomy(func, c, b, e);
}

int main() {
    double a = -2.0;
    double b = 2.0;
    double e = 1e-6;

    if (f(a) * f(b) >= 0) {
        cout << "f(a)*(b)<0" << endl;
        return 1;
    }

    double root = dichotomy(f, a, b, e);
    cout << "Found root: " << root << endl;
    cout << "Function value at root: " << f(root) << endl;

    return 0;
}
