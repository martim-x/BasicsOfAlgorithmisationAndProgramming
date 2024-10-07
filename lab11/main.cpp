#include <bits/stdc++.h>
using namespace std;


void task5_1() {
    int num;
    cout << "Input number: " << endl;
    cin >> num;
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
    cout << "Input A and B: " << endl;
    int numA, numB, n, m;
    cin >> numA >> numB;
    bitset<32> btA(numA), btB(numB);
    cout << "Input positions n and m: " << endl;
    cin >> n >> m;
    cout << "A: " << btA << endl;


    for (int i = 0; i < 3; i++) {
        numB[i + m] = numA & (1 << i + n);
    }


    for (int i = 0; i < 3; i++) {
        numA &= ~(1 << i + n);
    }

}


int main() {
    task5_1();
    task5_2();
    return 0;
}