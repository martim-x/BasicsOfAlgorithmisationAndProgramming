#include <bits/stdc++.h>
using namespace std;

void task1(){
    double a, b ,c, S, p;
    cin>>a>>b>>c;
    p = (a+b+c)/2;
    S = sqrt((p-a)*(p-b)*(p-c));
    cout<<"S = "<<S<<endl;
}

void task2(){
    char sym;
    cin>>sym;
    printf("**%c%c%c**", sym,sym,sym);
    printf("**%c%c%c**", sym,sym,sym);
    printf("***%c***", sym);
    printf("**%c%c%c**", sym,sym,sym);
    printf("*%c*%c*%c*", sym,sym,sym);
    printf("***%c***", sym);
    printf("**%c*%c**", sym,sym);
    printf("*%c***%c*", sym,sym);

}


int main(){
    task1();
    task2();
    return 0;
}