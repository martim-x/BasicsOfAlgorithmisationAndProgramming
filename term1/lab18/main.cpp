#include <iostream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <cstring>
using namespace std;


double func1(double x) {
    return pow(x, 3) + 3 * x - 1;
}


double func2(double x) {
    return exp(x) - 4;
}


double func3(double x) {
    return exp(x) + 2 * pow(x, 2) - 3;
}


double func4(double x) {
    return pow(x, 3) + 3;
}


double func5(double x) {
    return exp(x) + x - 4;
}


double func6(double x) {
    return pow(x, 2) - 4;
}


double func7(double x) {
    return pow(x, 2) + 4 * x - 2;
}


double func8(double x) {
    return pow(x, 3) + x - 3;
}


double task4_8(double (*func)(double), double a, double b, double e = 0.001) {
    double x;
    do {
        x = (a + b) / 2;
        if (func(x) * func(a) <= 0) {
            b = x;
        }
        else {
            a = x;
        }
    } while (abs(a - b) > 2 * e);
    return x;
}


int task5_8(int n, ...) {
    int* p = &n;
    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        cout << *p << endl;
        if (*(++p) < min)
            min = *p;
        cout << *p << endl;
    }
    return min;
}


int task5_11(int n, ...) {
    int* p = &n;

    int min = INT_MAX;

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    cout << "Matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = *(++p);
            if (min > matrix[i][j]) {
                min = matrix[i][j];
            }
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    cout << "Min value: ";
    return min;
}


char* compr(char* str) {
    int k = 0;
    char* start = str;
    while (*(str + k) != '\0') {
        while (*(str + k) == ' ')
            k++;
        *str = *(str + k);
        str++;
    }
    *str = '\0';
    return start;
}


int task5_1(int n, ...) {
    int* p = &n;
    int min = INT_MAX;
    for (int i = 0; i < n; i++)
        if (*(++p) < min)
            min = *p;
    return min;
}


int main() {
    cout << "Task 4_8" << endl;
    cout << "Input a & b: " << endl;
    double a, b;
    cin >> a >> b;

    cout << "Root for func1: " << task4_8(func1, a, b) << endl;
    cout << "Root for func2: " << task4_8(func2, a, b) << endl;

    cout << "Task 4_11" << endl;
    cout << "Root for func3: " << task4_8(func3, a, b) << endl;
    cout << "Root for func4: " << task4_8(func4, a, b) << endl;

    cout << "Task 4_14" << endl;
    cout << "Root for func5: " << task4_8(func5, a, b) << endl;
    cout << "Root for func6: " << task4_8(func6, a, b) << endl;

    cout << "Task 4_1" << endl;
    cout << "Root for func7: " << task4_8(func7, a, b) << endl;
    cout << "Root for func8: " << task4_8(func8, a, b) << endl;

    cout << "Task 5_8" << endl;
    cout << "Min for 1, 2, 3: " << task5_8(3, -100, 2, 300) << endl;
    cout << "Min for 1000, 2000, 3000: " << task5_8(3, 1000, 2000, 3000) << endl;
    cout << "Min for -1000, -2000, -3000: " << task5_8(3, -1000, -2000, -3000) << endl;

    cout << "Task 5_11" << endl;
    cout << task5_11(3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 9) << endl << endl;
    cout << task5_11(3,
        1000, 2000, 3000,
        4000, 5000, 6000,
        7000, 8000, 9000) << endl << endl;
    cout << task5_11(3,
        -1000, -2000, -3000,
        -4000, -5000, -6000,
        -7000, -8000, -9000) << endl << endl;
    cout << endl;

    cout << "Task 5_14" << endl;
    char str1[] = "Hello world, This is, a test\0";
    char str2[] = "  This   is   a  test \0";
    char str3[] = "NoSpacesHere\0";

    cout << compr(str1) << endl;
    cout << compr(str2) << endl;
    cout << compr(str3) << endl;

    cout << "Task 5_1" << endl;
    cout << "Min for 1, 2, 3: " << task5_1(3, 1, 2, 3) << endl;
    cout << "Min for 1000, 2000, 3000: " << task5_1(3, 1000, 2000, 3000) << endl;
    cout << "Min for -1000, -2000, -3000: " << task5_1(3, -1000, -2000, -3000) << endl;

    return 0;
}
