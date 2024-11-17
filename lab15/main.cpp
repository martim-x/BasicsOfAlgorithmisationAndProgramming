#include <bits/stdc++.h>
using namespace std;


void task8_1() {
    cout << "Task 8_1" << endl;
    int k;

    cout << "Enter array size k: ";
    cin >> k;

    int* A = (int*)malloc(k * sizeof(int));

    srand(time(0));

    for (int i = 0; i < k; i++) {
        A[i] = rand() % 101 - 50;
    }

    cout << "Array elements: ";
    for (int i = 0; i < k; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    int sum = 0;
    bool flag = true;
    int positiveCount = 0;
    for (int i = k - 1; i >= 0; i--) {
        if (A[i] > 0) {
            positiveCount++;
        }

        if (flag)
            sum += A[i];

        if (A[i] == 0)
            flag = false;

    }
    cout << "Number of positive elements: " << positiveCount << endl;
    cout << "Sum of elements after last zero: " << sum << endl;

}

void task8_2() {
    cout << "Task 8_2" << endl;
    int rows, cols;

    cout << "Enter amount of rows: ";
    cin >> rows;
    cout << "Enter amount of columns: ";
    cin >> cols;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 10;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    int columnWithZero = -1;

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 0) {
                columnWithZero = j;
                break;
            }
        }
        if (columnWithZero != -1)
            break;
    }

    if (columnWithZero != -1) {
        cout << "First column containing zero: " << columnWithZero + 1 << endl;
    }
    else {
        cout << "No columns contain zero" << endl;
    }

}


void task10_1() {
    cout << "Task 10_1" << endl;
    int k, min, max;
    long long sum, times;

    min = 0;
    max = 0;

    cout << "Enter array size k: ";
    cin >> k;

    int* A = (int*)malloc(k * sizeof(int));

    srand(time(0));

    for (int i = 0; i < k; i++) {
        A[i] = rand() % 21 - 10;
    }

    cout << "Array elements: " << endl;
    for (int i = 0; i < k; i++) {
        cout << A[i] << " ";
        if (abs(A[i]) < abs(A[min]))
            min = i;

        if (abs(A[i]) > abs(A[max]))
            max = i;

    }
    cout << endl;

    cout << "Maximum element: " << A[max] << endl;
    cout << "Minimum element: " << A[min] << endl;


    if (max < min) {
        swap(max, min);
    }

    sum = 0;
    times = 0;

    for (int i = min + 1; i < max; i++) {
        cout << "Current element: " << A[i] << endl;
        if (A[i] > 0)
            sum += A[i];

        if (!times) {
            times = A[i];
            continue;
        }

        times *= A[i];
    }

    cout << "Sum of elements between min and max: " << sum << endl;
    cout << "Times of elements between min and max: " << times << endl;

}

void task10_2() {
    cout << "Task 10_2" << endl;
    int rows, cols, index;

    cout << "Enter amount of rows: ";
    cin >> rows;
    cout << "Enter amount of columns: ";
    cin >> cols;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 21 - 10;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    bool flag = false;

    index = -1;

    for (int i = 0; i < rows; i++) {
        if (flag) {
            index = i - 1;
            break;
        }


        flag = true;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] > 0) {
                flag = false;
                break;
            }
        }
    }

    if (index == -1) {
        cout << "No rows with all negative elements" << endl;
    }
    else {
        cout << "Matrix with all elements: " << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] += matrix[index][0];
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

}


void task11_1() {
    cout << "Task 11_1" << endl;
    int n;
    cout << "Enter array size n: ";
    cin >> n;
    int* A = (int*)malloc(n * sizeof(int));

    srand(time(0));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 21 - 10;
        cout << A[i] << " ";
    }
    cout << endl;

    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (A[i] == 0) {
            cout << "Min k = " << i << " when A[k] = 0: " << endl;
            flag = false;
            break;
        }
    }

    if (flag)
        cout << "No elements equal to 0" << endl;

}


void task11_2() {
    cout << "Task 11_2" << endl;
    int rows = 4, cols = 4;

    cout << "(Default: 4 [input=0]) Enter amount of rows: ";
    cin >> rows;
    if (rows == 0) rows = 4;

    cout << "(Default: 4 [input=0]) Enter amount of columns: ";
    cin >> cols;
    if (cols == 0) cols = 4;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    srand(time(0));
    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 2 + 1;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    bool globalFlag = false;

    for (int i = 0; i < rows; i++) {
        bool rowEqualsCol = true;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                rowEqualsCol = false;
                break;
            }
        }
        if (rowEqualsCol) {
            globalFlag = true;
            cout << "Row[" << i + 1 << "] equals to column[" << i + 1 << "]: ";
            for (int k = 0; k < cols; k++) {
                cout << matrix[i][k] << " ";
            }
            cout << endl;
        }
    }

    if (!globalFlag) {
        cout << "No rows equal to columns" << endl;
    }

    cout << "Do you want to recall this func? (y/n): ";
    char c;
    cin >> c;
    if (c == 'y') {
        task11_2();
    }
}


void task14_1() {
    cout << "Task 14_1" << endl;
    int n, times = -1, NUM, max, counter = 0;
    cout << "Enter array size n: ";
    cin >> n;
    int* A = (int*)malloc(n * sizeof(int));

    cout << "Enter number: ";
    cin >> NUM;

    max = 0;

    srand(time(0));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 21 - 10;
        cout << A[i] << " ";

        if (A[i] > NUM)
            counter++;

        if (abs(A[i]) > abs(A[max]))
            max = i;
    }
    cout << endl;
    cout << "Number of elements greater than " << NUM << ": " << counter << endl;

    cout << "Max module element: " << A[max++] << endl;

    for (int i = max; i < n; i++) {
        if (times == -1){
            times = A[i];
            continue;
        }

        times *= A[i];
    }

    if (times != -1)
        cout << "Times of elements after max: " << times << endl;
    else
        cout << "Max module element is last element:(" << endl;
}


void task14_2() {
    cout << "Task 14_2" << endl;
    int rows, cols, number, index = -1;
    cout << "Enter amount of rows: ";
    cin >> rows;

    cout << "Enter amount of columns: ";
    cin >> cols;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    srand(time(0));
    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 21 - 10;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++) {
        if (index != -1)
            break;

        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                index = i;
                cout << "Row which contains 0: " << i + 1 << endl;
                break;
            }
        }
    }

    cout << endl;

    if (index != -1) {
        number = matrix[index][0];
        cout << "Matrix with decreased elements: " << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] -= number;
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
}


int main() {
    // task8_1();
    // task8_2();

    // task10_1();
    // task10_2();

    // task11_1();
    // task11_2();

    task14_1();
    task14_2();

    return 0;
}