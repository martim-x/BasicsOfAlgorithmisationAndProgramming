#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;


int inputValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value && ss.eof() && value >= min && value <= max) {
            return value;
        }
        cout << "Invalid input! Please try again." << endl;
    }
}


double f(double x) {
    return x * x * x + x * x - 2 * x - 2;
}

double dichotomy(double (*func)(double), double a, double b, double e) {
    double c = (a + b) / 2.0;

    if (b - a <= 2 * e) return c;

    if (func(a) * func(c) <= 0)
        return dichotomy(func, a, c, e);
    else
        return dichotomy(func, c, b, e);
}

int main() {
    double a, b;
    double e = 1e-6;

    a = inputValidatedInt("Input a (-10,000 - 10,000): ", -10000, 10000);
    b = inputValidatedInt("Input b (-10,000 - 10,000): ", -10000, 10000);
    if (a > b){
        cout<<"a must be lower than b"<<endl;
        return 0;
    }
    if (f(a) * f(b) >= 0) {
        cout << "f(a)*(b)<0" << endl;
        return 1;
    }

    double root = dichotomy(f, a, b, e);
    cout << "Found root: " << root << endl;
    cout << "Function value at root: " << f(root) << endl;

    return 0;
}
