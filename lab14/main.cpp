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
            A[i][j] = rand() % 12 - 2;
            B[i][j] = rand() % 12 - 2;
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
    cout << endl;
    cout << "a ij  < b ij: " << pairLW << ", " << "a ij  = b ij: " << pairEQ << ", " << "a ij  > b ij: " << pairGR << endl;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (A[i][j] < 0) {
                for (int k = 0; k < n; k++)
                    A[k][j] /= 2;
                break;
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


void task6_1() {
    cout << "task6_1" << endl;

    int n;
    cout << "Input Size n: " << endl;
    cin >> n;

    n = 2 * n;
    vector<vector<int>> matrix(n, vector<int>(n));
    vector<int> vecBuffer;

    srand(time(0));
    cout << "Start matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 11 + 1;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n - 1; i += 2)
        for (int j = 0; j < n - 1; j += 2) {
            swap(matrix[i][j], matrix[i + 1][j + 1]);
            swap(matrix[i + 1][j], matrix[i][j + 1]);
        }

    cout << "Result matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


void task6_2() {
    cout << "task6_2" << endl;
    vector<vector<int>> matrix;
    vector<int> vecBuffer;
    int n, intBuffer;
    cout << "Input Size n: " << endl;
    cin >> n;

    for (int i = 1; i <= n; i++)
        vecBuffer.push_back(i);

    matrix.push_back(vecBuffer);

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    n--;
    while (n) {
        intBuffer = vecBuffer[0];

        for (int i = 0; i < vecBuffer.size() - 1; i++)
            vecBuffer[i] = vecBuffer[i + 1];

        vecBuffer.pop_back();
        vecBuffer.push_back(intBuffer);
        matrix.push_back(vecBuffer);
        n--;
    }

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


void task6_3() {
    cout << "task6_3" << endl;
    priority_queue<int> qu;

    int n, buffer;
    cout << "Input Size n: " << endl;
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));


    srand(time(0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            buffer = rand() % 200 - 100;
            matrix[i][j] = buffer;
            qu.push(buffer);
        }

    cout << "Start matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }


    for (int i = 0; i < n; i++) {
        buffer = qu.top();
        qu.pop();
        matrix[i][i] = buffer;
    }

    cout << "Result matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

}


int main() {
    // task4();
    task6_1();
    // task6_2();
    // task6_3();
    return 0;
}