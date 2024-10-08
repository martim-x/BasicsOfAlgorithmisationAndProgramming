#include <bits/stdc++.h>
using namespace std;


void task5_8_1() {
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


void task5_8_2() {
    cout << "Input A and B: " << endl;
    int numA, numB, n, m;
    cin >> numA >> numB;
    bitset<32> btA(numA), btB(numB);
    cout << "btA: " << btA << "\nbtB: " << btB << endl;
    cout << "Input positions n and m: " << endl;
    cin >> n >> m;
    cout << "btA: " << btA << endl;

    for (int i = 0; i < 3; i++) {
        btB[i + m - 1] = numA & (1 << i + n - 1);
    }
    cout << "btB: " << btB << endl;

    for (int i = 0; i < 3; i++) {
        numA &= ~(1 << i + n);
    }
    cout << "numA" << numA << endl;


}


void task5_12_1() {
    int numA, n;
    cout << "Input A: " << endl;
    cin >> numA;
    bitset<32> bt(numA);
    cout << bt << endl;

    for (int i = 0; i < 32; i++)
        numA = (numA ^ (1 << i));

    bitset<32> bts(numA);
    cout << "num: " << numA << ", " << bts << endl;

}


int main() {
    // task5_8_1();
    task5_8_2();
    // task5_12_1();

    return 0;
}