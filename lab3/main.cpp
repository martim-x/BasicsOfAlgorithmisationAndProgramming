#include <bits/stdc++.h>
using namespace std;
// chcp 65001 For Windows
// export LANG=en_US.UTF-8 For Linux

void task4_7()
{
    double x = 1.4, m = 6, z = 5e-5, y, w;
    y = sqrt(1 + x) - cos(2 / m);
    w = 0.6 * z - 2 * exp(-2 * y * m);
    cout << "y = " << y << ", w = " << w << endl;
}
void task4_8()
{
    double x = 0.1, j = 12, y = 5e-6, s, t;
    s = 0.4 * x - 1 / j * tan(y);
    t = s - sin(s);
    cout << "s = " << s << ", t = " << t << endl;
}

void task4_16()
{
    double m = 6, z = 5e-7, y;
    y = cos(5 * m) / pow(sin(0.4 * m), 2);
    cout << "y = " << y << endl;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    task4_7();
    task4_8();
    task4_16();
    return 0;
}
