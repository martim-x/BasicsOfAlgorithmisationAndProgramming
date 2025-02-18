#include <bits/stdc++.h>
using namespace std;


double f(double x, int flag) {
    vector<double> f = { pow(x, 3) - 1, pow(x, 3) + 1, pow(x, 2) - 4, sin(x) + 1 };
    return f[flag];
}


double g(double x, int flag) {
    vector<double> g = { pow(x, 3) + x - 4, sin(x) + pow(x, 3), exp(x) + 2 * pow(x, 2) - 3, 2 * x + pow(x, 3) - 7 };
    return g[flag];
}


void task5(double a, double b, double n, int flag) {
    double h, x, s;
    h = (b - a) / n;
    x = a;
    s = 0;
    do {
        s += h * (f(x, flag) + f(x + h, flag)) / 2;
        x += h;
    } while (x <= (b - h));
    cout << s << endl;
}


void task5_1(double a, double b, double n, int flag) {
    double h, x, i, s1, s2, s;
    h = (b - a) / (2 * n);
    x = a + 2 * h;
    s1 = s2 = 0;
    i = 1;
    do {
        s2 += f(x, flag);
        x += h;
        s1 += f(x, flag);
        x += h;
        i++;
    } while (i < n);

    s = h / 3 * (f(a, flag) + 4 * f(a + h, flag) + 4 * s1 + 2 * s2 + f(b, flag));
    cout << s << endl;
}


void task6(double a, double b, double e, int flag) {
    double x;
    do {
        x = (a + b) / 2;
        if (g(x, flag) * g(a, flag) <= 0) {
            b = x;
        }
        else {
            a = x;
        }
    } while (abs(a - b) > 2 * e);
    cout << x << endl;
}


int main() {
    vector<double> A = { 0, 3, 4, 1 };
    vector<double> B = { 3, 6, 8, 3 };
    double n = 200, e = 1e-4;
    for (int i = 0; i < 4; i++) {
        task5(A[i], B[i], n, i);
        task5_1(A[i], B[i], n, i);
        task6(A[i], B[i], e, i);
        cout << endl;
    }
    return 0;
}