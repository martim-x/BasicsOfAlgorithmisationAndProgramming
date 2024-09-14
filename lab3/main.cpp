#include <bits/stdc++.h>
using namespace std;


void task3(){
    double t, u, k = 4, a = 4.1, x = 5e-5;
	t = 2 * tan(k) / a + log(3 + x) + exp(x);
	u = sqrt(t + 1) - sin(x) * cos(t);
    cout <<"t = "<<t<<", u = "<<u<<endl;
}


void task4_8(){
    double x = 0.1, j = 12, y = 5e-6, s ,t;
    s = 0.4 * x - 1 / j * tan(y);
    t = s - sin(s);
    cout<<"s = "<<s<<", t = "<<t<<endl;
}


void task4_16(){
    double m = 6, z = 5e-7, y;
    y = cos(5 * m) / pow(sin(0.4 * m), 2);
    cout<<"y = "<<y<<endl;
}


void task4_7(){
    double x = 1.4, m = 6, z = 5e-5, y ,w;
    y = sqrt(1+x) - cos(2/m);
    w = 0.6*z - 2*exp(-2*y*m);
    cout<<"y = "<<y<<", w = "<<w<<endl;
}


int main(){
    setlocale(LC_CTYPE, "Russian"); 
    task3();
    task4_8();
    task4_16();
    task4_7();
    return 0;
} 
