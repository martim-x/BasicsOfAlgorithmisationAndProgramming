#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
using namespace std;

double f(double x) {
    return x * x * x + x * x - 2 * x - 2;
}

double dichotomy(double (*f)(double), double a, double b, double e) {
    double c;
    while ((b - a) / 2.0 > e) {
        c = (a + b) / 2.0;
        if (f(c) == 0.0)
            return c;
        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
    }
    return (a + b) / 2.0;
}

vector<double> findAllRoots(double (*f)(double), double a, double b, double e, int subdivisions = 1000) {
    vector<double> roots;
    double step = (b - a) / subdivisions;
    double x1 = a;

    for (int i = 0; i < subdivisions; ++i) {
        double x2 = x1 + step;
        if (abs(f(x1)) < e) {
            if (roots.empty() || abs(roots.back() - x1) > e)
                roots.push_back(x1);
        }
        if (f(x1) * f(x2) < 0) {
            double root = dichotomy(f, x1, x2, e);
            bool alreadyFound = false;
            for (double r : roots) {
                if (abs(r - root) < e) {
                    alreadyFound = true;
                    break;
                }
            }
            if (!alreadyFound)
                roots.push_back(root);
        }
        x1 = x2;
    }

    if (abs(f(b)) < e) {
        if (roots.empty() || abs(roots.back() - b) > e)
            roots.push_back(b);
    }

    return roots;
}

int main() {
    double a = -100.0;
    double b = 100.0;
    double e = 0.00001;

    vector<double> roots = findAllRoots(f, a, b, e);

    if (roots.empty()) {
        cout << "Roots weren't found." << endl;
    }
    else {
        cout << "Found roots:" << endl;
        for (double root : roots) {
            cout << root << endl;
        }
    }

    return 0;
}
