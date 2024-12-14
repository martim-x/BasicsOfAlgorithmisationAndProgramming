#include <iostream>
#include <vector>
using namespace std;


FILE* standart_stdcout = stdout;
FILE* standart_stdcint = stdin;

void task8_1() {
    freopen("input8_1.txt", "rt", stdin);

    int num;
    vector<int> nums;
    while (cin >> num) {
        nums.push_back(num);
    }

    fclose(stdin);
    stdin = standart_stdcint;

    freopen("input8_1.txt", "wt", stdout);
    int n = nums.size();
    for (int i = 0; i < (n + 1) / 2; i++) {
        cout << nums[i] << " ";
        if (i != n - 1 - i) {
            cout << nums[n - 1 - i] << " ";
        }
    }

    fclose(stdout);
    stdout = standart_stdcout;
}


void task8_2() {
    vector<vector<int>> matrixA;
    vector<int> matrixB;
    freopen("input8_2.txt", "rt", stdin);

}


int main() {
    ios::sync_with_stdio(false);
    task8_1();
    return 0;
}