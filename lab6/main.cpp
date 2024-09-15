#include <bits/stdc++.h>
using namespace std;
// chcp 65001 For Windows
// export LANG=en_US.UTF-8 For Linux


double t = -7.4, n = 9, w, s;


void task5for(){
    vector<double> j = {0.5, 8.4, 0.3};
    double y = 5;
    for (auto el : j){
        w = 0.6 * el + exp(t - el) * pow(4 * y / n, 2);
        s = sqrt(w - 0.1 * t) / (2 + pow(n, 2));
        printf("s = %f\n", s);
    }
    printf("\n");
}


void task5while(){
    double y = 5, j = 0;
    while (j < 2){
        w = 0.6 * j + exp(t - j) * pow(4 * y / n, 2);
        s = sqrt(w - 0.1 * t) / (2 + pow(n, 2));
        printf("s = %f\n", s);
        j += 0.1;
    }
    printf("\n");
}


void task5forfor(){
    vector<double> y = {0.1, -3, 0.5};
    for (double j = 0.1; j < 0.4; j += 0.1)
        for (auto el : y){
            w = 0.6 * j + exp(t - j) * pow(4 * el / n, 2);
            s = sqrt(w - 0.1 * t) / (2 + pow(n, 2));
            printf("s = %f\n", s);
        }
}


void task6(){
    string str;
    cin >> str;
    str.erase(remove(str.begin(),str.end(),'3'), str.end());
    str.erase(remove(str.begin(),str.end(),'6'), str.end());
    cout<<"Строка без 3 и 6: "<<str<<endl;
}


int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    task5for();
    task5while();
    task5forfor();
    task6();
    return 0;
}