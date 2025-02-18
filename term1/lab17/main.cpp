#include <iostream>
using namespace std;


void task8_1() {
    cout << endl << "Task8_1" << endl;
    int k, num_buffer, min;
    cout << "Enter array size k: " << endl;
    cin >> k;

    int* A = (int*)malloc(k * sizeof(int));
    int* prefixSums = (int*)malloc(k * sizeof(int));
    int* indexedPrefixSums = (int*)malloc(k * sizeof(int));


    cout << "Array A: " << endl;
    srand(time(0));
    for (int i = 0; i < k; i++) {
        num_buffer = rand() % 21 - 10;
        if (num_buffer < 0)
            num_buffer = pow(num_buffer, 2);
        A[i] = num_buffer;
        cout << A[i] << " ";

        if (i == 0)
            prefixSums[i] = num_buffer;

        else
            prefixSums[i] = prefixSums[i - 1] + num_buffer;

    }
    cout << endl;

    cout << "IndexedPrefix sums: " << endl;
    for (int i = 0; i < k; i++) {
        if (i == 0)
            indexedPrefixSums[i] = INT_MAX;
        else
            indexedPrefixSums[i] = abs(prefixSums[k - 1] - 2 * prefixSums[i - 1] - A[i]);

        cout << indexedPrefixSums[i] << " ";
    }
    cout << endl;

    min = 0;
    for (int i = 0; i < k; i++)
        if (indexedPrefixSums[min] > indexedPrefixSums[i])
            min = i;

    if (min != 0)
        cout << "Minimal difference sum: " << indexedPrefixSums[min] << " before and after i:  " << min + 1 << endl << endl;
    else
        cout << "Minimal difference sum does not exist" << endl << endl;
}

void task8_2() {
    cout << endl << "Task8_2" << endl;
    int N, M;

    cout << "Enter the number of rows: " << endl;
    cin >> N;

    cout << "Enter the number of columns: " << endl;
    cin >> M;

    int** matrix = new int* [N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[M];
    }

    srand(time(0));
    cout << "Matrix:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = rand() % 21 - 10;
            cout << matrix[i][j] << "  ";

        }
        cout << endl;
    }


    int* bt = (int*)malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) {
        bt[i] = 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] < 0 && bt[j]) {
                for (int k = 0; k < N; k++)
                    matrix[k][j] /= 2;

                bt[j] = 0;
            }
        }
    }

    cout << "Modified matrix:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "Negative elements in columns: " << endl;
    for (int i = 0; i < M; i++) {
        if (!bt[i])
            cout << i + 1 << " ";
    }
    cout << endl << endl;
}


void task11_1() {
    cout << endl << "Task11_1" << endl;
    int k, count = 0, pos = 0;

    cout << "Enter array size k: " << endl;
    cin >> k;

    int* A = (int*)malloc(k * sizeof(int));

    srand(time(0));
    cout << "Array A: " << endl;
    for (int i = 0; i < k; i++) {
        A[i] = rand() % 11 + 1;
        cout << A[i] << " ";
        if (A[i] % 2 == 0)
            count++;
    }
    cout << endl;

    int* ModifedA = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < k; i++) {
        if (A[i] % 2 == 0)
            ModifedA[pos++] = A[i];
    }

    cout << "Modified array A: " << endl;
    for (int i = 0; i < count; i++) {
        cout << ModifedA[i] << " ";
    }
    cout << endl << endl;

}


void task11_2() {
    cout << endl << "Task11_2" << endl;
    int d, sum;

    cout << "Enter array size d * d: " << endl;
    cin >> d;

    int** matrix = new int* [d];
    for (int i = 0; i < d; i++) {
        matrix[i] = new int[d];
    }

    srand(time(0));
    cout << "Matrix:" << endl;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            matrix[i][j] = rand() % 21 - 10;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    bool flag = true;
    for (int i = 0; i < d; i++) {
        sum = 0;
        for (int j = 0; j < d; j++) {
            if (matrix[i][j] < 0) {
                sum = 0;
                break;

            }
            sum += matrix[i][j];
        }

        if (sum != 0) {
            cout << "Sum of elements in row " << i + 1 << ": " << sum << endl << endl;
            flag = false;
        }
    }
    if (flag)
        cout << "There are no rows with only positive elements" << endl << endl;

}


