#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

map<pair<int, int>, int> memo;

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

int F(int m, int n) {
    pair<int, int> key = make_pair(m, n);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    if (m == 0 || n == 0) {
        memo[key] = n + 1;
        return n + 1;
    }

    int result = F(m - 1, F(m, n - 1));
    memo[key] = result;
    return result;
}

int main() {
    int m = inputValidatedInt("Input m (0 - 10,000): ", 0, 10000);
    int n = inputValidatedInt("Input n (0 - 10,000): ", 0, 10000);

    int result = F(m, n);
    cout << "F(" << m << ", " << n << ") = " << result << endl;

    return 0;
}
