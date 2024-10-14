#include <bits/stdc++.h>
using namespace std;


void task5_1() {
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


int main() {
    // task5_1();
    task5_2();
    return 0;
}