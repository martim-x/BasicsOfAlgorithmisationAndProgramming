#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;
// chcp 65001 For Windows
// export LANG=en_US.UTF-8 For Linux
void task1_8()
{
    double a, b, c, S, p;
    cout << "Введите значения для сторон треугольника: " << endl;
    cin >> a >> b >> c;
    p = (a + b + c) / 2;
    S = sqrt((p - a) * (p - b) * (p - c));
    cout << "S = " << S << endl;
    cout << endl;
}

void task2_8()
{
    char sym;
    cout << "Введите символ для человечка: " << endl;
    cin >> sym;
    printf("**%c%c%c**\n", sym, sym, sym);
    printf("**%c%c%c**\n", sym, sym, sym);
    printf("***%c**\n", sym);
    printf("**%c%c%c**\n", sym, sym, sym);
    printf("*%c*%c*%c*\n", sym, sym, sym);
    printf("***%c***\n", sym);
    printf("**%c*%c**\n", sym, sym);
    printf("*%c***%c*\n", sym, sym);
    cout << endl;
}

void task1_16()
{
    char sym;
    cout << "Введите символ для грибочка: " << endl;
    cin >> sym;
    printf("***%c***\n", sym, sym, sym);
    printf("**%c%c%c**\n", sym, sym, sym);
    printf("*%c%c%c%c%c*\n", sym, sym, sym, sym, sym);
    printf("***%c***\n", sym, sym, sym);
    printf("***%c***\n", sym, sym, sym);
    cout << endl;
}

void task2_16()
{
    double sp1, sp2, sp3, sp4, sp5;
    cout << "Введите 5 скоростей: " << endl;
    cin >> sp1 >> sp2 >> sp3 >> sp4 >> sp5;
    cout << "Средняя скорость составила: " << (sp1 + sp2 + sp3 + sp4 + sp5) / 5 << endl;
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    task1_8();
    task2_8();
    task1_16();
    task2_16();
    return 0;
}