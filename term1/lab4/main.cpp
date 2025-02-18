#include <bits/stdc++.h>
using namespace std;
// chcp 65001 For Windows
// export LANG=en_US.UTF-8 For Linux


void task1_4(){
    char sym;
    cout << "Введите символ для круга: " << endl;
    cin>>sym;
    printf("    %c%c%c\n",sym,sym,sym);
    printf("  %c%c%c%c%c\n",sym,sym,sym,sym,sym);
    printf(" %c%c%c%c%c%c\n",sym,sym,sym,sym,sym,sym);
    printf(" %c%c%c%c%c%c\n",sym,sym,sym,sym,sym,sym);
    printf("  %c%c%c%c%c\n",sym,sym,sym,sym, sym);
    printf("    %c%c%c\n",sym,sym,sym);
}


void task2_4(){
    double X, Y, Z, avarageAriph, averageGeom;
    cout << "Введите значения для X Y Z: " << endl;
    avarageAriph = (X + Y + Z)/3;
    averageGeom = pow(X*Y*Z, 0.3);
    cout << "Среднее арифметическое: "<<avarageAriph<<", среднее геометрическое: "<<averageGeom << endl;
}


void task1_8(){
    double a, b, c, S, p;
    cout << "Введите значения для сторон треугольника: " << endl;
    cin >> a >> b >> c;
    p = (a + b + c) / 2;
    S = sqrt((p - a) * (p - b) * (p - c));
    cout << "S = " << S << endl;
    cout << endl;
}


void task2_8(){
    char sym;
    cout << "Введите символ для человечка: " << endl;
    cin >> sym;
    printf("  %c%c%c  \n", sym, sym, sym);
    printf("  %c%c%c  \n", sym, sym, sym);
    printf("   %c  \n", sym);
    printf("  %c%c%c  \n", sym, sym, sym);
    printf(" %c %c %c \n", sym, sym, sym);
    printf("   %c   \n", sym);
    printf("  %c %c  \n", sym, sym);
    printf(" %c   %c \n", sym, sym);
    cout << endl;
}


void task1_13(){
    char sym;
    cout << "Введите символ для сердечка: " << endl;
    printf("   %c     %c    \n",sym,sym);
    printf(" %c%c%c%c%c%c\n",sym,sym);
    printf("%c%c%c%c%c%c%c\n",sym,sym);
    printf(" %c%c%c%c%c%c\n",sym,sym);
    printf(" %c%c%c%c%c%c\n",sym,sym);
    printf("  %c%c%c%c\n",sym,sym);
    printf("   %c%c%c\n",sym,sym);
    printf("     %c\n",sym,sym);


}


void task2_13(){
    int N, M, summary = 0;
    cout << "Введите N и M: " << endl;
    summary += M;
    for( int i = 0; i < N; i++){
        summary += i*10 + M;
    }
    cout << "Всего часов работала вся бригада: " << endl;
}


void task1_16(){
    char sym;
    cout << "Введите символ для грибочка: " << endl;
    cin >> sym;
    printf("   %c   \n", sym, sym, sym);
    printf("  %c%c%c  \n", sym, sym, sym);
    printf(" %c%c%c%c%c \n", sym, sym, sym, sym, sym);
    printf("   %c   \n", sym, sym, sym);
    printf("   %c   \n", sym, sym, sym);
    cout << endl;
}


void task2_16(){
    double sp1, sp2, sp3, sp4, sp5;
    cout << "Введите 5 скоростей: " << endl;
    cin >> sp1 >> sp2 >> sp3 >> sp4 >> sp5;
    cout << "Средняя скорость составила: " << (sp1 + sp2 + sp3 + sp4 + sp5) / 5 << endl;
}


int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    task1_4();
    task2_4();
    task1_8();
    task2_8();
    task1_13();
    task2_13();
    task1_16();
    task2_16();
    return 0;
}