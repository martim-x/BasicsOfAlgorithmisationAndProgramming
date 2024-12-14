#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;


void task8_1() {
    ifstream inputFile("tests/input8_1.txt");

    vector<int> nums;
    int num;

    while (inputFile >> num)
        nums.push_back(num);

    inputFile.close();

    ofstream outputFile("tests/input8_1.txt");

    int n = nums.size();
    for (int i = 0; i < (n + 1) / 2; i++) {
        outputFile << nums[i] << " ";
        if (i != n - 1 - i)
            outputFile << nums[n - 1 - i] << " ";

    }
    outputFile.close();
}


void task8_2() {
    ifstream inputFileA("tests/input8_2A.txt");
    ifstream inputFileB("tests/input8_2B.txt");
    ofstream outputFile("tests/output8_2.txt");

    int n, buffer_num;
    inputFileA >> n;
    vector<vector<int>> matrixA(n, vector<int>(n));
    vector<int> matrixB(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inputFileA >> matrixA[i][j];

    inputFileA.close();

    for (int i = 0; i < n; i++)
        inputFileB >> matrixB[i];

    inputFileB.close();

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++)
            sum += matrixA[i][j] * matrixB[j];

        outputFile << sum << " ";
    }
    outputFile.close();
}


void task11_1() {
    ifstream inputFile("tests/input11_1.txt");
    ofstream outputFile("tests/output11_1.txt");

    set<int> numbers;
    int num;

    while (inputFile >> num)
        numbers.insert(num);

    inputFile.close();

    while (!numbers.empty()) {
        outputFile << *numbers.begin() << " ";
        numbers.erase(numbers.begin());
    }
    outputFile.close();
}


void task11_2() {
    ifstream inputFile("tests/input11_2.txt");
    ofstream outputFile("tests/output11_2.txt");
    vector<string> terminatedStrings;
    string line;

    while (getline(inputFile, line))
        if (!line.empty() && line.back() == 'a')
            terminatedStrings.push_back(line);

    inputFile.close();

    for (auto str : terminatedStrings)
        outputFile << str << endl;

    outputFile.close();
}


void task14_1() {
    ifstream inputFile("tests/input14_1.txt");
    ofstream outputFile("tests/output14_1.txt");

    int k, column;
    inputFile >> k;

    vector<vector<int>> matrix(k, vector<int>(k));

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            inputFile >> matrix[i][j];

    inputFile.close();

    while (true) {
        cout << "Enter the column number: ";
        cin >> column;
        if (column <= 0 || column > k)
            cout << "Invalid column number. Please try again." << endl;
        else
            break;
    }

    for (int i = 0; i < k; i++)
        outputFile << matrix[i][column - 1] << endl;

    outputFile.close();
}


void task14_2() {
    ifstream inputFile("tests/input14_2.txt");
    ofstream outputFile("tests/output14_2.txt");

    set<int> numbers;
    int num;

    while (inputFile >> num)
        numbers.insert(num);

    inputFile.close();

    while (!numbers.empty()) {
        outputFile << *numbers.begin() << " ";
        numbers.erase(numbers.begin());
    }
    outputFile.close();
}


void task1_1() {
    ifstream inputFileA("tests/input1_1A.txt");
    ifstream inputFileB("tests/input1_1B.txt");
    ofstream outputFile("tests/output1_1.txt");

    int rowsA, columnsA, rowsB, columnsB;

    inputFileA >> rowsA >> columnsA;
    vector<vector<int>> matrixA(rowsA, vector<int>(columnsA));

    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < columnsA; j++)
            inputFileA >> matrixA[i][j];

    inputFileB >> rowsB >> columnsB;
    vector<vector<int>> matrixB(rowsB, vector<int>(columnsB));

    for (int i = 0; i < rowsB; i++)
        for (int j = 0; j < columnsB; j++)
            inputFileB >> matrixB[i][j];

    inputFileA.close();
    inputFileB.close();

    if (columnsA != rowsB) {
        outputFile << "Error: Number of columns in the first matrix must be equal to the number of rows in the second matrix." << endl;
        outputFile.close();
        return;
    }

    vector<vector<int>> matrixC(rowsA, vector<int>(columnsB));
    int buffer = 0;

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < columnsB; j++) {
            for (int k = 0; k < columnsA; k++) {
                buffer += matrixA[i][k] * matrixB[k][j];
            }
            matrixC[i][j] = buffer;
            buffer = 0;
        }
    }

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < columnsB; j++)
            outputFile << matrixC[i][j] << " ";
        outputFile << endl;
    }
}


void task1_2() {
    ifstream inputFile("tests/input1_2.txt");
    ofstream outputFile("tests/output1_2.txt");

    int k;
    vector<int> numbers;

    while (inputFile >> k)
        numbers.push_back(k);

    inputFile.close();
    cout << "Input number k: ";
    cin >> k;

    for (auto num : numbers)
        if (num % k == 0)
            outputFile << num << " ";

    outputFile.close();
}


int main() {
    ios::sync_with_stdio(false);
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