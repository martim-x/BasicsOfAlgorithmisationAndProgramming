#include <bits/stdc++.h>
using namespace std;


void task4() {
    cout << "task4" << endl;
    int n, m, pairGR = 0, pairEQ = 0, pairLW = 0;
    vector<int> vecBuffer;
    cout << "Input n and m: " << endl;
    cin >> n >> m;
    vector<vector<int>> A(n, vector<int>(m));
    vector<vector<int>> B(n, vector<int>(m));
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = rand() % 200 - 5;
            B[i][j] = rand() % 200 - 5;
        }
    }

    cout << endl;
    cout << "Matrix A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Matrix B:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] < B[i][j])
                pairLW++;
            if (A[i][j] = B[i][j])
                pairEQ++;
            if (A[i][j] > B[i][j])
                pairGR++;
        }
    }
    cout<<endl;
    cout << "a ij  < b ij: " << pairLW << ", " << "a ij  = b ij: " << pairEQ << ", " << "a ij  > b ij: " << pairGR << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] < 0)
                for (int k_i = 0; k_i < n; k_i++) {
                    A[k_i][j] = A[k_i][j] / 2;
                }
        }
    }

    cout << endl;
    cout << "Matrix A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }


}

int main() {
    task4();
    return 0;
}