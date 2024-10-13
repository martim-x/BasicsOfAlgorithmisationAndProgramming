#include <bits/stdc++.h>
using namespace std;


void task5_1() {
    int num;
    cout << "Input number: " << endl;
    cin >> num;
    num = INT_MAX;
    bitset<32> bt(num);
    cout << bt << endl;
    for (int i = 0; i < 32; i++) {
        if ((i + 1) % 3 == 0)
            num &= ~(1 << i);
    }
    bitset<32> bts(num);
    cout << bts << endl;
}



void task5_2() {
    int numA, numB, n;
    cout << "Input number A: " << endl;
    cin >> numA;
    cout << "Input n: " << endl;
    cin >> n;
    bitset<32> bt(numA);
    cout << bt << endl;
    for (int i = 0; i < 3; i++) {
        numA &= ~(1 << n + i);
    }
}


int main() {
    task5();
    return 0;
}