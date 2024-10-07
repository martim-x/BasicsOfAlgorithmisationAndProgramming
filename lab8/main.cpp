#include <bits/stdc++.h>
using namespace std;


void task5() {
    vector<double> a = { 3, 12, -4 , 6, 2, 3, 0.4 }, b = { 19, 1, -24, 4.2, 8 };
    double d = 0, c = 0.7;
    for (auto elA : a) {
        for (auto elB : b) {
            d += elA - c * pow(elB - 1, 2);
        }
    }
    cout << "d: " << d << endl;



    double y = 0, z;
    vector<double> x = { 1, 6.7,4,6,17 };
    z = *min_element(x.begin(), x.end()) + 2;
    for (int i = 0; i < 5; i++) {
        y += pow(x[i], 2) + z;
    }
    cout << "y: " << y << endl;

}


void task6_1() {
    int n, num, sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num % 2 == 0) {
            sum += num;
            num = 0;
        }
    }
    cout << "Total amount: " << sum << endl;
}


void task6_2() {
    int n, num;
    vector<int> nums;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num < 0)
            nums.push_back(num);
    }
    cout << "last negative number: " << nums[nums.size() - 1] << endl;

}


void task6_3() {
    int n, indexMax, indexMin, max = INT_MIN, min = INT_MAX;
    double num;
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (max < num) {
            indexMax = n;
            max = num;
        }
        if (min > num) {
            indexMin = n;
            min = num;
        }
    }
    cout << "max: " << max << ", min: " << min << ", amount of nums: " << abs(indexMin - indexMax) << endl;
}


int main() {
    task5();
    task6_1();
    task6_2();
    task6_3();
    return 0;
}