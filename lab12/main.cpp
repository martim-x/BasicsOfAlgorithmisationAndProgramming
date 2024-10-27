#include <bits/stdc++.h>
using namespace std;


void task5_1() {
    cout << "task5_1" << endl;
    int k, n, buffer;
    cout << "Input k and n elements: " << endl;
    cin >> k >> n;
    vector<int> X, Y, Z;
    srand(time(0));

    cout << "\nMassive X" << endl;
    for (int i = 0; i < k; i++) {
        buffer = rand() % 21 - 10;
        X.push_back(buffer);
        cout << buffer << endl;
    }

    cout << "\nMassive Y" << endl;
    for (int i = 0; i < n; i++) {
        buffer = rand() % 21 - 10;
        Y.push_back(buffer);
        cout << buffer << endl;
    }

    cout << "\nMassive Z" << endl;
    for (auto elX : X)
        for (auto elY : Y)
            if (elX == elY) {
                Z.push_back(elX);
                cout << elX << endl;
            }
}


void task5_2() {
    cout << "task5_2" << endl;
    int k, n, buffer, q;
    cout << "Input k and n elements: " << endl;
    cin >> k >> n;
    cout << "Input q: " << endl;
    cin >> q;
    vector<int> x, y;
    set<int> summary;
    srand(time(0));

    cout << "\nMassive x" << endl;
    for (int i = 0; i < k; i++) {
        buffer = rand() % 21 - 10;
        x.push_back(buffer);
        cout << buffer << endl;
    }

    cout << "\nMassive y" << endl;
    for (int i = 0; i < n; i++) {
        buffer = rand() % 21 - 10;
        y.push_back(buffer);
        cout << buffer << endl;
    }

    for (auto i : x)
        for (auto j : y)
            if (i + j != q)
                summary.insert(i + j);

    cout << "\nSet" << endl;
    for (auto el : summary)
        cout << el << endl;


    auto it = summary.lower_bound(q);
    auto lastIt = summary.end();

    cout << "\nClosets sum" << endl;
    if (it == summary.end())
        cout << *(--it) << endl;
    else
        if (abs(q - *it) < abs(q - *(--it))) {
            cout << *(++it) << endl;
        }
        else {
            cout << *it << endl;
        }
}


void task12_1AND12_2() {
    cout << "task12_1AND12_2" << endl;
    int n, numA, numB, counter_eq = 0, counter_gr = 0, counter_lw = 0;
    vector<int> vecA, vecB;
    cout << "Input n: " << endl;
    srand(time(0));
    for (int i = 0;i < n;i++) {
        vecA.push_back(rand() % 100);
        vecB.push_back(rand() % 100);
    }

    for (int i = 0;i < n;i++) {
        numA = vecA[i];
        numB = vecB[i];
        if (numA = numB)
            counter_eq++;
        if (numA > numB)
            counter_gr++;
        if (numA = numB)
            counter_lw++;
    }

    cout << "counter_eq: " << counter_eq << endl;
    cout << "counter_gr: " << counter_gr << endl;
    cout << "counter_lw: " << counter_lw << endl;

    int k;
    cout << "Input k: " << endl;
    vector<int> A;
    for (int i = 0;i < 100;i++) {
        numA = rand() % 100;
    }

    for (int i = 0; i < 100; i++)
        if (A[i] < k)
            cout << "A[" << i << "] " << A[i] << " < " << k << endl;
}


void task14_1AND14_2() {
    cout << "task14_1AND14_2" << endl;
    int i, j, index = 0, counterPairs = 0;
    vector<int> vecA, vecB;
    srand(time(0));
    i = rand() % 100;
    j = rand() % 100;

    for (; index < i; index++)
        vecA.push_back(rand() % 100);

    index = 0;

    for (; index < j; index++)
        vecB.push_back(rand() % 100);

    for (auto elA : vecA)
        for (auto elB : vecB)
            if (elA == elB)
                counterPairs++;

    sort(vecA.begin(), vecA.end());
    for (auto el : vecA)
        cout << el << " ";
    cout << endl;
}


void task15_1AND15_2() {
    cout << "task14_1AND14_2" << endl;
    int a, c;
    c = 5;
    a = c;
    cout << "c: " << c << endl;
    cout << "a: " << a << endl;
    c--;
    cout << "c: " << c << endl;
    cout << "a: " << a << endl;

    int &b = c;
    cout << "c: " << c << endl;
    cout << "a: " << a << endl;
    c--;
    cout << "c: " << c << endl;
    cout << "a: " << a << endl;



}


int main() {
    // task5_1();
    // task5_2();
    // task12_1AND12_2();
    // task14_1AND14_2();
    task15_1AND15_2();
    return 0;
}