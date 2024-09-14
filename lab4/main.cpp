#include <bits/stdc++.h>
using namespace std;


void task1_8(){
    double a, b ,c, S, p;
    cout<<"Введите значения для сторон треугольника: "<<endl;
    cin>>a>>b>>c;
    p = (a+b+c)/2;
    S = sqrt((p-a)*(p-b)*(p-c));
    cout<<"S = "<<S<<endl;
    cout<<endl;
}


void task2_8(){
    char sym;
    cout<<"Введите символ для человечка: "<<endl;
    cin>>sym;
    printf("**%c%c%c**", sym,sym,sym);
    printf("**%c%c%c**", sym,sym,sym);
    printf("***%c***", sym);
    printf("**%c%c%c**", sym,sym,sym);
    printf("*%c*%c*%c*", sym,sym,sym);
    printf("***%c***", sym);
    printf("**%c*%c**", sym,sym);
    printf("*%c***%c*", sym,sym);
    cout<<endl;
}


void task1_16(){
    char sym;
    cout<<"Введите 5 скоростей: "<<endl;
    cin>>sym;
    printf("***%c***", sym,sym,sym);
    printf("**%c%c%c**", sym,sym,sym);
    printf("*%c%c%c%c%c*", sym,sym,sym,sym,sym);
    printf("***%c***", sym,sym,sym);
    printf("***%c***", sym,sym,sym);
    cout<<endl;
}


void task2_16(){
    double sp1, sp2, sp3, sp4, sp5;
    cin>>sp1>>sp2>>sp3>>sp4>>sp5;
    cout<<"Средняя скорость составила: "<<(sp1+sp2+sp3+sp4+sp5)/5<<endl;
}


int main(){
    task1_8();
    task2_8();
    task1_16();
    task2_16();
    return 0;
}


// chcp 65001 For windows
// export LANG=en_US.UTF-8 For Linux