void task12_1() {
    cout << endl << "Task12_1" << endl;
    int k, count = 0;

    cout << "Enter array size k: " << endl;
    cin >> k;

    int* A = (int*)malloc(k * sizeof(int));

    srand(time(0));
    cout << "Array A: " << endl;
    for (int i = 0; i < k; i++) {
        A[i] = rand() % 21 - 10;

        if ((i + 1) % 2 == 0 && A[i] < 0)
            count++;

        cout << A[i] << " ";
    }
    cout << endl;
    cout << "Amount of elements in even positions with negative values: " << count << endl << endl;

}


void task12_2() {
    cout << endl << "Task12_2" << endl;
    int N, M;

    cout << "Enter the number of rows: " << endl;
    cin >> N;

    cout << "Enter the number of columns: " << endl;
    cin >> M;

    int** matrix = new int* [N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[M];
    }

    srand(time(0));
    cout << "Matrix:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = rand() % 21 - 10;
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }

    cout << "Rows with negative element: ";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] < 0 && i < M) {
                cout << i + 1 << " ";
                for (int k = 0; k < N; k++) {
                    matrix[k][i] /= 2;
                }
                break;
            }
        }
    }

    cout << endl << endl;
    cout << "Modified matrix:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl << endl;
}


void task13_1() {
    cout << endl << "Task13_1" << endl;
    int k = 20, count = 0;

    int* A = (int*)malloc(k * sizeof(int));

    srand(time(0));
    cout << "Array A: " << endl;
    for (int i = 0; i < k; i++) {
        A[i] = rand() % 21 - 10;
        cout << A[i] << " ";
        if (A[i] > 0 && (i + 1) % 2 == 0)
            count++;
    }
    cout << endl;

    int* B = (int*)malloc(count * sizeof(int));

    int pos = 0, sum = 0;
    for (int i = 0; i < k; i++)
        if (A[i] > 0 && (i + 1) % 2 == 0) {
            B[pos++] = A[i];
            sum += A[i];
        }

    cout << "Array B: " << endl;
    for (int i = 0; i < count; i++) {
        cout << B[i] << " ";
    }
    cout << endl;
    cout << "Sum^2 of elements in array B: " << pow(sum, 2) << endl << endl;

}

void task13_2() {
    cout << endl << "Task13_2" << endl;
    int N, min = INT_MAX;
    cout << "Enter the number of rows and coluns: " << endl;
    cin >> N;

    int** matrix = new int* [N];

    srand(time(0));
    cout << "Matrix:" << endl;

    for (int i = 0; i < N; i++) {
        matrix[i] = new int[N];
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 21 - 10;
            cout << matrix[i][j] << "  ";

            if (i == j && matrix[i][j] < min)
                min = matrix[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j && matrix[i][j] == min) {
                min = matrix[i][j];
                cout << "Minimal element in main diagonal: " << min << " with coords " << i + 1 << " " << j + 1 << endl << endl;
            }
        }
    }
    cout << endl;
}


int main() {
    int choice;
    cout << "Enter the number of task: " << endl;
    cout << "   info -------- 0" << endl;
    cout << "   task8_1 ----- 1" << endl;
    cout << "   task8_2 ----- 2" << endl;
    cout << "   task11_1 ---- 3" << endl;
    cout << "   task11_2 ---- 4" << endl;
    cout << "   task12_1 ---- 5" << endl;
    cout << "   task12_2 ---- 6" << endl;
    cout << "   task13_1 ---- 7" << endl;
    cout << "   task13_2 ---- 8" << endl;
    cout << "   close ------- 9" << endl << endl;
    while (true) {
        cin >> choice;
        switch (choice) {
        case 0:
            cout << "   info -------- 0" << endl;
            cout << "   task8_1 ----- 1" << endl;
            cout << "   task8_2 ----- 2" << endl;
            cout << "   task11_1 ---- 3" << endl;
            cout << "   task11_2 ---- 4" << endl;
            cout << "   task12_1 ---- 5" << endl;
            cout << "   task12_2 ---- 6" << endl;
            cout << "   task13_1 ---- 7" << endl;
            cout << "   task13_2 ---- 8" << endl;
            cout << "   close ------- 9" << endl << endl;
            break;
        case 1:
            task8_1();
            break;
        case 2:
            task8_2();
            break;
        case 3:
            task11_1();
            break;
        case 4:
            task11_2();
            break;
        case 5:
            task12_1();
            break;
        case 6:
            task12_2();
            break;
        case 7:
            task13_1();
            break;
        case 8:
            task13_2();
            break;
        case 9:
            cout << "Goodbye" << endl;
            return 0;

        default:
            cout << "Invalid choice" << endl;
        }
    }
}