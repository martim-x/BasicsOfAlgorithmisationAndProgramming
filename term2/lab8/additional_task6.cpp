#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
using namespace std;


int inputValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value && ss.eof() && value >= min && value <= max) {
            return value;
        }
        cout << "Invalid input! Please try again." << endl;
    }
}


void generateNumbers(int A, int current, vector<int>& digits, ofstream& out) {
    if (current == A) {
        if (digits[0] == 0) return;
        for (int d : digits)
            out << d;
        out << "\n";
        return;
    }

    for (int d = (current == 0 ? 1 : 0); d <= A; d++) {
        digits[current] = d;
        generateNumbers(A, current + 1, digits, out);
    }
}

void task1() {
    int A = inputValidatedInt("Enter digit A (1 - 9): ", 1, 9);
    ofstream outFile("task1_output.txt");
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    vector<int> digits(A, 0);
    generateNumbers(A, 0, digits, outFile);
    outFile.close();
    cout << "Results saved to file 'task1_output.txt'" << endl;
}

int countCrossingEdges(const vector<vector<int>>& adj, const vector<int>& groups) {
    int cutEdges = 0;
    int n = adj.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adj[i][j] == 1 && groups[i] != groups[j]) {
                cutEdges++;
            }
        }
    }

    return cutEdges;
}

void findOptimalPartition(vector<vector<int>>& adj, vector<int>& groups, int index, vector<int>& bestGroups, int& bestCut) {
    int n = adj.size();
    if (index == n) {  // Все страны распределены
        int cut = countCrossingEdges(adj, groups);
        bool group1Exists = false, group2Exists = false;
        for (int group : groups) {
            if (group == 0) group1Exists = true;
            if (group == 1) group2Exists = true;
        }
        if (group1Exists && group2Exists && cut < bestCut) {
            bestCut = cut;
            bestGroups = groups;
        }
        return;
    }

    groups[index] = 0;
    findOptimalPartition(adj, groups, index + 1, bestGroups, bestCut);

    groups[index] = 1;
    findOptimalPartition(adj, groups, index + 1, bestGroups, bestCut);
}

void task2() {
    int n = inputValidatedInt("Enter number of countries: ", 1, 20);
    vector<vector<int>> adj(n, vector<int>(n, 0));

    srand(time(0));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int val = rand() % 2;
            adj[i][j] = val;
            adj[j][i] = val;
        }
    }

    cout << "Randomly generated adjacency matrix:\n";
    for (const auto& row : adj) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    vector<int> groups(n, 0), bestGroups(n, 0);
    int bestCut = INT32_MAX;
    findOptimalPartition(adj, groups, 0, bestGroups, bestCut);

    bool group1Exists = false, group2Exists = false;
    for (int group : bestGroups) {
        if (group == 0) group1Exists = true;
        if (group == 1) group2Exists = true;
    }

    if (!group1Exists || !group2Exists) {
        cout << "Unable to divide countries into two groups with the given adjacency matrix." << endl;
        return;
    }

    cout << "\nMinimum number of adjacent pairs from different groups: " << bestCut << endl;
    cout << "Country assignment (Country : Group):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Country " << i + 1 << " : Group " << (bestGroups[i] + 1) << endl;
    }
}


void generatePermutations(const vector<int>& arr, vector<int>& perm, vector<bool>& used, int depth) {
    int n = arr.size();
    if (depth == n) {
        for (int i = 0; i < n; i++)
            cout << perm[i] << " ";
        cout << "\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = true;
            perm[depth] = arr[i];
            generatePermutations(arr, perm, used, depth + 1);
            used[i] = false;
        }
    }
}

void task3() {
    const int n = 5;
    vector<int> arr(n);
    cout << "Enter " << n << " distinct natural numbers:" << endl;
    for (int i = 0; i < n; i++) {
        arr[i] = inputValidatedInt("Number " + to_string(i + 1) + " (1 - 100): ", 1, 100);
    }
    vector<int> perm(n, 0);
    vector<bool> used(n, false);
    cout << "All permutations:" << endl;
    generatePermutations(arr, perm, used, 0);
}

int main() {
    while (true) {
        int choice = inputValidatedInt("Choose task\n1 - Generate numbers\n2 - Create blocks\n3 - Permutations\n4 - Exit \nYour choice: ", 1, 4);
        switch (choice) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            return 0;

        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }
    return 0;
}
