#include <bits/stdc++.h>
using namespace std;


void task5_1() {
    cout << "task5_1" << endl;
    int k, n, buffer;
    cout << "Input k and n elements: " << endl;
    cin >> k >> n;
    vector<int> X, Y;
    set<int> Z;
    srand(time(0));

    cout << "\nMassive X" << endl;
    for (int i = 0; i < k; i++) {
        buffer = rand() % 201 - 100;
        X.push_back(buffer);
        cout << buffer << endl;
    }

    cout << "\nMassive Y" << endl;
    for (int i = 0; i < n; i++) {
        buffer = rand() % 201 - 100;
        Y.push_back(buffer);
        cout << buffer << endl;
    }

    cout << "\nMassive Z" << endl;
    for (auto elX : X)
        for (auto elY : Y)
            if (elX == elY) {
                Z.insert(elX);
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
        buffer = rand() % 201 - 100;
        x.push_back(buffer);
        cout << buffer << endl;
    }

    cout << "\nMassive y" << endl;
    for (int i = 0; i < n; i++) {
        buffer = rand() % 201 - 100;
        y.push_back(buffer);
        cout << buffer << endl;
    }

    for (auto i : x)
        for (auto j : y)
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
        if (it == summary.begin())
            cout << *(++it) << endl;

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
    cin >> n;
    srand(time(0));
    for (int i = 0; i < n; i++) {
        vecA.push_back(rand() % 101);
        vecB.push_back(rand() % 101);
    }

    for (int i = 0; i < n; i++) {
        numA = vecA[i];
        numB = vecB[i];
        if (numA == numB)
            counter_eq++;
        if (numA > numB)
            counter_gr++;
        if (numA < numB)
            counter_lw++;
    }

    cout << "counter_eq: " << counter_eq << endl;
    cout << "counter_gr: " << counter_gr << endl;
    cout << "counter_lw: " << counter_lw << endl;

    int k;
    cout << "Input k: " << endl;
    cin >> k;

    vector<int> A, GR, LW, EQ;

    for (int i = 0; i < 100; i++)
        A.push_back(rand() % 201 - 100);

    for (int i = 0; i < 100; i++) {
        if (A[i] < k)
            LW.push_back(i);

        if (A[i] == k)
            EQ.push_back(i);

        if (A[i] > k)
            GR.push_back(i);
    }
    cout << "Index which is lower than k: " << k << endl;
    for (auto i : LW)
        cout << i << endl;

    cout << "Index which is equal k: " << k << endl;
    for (auto i : EQ)
        cout << i << endl;

    cout << "Index which is greater than k: " << k << endl;
    for (auto i : GR)
        cout << i << endl;
}


void task14_1AND14_2() {
    cout << "task14_1AND14_2" << endl;
    int i, j, index = 0, counterPairs = 0;
    vector<int> vecA, vecB;
    srand(time(0));
    cout << "Input i and j: " << endl;
    cin >> i >> j;

    for (; index < i; index++)
        vecA.push_back(rand() % 100);

    index = 0;

    for (; index < j; index++)
        vecB.push_back(rand() % 100);

    for (auto elA : vecA)
        for (auto elB : vecB) {
            cout << "elA: " << elA << ", elB: " << elB << endl;
            if (elA == elB)
                counterPairs++;
        }
    cout << "Equal pairs: " << endl;
    sort(vecA.begin(), vecA.end());
    for (auto el : vecA)
        cout << el << " ";
    cout << endl;
}


void task15_1AND15_2() {
    cout << "task15_1AND15_2" << endl;
    vector<int> A;
    int n, num;
    cout << "Input size n: " << endl;
    cin >> n;
    srand(time(0));
    for (int i = 0; i < n; i++) {
        num = rand() % 201 - 100;
        if (!num) {
            num++;
        }
        A.push_back(num);
    }
    sort(A.begin(), A.end());
    cout << "Elements in A" << endl;
    for (int i : A)
        cout << i << endl;
    cout << endl;


    vector<int> F, D;
    for (int i = 0; i < 100; i++) {
        num = rand() % 201 - 100;
        if (!num) {
            num++;
        }
        F.push_back(num);

        num = rand() % 201 - 100;
        if (!num) {
            num++;
        }
        D.push_back(num);
    }

    int maxElF = *max_element(F.begin(), F.end());
    int maxElD = *max_element(D.begin(), D.end());
    if (maxElD == maxElF)
        cout << "Element in F: " << maxElF << " exists in D" << endl;
    else
        cout << "Element in F: " << maxElF << " doesn't exists in D" << endl;

}


int main() {
    task5_1();
    task5_2();
    task12_1AND12_2();
    task14_1AND14_2();
    task15_1AND15_2();
    return 0;
}