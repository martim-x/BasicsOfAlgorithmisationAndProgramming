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


void task5_12_2() {
    int n, numA, p, m, numB, q;
    cout << "Input A: " << endl;
    cin >> numA;
    bitset<32> btA(numA);
    cout << "btA: " << btA << endl;

    cout << "Input n bits and position p: " << endl;
    cin >> n >> p;

    cout << "Input B: " << endl;
    cin >> numB;
    bitset<32> btB(numB);
    cout << "btB: " << btB << endl;

    cout << "Input m(extra) bits and position q: " << endl;
    cin >> m >> q;

    for (int i = 0; i < n; i++) {
        btB[i + q - 1] = numA & (1 << i + p - 1);
    }

    for (int i = 0; i < n; i++) {
        numA &= ~(1 << i + p - 1);
    }

    bitset<32> btsA(numA);

    cout << "btA: " << btsA << endl;
    cout << "btB: " << btB << endl;


}


void task5_13() {
    int n, numA, numB, p;
    cout << "Input A: " << endl;
    cin >> numA;
    bitset<32> btA(numA);
    cout << "btA: " << btA << endl;

    cout << "Input B: " << endl;
    cin >> numB;
    bitset<32> btB(numB);
    cout << "btB: " << btB << endl;

    for (int i = 0; i < 2;i++)
        btB[5 + i] = numA & (1 << 5 + i);

    btA[5] = 0;
    btA[6] = 0;

    cout << "Input n bits and position p: " << endl;
    cin >> n >> p;
    for (int i = 0; i < n; i++)
        numA = (numA ^ (1 << i + p));

    bitset<32> btsA(numA);

    cout << "btA: " << btsA << endl;
    cout << "btB: " << btB << endl;

}


void task5_14() {
    cout << "Input A and B: " << endl;
    int numA, numB, n, m, count = 0;
    cin >> numA >> numB;
    bitset<32> btA(numA), btB(numB);
    cout << "btA: " << btA << endl;
    cout << "btB: " << btB << endl;
    cout << "Input positions n and m: " << endl;
    cin >> n >> m;

    cout << "btA: " << btA << endl;
    cout << "btB: " << btB << endl;

    for (int i = 0; i < 3; i++) {
        btB[i + m - 1] = numA & (1 << i + n - 1);
    }

    for (int i = 0; i < 3; i++) {
        numA &= ~(1 << i + n);
    }

    cout << "btA: " << btA << endl;
    cout << "btB: " << btB << endl;

    for (int i = 4; i < 10; i++) {
        if (numA & (1 << i)) {
            count++;
        }
    }
}


int main() {
    task5_8_1();
    task5_8_2();
    task5_12_1();
    task5_12_2();
    task5_13();
    task5_14();
    return 0;
}