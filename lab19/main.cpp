#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

void task8_1() {
    FILE* inputFile = fopen("tests/input8_1.txt", "r");

    vector<int> nums;
    int num;

    while (fscanf(inputFile, "%d", &num))
        nums.push_back(num);

    fclose(inputFile);

    FILE* outputFile = fopen("tests/output8_1.txt", "w");

    int n = nums.size();
    for (int i = 0; i < (n + 1) / 2; i++) {
        fprintf(outputFile, "%d ", nums[i]);
        if (i != n - 1 - i)
            fprintf(outputFile, "%d ", nums[n - 1 - i]);
    }

    fclose(outputFile);
}


void task8_2() {
    FILE* inputA = fopen("tests/input8_2A.txt", "r");
    FILE* inputB = fopen("tests/input8_2B.txt", "r");
    FILE* outputFile = fopen("tests/output8_2.txt", "w");

    int n;
    fscanf(inputA, "%d", &n);

    vector<vector<int>> matrixA(n, vector<int>(n));
    vector<int> matrixB(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(inputA, "%d", &matrixA[i][j]);

    for (int i = 0; i < n; i++)
        fscanf(inputB, "%d", &matrixB[i]);

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++)
            sum += matrixA[i][j] * matrixB[j];

        fprintf(outputFile, "%d ", sum);
    }

    fclose(inputA);
    fclose(inputB);
    fclose(outputFile);
}


void task11_1() {
    FILE* inputFile = fopen("tests/input11_1.txt", "r");
    FILE* outputFile = fopen("tests/output11_1.txt", "w");

    set<int> numbers;
    int num;

    while (fscanf(inputFile, "%d", &num))
        numbers.insert(num);

    for (const auto& val : numbers)
        fprintf(outputFile, "%d ", val);

    fclose(inputFile);
    fclose(outputFile);
}


void task11_2() {
    FILE* inputFile = fopen("tests/input11_2.txt", "r");
    FILE* outputFile = fopen("tests/output11_2.txt", "w");

    vector<string> terminatedStrings;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), inputFile)) {
        string line(buffer);
        if (!line.empty() && line.back() == '\n')
            line.pop_back();
        if (!line.empty() && line.back() == 'a')
            terminatedStrings.push_back(line);
    }

    for (const auto& str : terminatedStrings)
        fprintf(outputFile, "%s\n", str.c_str());

    fclose(inputFile);
    fclose(outputFile);
}


void task14_1() {
    FILE* inputFile = fopen("tests/input14_1.txt", "r");
    FILE* outputFile = fopen("tests/output14_1.txt", "w");

    int k, column;
    fscanf(inputFile, "%d", &k);
    vector<vector<int>> matrix(k, vector<int>(k));

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            fscanf(inputFile, "%d", &matrix[i][j]);

    fclose(inputFile);

    while (true) {
        cout << "Enter the column number: ";
        cin >> column;
        if (column <= 0 || column > k)
            cout << "Invalid column number. Please try again." << endl;
        else
            break;
    }

    for (int i = 0; i < k; i++)
        fprintf(outputFile, "%d\n", matrix[i][column - 1]);

    fclose(outputFile);
}


void task14_2() {
    FILE* inputFile = fopen("tests/input14_2.txt", "r");
    FILE* outputFile = fopen("tests/output14_2.txt", "w");

    set<int> numbers;
    int num;

    while (fscanf(inputFile, "%d", &num))
        numbers.insert(num);

    for (const auto& val : numbers)
        fprintf(outputFile, "%d ", val);

    fclose(inputFile);
    fclose(outputFile);
}


void task1_1() {
    FILE* inputA = fopen("tests/input1_1A.txt", "r");
    FILE* inputB = fopen("tests/input1_1B.txt", "r");
    FILE* outputFile = fopen("tests/output1_1.txt", "w");

    int rowsA, columnsA, rowsB, columnsB;

    fscanf(inputA, "%d%d", &rowsA, &columnsA);
    vector<vector<int>> matrixA(rowsA, vector<int>(columnsA));

    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < columnsA; j++)
            fscanf(inputA, "%d", &matrixA[i][j]);

    fscanf(inputB, "%d%d", &rowsB, &columnsB);
    vector<vector<int>> matrixB(rowsB, vector<int>(columnsB));

    for (int i = 0; i < rowsB; i++)
        for (int j = 0; j < columnsB; j++)
            fscanf(inputB, "%d", &matrixB[i][j]);

    fclose(inputA);
    fclose(inputB);

    if (columnsA != rowsB) {
        fprintf(outputFile, "Error: Number of columns in the first matrix must be equal to the number of rows in the second matrix.\n");
        fclose(outputFile);
        return;
    }

    vector<vector<int>> matrixC(rowsA, vector<int>(columnsB));
    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < columnsB; j++)
            for (int k = 0; k < columnsA; k++)
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];

    for (const auto& row : matrixC) {
        for (const auto& val : row)
            fprintf(outputFile, "%d ", val);
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);
}


void task1_2() {
    FILE* inputFile = fopen("tests/input1_2.txt", "r");
    FILE* outputFile = fopen("tests/output1_2.txt", "w");

    vector<int> numbers;
    int num;

    while (fscanf(inputFile, "%d", &num) == 1)
        numbers.push_back(num);

    fclose(inputFile);

    cout << "Input number k: ";
    int k;
    cin >> k;

    for (const auto& val : numbers)
        if (val % k == 0)
            fprintf(outputFile, "%d ", val);

    fclose(outputFile);
}


int main() {
    task8_1();
    task8_2();
    task11_1();
    task11_2();
    task14_1();
    task14_2();
    task1_1();
    task1_2();
    return 0;
}