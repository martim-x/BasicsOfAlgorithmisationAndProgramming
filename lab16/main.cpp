#include <bits/stdc++.h>
using namespace std;


void task8_1() {
    cout << endl << "Task8_1" << endl;
    int N, M, numGRzero = 0, numLWzero = 0, numEQzero = 0;
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
            if (matrix[i][j] > 0)
                numGRzero++;

            if (matrix[i][j] < 0)
                numLWzero++;

            if (matrix[i][j] == 0)
                numEQzero++;

            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Number of positive elements: " << numGRzero << endl;
    cout << "Number of negative elements: " << numLWzero << endl;
    cout << "Number of elements equal to zero: " << numEQzero << endl << endl;
}


void task8_2() {
    cout << endl << "Task8_2" << endl;
    string str1 = "Some text are put here\0";

    string str2;
    cout << "(Default [input : 0]) Enter the string: ";
    // cin.ignore(1000, '\n');
    getline(cin >> ws, str2);
    if (str2[0] == '0')
        str2 = str1;

    cout << str2 << endl;
    int words = 0;
    for (auto ch : str2)
        if (ch == ' ')
            words++;

    if (str2.length() > 0)
        cout << "Number of words: " << words + 1 << endl << endl;
    else
        cout << "Number of words: 0" << endl << endl;

}


void task11_1() {
    cout << endl << "Task11_1" << endl;
    int N, M, max = INT_MIN, sum = 0;

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

            if (j < i) {
                cout << "|" << matrix[i][j] << "| ";
                sum += matrix[i][j];
            }
            else
                cout << matrix[i][j] << "  ";

            if (max < matrix[i][j])
                max = matrix[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] == max)
                cout << "Max element: " << max << " Position: (" << i + 1 << "; " << j + 1 << ")" << endl;
        }
    }
    cout << "Sum of elements above the main diagonal: " << sum << endl << endl;
}


void task11_2() {
    cout << endl << "Task11_2" << endl;
    string str1 = "Somce text arce pcut c here\0";
    string str2 = "";
    char ch = 'c';
    int i = 0;

    for (char c : str1) {
        str2 += c;
        if (c == ch) {
            str2 += '*';
        }
    }
    str2 += '\0';
    cout << "Result string: " << str2 << endl << endl;

}


void task12_1() {
    cout << endl << "Task12_1" << endl;
    int d, p, min = INT_MAX;
    cout << "Enter the number of rows ( x <= 16 ): " << endl;
    cin >> d;
    if (d > 16) {
        cout << "Error! Number of rows must be less than 16" << endl;
        cout << "Value of k would be = 16" << endl;
        d = 16;
    }

    cout << "Enter the number of columns ( x <= 18 ): " << endl;
    cin >> p;
    if (p > 18) {
        cout << "Error! Number of columns must be less than 18" << endl;
        cout << "Value of n would be = 18" << endl;
        p = 18;
    }

    int** matrix = new int* [d];
    for (int i = 0; i < d; i++) {
        matrix[i] = new int[p];
    }

    srand(time(0));
    cout << "Matrix:" << endl;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < p; j++) {
            matrix[i][j] = rand() % 21 - 10;
            cout << matrix[i][j] << " ";
            if (min > matrix[i][j])
                min = matrix[i][j];
        }
        cout << endl;
    }
    cout << "Min element: " << min << endl << endl;

    cout << "Modified matrix:" << endl;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < p; j++) {
            if (i == j)
                matrix[i][j] = min;

            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

}


void task12_2() {
    cout << endl << "Task12_2" << endl;
    int rows = 4, cols = 4;

    cout << "(Default: 4 [input=0]) Enter amount of rows: " << endl;
    cin >> rows;
    if (rows == 0) rows = 4;

    cout << "(Default: 4 [input=0]) Enter amount of columns: " << endl;
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
        task12_2();
    }
    cout << endl;
}


