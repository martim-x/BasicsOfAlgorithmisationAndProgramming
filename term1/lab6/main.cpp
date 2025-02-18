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


int task6_1(double start, double end, int count){
    if (start>=end){
        return count;
    }
    else{
        start = start*1.03;
        count++;
        cout<<"день: "<<count<<", прибыль: "<<start<<endl;
        task6_1(start, end, count);
    }
}


int task6_4(int k){
    string strNum = "1";
    long long intNum = 1;
    int lim = round((k-5)/10);
    if (!lim) lim = 1;
    map<int, int> table = {
        {1,10},
        {2,10},
        {3,10},
        {4,20},
        {5,20},
        {6,20},
        {7,30},
        {8,30},
        {9,30},
        {10,40},
        {11,40},
        {12,40},
        {13,50},
        {14,50},
        {15,50},
        {16,50},
        {17,50},
        {18,60},
        {19,60}
    };

    for (int i = 0; i< table[lim]; i++){
        intNum = intNum<<1;
        strNum += to_string(intNum);
    }
    cout<<strNum<<endl;
    cout<<strNum[k-1]-'0'<<endl;
    return strNum[k-1]-'0';
}


void task6_6(){
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

    double P, Q;
    cout<<"Введите значение для P и Q: "<<endl;
    cin>>P>>Q;
    task6_6();
    cout<<"Столько дней потребуется для увеличения прибыли "<<task6_1(P, Q, 0)<<endl;

    cout<<"Введите значение для k: "<<endl;
    int k;
    cin>>k;
    task6_4(k);
    return 0;
}