void task13_1() {
    cout << endl << "Task13_1" << endl;
    int k, n, min = INT_MAX, a, b, indexA, indexB;
    cout << "Enter the number of rows ( x <= 12 ): " << endl;
    cin >> k;
    if (k > 12) {
        cout << "Error! Number of rows must be less than 12" << endl;
        cout << "Value of k would be = 12" << endl;
        k = 12;
    }


    cout << "Enter the number of columns ( x <= 8 ): " << endl;
    cin >> n;
    if (n > 8) {
        cout << "Error! Number of columns must be less than 8" << endl;
        cout << "Value of n would be = 8" << endl;
        n = 8;
    }

    cout << "Enter the number a[-10;10]: ";
    cin >> a;

    cout << "Enter the number b[-10;10]: ";
    cin >> b;

    int** matrix = new int* [k];
    for (int i = 0; i < k; i++) {
        matrix[i] = new int[n];
    }

    srand(time(0));
    cout << "Matrix:" << endl << endl;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 21 - 10;
            cout << matrix[i][j] << " ";

            if (matrix[i][j] == a)
                indexA = i;

            if (matrix[i][j] == b)
                indexB = i;

        }
        cout << endl;
    }

    swap(matrix[indexA], matrix[indexB]);
    cout << "Modified matrix:" << endl;
    for (int i = 0; i < k; i++) {
        if (i == indexA || i == indexB)
            cout << "|";

        else
            cout << " ";

        for (int j = 0; j < n; j++)
            cout << matrix[i][j] << " ";

        if (i == indexA || i == indexB)
            cout << "|";
        cout << endl;

    }
    cout << endl;
}


void OverRidestrcpy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


int OverRidestrlen(char str[]) {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}


bool OverRidestrcmp(char str1[], char str2[]) {
    int i = 0;
    if (OverRidestrlen(str1) != OverRidestrlen(str2))
        return false;

    while (str1[i] != '\0') {
        if (str1[i] != str2[i])
            return false;
        i++;
    }

    return true;
}


vector<char*> OverRidestrtok(char str[], char tokens[]) {
    int i = 0, j = 0;
    vector<char*> tokenedVec;
    int pointerToken = 0;

    char strSave[OverRidestrlen(str) + 1];
    OverRidestrcpy(strSave, str);

    while (str[i] != '\0') {
        j = 0;
        while (tokens[j] != '\0') {
            if (str[i] == tokens[j]) {
                str[i] = '\0';
                if (pointerToken != i) {
                    char* bufferchar = new char[OverRidestrlen(str + pointerToken) + 1];
                    OverRidestrcpy(bufferchar, str + pointerToken);

                    tokenedVec.push_back(bufferchar);
                }
                pointerToken = i + 1;
                break;
            }
            j++;
        }
        i++;
    }

    if (pointerToken < i) {
        char* bufferchar = new char[OverRidestrlen(str + pointerToken) + 1];
        OverRidestrcpy(bufferchar, str + pointerToken);
        tokenedVec.push_back(bufferchar);
    }

    OverRidestrcpy(str, strSave);

    return tokenedVec;

}


void task13_2() {
    cout << endl << "Task13_2" << endl;
    char str[] = { "A ternary conditional operation (from Latin ternarius - triple) is an operation implemented in many"
    " programming languages, which returns its second or third operand depending on the value of the"
    " of the logical expression specified by the first operand. Analogous to the ternary conditional operation in mathematical"
    " logic and Boolean algebra is the conditional disjunction, which is written in the form p , q , r] and"
    " realizes the algorithm : if q , then p , otherwise r" };

    char term[50];
    cout << "Input the terminate for the following string : " << endl;
    cout << str << endl;
    cin >> term;

    int term_len = OverRidestrlen(term);

    char terminators[] = " -,.;:[]()\n\0";
    vector<char*> words = OverRidestrtok(str, terminators);

    for (auto word : words)
        if (OverRidestrcmp(word + OverRidestrlen(word) - term_len, term))
            cout << word << endl;
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